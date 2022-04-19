#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <pthread.h>
#include <sys/types.h>
#include <vector>

using namespace std;

vector<uintmax_t> shared_data;

void *fibonacci_thread(void *const params) {
    uintmax_t fib0 = 0, fib1 = 1, next = 0;
    const int total = *(int *)params;

    for (int i = 0; i < total; i++) {
        if (i <= 1) {
            next = i;
        } else {
            next = fib0 + fib1;
            fib0 = fib1;
            fib1 = next;
        }

        // store to shared_data array
        shared_data.push_back(next);
    }

    pthread_exit(0);
}

void get_number(int *const numbers) {
    cout << "Enter in a number to generate the Fibonacci sequence: ";
    cin >> *numbers;
}

int main(int argc, char const *argv[]) {
    int number = 0;

    // create thread
    pthread_t child;
    pthread_attr_t attr;

    pthread_attr_init(&attr);

    // get user input then start separate thread.
    get_number(&number);

    // starts fibonacci thread
    pthread_create(&child, &attr, fibonacci_thread, (void *const)&number);

    // waits for thread to finish
    pthread_join(child, NULL);

    // output to command prompt after thread finishes.

    for (auto &it : shared_data) {
        cout << it << ", ";
    }

    return 0;
}
