use cities::City;

pub mod cities;
pub mod voronoi;
pub mod utils;
fn main() {
    let city = City::new(1000, 1000);
    city.render_out("test.png");
}
