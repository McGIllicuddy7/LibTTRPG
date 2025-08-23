pub mod gui;
pub mod gui_render;
pub mod state;
#[macro_use]
pub mod utils;
pub use crate::utils::{Error, Except, Throws};
pub use raylib_rs::ffi::*;
pub fn gui_update(gui: &mut gui::GUIStruct, mouse_x: i32, mouse_y: i32, mouse: bool) -> Throws {
    gui.begin(mouse_x, mouse_y, mouse);
    gui.create_frame(0, 0, 400, 1000);
    gui.rectangle(100)?;
    gui.text("hi toast i love you", 40)?;
    if gui.button("exit app", 40, "test button")? {
        std::process::exit(0);
    }
    gui.end_widget();
    gui.end();
    Ok(())
}
pub fn main() -> Throws {
    unsafe {
        SetTraceLogLevel(TraceLogLevel_LOG_ERROR as i32);
        InitWindow(1000, 1000, c"hello window".as_ptr());
    };
    let mut gui = gui::GUIStruct::new(1000, 1000);
    while !unsafe { WindowShouldClose() } {
        unsafe {
            gui_update(
                &mut gui,
                GetMouseX(),
                GetMouseY(),
                IsMouseButtonDown(MouseButton_MOUSE_BUTTON_LEFT as i32),
            )?;
            BeginDrawing();
            ClearBackground(Color {
                r: 32,
                g: 32,
                b: 32,
                a: 255,
            });
            gui_render::render_gui(gui.take_draw_calls());
            EndDrawing();
        }
    }
    Ok(())
}
