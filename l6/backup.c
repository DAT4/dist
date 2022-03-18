#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#define  MASTER		0
#define PI25DT 3.141592653589793238462643
#define INTERVALS 10000000


int main (int argc, char *argv[])
{
    long int intervals = INTERVALS/4;
    long int start, stop;
    double x, f, local_sum, pi;
    double dx = 1.0 / (double) intervals;

    int  numtasks, taskid, len, partner, message;

    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &taskid);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

    start = intervals * (int) taskid;
    stop = stop - intervals;

    long int i;
    //double time2;
    //time_t time1 = clock();

    if (taskid == 0) { printf("Number of intervals: %ld\n", intervals); }

    local_sum = 0.0;
    for (i = start; i > stop ; i--) {
	x = dx * ((double) (i - 0.5));
	local_sum = local_sum + 4.0 / (1.0 + x*x);;
    }
    //printf("Intervals : %d\n", intervals);
    printf("DX: %f\n", dx);
    //printf("Local SUM: %d\n", local_sum);

    double global_sum;

    MPI_Reduce(&local_sum, &global_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);


    //time2 = (clock() - time1) / (double) CLOCKS_PER_SEC;

    if (taskid == 0) {
	pi = dx*global_sum;
	printf("Computed PI %.24f\n", pi);
	printf("The true PI %.24f\n", PI25DT);
	printf("Error       %.24f\n\n", PI25DT-pi);
	//printf("Elapsed time (s) = %f\n", time2);
    }

    MPI_Finalize();

    return 0;
}
