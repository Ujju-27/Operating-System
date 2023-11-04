#include<stdio.h>
#include<stdlib.h>

struct Process{
    int pid; // process id
    int at; // arrival time 
    int bt; // burst time
    int ct; // compiletion time 
    int tat; // trun round time 
    int wt ; // waiting time 
    int rt; // response time
    int st; // start time 
};


int compare(const void *p1 , const void *p2){
    int a = ((struct Process *) p1)->at;
    int b = ((struct Process *) p2)->at;
    
    if(a < b)
        return -1;
    else
        return 1;
}


int main(){
    int n;
    float sumWT = 0 , sumTat = 0 , sumrt = 0;
    float avgrt = 0, avgWT = 0 , avgTat = 0;
    int idealTime = 0;
    float cpuUtilization , Throughput;
    
    printf("Enter the number of processes : ");
    scanf("%d" , &n);
    
    struct Process p[n];
    
    for(int i = 0 ; i < n ; i++){
        
        p[i].pid = i;
        printf("Enter the Arrival Time and Burst time for process = %d : ",i);
        scanf("%d%d", &p[i].at , &p[i].bt);
    }
    
    qsort((void*)p , n , sizeof(struct Process) , compare);
    
    for(int i = 0 ; i < n ; i++){
        
        // first time CPU milaiga jab process ko
        if(i == 0){
            p[i].st = p[i].at;
            p[i].ct = p[i].st + p[i].bt;
            p[i].rt = 0;
        }
        
        // CPU mila par context switch ke baad
        else if(p[i-1].ct < p[i].at){
            p[i].st = p[i].at;
            p[i].ct = p[i].st + p[i].bt;
            p[i].rt = 0;
            idealTime += p[i].st - p[i-1].ct;
        }
        
        // CPU mila par kise process ke baad
        else
        {
            p[i].st = p[i-1].ct;
            p[i].ct = p[i].st + p[i].bt;
            p[i].rt = p[i].st-p[i].at;
        }
        p[i].tat = p[i].ct-p[i].at;
        p[i].wt = p[i].tat-p[i].bt;
    }
    
    
    for(int i = 0 ; i <n ; i++){
        sumWT += p[i].wt;
        sumTat +=p[i].tat;
        sumrt += p[i].rt;
    }
    
    
    avgWT = sumWT/n;
    avgTat = sumTat/n;
    avgrt = sumrt/n;
    
    
    printf("Process\t\tat\tbt\tst\tct\trt\ttat\twt\n");
    
    for(int i = 0 ; i < n ; i++){
        printf("%d\t\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",p[i].pid , p[i].at , p[i].bt , p[i].st , p[i].ct , p[i].rt , p[i].tat , p[i].wt);
    }
    
     printf("Average Response Time =  %0.2f\nAverage TurnAround Time = %0.2f\nAverage Waiting Time = %0.2f\n" , avgrt , avgTat , avgWT);
    
    int totalTime = p[n-1].ct;

    cpuUtilization = ((float)(totalTime - idealTime) / totalTime )*100;
    Throughput = (float)n/(float)totalTime;

    printf("CPU Utilitzation - %0.2f \nThroughput - %0.2f\n" , cpuUtilization , Throughput);

}
