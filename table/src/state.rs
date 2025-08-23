use raylib_rs::ffi::*;
pub use std::collections::HashMap;
const ELEMENT_COUNT_MAX: usize = 16384;
pub struct User {
    pub username: String,
}
pub enum ElementType {
    Note,
    Token,
    Image,
}
pub struct Element {
    pub owner: User,
    pub element_type: ElementType,
    pub message: String,
    pub image: String,
    pub x: i32,
    pub y: i32,
    pub width: i32,
    pub height: i32,
}
pub struct ElementRef {
    pub idx: u32,
    pub genr: u32,
}
pub struct State {
    pub selected_element: Option<usize>,
    pub elements: Box<[Option<Element>]>,
    pub generations: Box<[usize]>,
    pub images: HashMap<String, Image>,
}
pub enum Event {}
impl Default for State {
    fn default() -> Self {
        Self::new()
    }
}
impl State {
    pub fn new() -> Self {
        let mut elemns = Vec::new();
        elemns.reserve_exact(ELEMENT_COUNT_MAX);
        for _ in 0..ELEMENT_COUNT_MAX {
            elemns.push(None);
        }
        let mut gens = Vec::new();
        gens.reserve_exact(ELEMENT_COUNT_MAX);
        for _ in 0..ELEMENT_COUNT_MAX {
            gens.push(0);
        }
        Self {
            selected_element: None,
            elements: elemns.into(),
            generations: gens.into(),
            images: HashMap::new(),
        }
    }
    pub fn update_local(&mut self) {
        todo!()
    }
}
