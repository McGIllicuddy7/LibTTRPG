pub use crate::throw;
pub use crate::utils::{Error, Except, Throws};
pub use std::collections::HashMap;
pub use std::sync::Mutex;

#[derive(Copy, Clone, Debug)]
#[repr(C)]
pub struct GuiColor {
    pub r: u8,
    pub g: u8,
    pub b: u8,
    pub a: u8,
}
#[derive(Copy, Clone, Debug, PartialEq)]
#[repr(C)]
pub enum DrawCallType {
    DrawNone,
    Rectangle,
    RectangleOutline,
    Text,
    Image,
    DrawMasked,
    DrawMaskedEnd,
}
#[derive(Copy, Clone, Debug)]
#[repr(C)]
pub struct Frame {
    pub x: i32,
    pub y: i32,
    pub h: i32,
    pub w: i32,
    pub sp: i32,
    pub pushed: bool,
    pub masked: bool,
}
//need to be translated to screen coordinates
#[derive(Clone, Debug)]
#[repr(C)]
pub struct DrawCall {
    pub dct: DrawCallType,
    pub rounded: f32,
    pub text: String,
    pub img_name: String,
    pub color: GuiColor,
    pub x: i32,
    pub y: i32,
    pub h: i32,
    pub w: i32,
}
impl Default for DrawCall {
    fn default() -> Self {
        Self::new()
    }
}
impl DrawCall {
    pub fn new() -> Self {
        Self {
            dct: DrawCallType::DrawNone,
            rounded: 0.0,
            text: String::new(),
            img_name: String::new(),
            color: GuiColor {
                r: 0,
                g: 0,
                b: 0,
                a: 0,
            },
            x: 0,
            y: 0,
            h: 0,
            w: 0,
        }
    }
}
#[derive(Clone, Copy, Debug)]
#[repr(C)]
pub struct Theme {
    pub foreground: GuiColor,
    pub background: GuiColor,
    pub text: GuiColor,
    pub title_text: GuiColor,
    pub rounded: f32,
}
impl Theme {
    pub fn new() -> Self {
        Self {
            foreground: GuiColor {
                r: 125,
                g: 125,
                b: 125,
                a: 255,
            },
            background: GuiColor {
                r: 0,
                g: 0,
                b: 0,
                a: 255,
            },
            text: GuiColor {
                r: 255,
                g: 255,
                b: 255,
                a: 255,
            },
            title_text: GuiColor {
                r: 255,
                g: 255,
                b: 255,
                a: 255,
            },
            rounded: 0.0,
        }
    }
}
#[derive(Clone, Copy, Debug)]
pub struct ScrollBoxInfo {
    pub h: i32,
    pub touched: bool,
}
#[derive(Clone, Copy, Debug)]
pub struct Bounds {
    pub x: i32,
    pub y: i32,
    pub w: i32,
    pub h: i32,
}
#[derive(Clone, Debug)]
#[repr(C)]
pub struct GUIStruct {
    pub height: i32,
    pub width: i32,
    pub scroll_boxes: HashMap<String, ScrollBoxInfo>,
    pub frames: Vec<Frame>,
    pub selected_widget: Option<String>,
    pub prev_selected_widget: Option<String>,
    pub mouse_x: i32,
    pub mouse_y: i32,
    pub old_mouse_x: i32,
    pub old_mouse_y: i32,
    pub mouse_button: bool,
    pub mouse_button_prev: bool,
    pub scroll_offsets: Vec<i32>,
    pub draw_calls: Vec<DrawCall>,
    pub theme: Theme,
}
impl Default for GUIStruct {
    fn default() -> Self {
        Self::new(1920, 1080)
    }
}
impl GUIStruct {
    pub fn new(width: i32, height: i32) -> Self {
        GUIStruct {
            height,
            width,
            scroll_boxes: HashMap::new(),
            frames: vec![],
            selected_widget: None,
            prev_selected_widget: None,
            mouse_x: 0,
            mouse_y: 0,
            old_mouse_x: 0,
            old_mouse_y: 0,
            mouse_button: false,
            mouse_button_prev: false,
            scroll_offsets: Vec::new(),
            draw_calls: Vec::new(),
            theme: Theme::new(),
        }
    }
    pub fn push_bb(&mut self, height: i32) -> Except<Bounds> {
        let bounds = self.get_remaining_bounds();
        let act_h = if height > bounds.h { bounds.h } else { height };
        let b = Bounds {
            x: bounds.x,
            y: bounds.y,
            w: bounds.w,
            h: act_h,
        };
        if b.h <= 0 {
            throw!("error not enough space");
        }
        self.prev_frame_push(act_h);
        Ok(b)
    }
    pub fn create_bb(&mut self, x: i32, y: i32, w: i32, h: i32) -> Except<Bounds> {
        if let Some(prev) = self.frames.last() {
            Ok(Bounds {
                x: x + prev.x,
                y: y + prev.y,
                w,
                h,
            })
        } else {
            Ok(Bounds { x, y, w, h })
        }
    }
    pub fn is_mouse_over(&self, b: Bounds) -> bool {
        (self.mouse_x >= b.x && self.mouse_x < b.x + b.w)
            && (self.mouse_y >= b.y && self.mouse_y < b.y + b.h)
    }
    pub fn should_be_active(&self, b: Bounds) -> bool {
        self.is_mouse_over(b) && self.mouse_button
    }
    pub fn was_selected(&self, name: &str) -> bool {
        if let Some(prev) = self.prev_selected_widget.as_ref() {
            prev == name
        } else {
            false
        }
    }
    pub fn prev_frame_push(&mut self, dim: i32) {
        let p = self.frames.last_mut();
        if let Some(f) = p {
            f.sp += dim;
        }
    }
    pub fn get_remaining_bounds(&self) -> Bounds {
        if let Some(f) = self.frames.last() {
            Bounds {
                x: f.x,
                y: f.y + f.sp,
                w: f.w,
                h: f.h - f.sp,
            }
        } else {
            Bounds {
                x: 0,
                y: 0,
                w: self.width,
                h: self.height,
            }
        }
    }
    pub fn begin(&mut self, mouse_x: i32, mouse_y: i32, mouse_button_down: bool) {
        self.mouse_x = mouse_x;
        self.mouse_y = mouse_y;
        self.mouse_button = mouse_button_down;
        self.selected_widget = None;
        self.draw_calls = Vec::new();
    }
    pub fn end(&mut self) {
        self.old_mouse_x = self.mouse_x;
        self.old_mouse_y = self.mouse_y;
        self.mouse_button_prev = self.mouse_button;
        self.prev_selected_widget = self.selected_widget.clone();
        self.selected_widget = None;
    }
    pub fn take_draw_calls(&mut self) -> Vec<DrawCall> {
        let out = self.draw_calls.clone();
        self.draw_calls.clear();
        out
    }
    pub fn begin_frame(&mut self, height: i32) {
        let bounds = self.get_remaining_bounds();
        let act_h = if height > bounds.h { bounds.h } else { height };
        let f: Frame = Frame {
            x: bounds.x,
            y: bounds.y,
            w: bounds.w,
            h: act_h,
            sp: 0,
            pushed: true,
            masked: false,
        };
        self.prev_frame_push(act_h);
        self.frames.push(f);
    }
    pub fn create_frame(&mut self, x: i32, y: i32, width: i32, height: i32) {
        let bounds = if let Some(p) = self.frames.last() {
            Bounds {
                x: p.x,
                y: p.y,
                w: p.w,
                h: p.h,
            }
        } else {
            Bounds {
                x,
                y,
                w: width,
                h: height,
            }
        };
        let act_h = if height > bounds.h { bounds.h } else { height };
        let f: Frame = Frame {
            x: bounds.x,
            y: bounds.y,
            w: bounds.w,
            h: act_h,
            sp: 0,
            pushed: true,
            masked: false,
        };
        self.prev_frame_push(act_h);
        self.frames.push(f);
    }
    pub fn end_widget(&mut self) {
        if let Some(f) = self.frames.pop() {
            if f.masked {
                let mut dc = DrawCall::new();
                dc.dct = DrawCallType::DrawMaskedEnd;
                self.draw_calls.push(dc);
            }
        }
    }
    pub fn button(&mut self, text: &str, height: i32, name: &str) -> Except<bool> {
        let b = self.push_bb(height)?;
        let draw_box: DrawCall = DrawCall {
            dct: DrawCallType::Rectangle,
            x: b.x,
            y: b.y,
            w: b.w,
            h: b.h,
            rounded: self.theme.rounded,
            img_name: String::new(),
            text: String::new(),
            color: self.theme.foreground,
        };
        let draw_text: DrawCall = DrawCall {
            dct: DrawCallType::Text,
            x: b.x,
            y: b.y,
            w: b.w,
            h: b.h,
            rounded: self.theme.rounded,
            img_name: String::new(),
            color: self.theme.text,
            text: text.into(),
        };
        self.draw_calls.push(draw_box);
        self.draw_calls.push(draw_text);
        if self.should_be_active(b) {
            self.selected_widget = Some(name.to_string());
            return Ok(false);
        } else if self.is_mouse_over(b) && self.was_selected(name) {
            return Ok(true);
        }
        Ok(false)
    }
    pub fn create_button(
        &mut self,
        text: &str,
        x: i32,
        y: i32,
        w: i32,
        h: i32,
        name: &str,
    ) -> Except<bool> {
        let b = self.create_bb(x, y, w, h)?;
        let draw_box: DrawCall = DrawCall {
            dct: DrawCallType::Rectangle,
            x: b.x,
            y: b.y,
            w: b.w,
            h: b.h,
            rounded: self.theme.rounded,
            img_name: String::new(),
            text: String::new(),
            color: self.theme.foreground,
        };
        let draw_text: DrawCall = DrawCall {
            dct: DrawCallType::Text,
            x: b.x,
            y: b.y,
            w: b.w,
            h: b.h,
            rounded: self.theme.rounded,
            img_name: String::new(),
            text: text.into(),
            color: self.theme.text,
        };
        self.draw_calls.push(draw_box);
        self.draw_calls.push(draw_text);
        if self.should_be_active(b) {
            self.selected_widget = Some(name.to_string());
            return Ok(false);
        } else if self.is_mouse_over(b) && self.was_selected(name) {
            return Ok(true);
        }
        Ok(false)
    }
    pub fn text(&mut self, text: &str, height: i32) -> Throws {
        let b = self.push_bb(height)?;
        let draw_box: DrawCall = DrawCall {
            dct: DrawCallType::Rectangle,
            x: b.x,
            y: b.y,
            w: b.w,
            h: b.h,
            rounded: self.theme.rounded,
            img_name: String::new(),
            text: String::new(),
            color: self.theme.background,
        };
        let draw_text: DrawCall = DrawCall {
            dct: DrawCallType::Text,
            x: b.x,
            y: b.y,
            w: b.w,
            h: b.h,
            rounded: self.theme.rounded,
            img_name: String::new(),
            color: self.theme.text,
            text: text.into(),
        };
        self.draw_calls.push(draw_box);
        self.draw_calls.push(draw_text);
        Ok(())
    }
    pub fn create_text(&mut self, text: &str, x: i32, y: i32, w: i32, h: i32) -> Throws {
        let b = self.create_bb(x, y, w, h)?;
        let draw_box: DrawCall = DrawCall {
            dct: DrawCallType::Rectangle,
            x: b.x,
            y: b.y,
            w: b.w,
            h: b.h,
            rounded: self.theme.rounded,
            img_name: String::new(),
            text: String::new(),
            color: self.theme.foreground,
        };
        let draw_text: DrawCall = DrawCall {
            dct: DrawCallType::Text,
            x: b.x,
            y: b.y,
            w: b.w,
            h: b.h,
            rounded: self.theme.rounded,
            img_name: String::new(),
            text: text.into(),
            color: self.theme.text,
        };
        self.draw_calls.push(draw_box);
        self.draw_calls.push(draw_text);
        Ok(())
    }
    pub fn rectangle(&mut self, height: i32) -> Throws {
        let b = self.push_bb(height)?;
        let draw_box: DrawCall = DrawCall {
            dct: DrawCallType::Rectangle,
            x: b.x,
            y: b.y,
            w: b.w,
            h: b.h,
            rounded: self.theme.rounded,
            img_name: String::new(),
            text: String::new(),
            color: self.theme.background,
        };
        self.draw_calls.push(draw_box);
        Ok(())
    }
    pub fn create_rectangle(&mut self, x: i32, y: i32, w: i32, h: i32) -> Throws {
        let b = self.create_bb(x, y, w, h)?;
        let draw_box: DrawCall = DrawCall {
            dct: DrawCallType::Rectangle,
            x: b.x,
            y: b.y,
            w: b.w,
            h: b.h,
            rounded: self.theme.rounded,
            img_name: String::new(),
            text: String::new(),
            color: self.theme.foreground,
        };
        self.draw_calls.push(draw_box);
        Ok(())
    }
    pub fn scrollbox(&mut self, height: i32, name: &str, size: i32) -> Throws {
        let b = self.push_bb(height)?;
        let mut sb = b;
        sb.w = 5;
        sb.x = sb.x + sb.w - 5;
        let dc = DrawCall {
            dct: DrawCallType::RectangleOutline,
            x: b.x + 1,
            y: b.y + 1,
            w: b.w - 2,
            h: b.h - 2,
            rounded: self.theme.rounded,
            img_name: String::new(),
            text: String::new(),
            color: self.theme.foreground,
        };
        self.draw_calls.push(dc);
        let dc = DrawCall {
            dct: DrawCallType::RectangleOutline,
            x: sb.x + 1,
            y: sb.y + 1,
            w: sb.w - 2,
            h: sb.h - 2,
            rounded: self.theme.rounded,
            img_name: String::new(),
            text: String::new(),
            color: self.theme.foreground,
        };
        self.draw_calls.push(dc);
        sb.h = 10;
        sb.y = sb.y + sb.h - 10;
        let dc = DrawCall {
            dct: DrawCallType::RectangleOutline,
            x: sb.x + 1,
            y: sb.y + 1,
            w: sb.w - 2,
            h: sb.h - 2,
            rounded: self.theme.rounded,
            img_name: String::new(),
            text: String::new(),
            color: self.theme.foreground,
        };
        self.draw_calls.push(dc);
        let mut bs = b;
        let mut hoff = 0;

        if self.should_be_active(sb) {
            if let Some(p) = self.prev_selected_widget.as_ref() {
                if p == name {
                    todo!();
                }
            }
            self.selected_widget = Some(name.to_owned());
        }

        bs.w -= 6;
        if let Some(n) = self.scroll_boxes.get_mut(name) {
            bs.y = hoff + n.h;
            n.touched = true;
            n.h = bs.y;
        } else {
            let si = ScrollBoxInfo {
                h: sb.y,
                touched: true,
            };
            self.scroll_boxes.insert(name.to_owned(), si);
        };
        let f = Frame {
            x: bs.x,
            y: bs.y,
            w: bs.w,
            h: bs.h,
            masked: true,
            pushed: true,
            sp: 0,
        };
        self.frames.push(f);
        todo!()
    }
    pub fn create_scrollbox(
        &mut self,
        x: i32,
        y: i32,
        width: i32,
        height: i32,
        name: &str,
        size: u32,
    ) {
        todo!()
    }
}
