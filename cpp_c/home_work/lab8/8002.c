#include <stdio.h>

void find_top_k_index(int *interest,int n,int k,int *top_k_index);

int main() 
{
    int n,k;
    if(scanf("%d",&n)!=1) 
    return 0;
    if(scanf("%d",&k)!=1) 
    return 0;
    int interest[100];
    for(int i=0;i<n;i++) 
    {
        scanf("%d",&interest[i]);
    }
    int top_k_index[100];
    find_top_k_index(interest,n,k,top_k_index);
    for(int i=0;i<k;i++) 
    {
        if(i>0) printf(" ");
        printf("%d",top_k_index[i]);
    }
    printf("\n");
    return 0;
}

void find_top_k_index(int *interest,int n,int k,int *top_k_index) 
{
    int temp_val[100],temp_idx[100];
    for(int i=0;i<n;i++) 
    {
        temp_val[i]=interest[i];
        temp_idx[i]=i+1;
    }
    for(int i=0;i<k;i++) 
    {
        int max_pos=i;
        for(int j=i+1;j<n;j++) 
        {
            if(temp_val[j]>temp_val[max_pos]) 
            {
                max_pos=j;
            }
        }
        int v_tmp=temp_val[i];
        temp_val[i]=temp_val[max_pos];
        temp_val[max_pos]=v_tmp;
        int i_tmp=temp_idx[i];
        temp_idx[i]=temp_idx[max_pos];
        temp_idx[max_pos]=i_tmp;
        top_k_index[i]=temp_idx[i];
    }
}