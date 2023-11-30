#include<stdio.h>
#include<stdlib.h>

int main(){
    
    int head_pos, n;
    int TotalSeekTime = 0 , seekTime = 0;
    
    printf("Enter the head position:= ");
    scanf("%d" , &head_pos);
    printf("Enter the disk queues = ");
    scanf("%d" , &n);
    int q[n];
    printf("Enter the Disk Elements = ");
    for(int i = 0; i < n; i++){
        scanf("%d" ,&q[i]);
    }

    for(int i = 0; i < n ; i++)
    {
        seekTime = abs(head_pos - q[i]);
        head_pos = q[i];
        TotalSeekTime +=seekTime;
    }
    
    printf("Total Seek time is equal to:%d\n",TotalSeekTime);
    printf("Average Seek time:%.2f\n",(float)TotalSeekTime/n);    
}
