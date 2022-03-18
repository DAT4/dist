# CLEAN
rm data.csv

# BUILD
gcc -g -Wall -std=c99 -fopenmp -o out main.c 

# RUN
for i in {1..40}; do for j in {1..20}; do ./out $i >> data.csv ; done ; done
