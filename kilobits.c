#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
        float bytes;
        float request_time;

        printf("Enter Bytes Sent: ");
        scanf("%f",&bytes);

        printf("Enter Request Time (in sec): ");
        scanf("%f",&request_time);

        float bits = bytes*8;
        float kilobits = bits*0.001;

        float kbps = kilobits / request_time;

        char output[100] = "curl -I http:";
        strcat(output,"/");
        strcat(output,"/");
        strcat(output,"localhost:81?");
        char buf[50];
        printf("\n");
        printf("Enter into terminal : ");
        if(gcvt(kbps, 4, buf)!=NULL){
                strcat(output,buf);
                strcat(output,"\n");
                printf("%s",output);
        }
        else{
                strcat(output,"NULL");
                strcat(output,"\n");
                printf("%s",output);
        }
        return 0;
}
