#include <stdio.h>
#include <stdlib.h>

int i, j, k;
int F, E, A, B;
int X[105];
int Y[105];
int A_star[105][105];
int elev_start, elev_end;

int main()
{
    int testcases;
    scanf("%d", &testcases);
    int flag;
    int n;
    while(testcases--)
    {
        for(i = 0; i <= E; i++){
            for(j = 0; j <= E; j++){
                A_star[i][j] = 0;
            }
        }

        scanf("%d%d%d%d", &F, &E, &A, &B);
        for(i = 1; i <= E; i++){
            scanf("%d%d", &X[i], &Y[i]);
        }

        int judge;
        for(i = 1; i <= E; i++){
            for(j = 1; j <= E; j++){
                flag = 0;
                for(n = 0; n <= X[i]; n++){
                    if((X[j]*n + Y[j])%X[i] == Y[i] && (X[j]*n + Y[j]) <= F){
                        flag = 1;
                        break;
                    }
                }
                if(flag == 1){
                    A_star[i][j] = 1;
                    A_star[j][i] = 1;
                }
            }
        }

        for(k = 1; k <= E; k++)
            for(i = 1; i <= E; i++)
                for(j = 1; j <= E; j++)
                    if(A_star[i][k] && A_star[k][j])
                        A_star[i][j] = 1;

        elev_start = -1;
        elev_end = -1;
        for(i = 1; i <= E; i++){
            if(A - Y[i] == 0){
                elev_start = i;
                break;
            } else if(A - Y[i] > X[i]){
                if((A - Y[i]) % X[i] == 0){
                    elev_start = i;
                    break;
                }
            }
        }
        for(i = 1; i <= E; i++){
            if(B - Y[i] == 0){
                elev_end = i;
                break;
            } else if(B - Y[i] > X[i]){
                if((B - Y[i]) % X[i] == 0){
                    elev_end = i;
                    break;
                }
            }
        }

        if(elev_start == -1 || elev_end == -1){
            printf("The furniture cannot be moved.\n");
        } else{
            if(A_star[elev_start][elev_end] == 1 && A_star[elev_end][elev_start] == 1)
                printf("It is possible to move the furniture.\n");
            else
                printf("The furniture cannot be moved.\n");
        }
    }
    return 0;
}
