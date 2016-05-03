#include <stdio.h>
#include <stdlib.h>

int matrix[500][500];
int d[500];
int Q[500];
int N;

void relax(int u, int v)
{
    if(d[v] > d[u] + matrix[u][v] || d[v] == -1){
        d[v] = d[u] + matrix[u][v];
    }

    /*int i; printf("%d %d!!\n", u, v);
    for(i = 0; i < 10; i++){
            printf("%d ", d[i]);
    } printf("\n");
    for(i = 0; i < 10; i++){
            printf("%d ", Q[i]);
    } printf("\n");*/
}

int Min_d()
{
    int i;
    int minimum = 5000000;
    int ans = 1;
    for(i = 2; i <= N; i++){
        if(d[i] != -1 && d[i] < minimum && Q[i] == 1){
            minimum = d[i];
            ans = i;
        }
    }
    return ans;
}

void Dijkstra()
{
    int i, v;
    for(i = 1; i <= N; i++){
        int u = Min_d();
        Q[u] = 0;
        for(v = 1; v <= N; v++){
            if(matrix[u][v] != 0)
                relax(u, v);
        }
    }

}

int main()
{
    int i, j;
    int M;
    int X, Y, Time;
    int testcase = 1;
    while(scanf("%d%d", &N, &M) && N)
    {
        for(i = 0; i < 500; i++){
            Q[i] = 1;
            d[i] = -1;
            for(j = 0; j < 500; j++){
                matrix[i][j] = 0;
            }
        }
        d[1] = 0;

        while(M--){
            scanf("%d%d%d", &X, &Y, &Time);
            matrix[X][Y] = Time;
            matrix[Y][X] = Time;
        }

        Dijkstra();

        double maximum = 0;
        int max_point = 1;
        for(i = 2; i <= N; i++){
            if(d[i] > maximum){
                maximum = d[i];
                max_point = i;
            }
        }

        double row_max = 0;
        double tmp = 0;
        int a, b;
        int row_front, row_back;
        for(i = 1; i <= N; i++){
            for(j = 1; j <= N; j++){
                if(matrix[i][j] != 0){
                    if(d[i] > d[j]){
                        a = d[j];
                        b = d[i];
                    }
                    else{
                        a = d[i];
                        b = d[j];
                    }
                    tmp = matrix[i][j] - (b-a);
                    tmp /= 2;
                    tmp += b;
                    if(tmp > row_max){
                        row_max = tmp;
                        if(i > j){
                            row_front = j;
                            row_back = i;
                        }
                        else{
                            row_front = i;
                            row_back = j;
                        }
                    }
                }
            }
        }

        printf("System #%d\n", testcase);
        if(maximum >= row_max){
            printf("The last domino falls after %.1f seconds, ", maximum);
            printf("at key domino %d.\n\n", max_point);
        }
        else{
            printf("The last domino falls after %.1f seconds, ", row_max);
            printf("between key dominoes %d and %d.\n\n", row_front, row_back);
        }

        testcase++;
    }
    return 0;
}
