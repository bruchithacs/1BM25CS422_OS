#include <stdio.h>

void sjf_non_preemptive(int n,int pid[],int at[],int bt[])
{
    int ct[n],tat[n],wt[n],rt[n];
    int completed[n],time=0,count=0,i,min,idx;

    for(i=0;i<n;i++)
        completed[i]=0;

    while(count<n)
    {
        min=9999;
        idx=-1;

        for(i=0;i<n;i++)
        {
            if(at[i]<=time && completed[i]==0 && bt[i]<min)
            {
                min=bt[i];
                idx=i;
            }
        }

        if(idx!=-1)
        {
            time+=bt[idx];
            ct[idx]=time;
            completed[idx]=1;
            count++;
        }
        else
            time++;
    }

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\tRT\n");

    for(i=0;i<n;i++)
    {
        tat[i]=ct[i]-at[i];
        wt[i]=tat[i]-bt[i];
        rt[i]=wt[i];

        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
        pid[i],at[i],bt[i],ct[i],tat[i],wt[i],rt[i]);
    }
}

void sjf_preemptive(int n,int pid[],int at[],int bt[])
{
    int ct[n],tat[n],wt[n],rt[n];
    int remaining[n],completed[n];
    int time=0,count=0,i,min,idx;

    for(i=0;i<n;i++)
    {
        remaining[i]=bt[i];
        completed[i]=0;
    }

    while(count<n)
    {
        min=9999;
        idx=-1;

        for(i=0;i<n;i++)
        {
            if(at[i]<=time && completed[i]==0 && remaining[i]<min)
            {
                min=remaining[i];
                idx=i;
            }
        }

        if(idx!=-1)
        {
            remaining[idx]--;
            time++;

            if(remaining[idx]==0)
            {
                ct[idx]=time;
                completed[idx]=1;
                count++;
            }
        }
        else
            time++;
    }

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\tRT\n");

    for(i=0;i<n;i++)
    {
        tat[i]=ct[i]-at[i];
        wt[i]=tat[i]-bt[i];
        rt[i]=wt[i];

        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
        pid[i],at[i],bt[i],ct[i],tat[i],wt[i],rt[i]);
    }
}

int main()
{
    int n,i,choice;

    printf("Enter number of processes: ");
    scanf("%d",&n);

    int pid[n],at[n],bt[n];

    printf("Enter PID, Arrival Time, Burst Time:\n");

    for(i=0;i<n;i++)
        scanf("%d %d %d",&pid[i],&at[i],&bt[i]);

    printf("\n1. SJF Non Preemptive\n");
    printf("2. SJF Preemptive\n");
    printf("Enter choice: ");
    scanf("%d",&choice);

    if(choice==1)
        sjf_non_preemptive(n,pid,at,bt);
    else
        sjf_preemptive(n,pid,at,bt);

    return 0;
}
