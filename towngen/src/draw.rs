#[derive(Copy, Clone)]
pub struct Color {
    pub r: u8,
    pub g: u8,
    pub b: u8,
    pub a: u8,
}
#[derive(Copy, Clone, PartialEq, Eq)]
pub struct Vec2 {
    pub x: i32,
    pub y: i32,
}
impl Vec2 {
    pub fn new(x: i32, y: i32) -> Self {
        return Self { x, y };
    }
    pub fn dot(&self, other: Self) -> i32 {
        self.x * other.x + self.y * other.y
    }
}
impl std::ops::Add for Vec2 {
    type Output = Self;
    fn add(self, other: Self) -> Self::Output {
        Self {
            x: self.x + other.x,
            y: self.y + other.y,
        }
    }
}
impl std::ops::Sub for Vec2 {
    type Output = Self;
    fn sub(self, other: Self) -> Self::Output {
        Self {
            x: self.x - other.x,
            y: self.y - other.y,
        }
    }
}
impl std::ops::AddAssign for Vec2 {
    fn add_assign(&mut self, other: Self) {
        self.x += other.x;
        self.y += other.y;
    }
}
impl std::ops::SubAssign for Vec2 {
    fn sub_assign(&mut self, other: Self) {
        self.x -= other.x;
        self.y -= other.y;
    }
}
impl std::ops::Mul<i32> for Vec2 {
    type Output = Self;
    fn mul(self, v: i32) -> Self::Output {
        Self {
            x: self.x * v,
            y: self.y * v,
        }
    }
}
impl std::ops::Div<i32> for Vec2 {
    type Output = Self;
    fn div(self, v: i32) -> Self::Output {
        Self {
            x: self.x / v,
            y: self.y / v,
        }
    }
}
impl std::ops::Rem<i32> for Vec2 {
    type Output = Self;
    fn rem(self, v: i32) -> Self::Output {
        Self {
            x: self.x % v,
            y: self.y % v,
        }
    }
}
impl std::ops::MulAssign<i32> for Vec2 {
    fn mul_assign(&mut self, v: i32) {
        self.x *= v;
        self.y *= v;
    }
}
impl std::ops::DivAssign<i32> for Vec2 {
    fn div_assign(&mut self, v: i32) {
        self.x /= v;
        self.y /= v;
    }
}
impl std::ops::RemAssign<i32> for Vec2 {
    fn rem_assign(&mut self, v: i32) {
        self.x %= v;
        self.y %= v;
    }
}
pub struct BB {
    pub x: i32,
    pub y: i32,
    pub w: i32,
    pub h: i32,
}
impl BB {
    pub fn intersects(&self, p: Vec2) -> bool {
        (p.x >= self.x && p.x < (self.x + self.w)) && (p.y >= self.y && p.y < (self.y + self.h))
    }
    pub fn from_points(p: &[Vec2]) -> Self {
        let mut min = p[0];
        let mut max = p[0];
        for i in p {
            if i.x > max.x {
                max.x = i.x;
            }
            if i.y > max.y {
                max.y = i.y;
            }
            if i.x < min.x {
                min.x = i.x
            }
            if i.y < min.y {
                min.y = i.y;
            }
        }
        Self {
            x: min.x,
            y: min.y,
            w: max.x - min.x,
            h: max.y - min.y,
        }
    }
}
pub fn in_triangle(p1: Vec2, p2: Vec2, p3: Vec2, pos: Vec2) -> bool {
    fn same_side(ptest: Vec2, start: Vec2, end: Vec2, mid: Vec2) -> bool {
        let m = (end - start) / 2;
        let mp = mid - m;
    }
    todo!()
}
#[derive(Clone)]
pub struct Image {
    pub height: usize,
    pub width: usize,
    pub data: Box<[Color]>,
}
impl Image {
    pub fn new(height: usize, width: usize) -> Self {
        let mut vs = Vec::new();
        vs.reserve_exact(height * width);
        for _ in 0..height * width {
            vs.push(Color {
                r: 0,
                g: 0,
                b: 0,
                a: 255,
            });
        }
        Image {
            height,
            width,
            data: vs.into(),
        }
    }
    pub fn set_pixel(&mut self, x: usize, y: usize, color: Color) {
        let c = &mut self.data[y * self.width + x];
        *c = color;
    }
    pub fn get_pixel(&self, x: usize, y: usize) -> Color {
        self.data[y * self.width + x]
    }

    pub fn draw_triangle(&self, p1: Vec2, p2: Vec2, p3: Vec2) {
        todo!()
    }
}
