# Rust vs Go in performance

This is a speed comparison between Rust and Go - when running multiple threads / coroutines 

The problem is calculating PI where we will divide the computation into different parts and then merging the result in the end.

Both Rust and Go makes it possible to use channels to communicate between the threads.

## Implementations

Lets look at the implementations.

### Go

```go
package main

import (
	"fmt"
	"runtime"
	"time"
)

const PI25DT float64 = 3.141592653589793238462643
const INTERVALS int = 10000000

func main() {
	cpus := runtime.NumCPU()
	for i := 1; i <= cpus; i++ {
		for j := 0; j <= 20; j++ {
			fmt.Println(run(i))
		}
	}
}

func run(cpus int) string {
	var (
		time1     = time.Now()
		ch        = make(chan float64)
		intervals = INTERVALS / cpus
		dx        = 1.0 / float64(INTERVALS)
	)

	for i := cpus; i > 0; i-- {
		go func(cpu int) {
			var (
				innerSum float64
				x        float64
				start    = intervals * cpu
				end      = start - intervals
			)
			for j := start; j > end; j-- {
				x = dx * (float64(j) - 0.5)
				innerSum += 4.0 / (1.0 + x*x)
			}
			ch <- innerSum
		}(i)
	}

	var sum float64

	for i := cpus; i > 0; i-- {
		sum += <-ch
	}

	var (
		pi    = dx * sum
		time2 = time.Since(time1).Seconds()
	)

	return fmt.Sprintf("%d, %.24f, %.24f, %.24f", cpus, pi, PI25DT-pi, time2)
}
```

### Rust

```rust
use std::sync::mpsc;
use std::thread;
use std::time::Instant;

const PI25DT : f64 = 3.141592653589793238462643_f64;
const INTERVALS : i64 = 10000000;

fn main() {
    let cpus = num_cpus::get() as i64;
    for cpu in 1..= cpus {
        for _ in 0..1 {
            let x = run(cpu);
            println!("{x}");
        }
    }
}

fn run(cpus: i64) -> String {
    let time1 = Instant::now();
    let (tx, rx) = mpsc::channel();
    let intervals = INTERVALS/cpus;
    let dx = 1.0 / INTERVALS as f64;

    for cpu in 1..cpus+1 {
        let thread_tx = tx.clone();

        thread::spawn(move || {
            let mut inner_sum: f64 = 0.0;
            let mut x;

            let start = intervals * cpu;
            let end = start - intervals;

            for j in (end..start).rev() {
                x = dx * j as f64 - 0.5;
                inner_sum += 4.0 / (1.0 + x*x);
            }

            thread_tx.send(inner_sum).unwrap();
        });
    }

    let mut sum: f64 = 0.0;

    for _ in 0..cpus {
        sum += rx.recv().unwrap()
    }

    let pi = dx * sum;
    let time2 = time1.elapsed();

    format!("{cpus}, {pi}, {:.24?}, {:.24?}", PI25DT-pi, time2.as_secs_f64())
}
```

Both implementations are very very similar, but the results are very very different.

## Results

To get the results the code has been launched on a HPC machine with a special assigned job to avoid errors in the measurements.

The implementations both print out a csv format which will be saved in a file and is then read by a python script which will plot the results.

### Go

### Rust
