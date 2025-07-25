use std::sync::Mutex;
pub struct ThreadPool<'a> {
    queue: Mutex<Vec<&'a (dyn Fn() + Send + Sync)>>,
}
impl<'a> ThreadPool<'a> {
    pub fn new() -> Self {
        Self {
            queue: Mutex::new(Vec::new()),
        }
    }
    pub fn spawn_task<T: Fn() + Send + Sync>(&self, f: &'a T) {
        let mut lock = self.queue.lock().unwrap();
        lock.push(f);
    }
    pub fn run_tasks(&self) {
        pub fn task_queue(s: &ThreadPool) {
            loop {
                let mut q = s.queue.lock().unwrap();
                if q.is_empty() {
                    break;
                }
                let a = q.pop().unwrap();
                drop(q);
                a();
            }
        }
        std::thread::scope(|scope| {
            let par = std::thread::available_parallelism().unwrap().get();
            for _ in 0..par - 1 {
                scope.spawn(|| {
                    task_queue(self);
                });
            }
            task_queue(self);
        });
    }
}
