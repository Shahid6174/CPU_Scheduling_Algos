/*
    author - Mohammed Shahid
    Implementing First Come First Serve CPU scheduling algorithm
*/

#include <stdio.h>

#define MAX 10

struct process
{
    int processNo;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int turnAroundTime;
    int waitingTime;
}p[MAX];


int main()
{
    int np;
    int i, j;
    printf("Enter the number of processes: ");
    scanf("%d", &np);
    for(i=0; i<np; i++)
    {
        p[i].processNo = 0;
        p[i].arrivalTime = 0;
        p[i].burstTime = 0;
        p[i].completionTime = 0;
        p[i].turnAroundTime = 0;
        p[i].waitingTime = 0;
    }
    printf("Enter the arrival time of each process: ");
    for(i=0; i<np; i++)
    {
        scanf("%d", &p[i].arrivalTime);
    }
    for(i=0; i<np; i++)
    {
        p[i].processNo = i+1;
    }
    printf("Enter the burst time of each process: ");
    for(i=0;i<np;i++)
    {
        scanf("%d", &p[i].burstTime);
    }
    for(i=0; i<np-1; i++)
    {
        for(j=0;j<np-i-1; j++)
        {
            if(p[j].arrivalTime > p[j+1].arrivalTime)
            {
                struct process temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }
    for(i=0; i<np; i++)
    {
        if(i==0)
        {
            p[i].completionTime = p[i].burstTime + p[i].arrivalTime;
        }
        else if(p[i].arrivalTime - p[i-1].completionTime > 0) //wait-idle cpu condition
        {
            int idle = p[i].arrivalTime - p[i-1].completionTime;
            p[i].completionTime = p[i].burstTime + p[i-1].completionTime + idle;
        }
        else
        {
            p[i].completionTime = p[i].burstTime + p[i-1].completionTime;
        }   
    }
    float sumTAT = 0;
    float sumWT = 0;
    for(i=0; i<np; i++)
    {
        p[i].turnAroundTime = p[i].completionTime - p[i].arrivalTime;
        p[i].waitingTime = p[i].turnAroundTime - p[i].burstTime;
        sumTAT += p[i].turnAroundTime;
        sumWT += p[i].waitingTime;
    }

    printf("\nProcessNo\tAT\tBT\tCT\tTAT\tWt\n");
    for(i=0; i<np; i++)
    {
            printf("P%d\t\t%d\t%d\t%d\t%d\t%d\n", p[i].processNo, p[i].arrivalTime, p[i].burstTime, p[i].completionTime, p[i].turnAroundTime, p[i].waitingTime);
    }
    printf("\nAverage TAT: %lf\n", sumTAT/np);
    printf("Average WT: %lf\n",sumWT/np);
}