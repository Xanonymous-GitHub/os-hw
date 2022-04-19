#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int i = 0;
unsigned long long int amtWanted = 0;
unsigned int totalPts = 0;

void *count(void *X) {
    for (i = 0; i < amtWanted; i++) {
        const double X = (double)rand() / RAND_MAX;
        const double Y = (double)rand() / RAND_MAX;

        if (((X * X) + (Y * Y)) <= 1) {
            totalPts++;
        }
    }

    return NULL;
}

int main() {
    srand(time(NULL));
    pthread_t thread;

    do {
        printf("Please enter a positive number for the amount of points you would like to generate? \n");
        scanf("%lld", &amtWanted);
    } while (amtWanted <= 0);

    pthread_create(&thread, NULL, &count, NULL);
    pthread_join(thread, NULL);

    double points = 4.0 * totalPts;
    double pi = points / amtWanted;
    printf("The approximate value of pi for the desired amount of points (%llu) is: %f \n", amtWanted, pi);
    return 0;
}