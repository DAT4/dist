# Distributed systems

This is my documentation from the course 

# Week 1
# Week 2
# Week 3
# Week 4
# Week 5
- When is `MPI_REDUCE` useful:
- When is `MPI_Scatter` and `MPI_Gather` useful?
- What happens if all jobs send before receiving?
- Change communication.c to use non blocking operations
- Use MPI to implement a parallel version of PI
```c
#include "mpi.h"
#include "time.h"
#include <stdio.h>
#include <stdlib.h>
#define  MASTER		0
#define PI25DT 3.141592653589793238462643
#define INTERVALS 10000000


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
#!/bin/sh 
### General options 
### -- specify queue -- 
#BSUB -q hpc
### -- set the job Name -- 
#BSUB -J My_Application
### -- ask for number of cores (default: 1) -- 
#BSUB -n {cpucore}
### -- specify that the cores must be on the same host -- 
#BSUB -R "span[hosts=1]"
### -- specify that we need 2GB of memory per core/slot -- 
#BSUB -R "rusage[mem=2GB]"
### -- specify that we want the job to get killed if it exceeds 3 GB per core/slot -- 
#BSUB -M 3GB
### -- set walltime limit: hh:mm -- 
#BSUB -W 24:00 
### -- set the email address -- 
# please uncomment the following line and put in your e-mail address,
# if you want to receive e-mail notifications on a non-default address
##BSUB -u your_email_address
### -- send notification at start -- 
#BSUB -B 
### -- send notification at completion -- 
#BSUB -N 
### -- Specify the output and error file. %J is the job-id -- 
### -- -o and -e mean append, -oo and -eo mean overwrite -- 
#BSUB -o Output_%J.out 
#BSUB -e Error_%J.err 

module load mpi

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
bsub < run/run_01_0.txt
bsub < run/run_01_10.txt
bsub < run/run_01_11.txt
bsub < run/run_01_12.txt
bsub < run/run_01_13.txt
bsub < run/run_01_14.txt
bsub < run/run_01_15.txt
bsub < run/run_01_16.txt
bsub < run/run_01_17.txt
bsub < run/run_01_18.txt
bsub < run/run_01_19.txt
bsub < run/run_01_1.txt
bsub < run/run_01_2.txt
bsub < run/run_01_3.txt
bsub < run/run_01_4.txt
bsub < run/run_01_5.txt
bsub < run/run_01_6.txt
bsub < run/run_01_7.txt
bsub < run/run_01_8.txt
bsub < run/run_01_9.txt
bsub < run/run_02_0.txt
bsub < run/run_02_10.txt
bsub < run/run_02_11.txt
bsub < run/run_02_12.txt
bsub < run/run_02_13.txt
bsub < run/run_02_14.txt
bsub < run/run_02_15.txt
bsub < run/run_02_16.txt
bsub < run/run_02_17.txt
bsub < run/run_02_18.txt
bsub < run/run_02_19.txt
bsub < run/run_02_1.txt
bsub < run/run_02_2.txt
bsub < run/run_02_3.txt
bsub < run/run_02_4.txt
bsub < run/run_02_5.txt
bsub < run/run_02_6.txt
bsub < run/run_02_7.txt
bsub < run/run_02_8.txt
bsub < run/run_02_9.txt
bsub < run/run_03_0.txt
bsub < run/run_03_10.txt
bsub < run/run_03_11.txt
bsub < run/run_03_12.txt
bsub < run/run_03_13.txt
bsub < run/run_03_14.txt
bsub < run/run_03_15.txt
bsub < run/run_03_16.txt
bsub < run/run_03_17.txt
bsub < run/run_03_18.txt
bsub < run/run_03_19.txt
bsub < run/run_03_1.txt
bsub < run/run_03_2.txt
bsub < run/run_03_3.txt
bsub < run/run_03_4.txt
bsub < run/run_03_5.txt
bsub < run/run_03_6.txt
bsub < run/run_03_7.txt
bsub < run/run_03_8.txt
bsub < run/run_03_9.txt
bsub < run/run_04_0.txt
bsub < run/run_04_10.txt
bsub < run/run_04_11.txt
bsub < run/run_04_12.txt
bsub < run/run_04_13.txt
bsub < run/run_04_14.txt
bsub < run/run_04_15.txt
bsub < run/run_04_16.txt
bsub < run/run_04_17.txt
bsub < run/run_04_18.txt
bsub < run/run_04_19.txt
bsub < run/run_04_1.txt
bsub < run/run_04_2.txt
bsub < run/run_04_3.txt
bsub < run/run_04_4.txt
bsub < run/run_04_5.txt
bsub < run/run_04_6.txt
bsub < run/run_04_7.txt
bsub < run/run_04_8.txt
bsub < run/run_04_9.txt
bsub < run/run_05_0.txt
bsub < run/run_05_10.txt
bsub < run/run_05_11.txt
bsub < run/run_05_12.txt
bsub < run/run_05_13.txt
bsub < run/run_05_14.txt
bsub < run/run_05_15.txt
bsub < run/run_05_16.txt
bsub < run/run_05_17.txt
bsub < run/run_05_18.txt
bsub < run/run_05_19.txt
bsub < run/run_05_1.txt
bsub < run/run_05_2.txt
bsub < run/run_05_3.txt
bsub < run/run_05_4.txt
bsub < run/run_05_5.txt
bsub < run/run_05_6.txt
bsub < run/run_05_7.txt
bsub < run/run_05_8.txt
bsub < run/run_05_9.txt
bsub < run/run_06_0.txt
bsub < run/run_06_10.txt
bsub < run/run_06_11.txt
bsub < run/run_06_12.txt
bsub < run/run_06_13.txt
bsub < run/run_06_14.txt
bsub < run/run_06_15.txt
bsub < run/run_06_16.txt
bsub < run/run_06_17.txt
bsub < run/run_06_18.txt
bsub < run/run_06_19.txt
bsub < run/run_06_1.txt
bsub < run/run_06_2.txt
bsub < run/run_06_3.txt
bsub < run/run_06_4.txt
bsub < run/run_06_5.txt
bsub < run/run_06_6.txt
bsub < run/run_06_7.txt
bsub < run/run_06_8.txt
bsub < run/run_06_9.txt
bsub < run/run_07_0.txt
bsub < run/run_07_10.txt
bsub < run/run_07_11.txt
bsub < run/run_07_12.txt
bsub < run/run_07_13.txt
bsub < run/run_07_14.txt
bsub < run/run_07_15.txt
bsub < run/run_07_16.txt
bsub < run/run_07_17.txt
bsub < run/run_07_18.txt
bsub < run/run_07_19.txt
bsub < run/run_07_1.txt
bsub < run/run_07_2.txt
bsub < run/run_07_3.txt
bsub < run/run_07_4.txt
bsub < run/run_07_5.txt
bsub < run/run_07_6.txt
bsub < run/run_07_7.txt
bsub < run/run_07_8.txt
bsub < run/run_07_9.txt
bsub < run/run_08_0.txt
bsub < run/run_08_10.txt
bsub < run/run_08_11.txt
bsub < run/run_08_12.txt
bsub < run/run_08_13.txt
bsub < run/run_08_14.txt
bsub < run/run_08_15.txt
bsub < run/run_08_16.txt
bsub < run/run_08_17.txt
bsub < run/run_08_18.txt
bsub < run/run_08_19.txt
bsub < run/run_08_1.txt
bsub < run/run_08_2.txt
bsub < run/run_08_3.txt
bsub < run/run_08_4.txt
bsub < run/run_08_5.txt
bsub < run/run_08_6.txt
bsub < run/run_08_7.txt
bsub < run/run_08_8.txt
bsub < run/run_08_9.txt
bsub < run/run_09_0.txt
bsub < run/run_09_10.txt
bsub < run/run_09_11.txt
bsub < run/run_09_12.txt
bsub < run/run_09_13.txt
bsub < run/run_09_14.txt
bsub < run/run_09_15.txt
bsub < run/run_09_16.txt
bsub < run/run_09_17.txt
bsub < run/run_09_18.txt
bsub < run/run_09_19.txt
bsub < run/run_09_1.txt
bsub < run/run_09_2.txt
bsub < run/run_09_3.txt
bsub < run/run_09_4.txt
bsub < run/run_09_5.txt
bsub < run/run_09_6.txt
bsub < run/run_09_7.txt
bsub < run/run_09_8.txt
bsub < run/run_09_9.txt
bsub < run/run_10_0.txt
bsub < run/run_10_10.txt
bsub < run/run_10_11.txt
bsub < run/run_10_12.txt
bsub < run/run_10_13.txt
bsub < run/run_10_14.txt
bsub < run/run_10_15.txt
bsub < run/run_10_16.txt
bsub < run/run_10_17.txt
bsub < run/run_10_18.txt
bsub < run/run_10_19.txt
bsub < run/run_10_1.txt
bsub < run/run_10_2.txt
bsub < run/run_10_3.txt
bsub < run/run_10_4.txt
bsub < run/run_10_5.txt
bsub < run/run_10_6.txt
bsub < run/run_10_7.txt
bsub < run/run_10_8.txt
bsub < run/run_10_9.txt
bsub < run/run_11_0.txt
bsub < run/run_11_10.txt
bsub < run/run_11_11.txt
bsub < run/run_11_12.txt
bsub < run/run_11_13.txt
bsub < run/run_11_14.txt
bsub < run/run_11_15.txt
bsub < run/run_11_16.txt
bsub < run/run_11_17.txt
bsub < run/run_11_18.txt
bsub < run/run_11_19.txt
bsub < run/run_11_1.txt
bsub < run/run_11_2.txt
bsub < run/run_11_3.txt
bsub < run/run_11_4.txt
bsub < run/run_11_5.txt
bsub < run/run_11_6.txt
bsub < run/run_11_7.txt
bsub < run/run_11_8.txt
bsub < run/run_11_9.txt
bsub < run/run_12_0.txt
bsub < run/run_12_10.txt
bsub < run/run_12_11.txt
bsub < run/run_12_12.txt
bsub < run/run_12_13.txt
bsub < run/run_12_14.txt
bsub < run/run_12_15.txt
bsub < run/run_12_16.txt
bsub < run/run_12_17.txt
bsub < run/run_12_18.txt
bsub < run/run_12_19.txt
bsub < run/run_12_1.txt
bsub < run/run_12_2.txt
bsub < run/run_12_3.txt
bsub < run/run_12_4.txt
bsub < run/run_12_5.txt
bsub < run/run_12_6.txt
bsub < run/run_12_7.txt
bsub < run/run_12_8.txt
bsub < run/run_12_9.txt
bsub < run/run_13_0.txt
bsub < run/run_13_10.txt
bsub < run/run_13_11.txt
bsub < run/run_13_12.txt
bsub < run/run_13_13.txt
bsub < run/run_13_14.txt
bsub < run/run_13_15.txt
bsub < run/run_13_16.txt
bsub < run/run_13_17.txt
bsub < run/run_13_18.txt
bsub < run/run_13_19.txt
bsub < run/run_13_1.txt
bsub < run/run_13_2.txt
bsub < run/run_13_3.txt
bsub < run/run_13_4.txt
bsub < run/run_13_5.txt
bsub < run/run_13_6.txt
bsub < run/run_13_7.txt
bsub < run/run_13_8.txt
bsub < run/run_13_9.txt
bsub < run/run_14_0.txt
bsub < run/run_14_10.txt
bsub < run/run_14_11.txt
bsub < run/run_14_12.txt
bsub < run/run_14_13.txt
bsub < run/run_14_14.txt
bsub < run/run_14_15.txt
bsub < run/run_14_16.txt
bsub < run/run_14_17.txt
bsub < run/run_14_18.txt
bsub < run/run_14_19.txt
bsub < run/run_14_1.txt
bsub < run/run_14_2.txt
bsub < run/run_14_3.txt
bsub < run/run_14_4.txt
bsub < run/run_14_5.txt
bsub < run/run_14_6.txt
bsub < run/run_14_7.txt
bsub < run/run_14_8.txt
bsub < run/run_14_9.txt
bsub < run/run_15_0.txt
bsub < run/run_15_10.txt
bsub < run/run_15_11.txt
bsub < run/run_15_12.txt
bsub < run/run_15_13.txt
bsub < run/run_15_14.txt
bsub < run/run_15_15.txt
bsub < run/run_15_16.txt
bsub < run/run_15_17.txt
bsub < run/run_15_18.txt
bsub < run/run_15_19.txt
bsub < run/run_15_1.txt
bsub < run/run_15_2.txt
bsub < run/run_15_3.txt
bsub < run/run_15_4.txt
bsub < run/run_15_5.txt
bsub < run/run_15_6.txt
bsub < run/run_15_7.txt
bsub < run/run_15_8.txt
bsub < run/run_15_9.txt
```
# Week 6 
