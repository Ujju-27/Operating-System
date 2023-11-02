#include<stdio.h>


struct Process{
    int A , B , C; // resources
};


int main()
{
    int n , A , B , C;
    printf("Enter the Number of Process - ");
    scanf("%d" ,&n);

    struct Process allocated[n];
    struct Process require[n];
    struct Process Need[n];
    int isExecute[n];
    int ans[n];

    for(int i = 0 ; i < n ; i++)
        isExecute[i] = 0;
                
    for(int i = 0 ; i < n ; i++)
    {
        printf("Enter the Allocated and Required Resources of P%d - " , i);
	      scanf("%d%d%d" , &require[i].A , &require[i].B , &require[i].C);
        scanf("%d%d%d" , &allocated[i].A, &allocated[i].B, &allocated[i].C);

        Need[i].A = require[i].A - allocated[i].A;
        Need[i].B = require[i].B - allocated[i].B;
        Need[i].C = require[i].C - allocated[i].C;  
    }

    printf("Enter the Available Resources = ");
    scanf("%d%d%d" , &A,&B,&C);

    int idx = 0;
    for(int i = 0 ; i < n ; i++)
    {
        if(isExecute[i] == 0){
        for(int j = 0 ; j < n ; j++)
        {
            if(isExecute[j] == 0){
                if(Need[j].A <= A && Need[j].B <= B && Need[j].C <= C)
                {
                    A += allocated[j].A;
                    B += allocated[j].B;
                    C += allocated[j].C;

                    ans[idx] = j;
                    idx++;
                    isExecute[j] = 1;
                } 
            }
        }
        }
    }


    for(int i = 0 ; i < n ; i++)
    {
        if(isExecute[i] == 0)
        {
            printf("No Safe Sequence is Possible");
            return 0;
        }
    }

    printf("The Safe Sequence is - ");
    for(int i = 0 ; i < n-1 ; i++)
    {
        printf("P%d ->" , ans[i]);
    }
    printf("P%d" , ans[n-1]);
    return 0; 
}    
