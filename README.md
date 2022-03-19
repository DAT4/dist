# Distributed systems

This is my documentation from the course 

# Week 1
# Week 2
# Week 3
- Conceptually write a parallel version of pi running on an arbitrary number of processors.
I made a version with mutex and waitgroups
```go
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
}
```
which gave the following output with 20 threads

| threads | pi                | error                  | time                 |
|---------|-------------------|------------------------|----------------------|
| 1.0     | 3.141592653589793 | 3.57047724719e-13      | 0.05423645338095238  |
| 2.0     | 3.141592653589793 | 5.3290705182e-14       | 0.03858928442857143  |
| 3.0     | 3.141592653589793 | 1.9999996858643954e-07 | 0.03377063738095238  |
| 4.0     | 3.141592653589793 | 8.881784197e-15        | 0.03148214357142857  |
| 5.0     | 3.141592653589793 | 7.211162883619048e-15  | 0.027955456476190476 |
| 6.0     | 3.141592653589793 | 8.000001265672822e-07  | 0.028463973142857143 |
| 7.0     | 3.141592653589793 | 6.000000984940357e-07  | 0.03183754328571429  |
| 8.0     | 3.141592653589793 | 1.0298640247761905e-14 | 0.028439853714285715 |
| 9.0     | 3.141592653589793 | 2.000000396407131e-07  | 0.027101552476190477 |
| 10.0    | 3.141592653589793 | 2.3494433911523812e-14 | 0.02337746119047619  |
| 11.0    | 3.141592653589793 | 2.0000009698320366e-06 | 0.025170761          |
| 12.0    | 3.141592653589793 | 8.000001244314246e-07  | 0.025845478285714287 |
| 13.0    | 3.141592653589793 | 2.000001016905493e-06  | 0.024133992523809523 |
| 14.0    | 3.141592653589793 | 2.0000009813149145e-06 | 0.02736389476190476  |
| 15.0    | 3.141592653589793 | 2.0000009909579946e-06 | 0.023870838142857145 |
| 16.0    | 3.141592653589793 | 8.331959460809524e-15  | 0.028217270238095237 |
| 17.0    | 3.141592653589793 | 1.0000002471591142e-06 | 0.022219067619047617 |
| 18.0    | 3.141592653589793 | 2.0000009887586956e-06 | 0.02301042480952381  |
| 19.0    | 3.141592653589793 | 3.000002241906753e-06  | 0.02155738580952381  |
| 20.0    | 3.141592653589793 | 3.573860784238095e-15  | 0.029006359952380954 |


with some statistics I got this graph

![graph](l4/pigomutexdtu.svg)

I made another version with channels
```go
go func() {
	for i := cpus; i > 0; i-- {
		go func() {
			var (
				innerSum float64
				x        float64
				start    = intervals * i
				end      = start - intervals
			)
			for j := start; j > end; j-- {
				x = dx * (float64(j) - 0.5)
				innerSum += 4.0 / (1.0 + x*x)
			}
			ch <- innerSum
		}()
	}
}()

for i := cpus; i > 0; i-- {
	sum += <-ch
}

pi = dx * sum
```

which gave this output


| threads | pi                 | error                  | time                  |
|---------|--------------------|------------------------|-----------------------|
| 1.0     | 3.141592653589436  | 3.57047724719e-13      | 0.05421268233333333   |
| 2.0     | 3.14159265358974   | 5.3290705182e-14       | 0.02713205761904762   |
| 3.0     | 3.1415924535898245 | 1.9999996858643954e-07 | 0.018175455523809524  |
| 4.0     | 3.1415926535897842 | 8.881784197e-15        | 0.013596884238095238  |
| 5.0     | 3.141592653589786  | 7.105427357714285e-15  | 0.010893526428571429  |
| 6.0     | 3.1415918535896665 | 8.000001265461351e-07  | 0.009089162714285713  |
| 7.0     | 3.1415920535896946 | 6.000000984728886e-07  | 0.007834049238095237  |
| 8.0     | 3.141592653589783  | 1.0340934458142858e-14 | 0.006853302285714286  |
| 9.0     | 3.1415924535897535 | 2.000000396407131e-07  | 0.006101394285714285  |
| 10.0    | 3.141592653589817  | 2.3790493384857144e-14 | 0.005507942523809524  |
| 11.0    | 3.1415906535888234 | 2.0000009698108896e-06 | 0.005029258238095238  |
| 12.0    | 3.1415918535896687 | 8.000001243468362e-07  | 0.004656678285714286  |
| 13.0    | 3.1415906535887763 | 2.000001016884346e-06  | 0.004280971333333333  |
| 14.0    | 3.141590653588812  | 2.0000009813149145e-06 | 0.003995460047619048  |
| 15.0    | 3.141590653588802  | 2.0000009909157005e-06 | 0.003738446523809524  |
| 16.0    | 3.141592653589801  | 8.205076829428571e-15  | 0.0035624690476190476 |
| 17.0    | 3.141591653589546  | 1.0000002471591142e-06 | 0.003689629619047619  |
| 18.0    | 3.1415906535888043 | 2.000000988779843e-06  | 0.0035705435238095238 |
| 19.0    | 3.1415896535875514 | 3.000002241906753e-06  | 0.0037522158571428573 |
| 20.0    | 3.1415926535897896 | 3.5315665737619046e-15 | 0.003566161523809524  |




with some statistics I got this graph

![graph](l4/pigochandtu.svg)

# Week 4
# Week 5
- When is `MPI_REDUCE` useful:
- When is `MPI_Scatter` and `MPI_Gather` useful?
- What happens if all jobs send before receiving?
- Change communication.c to use non blocking operations
- Use MPI to implement a parallel version of PI
```c
int main (int argc, char *argv[])
{
    double x, f, local_sum, pi;

    double dx = 1.0 / (double) INTERVALS;

    int  numtasks, taskid, len, partner, message;


    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &taskid);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

    long int intervals = INTERVALS/numtasks;
    long int start = intervals * (int) (taskid+1);
    long int stop = start - intervals;
    time_t time1;
    double time2;


    if (taskid == 0) { 
	time1 = clock();
    }

    local_sum = 0.0;
    for (int i = start; i > stop ; i--) {
	x = dx * ((double) (i - 0.5));
	local_sum = local_sum + 4.0 / (1.0 + x*x);
    }

    double global_sum;

    MPI_Reduce(&local_sum, &global_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);


    if (taskid == 0) {
	time2 = (clock() - time1) / (double) CLOCKS_PER_SEC;
	pi = dx*global_sum;
	printf("%d, %.24f, %.24f, %.24f, %.24f\n", numtasks, pi, PI25DT, PI25DT-pi, time2);
    }

    MPI_Finalize();

    return 0;
}

```
- Make statistics on the output by changing factors
```sh
mpirun ./main > log/main_{n}.log 
```


```python
from os import execvp 
data = open('run.txt').read()

for i in range(1,16):
    for j in range(20):
        open(f'run/run_{str(i).zfill(2)}_{j}.txt', 'w').write(data.format(cpucore=i, n=f'{str(i).zfill(2)}_{j}'))

```

```sh
cd run
for x in *.txt; do bsub < x ; done
```

Wait until everything is complete

```sh
cat *.log >> out.log
```

out.log will have the following

| cores | pi                 | error                  | time   |
|-------|--------------------|------------------------|--------|
| 1.0   | 3.141592653589436  | 3.57047724719e-13      | 0.142  |
| 2.0   | 3.14159265358974   | 5.3290705182e-14       | 0.094  |
| 3.0   | 3.1415924535898245 | 1.9999996858643954e-07 | 0.063  |
| 4.0   | 3.1415926535897842 | 8.881784197e-15        | 0.049  |
| 5.0   | 3.1415926535897856 | 7.549516567e-15        | 0.0375 |
| 6.0   | 3.1415918535896665 | 8.000001265884293e-07  | 0.0315 |
| 7.0   | 3.1415920535896946 | 6.000000984940357e-07  | 0.027  |
| 8.0   | 3.141592653589783  | 1.0214051827e-14       | 0.0255 |
| 9.0   | 3.1415924535897535 | 2.000000396407131e-07  | 0.0205 |
| 10.0  | 3.1415926535898167 | 2.3536728122e-14       | 0.017  |
| 11.0  | 3.141590653588823  | 2.0000009701703902e-06 | 0.016  |
| 12.0  | 3.1415918535896683 | 8.000001248120725e-07  | 0.016  |
| 13.0  | 3.1415906535887763 | 2.0000010167997573e-06 | 0.0145 |
| 14.0  | 3.141590653588812  | 2.0000009812726205e-06 | 0.0125 |
| 15.0  | 3.141590653588802  | 2.000000991042583e-06  | 0.0125 |

We get this graph

![graph](l6/pimpidtu.svg)

Which shows that the execution time becomes lower the more cores we assign.

# Week 6 
- Write an OpenMP version of PI
```c
int main (int argc, char *argv[])
{
	if (strlen(argv[1]) == 0) {return 1;}
	char* p;
	errno = 0;
	long arg = strtol(argv[1], &p, 10);
	if (*p != '\0' || errno != 0) {return 1;}
	if (arg < INT_MIN || arg > INT_MAX) {return 1;}
	int cpu = arg;
	double itime, ftime, exec_time;
	itime = omp_get_wtime();

	double global_sum, pi, dx;

	dx = 1.0 / (double) INTERVALS;

#	pragma omp parallel num_threads(cpu) reduction(+: global_sum)
	global_sum += PI(&global_sum);

	pi = dx*global_sum;

	ftime = omp_get_wtime();
	exec_time = ftime - itime;

	printf("%d, %.24f, %.24f, %.24f\n", cpu, pi, PI25DT-pi, exec_time);

	return 0;
}

double PI()
{
	double x;
	double dx = 1.0 / (double) INTERVALS;

	int numtasks = omp_get_num_threads();
	int taskid = omp_get_thread_num();
	int intervals = INTERVALS/numtasks;

	int start = intervals * (int) (taskid+1);
	int stop = start - intervals;

	double local_sum = 0.0;

	for (int i = start; i > stop ; i--) {
		x = dx * ((double) (i - 0.5));
		local_sum = local_sum + 4.0 / (1.0 + x*x);
	}

	return local_sum;
}
```
- Make some statistict

First we get the output.

```sh
# CLEAN
rm data.csv

# BUILD
gcc -g -Wall -std=c99 -fopenmp -o out main.c 

# RUN
for i in {1..20}; do for j in {1..20}; do ./out $i >> data.csv ; done ; done
```

The output looks like this csv.

| threads | pi                 | error                  | time                 |
|---------|--------------------|------------------------|----------------------|
| 1.0     | 3.141592653589436  | 3.57047724719e-13      | 0.18584446752211078  |
| 2.0     | 3.14159265358974   | 5.3290705182e-14       | 0.09299461473710835  |
| 3.0     | 3.1415924535898245 | 1.9999996858643954e-07 | 0.062060013704467565 |
| 4.0     | 3.1415926535897842 | 8.881784197e-15        | 0.046603204170241955 |
| 5.0     | 3.141592653589786  | 7.19424519975e-15      | 0.03728697014739737  |
| 6.0     | 3.1415918535896665 | 8.000001265440205e-07  | 0.0311086957459338   |
| 7.0     | 3.1415920535896946 | 6.000000984940357e-07  | 0.026703226927202194 |
| 8.0     | 3.141592653589783  | 1.039168751065e-14     | 0.023409910709597172 |
| 9.0     | 3.1415924535897535 | 2.0000003970732648e-07 | 0.02083822079002857  |
| 10.0    | 3.1415926535898167 | 2.3625545964e-14       | 0.018772891559638082 |
| 11.0    | 3.1415906535888234 | 2.0000009699039366e-06 | 0.017115934554021807 |
| 12.0    | 3.1415918535896687 | 8.000001245678235e-07  | 0.01575561014469713  |
| 13.0    | 3.141590653588776  | 2.0000010170440064e-06 | 0.014585135015659034 |
| 14.0    | 3.141590653588812  | 2.000000981294825e-06  | 0.01354914647527039  |
| 15.0    | 3.141590653588802  | 2.000000990842743e-06  | 0.012722483789548277 |
| 16.0    | 3.1415926535898016 | 8.282263763499999e-15  | 0.012088755960576236 |
| 17.0    | 3.141591653589546  | 1.0000002470977875e-06 | 0.011427389946766198 |
| 18.0    | 3.1415906535888043 | 2.000000988822137e-06  | 0.010863741033244879 |
| 19.0    | 3.1415896535875514 | 3.0000022418041892e-06 | 0.010505183890927583 |
| 20.0    | 3.1415926535897896 | 3.3972824555e-15       | 0.012721628556028009 |


this graph

![graph](l7/piopenmpdtu.svg)

which shows us that the code becomes faster with more threads, but flattens out
