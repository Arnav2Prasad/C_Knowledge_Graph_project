#include <stdio.h>
#include <time.h>

// Example function to measure
void exampleFunction() {
    // Simulate a function that takes time
    for (volatile int i = 0; i < 1000000; i++);
}

int main() {
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    exampleFunction();
    end = clock();

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("Time taken by function: %f seconds\n", cpu_time_used);

    return 0;
}
