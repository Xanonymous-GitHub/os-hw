#include <cstdio>
#include <cstdlib>
#include <time.h>

void printfunction(int a[], int frame_number);

int main(int argc, char const *argv[]) {
    int page_string[12];
    srand(time(NULL));
    int i;
    for (i = 0; i < 12; i++) {
        page_string[i] = rand() % 10;
    }
    printf("page reference string is :\n");
    printfunction(page_string, 12);

    int page_frame;

    printf("please enter page frame : ");
    scanf("%d", &page_frame);
    printf("\n");

    int frame[page_frame];
    for (i = 0; i < page_frame; i++) {
        frame[i] = -1;
    }

    // FIFO
    int fifo_fault = 0;
    int fifo_order = 0;
    int turn = 0; // number of page input
    while (turn < 12) {
        for (i = 0; i < page_frame; i++) {
            if (page_string[turn] == frame[i]) {
                break;
            }
            if (i == (page_frame - 1)) {
                fifo_fault++;
                frame[fifo_order] = page_string[turn];
                fifo_order++;
            }
        }
        printfunction(frame, page_frame);

        // fifo_order++;
        turn++;

        if (fifo_order == page_frame) {
            fifo_order = 0;
        }
    }

    printf("\nFIFO page fault = %d\n\n", fifo_fault);

    // LRU
    int frame_LRU[page_frame];
    for (i = 0; i < page_frame; i++) {
        frame_LRU[i] = -1;
    }

    int LRU_fault = 0;
    int turn_LRU = 0; // number of page input
    int write_position = 0;

    int k;
    while (turn_LRU < 12) {
        for (i = 0; i < page_frame; i++) {
            if (page_string[turn_LRU] == frame_LRU[i]) {
                write_position--;
                for (k = i; k < write_position; k++) {
                    frame_LRU[k] = frame_LRU[k + 1];
                }
                frame_LRU[write_position] = page_string[turn_LRU];
                write_position++;
                break;
            }

            if (i == (page_frame - 1)) {
                LRU_fault++;
                if (write_position != page_frame) {
                    frame_LRU[write_position] = page_string[turn_LRU];
                    write_position++;
                } else {
                    for (k = 0; k < (page_frame - 1); k++) {
                        frame_LRU[k] = frame_LRU[k + 1];
                    }
                    frame_LRU[page_frame - 1] = page_string[turn_LRU];
                }
            }
        }
        printfunction(frame_LRU, page_frame);
        turn_LRU++;
    }

    printf("\nLRU page fault = %d\n", LRU_fault);

    return 0;
}

void printfunction(int a[], int frame_number) {
    int t;
    for (t = 0; t < frame_number; t++) {
        printf("%d ", a[t]);
    }
    printf("\n");
}
