use std::collections::HashMap;

use rand::random_range;
use raylib_rs::ffi::{Color, UnloadImage};

use crate::utils::Grid;
#[derive(Clone, Copy)]
pub struct Int2 {
    pub x: i32,
    pub y: i32,
}
impl Int2 {
    pub fn dist_sqr(&self, other: Self) -> i32 {
        let x1 = self.x - other.x;
        let y1 = self.y - other.y;
        x1 * x1 + y1 * y1
    }
}
#[derive(Clone)]
pub struct Voronoi {
    pub values: Grid<usize>,
    pub points: Vec<Int2>,
}
impl Voronoi {
    pub fn new(height: usize, width: usize) -> Self {
        let mut values = Vec::with_capacity(height * width);
        for _ in 0..height {
            for _ in 0..width {
                values.push(0);
            }
        }
        Self {
            values: Grid::new(values, height, width),
            points: Vec::new(),
        }
    }
    pub fn get(&self, x: usize, y: usize) -> usize {
        return *self.values.get(x, y);
    }
    pub fn set(&mut self, x: usize, y: usize, value: usize) {
        self.values.set(x, y, value);
    }
    pub fn height(&self) -> usize {
        self.values.height()
    }
    pub fn width(&self) -> usize {
        return self.values.width();
    }
    pub fn generate_voronoi_points(
        &self,
        nc: usize,
        theta: f64,
        dx: i32,
        dy: i32,
        jiggle_mult: i32,
        jiggle_div: i32,
        w0: i32,
        h0: i32,
        min_x: i32,
        min_y: i32,
        max_x: i32,
        max_y: i32,
    ) -> Vec<Int2> {
        let mut new_points = Vec::new();
        for i in -(nc as i32 / 2 + 1)..nc as i32 / 2 + 2 {
            for j in -(nc as i32 / 2 + 1)..nc as i32 / 2 + 2 {
                let basx_x = theta.cos();
                let basx_y = theta.sin();
                let basy_x = basx_y;
                let basy_y = -basx_x;
                //assert!((basx_x * basy_x + basx_y * basy_y).abs() < 0.01);
                let delx = (dx * jiggle_mult) / jiggle_div;
                let dely = (dy * jiggle_mult) / jiggle_div;
                let jitter_x = random_range(-delx..delx + 1);
                let jitter_y = random_range(-dely..dely + 1);
                let p1 = Int2 {
                    x: i * dx,
                    y: j * dy,
                };
                let px = p1.x as f64 * basx_x + p1.y as f64 * basy_x;
                let py = p1.x as f64 * basx_y + p1.y as f64 * basy_y;
                let p = Int2 {
                    x: px as i32 + min_x + dx / 2 + jitter_x,
                    y: py as i32 + min_y + dy / 2 + jitter_y,
                };
                //p.x += self.width() as i32 / 2;
                //p.y += self.height() as i32 / 2;
                //println!("{},{}", p.x, p.y);
                if p.x < 0 || p.x > w0 || p.y < 0 || p.y > h0 {
                    continue;
                }
                new_points.push(p);
            }
        }
        new_points
    }
    pub fn divide_masked_jiggle(
        &mut self,
        count: usize,
        mask: usize,
        jiggle_mult: i32,
        jiggle_div: i32,
        theta0: &mut f64,
    ) {
        let w0 = self.width() as i32;
        let h0 = self.height() as i32;
        let mut min_x = 0;
        let mut min_y = 0;
        let mut max_x = w0;
        let mut max_y = h0;
        if mask != 0 {
            min_x = w0;
            min_y = h0;
            max_x = 0;
            max_y = 0;
            // let mut hit = false;
            for y in 0..(h0 as usize) {
                for x in 0..(w0 as usize) {
                    if self.get(x, y) != mask {
                        continue;
                    }
                    if x < min_x as usize {
                        min_x = x as i32;
                    }
                    if y < min_y as usize {
                        min_y = y as i32;
                    }
                    if x > max_x as usize {
                        max_x = x as i32;
                    }
                    if y > max_y as usize {
                        max_y = y as i32;
                    }
                }
            }
            if min_x >= max_x || min_y >= max_y {
                return;
            }
        }

        let nc = count.isqrt();
        if nc == 0 {
            return;
        }
        let mut dx = (max_x - min_x) / (nc as i32);
        if dx < 2 {
            dx = 2
        }
        let mut dy = (max_y - min_y) / (nc as i32);
        if dy < 2 {
            dy = 2;
        }
        let theta = *theta0 + (rand::random::<i64>() % 1000 - 500) as f64 / 5000.0 * 2. * 3.14;
        //*theta0 = theta;
        let base = self.points.len() + 1;
        let new_points = self.generate_voronoi_points(
            nc,
            theta,
            dx,
            dy,
            jiggle_mult,
            jiggle_div,
            w0,
            h0,
            min_x,
            min_y,
            max_x,
            max_y,
        );
        {
            let shader = |x: usize, y: usize, current: &usize| {
                if *current != mask {
                    return *current;
                }
                let x = x as i32;
                let y = y as i32;
                let mut min = h0 * w0;
                let mut min_idx = 0;
                for i in 0..new_points.len() {
                    let p = new_points[i];
                    let dx = p.x - x;
                    let dy = p.y - y;
                    let distance = dx * dx + dy * dy;
                    if distance >= min {
                        continue;
                    }
                    min = distance;
                    min_idx = i;
                }
                base + min_idx
            };
            self.values.shader_bound(
                &shader,
                min_x as usize,
                max_x as usize,
                min_y as usize,
                max_y as usize,
            );
        }
        self.points.reserve(new_points.len());
        for i in new_points {
            self.points.push(i);
        }
    }
    pub fn divide_masked(&mut self, count: usize, mask: usize, theta0: &mut f64) {
        self.divide_masked_jiggle(count, mask, 1, 8, theta0);
    }
    pub fn divide(&mut self, count: usize, theta0: &mut f64) {
        self.divide_masked(count, 0, theta0)
    }
    pub fn divide_jiggle(
        &mut self,
        count: usize,
        jiggle_mult: i32,
        jiggle_div: i32,
        theta0: &mut f64,
    ) {
        self.divide_masked_jiggle(count, 0, jiggle_mult, jiggle_div, theta0);
    }
    pub fn on_border(&self, x: usize, y: usize) -> bool {
        let v = self.get(x, y);
        let x = x as i32;
        let y = y as i32;
        for dy in -1..2 {
            for dx in -1..2 {
                if x + dx < 0
                    || x + dx >= self.width() as i32
                    || y + dy < 0
                    || y + dy >= self.height() as i32
                {
                    continue;
                }
                let px = (x + dx) as usize;
                let py = (y + dy) as usize;
                if self.get(px, py) != v {
                    return true;
                }
            }
        }
        false
    }
    pub fn on_border_nonzero(&self, x: usize, y: usize) -> bool {
        let v = self.get(x, y);
        let x = x as i32;
        let y = y as i32;
        for dy in -1..2 {
            for dx in -1..2 {
                if x + dx < 0
                    || x + dx >= self.width() as i32
                    || y + dy < 0
                    || y + dy >= self.height() as i32
                {
                    continue;
                }
                let px = (x + dx) as usize;
                let py = (y + dy) as usize;
                if self.get(px, py) != v && v != 0 {
                    return true;
                }
            }
        }
        false
    }
    pub fn shrink_divisions(&mut self, loop_count: usize) {
        let mut count = loop_count;
        while count > 0 {
            let mut out = self.clone();
            for y in 0..self.height() {
                for x in 0..self.width() {
                    if self.on_border_nonzero(x, y) {
                        out.set(x, y, 0);
                    }
                }
            }
            *self = out;
            count -= 1;
        }
    }
    pub fn render_out(&self, name: &str) {
        unsafe {
            let mut img = raylib_rs::ffi::GenImageColor(
                self.width() as i32,
                self.height() as i32,
                raylib_rs::ffi::Color {
                    r: 0,
                    g: 0,
                    b: 0,
                    a: 255,
                },
            );
            let mut colors: HashMap<usize, Color> = HashMap::new();
            colors.insert(
                0,
                Color {
                    r: 0,
                    g: 0,
                    b: 0,
                    a: 255,
                },
            );
            for i in 0..self.points.len() {
                let col = Color {
                    r: random_range(0..255) as u8,
                    g: random_range(0..255) as u8,
                    b: random_range(0..255) as u8,
                    a: 255,
                };
                colors.insert(i + 1, col);
            }
            for y in 0..self.height() {
                for x in 0..self.width() {
                    let col = colors[&self.get(x, y)];
                    raylib_rs::ffi::ImageDrawPixel(
                        (&mut img) as *mut raylib_rs::ffi::Image,
                        x as i32,
                        y as i32,
                        col,
                    );
                }
            }
            let mut v = name.as_bytes().to_vec();
            v.push(0);
            raylib_rs::ffi::ExportImage(img, v.as_ptr() as *const i8);
            UnloadImage(img);
        }
    }
    pub fn subdivide(&mut self, subdivision_count: usize, theta0: &mut f64) {
        let count = self.points.len();
        for i in 0..count {
            self.divide_masked(subdivision_count, i + 1, theta0);
        }
    }
    pub fn subdivide_jiggle(
        &mut self,
        subdivision_count: usize,
        jiggle_mult: i32,
        jiggle_div: i32,
        theta0: &mut f64,
    ) {
        let count = self.points.len();
        let p = self.pop_count();
        for i in 0..count {
            let t = p[i + 1].isqrt() * subdivision_count / (120);
            if t == 0 {
                continue;
            }
            self.divide_masked_jiggle(t, i + 1, jiggle_mult, jiggle_div, theta0);
        }
    }
    pub fn break_up(&mut self, thresh: usize, theta0: &mut f64) {
        let p = self.pop_count();
        let count = self.points.len();
        for i in 0..count {
            if p[i + 1] > thresh {
                self.divide_masked_jiggle(4, i + 1, 0, 4, theta0);
            }
        }
    }
    pub fn get_points(&self) -> &[Int2] {
        &self.points
    }
    pub fn pop_count(&self) -> Vec<usize> {
        let mut out = Vec::new();
        out.push(0);
        for _ in 0..self.points.len() {
            out.push(0);
        }
        for i in 0..self.height() {
            for j in 0..self.width() {
                out[*self.values.get(i, j)] += 1;
            }
        }
        out
    }
}
