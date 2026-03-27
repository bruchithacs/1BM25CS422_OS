#include <stdio.h>

int main() {
    int n, tq;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int at[n], bt[n], rt[n];
    int ct[n], tat[n], wt[n], rt_time[n];
    int visited[n];

    for (int i = 0; i < n; i++) {
        printf("\nProcess P%d\n", i + 1);

        printf("Arrival Time: ");
        scanf("%d", &at[i]);

        printf("Burst Time: ");
        scanf("%d", &bt[i]);

        rt[i] = bt[i];
        visited[i] = 0;
    }

    printf("\nEnter Time Quantum: ");
    scanf("%d", &tq);

    // Queue implementation
    int queue[100], front = 0, rear = 0;
    int inQueue[n];

    for (int i = 0; i < n; i++)
        inQueue[i] = 0;

    int time = 0, completed = 0;

    // Add initially arrived processes
    for (int i = 0; i < n; i++) {
        if (at[i] == 0) {
            queue[rear++] = i;
            inQueue[i] = 1;
        }
    }

    while (completed < n) {

        if (front == rear) {
            time++;
            for (int i = 0; i < n; i++) {
                if (at[i] <= time && !inQueue[i] && rt[i] > 0) {
                    queue[rear++] = i;
                    inQueue[i] = 1;
                }
            }
            continue;
        }

        int i = queue[front++];

        // Response Time
        if (visited[i] == 0) {
            rt_time[i] = time - at[i];
            visited[i] = 1;
        }

        if (rt[i] > tq) {
            time += tq;
            rt[i] -= tq;
        } else {
            time += rt[i];
            rt[i] = 0;
            ct[i] = time;
            completed++;
        }

        // Add newly arrived processes
        for (int j = 0; j < n; j++) {
            if (at[j] <= time && !inQueue[j] && rt[j] > 0) {
                queue[rear++] = j;
                inQueue[j] = 1;
            }
        }

        // Add current process back if not finished
        if (rt[i] > 0) {
            queue[rear++] = i;
        }
    }

    float total_tat = 0, total_wt = 0, total_rt = 0;

    for (int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];

        total_tat += tat[i];
        total_wt += wt[i];
        total_rt += rt_time[i];
    }

    printf("\nP\tAT\tBT\tCT\tTAT\tWT\tRT\n");

    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               i + 1, at[i], bt[i], ct[i],
               tat[i], wt[i], rt_time[i]);
    }

    printf("\nAverage Turnaround Time = %.2f", total_tat / n);
    printf("\nAverage Waiting Time    = %.2f", total_wt / n);
    printf("\nAverage Response Time   = %.2f\n", total_rt / n);

    return 0;
}
