#include <stdio.h>
int main()
{
    FILE *fp;
    fp=fopen("test.txt","w");
    if(fp==NULL)
    {
        printf("FOPEN ERROR");
        return -1;
    }
    fprintf(fp,"Hello World!\n");
    fclose(fp);
    fp=fopen("test.txt","r");
    char buffer[1001];
    while(fgets(buffer,1001,fp)!=NULL)
    {
        printf("%s",buffer);
    }
    fclose(fp);
    return 0;
}