#include <stdio.h>
#include <stdlib.h>
#define MAX 3010
int record[1001][MAX] = {0};
int main()
{
    int N;
    int i, j;
    int num;
    int carry;
    int ans[MAX] = {0};
    ans[0] = 1;
    int index = 2;
    for(i = 2; i < 1001; i++){
        carry = 0;
        for(j = 0; j < MAX; j = j + 4){
            num = (1*ans[j] + 10*ans[j+1] + 100*ans[j+2] + 1000*ans[j+3])
                       *i + carry;
            carry = num / 10000;
            ans[j] = num % 10;
            num /= 10;
            ans[j+1] = num % 10;
            num /= 10;
            ans[j+2] = num % 10;
            num /= 10;
            ans[j+3] = num % 10;
        }
        for(j = 0; j < MAX; j++){
            record[index][j] = ans[j];
        }
        index++;
    }
    while(scanf("%d", &N) != EOF)
    {
        printf("%d!\n",N);
        int flag = 0;
        if(N==0){
            printf("1\n");
        } else if(N==1){
            printf("1\n");
        } else{
            for(i = MAX-1; i >= 0; i --){
                if(flag){
                    printf("%d", record[N][i]);
                }
                if(record[N][i]!=0 && flag==0){
                    printf("%d", record[N][i]);
                    flag = 1;
                }
            }
            printf("\n");
        }
    }
    return 0;
}
