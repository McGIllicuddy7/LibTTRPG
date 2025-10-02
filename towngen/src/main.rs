pub mod imaglib;
pub use minifb::{Key, Window, WindowOptions};

use imaglib::draw::{begin_rendering, window_should_continue, BLACK, WHITE};
pub use imaglib::draw::{Color, Image, Shader, Vec2, Vec2r};

use crate::imaglib::draw;
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
                img.draw_rect(100, 320, 500, 100, Color { b: 0, g: 0, r: 125, a: 255 });
                img.draw_text_box(100+2, 320+2,500-4,100-4,"howdy :3, THE QUICK BROWN FOX JUMPED OVER THE LAZY DOG\nthe quick brown fox jumped over the lazy dog lmao, also i love you", BLACK);
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
        let (mut img, mut window) = begin_rendering(1000, 1000);
        let mut timer = std::time::SystemTime::now();
        let mut prev = timer.duration_since(timer).unwrap();
        let txt = std::fs::read_to_string("src/draw.rs").unwrap();
        while window_should_continue(&window, true){
            let text = format!("fps:{:#?}\n{}",prev, txt);
            img.clear(BLACK);
           // img.draw_rect_rot(320, 240, 120, 120,rt ,&sh);
            img.draw_text_scaled(0, 0, 14,&text, WHITE);
            img.draw(&mut window);
            let next =std::time::SystemTime::now(); 
            prev = next.duration_since(timer).unwrap();   
            timer = next;
        }
}
fn main() {
    spinny();
}
