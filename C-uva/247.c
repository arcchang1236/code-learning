#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int matrix[30][30];
char namelist[30][30];
int flag[30];

int main()
{
    int i, j, k;
    int users, times;
    char first[30];
    char last[30];
    int f_num, l_num;
    int count = 1;
    while(scanf("%d %d", &users, &times) && users)
    {
        for(i = 0; i < 30; i++){
            flag[i] = 1;
            for(j = 0; j < 30; j++){
                matrix[i][j] = 10000;
                namelist[i][j] = '0';
            }
            matrix[i][i] = 0;
        }

        int now = 0;
        while(times--)
        {
            scanf("%s", first);
            scanf("%s", last);
            int judge = 0;
            for(i = 0; i < now; i++){
                if(!strcmp(first, namelist[i])){
                    f_num = i;
                    judge = 1;
                    break;
                }
            }
            if(!judge){
                strcpy(namelist[now] ,first);
                f_num = now;
                now++;
            }
            judge = 0;
            for(i = 0; i < now; i++){
                if(!strcmp(last, namelist[i])){
                    l_num = i;
                    judge = 1;
                    break;
                }
            }
            if(!judge){
                strcpy(namelist[now], last);
                l_num = now;
                now++;
            }
            matrix[f_num][l_num] = 1;
        }


        for(k = 0; k < users; k++){
            for(i = 0; i < users; i++){
                for(j = 0; j < users; j++){
                    if(matrix[i][j] > matrix[i][k]+matrix[k][j])
                        matrix[i][j] = matrix[i][k] + matrix[k][j];
                }
            }
        }
        if (count==1)
            printf("Calling circles for data set %d:\n", count++);
        else
            printf("\nCalling circles for data set %d:\n", count++);
        for(i = 0; i < users; i++){
            if(flag[i] == 1){
                flag[i] = 0;
                printf("%s", namelist[i]);
                for(j = 0; j < users; j++){
                    if(matrix[i][j] < 10000 && matrix[j][i] < 10000 && flag[j] == 1){
                        flag[j] = 0;
                        printf(", %s", namelist[j]);
                    }
                }
                printf("\n");
            }
        }
    }

    return 0;
}
