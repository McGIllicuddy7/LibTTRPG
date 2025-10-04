pub mod imaglib;
pub use minifb::{Key, Window, WindowOptions};
pub mod map;
use imaglib::draw::{begin_rendering, window_should_continue};
pub use imaglib::draw::{Color, Image, Shader, Vec2, Vec2r};

use crate::imaglib::draw::{self, rand, srand_time};
use crate::imaglib::draw::colors::*;
use crate::map::{City, VecField};
struct Shade{
    tex:Image
}
impl Shade{
    pub fn new(tex:&str)->Self{
        let tex = Image::load(tex).unwrap();
        Self{tex}
    }
}
impl Shader for Shade{
    fn kernel(&self,_screen_location:Vec2, tex_coord:draw::Vec2r)->Color {
            self.tex.get(tex_coord.x as f64, tex_coord.y as f64)
    }
}
pub fn spinny(){
        let (mut img, mut window) = begin_rendering(1000, 1000);
        let mut rt = 0.0;
        let mut timer = std::time::SystemTime::now();
        let sh = Shade::new("nyancat.png");
        while window_should_continue(&window, true){
               img.clear(WHITE);
                rt += 1.0/60.0;
                img.draw_rect_rot(320, 240, 120, 120,rt ,&sh);
                img.draw_rect(100, 320, 500, 100, RED);
                img.draw_text_box(100+5, 320+5,500-10,100-10,"howdy :3, THE QUICK BROWN FOX JUMPED OVER THE LAZY DOG\nthe quick brown fox jumped over the lazy dog lmao, also i love you", PINK);
            img.draw(&mut window);
            let next =std::time::SystemTime::now(); 
          // println!("{:#?}", next.duration_since(timer).unwrap());
            timer = next;
        }
}
pub fn old(){
    let mut img = Image::new(1000, 1000);
    img.clear(Color {
        r: 255,
        g: 255,
        b: 255,
        a: 255,
    });
    let sh = Shade::new("nyancat.png");
    img.draw_rect_rot(500,500, 400,400,0.0, &sh);
    img.export("test.ppm");
    img.draw_forever();
}
pub fn printr(){
        let (mut img, mut window) = begin_rendering(1100, 1100);
        let mut timer = std::time::SystemTime::now();
        let mut prev = timer.duration_since(timer).unwrap();
        let txt = std::fs::read_to_string("src/main.rs").unwrap();
        while window_should_continue(&window, true){
            let text = format!("fps:{:#?}\n{}",prev, txt);
            img.clear(BLACK);
           // img.draw_rect_rot(320, 240, 120, 120,rt ,&sh);
            img.draw_text_scaled(0, 0, 14,&text, DARK_TEAL);
            img.draw(&mut window);
            let next =std::time::SystemTime::now(); 
            prev = next.duration_since(timer).unwrap();   
            timer = next;
        }
}
pub fn rands(){
    let mut counts = [0;10];
    srand_time();
    for _ in 0..100{
        let v = rand()%10;
        println!("{v}");
        counts[v as usize]+=1;
    } 
    for i in 0..counts.len(){
        print!("{i}:{},", counts[i]);
    }
}
pub fn map(){
    srand_time();
    let w = 1000;
    let h = 1000;
    let mut img = Image::new(w, h);
    img.clear(WHITE);
    let mut msh= City::new(w as i32,h as i32,30);
    msh.build();
   // msh.draw(&mut img,BLACK, false);
    //img.draw_forever();
}
pub fn map_draw(){
    srand_time();
    let w = 1000;
    let h = 1000;
    let (mut img, mut window) = begin_rendering(w,h);
    img.clear(WHITE);
    let mut msh= City::new(w as i32,h as i32,45);
    msh.build();
    let mut should_draw = false;
    let mut timer = std::time::SystemTime::now();
    let mut prev = timer.duration_since(timer).unwrap();
    while window_should_continue(&window, true){
        window.update();
        if window.is_key_pressed(Key::Space, minifb::KeyRepeat::No){
            should_draw = !should_draw;
        }
        let text = format!("fps:{:#?}",prev);
        img.clear(WHITE);
        msh.draw(&mut img,BLACK,should_draw);
        img.draw_text_scaled(0, 0, 14,&text, RED);
        img.draw(&mut window);
        let next =std::time::SystemTime::now(); 
        prev = next.duration_since(timer).unwrap();   
        timer = next;
    }
    img.export("test.ppm");
}
fn main() {
    map_draw();
}
