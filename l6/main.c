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
	printf("Number of intervals pr core: %ld\n", intervals); 
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

	printf("\n");
	printf("Computed PI %.24f\n", pi);
	printf("The true PI %.24f\n", PI25DT);
	printf("Error       %.24f\n", PI25DT-pi);
	printf("Elapsed time (ns) = %.24f\n", time2);
	printf("\n");
    }

    MPI_Finalize();

    return 0;
}
