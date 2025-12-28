#include <stdio.h>
#include <string.h>
int main() {

    char *weekdays[] = {
        "Monday", "Tuesday", "Wednesday", "Thursday", 
        "Friday", "Saturday", "Sunday"
    };
    char input[20];
    int found = 0;
    scanf("%s", input);
    for(int i = 0; i < 7; i++) {
        if(strcmp(input, weekdays[i]) == 0) {
            printf("%d\n",i + 1);
            found = 1;
            break;
        }
    }
    if(!found) {
        printf("ERROR\n");
    }
    return 0;
}