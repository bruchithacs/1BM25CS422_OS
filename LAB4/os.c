#include <stdio.h>

#define MAX 10

typedef struct {
    int id, burst, deadline, period;
    int remaining, completion, waiting, turnaround;
} Process;

Process p[MAX];

// Function to calculate CPU utilization
float cpu_utilization(int n) {
    float u = 0;
    for (int i = 0; i < n; i++) {
        u += (float)p[i].burst / p[i].period;
    }
    return u;
}

// ---------- EDF Scheduling ----------
void EDF(int n) {
    printf("\n===== Earliest Deadline First (EDF) =====\n");

    int time = 0, completed = 0;

    for (int i = 0; i < n; i++)
        p[i].remaining = p[i].burst;

    while (completed < n) {
        int idx = -1;
        int min_deadline = 9999;

        for (int i = 0; i < n; i++) {
            if (p[i].remaining > 0 && p[i].deadline < min_deadline) {
                min_deadline = p[i].deadline;
                idx = i;
            }
        }

        if (idx != -1) {
            time += p[idx].remaining;
            p[idx].completion = time;
            p[idx].turnaround = time;
            p[idx].waiting = p[idx].turnaround - p[idx].burst;
            p[idx].remaining = 0;
            completed++;
        }
    }

    printf("ID\tCT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\n", p[i].id, p[i].completion,
               p[i].waiting, p[i].turnaround);
    }
}

// ---------- RMS Scheduling ----------
void RMS(int n) {
    printf("\n===== Rate Monotonic Scheduling (RMS) =====\n");

    // Sort by period (shorter period = higher priority)
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].period > p[j].period) {
                Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    int time = 0;

    for (int i = 0; i < n; i++) {
        time += p[i].burst;
        p[i].completion = time;
        p[i].turnaround = time;
        p[i].waiting = p[i].turnaround - p[i].burst;
    }

    printf("ID\tCT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\n", p[i].id, p[i].completion,
               p[i].waiting, p[i].turnaround);
    }
}

// ---------- Proportional Scheduling ----------
void Proportional(int n) {
    printf("\n===== Proportional Scheduling =====\n");

    int total_burst = 0;
    for (int i = 0; i < n; i++)
        total_burst += p[i].burst;

    printf("ID\tShare(%%)\n");
    for (int i = 0; i < n; i++) {
        float share = ((float)p[i].burst / total_burst) * 100;
        printf("%d\t%.2f%%\n", p[i].id, share);
    }
}

// ---------- MAIN ----------
int main() {
    int n;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        p[i].id = i;
        printf("\nProcess %d:\n", i);

        printf("Burst Time: ");
        scanf("%d", &p[i].burst);

        printf("Deadline: ");
        scanf("%d", &p[i].deadline);

        printf("Period: ");
        scanf("%d", &p[i].period);
    }

    float util = cpu_utilization(n);
    printf("\nCPU Utilization = %.2f\n", util);

    EDF(n);
    RMS(n);
    Proportional(n);

    return 0;
}