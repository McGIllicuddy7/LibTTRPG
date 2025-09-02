pub use crate::gui::{DrawCall, DrawCallType, GuiColor};
pub use crate::throw;
pub use crate::utils::{Except, Throws};
pub use raylib_rs::ffi::*;
impl Into<Color> for GuiColor {
    fn into(self) -> Color {
        Color {
            r: self.r,
            g: self.g,
            b: self.b,
            a: self.a,
        }
    }
}
pub fn calc_text_bounds(text: *const i8, w: i32, h: i32) -> Except<(i32, i32, i32)> {
    unsafe {
        let mut guess = h;
        let mut bounds = raylib_rs::ffi::MeasureText(text, guess);
        while bounds > w {
            guess -= 1;
            if guess == 0 {
                throw!("text cannot fit");
            }
            bounds = raylib_rs::ffi::MeasureText(text, guess);
        }
        let dx = (w - bounds) / 2;
        let dy = (h - guess) / 2;
        Ok((dx, dy, guess))
    }
}
pub unsafe fn draw_call(i: DrawCall) -> Throws {
    unsafe {
        if i.dct == DrawCallType::Rectangle {
            DrawRectangle(i.x, i.y, i.w, i.h, i.color.into());
        } else if i.dct == DrawCallType::Text {
            let s = i.text + "\0";
            let ptr = s.as_ptr() as *const i8;
            let bounds = calc_text_bounds(ptr, i.w, i.h)?;
            DrawText(
                ptr,
                i.x + bounds.0,
                i.y + bounds.1,
                bounds.2,
                i.color.into(),
            );
        } else if i.dct == DrawCallType::Image {
            todo!()
        } else if i.dct == DrawCallType::DrawMasked {
            BeginScissorMode(i.x, i.y, i.w, i.h);
        } else {
            todo!()
        }
    }
    Ok(())
}
pub unsafe fn render_gui(instructions: Vec<DrawCall>) {
    unsafe {
        for i in instructions {
            draw_call(i);
        }
    }
}
