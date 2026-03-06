#include<stdio.h>
int main(){
int n;

printf("Enter the number of process\n");
scanf("%d",&n);

int p[n],at[n],bt[n];
int ct[n],tat[n],wt[n],rt[n];

for(int i=0; i<n;i++){
    printf("Enter the Process ID, Arrival Time, Burst Time of the process\n");
    scanf("%d %d %d",&p[i],&at[i],&bt[i]);
}

int time=0;

for(int i=0;i<n;i++){
     if(time<at[i]){
        time=at[i];
     }
     time=time+bt[i];
     ct[i]=time;
     tat[i]=ct[i]-at[i];
     wt[i]=tat[i]-bt[i];
     rt[i]=wt[i];
}

 //printf("\n-------------------------------------------------------------\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    //printf("-------------------------------------------------------------\n");

    for(int i = 0; i < n; i++){
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",p[i], at[i], bt[i], ct[i], tat[i], wt[i], rt[i]);
    }

    //printf("-------------------------------------------------------------\n");
    return 0;



}
