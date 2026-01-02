#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
void Spin(int howlong) {
    time_t t = time(NULL);
    while ((time(NULL) - t) < howlong); 
}
int main()
{
    int *p=malloc(sizeof(int));
    assert(p!=NULL);
    printf("(%d)memory address of p: %p\n",getpid(),(void*)p);
    *p=0;
    while(1)
    {
        Spin(1);
        *p=*p+1;
        printf("(%d)p:%d\n",getpid(),*p);
    }
    return 0;
}