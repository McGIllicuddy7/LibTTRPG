pub mod draw;
pub mod math;
pub mod letters;
pub use minifb::{Key, Window, WindowOptions};

use crate::draw::BLACK;
pub use crate::draw::{Color, Image, Shader, Vec2, Vec2r};
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
    fn kernel(&self,screen_location:Vec2, tex_coord:draw::Vec2r)->Color {
            self.tex.get(tex_coord.x as f64, tex_coord.y as f64)
    }
}
pub fn spinny(){
        let mut img = Image::new(1000, 1000);
        let mut window = Window::new(
            "Test - ESC to exit",
            img.width as usize,
            img.height as usize,
            WindowOptions::default(),
        )
        .unwrap_or_else(|e| {
            panic!("{}", e);
        });
        window.set_target_fps(60);
        let mut rt = 0.0;
        let mut timer = std::time::SystemTime::now();
        let sh = Shade::new("nyancat.png");
        while window.is_open() && !window.is_key_down(Key::Escape) {
               img.clear(Color {
                    r: 255,
                    g: 255,
                    b: 255, 
                    a: 255,
                });
                rt += 1.0/60.0;
                img.draw_rect_rot(320, 240, 120, 120,rt ,&sh);
                img.draw_text(100, 320, "howdy :3, THE QUICK BROWN FOX JUMPED OVER THE LAZY DOG\nthe quick brown fox jumped over the lazy dog", BLACK);
            img.draw(&mut window);
            let next =std::time::SystemTime::now(); 
            println!("{:#?}", next.duration_since(timer));
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
fn main() {
    spinny();
}
