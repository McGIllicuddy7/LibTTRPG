use cities::City;
pub mod cities;
pub mod pool;
pub mod utils;
pub mod voronoi;
//32 threads 8.2 seconds
//16 threads 6.6 seconds
fn main() {
    let guard = pprof::ProfilerGuardBuilder::default()
        .frequency(1000)
        .blocklist(&["libc", "libgcc", "pthread", "vdso"])
        .build()
        .unwrap();
    let city = City::new(2000, 2000);
    city.render_out("test.png");
    println!("num_buildings:{}", city.buildings.len());
    if let Ok(report) = guard.report().build() {
        let file = std::fs::File::create("flamegraph.svg").unwrap();
        report.flamegraph(file).unwrap();
    };
}
