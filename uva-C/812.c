#include <stdio.h>
#include <stdlib.h>
# define MAX 1001
int main()
{
    int i, j, k;
    int price[50][20];
    int profit[50][20];
    int prob[51][MAX];
    int maxProfit[50];
    int boxes[50];
    int w;
    int num = 1;
    while(scanf("%d", &w) && w)
    {
        for(i = 0; i< w; i++){
            scanf("%d", &boxes[i]);
            maxProfit[i] = -100000000;
            for(j = 0; j < boxes[i]; j++){
                scanf("%d", &price[i][j]);
                profit[i][j] = 10 - price[i][j];
                if(j != 0){
                    profit[i][j] += profit[i][j-1];
                }
                if(profit[i][j] > maxProfit[i]){
                    maxProfit[i] = profit[i][j];
                }
            }
        }

        memset(prob, 0, sizeof(prob));
        prob[0][0]=1;
        int ans = 0;
        for(i = 0; i < w; i++) {
            if(maxProfit[i] >= 0) {
                ans += maxProfit[i];
                for(j = 0; j < boxes[i]; j++){
                    if(maxProfit[i] == profit[i][j]){
                        for(k = 0; k < MAX; k++){
                             if(prob[i][k]){
                                prob[i+1][k+j+1]=1;
                             }
                        }
                    }
                }
                if(maxProfit[i]==0){
                    for(k = 0; k < MAX; k++){
                        if(prob[i][k]){
                            prob[i+1][k] = 1;
                        }
                    }
                }
            } else{
                for(k = 0; k < MAX;k++){
                    prob[i+1][k] = prob[i][k];
                }
            }
        }
        if(num != 1) printf("\n");
        printf("Workyards %d\n", num);
        printf("Maximum profit is %d.\n", ans);
        printf("Number of pruls to buy:");
        if(ans == 0) printf(" 0");
        int ic = 0;
        for(i = 1; i < MAX && ic < 10; i++){
            if(prob[w][i]) {
                printf(" %d", i);
                ic++;
            }
        }
        printf("\n");
        num ++;
    }




    return 0;
}
