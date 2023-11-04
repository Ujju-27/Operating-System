#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

struct Process{
    int pid,at,bt,ct,tat,wt,rt,st;
    int remt;
};

int findmax(int a, int b)
{
    return a>b?a:b;
}

int main(){

    // Input Section 

    int n  , tq;
    float avgrt = 0, avgWT = 0 , avgTat = 0 ;
    float sumWT = 0 , sumTat = 0 , sumrt = 0;

    int curr_time = 0 , executed = 0;
    int queue[100] , front = -1 , rear = -1;

    bool vis[100];
    memset(vis , false , 100*sizeof(bool));

    printf("Enter the number of Process - ");
    scanf("%d" , &n);

    struct Process p[n+1];

    for(int i = 0 ; i < n ; i++)
    {
        p[i].pid = i;
        printf("Enter the Arrival Time and Burst Time for Process = %d - " , p[i].pid);
        scanf("%d%d" , &p[i].at , &p[i].bt); 
        p[i].remt = p[i].bt;     
    }

    printf("Enter the value of time Quanta = ");
    scanf("%d" , &tq);

    // bubble sort on based on at
    struct Process temp;

    for(int i = 0 ; i < n-1 ; i++)
    {
        for(int j = 0 ; j < n-i-1 ; j++)
        {
            if(p[j].at > p[j+1].at)
            {
                temp = p[j];
                p[j]= p[j+1];
                p[j+1]= temp;
            }
        }
    }

    
    // start processing in the queue

    front = rear = 0;
    queue[rear] = 0;
    vis[0] = true;
    
    while(executed != n)
    {
        int idx = queue[front];
        front++;

        // Kiya jo process aya hai vo first time aya hai 

        if(p[idx].remt == p[idx].bt)
        {
            p[idx].st = findmax(curr_time , p[idx].at);
            curr_time = p[idx].st;
        }

        // isska matlab vo process tq time tak run karne val hai 
        if(p[idx].remt - tq > 0)
        {
            p[idx].remt -= tq;
            curr_time +=tq;
        }
        // completely over remaining time
        else{
            curr_time += p[idx].remt;
            p[idx].remt = 0;
            executed++;

            p[idx].ct = curr_time;
            p[idx].rt = p[idx].st - p[idx].at;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt =  p[idx].tat - p[idx].bt;

            sumrt += p[idx].rt;
            sumTat += p[idx].tat;
            sumWT += p[idx].wt;
        }


        // check for till which process are should enter the queue

        for(int i = 1 ;  i < n ; i++)
        {
            if(p[i].remt > 0 && p[i].at <= curr_time && vis[i] == false)
            {
                queue[++rear] = i;
                vis[i] = true;
            }
        }

        // kiya jis process ko hum process kar rhai thai vo fir se tho queue mai nhi jaane chahiya

        if(p[idx].remt > 0)
            queue[++rear] = idx;

         //if queue is empty, just add one process from list, whose remaining burst time > 0
        if(front > rear)
        {
            for(int i = 1 ; i < n ; i++)
            {
                if(p[i].remt > 0)
                {
                    queue[rear++] = i;
                    vis[i] = true;
                    break;
                }
            }
        }    

    }

    avgWT = sumWT/n;
    avgTat = sumTat/n;
    avgrt = sumrt/n;

     printf("process\t\tat\tbt\tst\tct\trt\ttat\twt\n");
    
    for(int i = 0 ; i < n ; i++){
        printf("%d\t\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",p[i].pid , p[i].at , p[i].bt , p[i].st , p[i].ct , p[i].rt , p[i].tat , p[i].wt);
    }
    
     printf("Average Response Time =  %0.2f\n Average TurnAround Time = %0.2f\n  Average Waiting Time = %0.2f\n" , avgrt , avgTat , avgWT);
    
    return 0;
}
