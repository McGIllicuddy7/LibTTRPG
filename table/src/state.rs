pub use std::collections::LinkedList;
pub use std::sync::{Arc, Mutex};
pub enum ElementType {
    Text,
    Image,
    Token,
}
pub struct GuiElement {
    pub x: usize,
    pub y: usize,
    pub height: usize,
    pub width: usize,
    pub text: String,
}

pub struct ElementRef {
    pub idx: u32,
    pub gnr: u32,
}
pub enum Event {
    ElementMove { idx: u32 },
    ElementCreate { e: GuiElement },
    ElementDestroy { e: ElementRef },
}
pub struct GlobalState {
    pub elements: Box<[Option<GuiElement>]>,
    pub generations: Box<[u32]>,
}
impl Default for GlobalState {
    fn default() -> Self {
        Self::new()
    }
}
impl GlobalState {
    pub fn new() -> Self {
        let mut elements = Vec::new();
        let mut gens = Vec::new();
        elements.reserve_exact(4096);
        gens.reserve_exact(4096);
        for _ in 0..4096 {
            elements.push(None);
            gens.push(0);
        }
        Self {
            elements: elements.into(),
            generations: gens.into(),
        }
    }
}
pub struct LocalState {
    pub prev_state: GlobalState,
    pub events: Arc<Mutex<LinkedList<Event>>>,
    pub selected: Option<ElementRef>,
}
impl Default for LocalState {
    fn default() -> Self {
        Self::new()
    }
}
impl LocalState {
    pub fn new() -> Self {
        Self {
            prev_state: GlobalState::default(),
            events: Arc::new(Mutex::new(LinkedList::new())),
            selected: None,
        }
    }
}
