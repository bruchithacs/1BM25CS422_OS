#include <stdio.h>

#define MAX 100

int search(int frames[], int key, int f) {
    for (int i = 0; i < f; i++) {
        if (frames[i] == key)
            return i;
    }
    return -1;
}

void displayFrames(int frames[], int f) {
    printf("[ ");
    for (int i = 0; i < f; i++) {
        if (frames[i] == -1)
            printf("- ");
        else
            printf("%d ", frames[i]);
    }
    printf("]");
}

void FIFO(int pages[], int n, int f) {

    int frames[MAX];
    int index = 0;
    int faults = 0;

    for (int i = 0; i < f; i++)
        frames[i] = -1;

    printf("\n========== FIFO ==========\n");

    for (int i = 0; i < n; i++) {

        printf("\nPage %d -> ", pages[i]);

        if (search(frames, pages[i], f) == -1) {

            frames[index] = pages[i];
            index = (index + 1) % f;

            faults++;

            displayFrames(frames, f);
            printf("  PAGE FAULT");
        }

        else {

            displayFrames(frames, f);
            printf("  PAGE HIT");
        }
    }

    printf("\n\nTotal Page Faults = %d\n", faults);
}

void LRU(int pages[], int n, int f) {

    int frames[MAX];
    int time[MAX];

    int counter = 0;
    int faults = 0;

    for (int i = 0; i < f; i++) {
        frames[i] = -1;
        time[i] = 0;
    }

    printf("\n========== LRU ==========\n");

    for (int i = 0; i < n; i++) {

        printf("\nPage %d -> ", pages[i]);

        int pos = search(frames, pages[i], f);

        if (pos != -1) {

            counter++;
            time[pos] = counter;

            displayFrames(frames, f);
            printf("  PAGE HIT");
        }

        else {

            int min = 0;

            for (int j = 1; j < f; j++) {
                if (time[j] < time[min])
                    min = j;
            }

            frames[min] = pages[i];

            counter++;
            time[min] = counter;

            faults++;

            displayFrames(frames, f);
            printf("  PAGE FAULT");
        }
    }

    printf("\n\nTotal Page Faults = %d\n", faults);
}

int findOptimal(int pages[], int frames[], int n, int index, int f) {

    int farthest = index;
    int pos = -1;

    for (int i = 0; i < f; i++) {

        int j;

        for (j = index; j < n; j++) {

            if (frames[i] == pages[j]) {

                if (j > farthest) {
                    farthest = j;
                    pos = i;
                }

                break;
            }
        }

        if (j == n)
            return i;
    }

    if (pos == -1)
        return 0;

    return pos;
}

void Optimal(int pages[], int n, int f) {

    int frames[MAX];
    int faults = 0;

    for (int i = 0; i < f; i++)
        frames[i] = -1;

    printf("\n========== OPTIMAL ==========\n");

    for (int i = 0; i < n; i++) {

        printf("\nPage %d -> ", pages[i]);

        if (search(frames, pages[i], f) != -1) {

            displayFrames(frames, f);
            printf("  PAGE HIT");
        }

        else {

            int pos = findOptimal(pages, frames, n, i + 1, f);

            frames[pos] = pages[i];

            faults++;

            displayFrames(frames, f);
            printf("  PAGE FAULT");
        }
    }

    printf("\n\nTotal Page Faults = %d\n", faults);
}

int main() {

    int pages[MAX];
    int n, frames;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter reference string:\n");

    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter number of frames: ");
    scanf("%d", &frames);

    FIFO(pages, n, frames);

    LRU(pages, n, frames);

    Optimal(pages, n, frames);

    return 0;
}
