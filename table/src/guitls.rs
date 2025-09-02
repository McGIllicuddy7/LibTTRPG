pub use raylib_rs::ffi::*;
pub fn calc_text_bounds(text: *const i8, w: i32, h: i32) -> (i32, i32, i32) {
    unsafe {
        let mut guess = h;
        let mut bounds = raylib_rs::ffi::MeasureText(text, guess);
        while bounds > w {
            guess -= 1;
            if guess == 0 {
                return (0, 0, 0);
            }
            bounds = raylib_rs::ffi::MeasureText(text, guess);
        }
        let dx = (w - bounds) / 2;
        let dy = (h - guess) / 2;
        (dx, dy, guess)
    }
}
pub unsafe fn draw_text_bounded(text: &str, rect: raylib_rs::ffi::Rectangle, color: Color) {
    unsafe {
        let s = text.to_string() + "\0";
        let ptr = s.as_ptr() as *const i8;
        let bounds = calc_text_bounds(ptr, rect.width as i32, rect.height as i32);
        DrawText(
            ptr,
            rect.x as i32 + bounds.0,
            rect.y as i32 + bounds.1,
            bounds.2,
            color,
        );
    }
}
