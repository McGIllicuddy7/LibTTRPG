

use std::{collections::HashSet, f64::consts::TAU};

use raylib_rs::ffi::Color;

use crate::{utils::{Grid, NoiseRing}, voronoi::{Int2, Voronoi}};

pub enum GridType{
    Road, Building,Grass
}
impl GridType{
    pub fn color(&self)->Color{
        match self{
            GridType::Road => Color { r: 125, g: 125, b: 125, a: 255 },
            GridType::Building => Color { r: 0, g: 0, b: 0, a: 255 },
            GridType::Grass =>  Color { r: 125, g: 125, b: 125, a: 255 },
        }
    }
}
#[derive(Clone)]
pub struct Building{
    pub location:Int2,
    pub points:Vec<Int2>
}
pub struct City{
    pub grid:Grid<GridType>,
    pub buildings:Vec<Building>,
    pub internal_voronoi:Voronoi,
}
impl City{
    pub fn purge_building_set(buildings:&[Building], height:usize, width:usize)->HashSet<usize>{
        let center = Int2{x:(width/2) as i32, y:(height/2) as i32};
        let max_dist = (height*height/4) as i32;
        let mut out =HashSet::new();
        let min_dim = 11;
        let min_count = min_dim*min_dim;
        let noise = NoiseRing::new(TAU, 5);
        for i in 0..buildings.len(){
            let b = &buildings[i];
            let dist = b.location.dist_sqr(center);
            let mul = 0.5+(noise.sample(crate::utils::angle_from(b.location.x, b.location.y, center.x, center.y))*2.-1.)/2.;
            let dst = (max_dist as f64*(mul)) as i32;
            if b.points.len()>=min_count&& dist<dst{
                out.insert(i);
            }
        }
        out
    }
    pub fn new(height:usize, width:usize)->Self{
        let mut vor = Voronoi::new(height, width);
        vor.divide_jiggle(height*width/80000,1,8);
        for i in 0..4{
            vor.subdivide_jiggle(8-i, 1, (7+i) as i32);
            if i == 0 || i == 1 || i ==2{
                vor.shrink_divisions(1);
            } 
        }
        vor.shrink_divisions(2);
        let mut values = Vec::new();
        values.reserve_exact(height*width);
        (0..height*width).for_each(|_|{values.push(GridType::Grass);});
        let mut buildings = Vec::new();
        for i in vor.get_points(){
            buildings.push(Building{location:*i, points:Vec::new()});
        }
        for y in 0..vor.height(){
            for x in 0..vor.width(){
                let p = vor.get(x, y);
                if p == 0{
                    continue;
                } else{
                    buildings[p-1].points.push(Int2 { x:x as i32, y:y as i32 });
                }
            }
        }
        let idxes = Self::purge_building_set(&buildings, height, width);
        let mut grid = Grid::new(values, height, width);
        for y in 0..vor.height(){
            for x in 0..vor.width(){
                let v = if vor.get(x, y) == 0{GridType::Grass} else if idxes.contains(&(vor.get(x, y)-1)){ GridType::Building} else{GridType::Grass};
                grid.set(x, y, v);
            }
        }
        let mut new_buildings = Vec::new();
        for i in 0..buildings.len(){
            if idxes.contains(&i){
                new_buildings.push(buildings[i].clone());
            }
        }
        Self { grid, buildings: new_buildings, internal_voronoi:vor }
    }
    pub fn render_out(&self, name:&str){
        unsafe{
            //raylib_rs::ffi::InitWindow(100, 50,b"rendering image\0".as_ptr() as *const i8);
            let mut img = raylib_rs::ffi::GenImageColor(self.grid.width() as i32, self.grid.height() as i32, raylib_rs::ffi::Color{r:0, g:0, b:0, a:255});
            for y in 0..self.grid.height(){
                for x in 0..self.grid.width(){
                    let col = self.grid.get(x, y).color();
                    raylib_rs::ffi::ImageDrawPixel((&mut img) as *mut raylib_rs::ffi::Image,x as i32, y as i32, col);
                }
            }
            for i in 0..self.buildings.len(){
                let b = &self.buildings[i];
                let text = format!("{}\0",i);
               // raylib_rs::ffi::ImageDrawText((&mut img) as *mut raylib_rs::ffi::Image, text.as_ptr() as *const i8, b.location.x, b.location.y, 12, Color { r: 0, g:255, b: 0, a: 255});
            }
            let mut v = name.as_bytes().to_vec();
            v.push(0);
            raylib_rs::ffi::ExportImage(img, v.as_ptr() as *const i8);
            raylib_rs::ffi::UnloadImage(img);
            //raylib_rs::ffi::CloseWindow();
        }
    }
}