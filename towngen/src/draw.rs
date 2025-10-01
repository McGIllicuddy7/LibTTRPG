use std::error::Error;
pub use crate::letters::*;
use minifb::{Key, Window, WindowOptions};
pub use crate::math::*;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct Color {
    pub b: u8,
    pub g: u8,
    pub r: u8,
    pub a: u8,
}
pub const BLACK:Color = Color{r:0, g:0, b:0, a:255};
pub const WHITE:Color = Color{r:220, g:220, b:220, a:255};
#[derive(Clone)]
pub struct Image {
    pub height: usize,
    pub width: usize,
    pub data: Box<[Color]>,
}
impl Image {
    pub fn new(width: usize, height:usize) -> Self {
        let mut vs = Vec::new();
        vs.reserve_exact(height * width);
        for _ in 0..height * width {
            vs.push(Color {
                r: 0,
                g: 0,
                b: 0,
                a: 255,
            });
        }
        Image {
            height,
            width,
            data: vs.into(),
        }
    }
    pub fn draw_pixel(&mut self, x: usize, y: usize, color: Color) {
        if x>=self.width || y>=self.height{
            return;
        }
        let c = &mut self.data[y * self.width + x];
        *c = color;
    }
    pub fn get_pixel(&self, mut x: usize, mut y: usize) -> Color {
        if x>=self.width {
            x = self.width-1;
        }
        if y>=self.height{
            y = self.height-1;
        }
        self.data[y * self.width + x]
    }
    pub fn get(&self, x:f64, y:f64)->Color{
        let mut x0 = (x*self.width as f64) as usize;
        let mut y0 = (y*self.height as f64) as usize;
        if x0>=self.width {
            x0 = self.width-1;
        }
        if y0>=self.height{
            y0 = self.height-1;
        }
        self.data[y0*self.width+x0]
    }

    pub fn clear(&mut self, color: Color) {
        self.data.fill(color);
    }
    pub fn export(&self, to: &str) {
        let mut out = String::from("P3\n");
        out += &format!("{} {}\n", self.width, self.height);
        out += "255\n";
        for i in &self.data {
            out += &format!("{} {} {}\n", i.r, i.g, i.b);
        }
        std::fs::write(to, out).unwrap();
    }
    pub fn draw(&self,window:&mut Window){
                let buffptr = self.data.as_ptr()as *mut u32;
                let buffer = unsafe{
                std::slice::from_raw_parts_mut(buffptr, self.height*self.width)
                };
                window
                .update_with_buffer(&buffer, self.width, self.height)
                .unwrap();
    }
    pub fn draw_forever(&self) {
        let mut window = Window::new(
            "Test - ESC to exit",
        self.width as usize,
            self.height as usize,
            WindowOptions::default(),
        )
        .unwrap_or_else(|e| {
            panic!("{}", e);
        });
        window.set_target_fps(60);
        let buffptr = self.data.as_ptr()as *mut u32;
        let buffer = unsafe{
            std::slice::from_raw_parts_mut(buffptr, self.height*self.width)
        };
        while window.is_open() && !window.is_key_down(Key::Escape) {
            window
                .update_with_buffer(&buffer, self.width, self.height)
                .unwrap();
        }
    }
    pub fn draw_triangle(&mut self, p1: Vec2, p2: Vec2, p3: Vec2, color: Color) {
        let bx = BB::from_points(&[p1, p2, p3]);
        //for y in bx.y..bx.y + bx.h + 1 {
        //   for x in bx.x..bx.x + bx.w + 1 {
        for y in bx.y..bx.y+bx.h {
            for x in bx.x..bx.x+bx.w {
                let v = Vec2 { x, y };
                if in_triangle(p1, p2, p3, v) {
                    self.draw_pixel(v.x as usize, v.y as usize, color);
                }
            }
        }
    }
    pub fn calc_uvs_lin(p1:Vec2, p2:Vec2, p3:Vec2, uv1:Vec2r, uv2:Vec2r, uv3:Vec2r, pos:Vec2)->Vec2r{ 
        let denum = triangle_area(p1, p2, p3) as f32;
        let t1 = triangle_area(pos, p2, p3) as f32/denum;
        let t2 = triangle_area(pos, p3, p1) as f32/denum;
        let t3 = triangle_area(pos, p2, p1) as f32/denum;
      // println!("{t1}, {t2},{t3},{denum}, {}", t1+t2+t3);
        uv1*t1+uv2*t2+uv3*t3
    }  
    pub fn draw_triangle_shader<Shade:Shader>(&mut self, p1: Vec2, p2: Vec2, p3: Vec2, uv1:Vec2r,uv2:Vec2r, uv3:Vec2r,shader:&Shade) {
        let bx = BB::from_points(&[p1, p2, p3]);
        for y in bx.y..bx.y+bx.h {
            for x in bx.x..bx.x+bx.w {
                let v = Vec2 { x, y };
                if in_triangle(p1, p2, p3, v) {
                    let color = shader.kernel(v, Self::calc_uvs_lin(p1, p2, p3, uv1, uv2, uv3, v));
                    self.draw_pixel(v.x as usize, v.y as usize, color);
                }
            }
        }
    }
    pub fn draw_rect(&mut self, x:i32, y:i32, w:i32, h:i32,color:Color){
        for yp in y..y+h{
            for xp in x..x+w{
                self.draw_pixel(xp as usize, yp as usize, color);
            }
        }
    }
    pub fn draw_bitmap(&mut self, x:i32, y:i32, bmp:&Bitmap, color:Color){
        let x0 = x as usize;
        let y0 = y as usize;
        for yp in 0..bmp.height{
            for xp in 0..bmp.width{
                if bmp.get(xp, yp){
                    self.draw_pixel(xp+x0, yp+y0, color);
                }
            }
        }
    }
    pub fn draw_rect_shader<Shade:Shader>(&mut self, x:i32, y:i32, w:i32, h:i32, shader:&Shade){
        for yp in y..y+h{
            for xp in x..x+w{
                let color = shader.kernel(Vec2::new(xp, yp), Vec2r::new((xp-x) as f32/(w as f32), (yp-y) as f32/(h as f32)));
                self.draw_pixel(xp as usize, yp as usize, color);
            }
        }
    }
    pub fn draw_rect_rot<Shade:Shader>(&mut self, x:i32, y:i32, w:i32, h:i32, rot:f64,shader:&Shade){
        let dx = Vec2r::new(w as f32/2.0, h as f32/2.0);
        let dy = Vec2r::new(w as f32/2.0, -h  as f32/2.0);
        let rotr = Mat2::rotmat(rot);
        let xp = (rotr*dx).to_int();
        let yp = (rotr*dy).to_int();
        let c = Vec2::new(x,y);
        let p1 = c+xp;
        let p2 = c-yp;
        let p3 = c+yp;
        let p4 = c-xp;
        let u1 = Vec2r::new(0.0, 0.0);
        let u2 = Vec2r::new(1.0, 0.0);
        let u3 = Vec2r::new(0.0, 1.0);
        let u4 = Vec2r::new(1.0, 1.0);
        self.draw_triangle_shader(p1, p2, p3, u1, u2, u3, shader);
        self.draw_triangle_shader(p4, p2, p3, u4, u2, u3, shader);
    }
    pub fn load(name:&str)->Result<Self, Box<dyn Error>>{
        let img = load_image::load_path(name)?;
        let h = img.height;
        let w = img.width;
        let (ig ,_)= img.into_rgba();
        let mut out = Self::new(h,w);
        for yp in 0..h{
            for x in 0..w{
                let y = h-yp-1;
                let ct = ig[yp][x];
                let col = Color{r:ct.r, g:ct.g, b:ct.b, a:ct.a};
                out.draw_pixel(x, y, col);
            }
        }
        Ok(out)
    }
    pub fn draw_char(&mut self,x:i32, y:i32, c:char, color:Color){
        let bmp = char_to_bmp(c);
        self.draw_bitmap(x, y, bmp, color);
    }
    pub fn draw_text(&mut self, x:i32, y:i32, text:&str, color:Color){
        let mut cx = x;
        let mut cy = y;
        for i in text.chars(){
            if i == '\n'{
                cy += TEXT_SPACE;
                cx = x;
            }else if i == '\t'{
                cx += (TEXT_SPACE)*3;
            }else{
                self.draw_char(cx, cy, i, color);
                cx += TEXT_SPACE;

            }
        }
    }
}

pub trait Shader{
    fn kernel(&self,screen_location:Vec2, text_coord:Vec2r)->Color;
}

#[derive(Clone)]
pub struct Bitmap{
    pub width:usize,
    pub height:usize,
    pub data:&'static [u8],
}
impl Bitmap{
    pub const fn from_data<const W:usize, const H:usize>(inp:&'static [[u8;W];H])->Self{
        let data = unsafe{std::slice::from_raw_parts(inp.as_ptr() as * const u8, W*H)};
        Self { width: W, height: H, data}
    }
    pub const fn get(&self,x:usize, y:usize)->bool{
        if x>=self.width || y>= self.height{
            return false;
        }
        self.data[y*self.width+x] != 0
    }
    pub const fn getf(&self, x:f32, y:f32)->bool{
        self.get((x*self.width as f32) as usize, (y*self.width as f32) as usize)
    }
}