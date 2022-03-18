package main

import (
	"fmt"
	"runtime"
	"sync"
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
		sum, pi, time2 float64
		wg             sync.WaitGroup
		mu             sync.Mutex
		intervals      = INTERVALS / cpus
		dx             = 1.0 / float64(INTERVALS)
		time1          = time.Now()
	)

	for i := cpus; i > 0; i-- {
		var (
			innerSum float64
			x        float64
			start    = intervals * i
			end      = start - intervals
		)
		wg.Add(1)
		go func(w *sync.WaitGroup) {
			defer w.Done()
			for j := start; j > end; j-- {
				x = dx * (float64(j) - 0.5)
				innerSum += 4.0 / (1.0 + x*x)
			}
			mu.Lock()
			sum += innerSum
			mu.Unlock()
		}(&wg)
	}

	wg.Wait()

	pi = dx * sum

	time2 = time.Since(time1).Seconds()

	return fmt.Sprintf("%d, %.24f, %.24f, %.24f", cpus, PI25DT, PI25DT-pi, time2)
}
