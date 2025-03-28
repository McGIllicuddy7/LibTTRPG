use cities::City;

pub mod cities;
pub mod voronoi;
pub mod utils;
fn main() {
    let guard = pprof::ProfilerGuardBuilder::default().frequency(1000).blocklist(&["libc", "libgcc", "pthread", "vdso"]).build().unwrap();
    let city = City::new(3000, 3000);
    city.render_out("test.png");
    println!("num_buildings:{}", city.buildings.len());
    if let Ok(report) = guard.report().build() {
        let file =std::fs::File::create("flamegraph.svg").unwrap();
        report.flamegraph(file).unwrap();
    };
}    