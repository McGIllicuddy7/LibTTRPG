pub use std::error::Error;
pub type Except<T> = Result<T, Box<dyn Error>>;
pub type Throws = Result<(), Box<dyn Error>>;
#[macro_export]
macro_rules! throw {
    ($x:expr) => {
        return Err($x.into());
    };
}
#[macro_export]
macro_rules! try_catch {
    ($x:expr, $catch:expr) => {
        if let Ok(_tmp) = ($x) { _tmp } else { $catch }
    };
}
#[repr(C)]
pub struct CharPtr {
    data: *mut i8,
}
impl From<&str> for CharPtr {
    fn from(st: &str) -> Self {
        unsafe {
            let out = Self::byte_alloc(st.len() + 1);
            Self::copy(out, st.as_ptr() as *const i8, st.len());
            *(out.add(st.len())) = 0;
            Self { data: out }
        }
    }
}
impl std::convert::AsRef<str> for CharPtr {
    fn as_ref(&self) -> &str {
        unsafe {
            let l = self.len();
            if self.len() == 0 {
                ""
            } else {
                std::str::from_utf8(std::slice::from_raw_parts(self.data as *const u8, l)).unwrap()
            }
        }
    }
}
impl Drop for CharPtr {
    fn drop(&mut self) {
        unsafe {
            if self.data.is_null() {
                return;
            }
            let l = self.len();
            std::alloc::dealloc(
                self.data as *mut u8,
                std::alloc::Layout::from_size_align_unchecked(l, 1),
            );
        }
    }
}
impl CharPtr {
    pub fn len(&self) -> usize {
        unsafe {
            if self.data.is_null() {
                0
            } else {
                let mut count = 0;
                while *self.data.add(count) != 0 {
                    count += 1
                }
                count
            }
        }
    }
    pub unsafe fn copy(dest: *mut i8, src: *const i8, count: usize) {
        for i in 0..count {
            unsafe { *(dest.add(i)) = *(src.add(i)) };
        }
    }
    pub unsafe fn byte_alloc(count: usize) -> *mut i8 {
        unsafe {
            std::alloc::alloc(std::alloc::Layout::from_size_align_unchecked(count, 1)) as *mut i8
        }
    }
    pub fn new() -> Self {
        Self {
            data: std::ptr::null_mut(),
        }
    }
    pub fn cat(&self, other: &Self) {
        let sl = self.len();
        let ol = other.len();
    }
}
