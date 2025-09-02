pub mod state;
pub use raylib_rs::ffi::*;
pub mod guitls;
pub fn main() {
    unsafe {
        SetTraceLogLevel(TraceLogLevel_LOG_ERROR as i32);
        InitWindow(
            GetScreenWidth(),
            GetScreenHeight(),
            c"hello window".as_ptr(),
        );
    };

    while !unsafe { WindowShouldClose() } {
        unsafe {
            BeginDrawing();
            ClearBackground(Color {
                r: 32,
                g: 32,
                b: 32,
                a: 255,
            });
            EndDrawing();
        }
    }
}
