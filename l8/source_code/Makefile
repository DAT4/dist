clean:
	rm images/*processed.bmp
	rm images/*processed-omp.bmp

build:
	gcc -fopenmp -std=c99 filter.c writeBMP.c readBMP.c -o filter

run:
	./runFilter.sh

