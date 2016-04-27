#include <stdio.h>
#include <stdlib.h>

typedef struct edge
{
    int first;
    int last;
    int value;
} edge;

edge in[30000];
int degree[45];
int deleted[30000];
int answer[30000];
int adj[45];
int temp[45];
int num;

int comp(const void *a, const void *b)
{
    edge c = *(edge*)a;
    edge d = *(edge*)b;
    if(c.first<d.first)
        return -1 ;
    else if (c.first == d.first){
        if(c.value > d.value)
            return 1 ;
        else
            return -1 ;
    }
    else return 1;
}

void DFS(int v)
{
    int i;
    int tmp = adj[v];
    for(i = 0; i < degree[v]; i++){
        if(deleted[in[i+tmp].value] == 0)
        {
            deleted[in[i+tmp].value] = 1 ;
            DFS(in[i+tmp].last) ;
            answer[num++] = in[i+tmp].value;
        }
    }
}

int main()
{
    int i;
    int x, y , z;
    int now;
    int solution;
    int begin;

    while(scanf("%d%d", &x, &y) && x && y)
    {
        now = 0;
        num = 0;
        solution = 1;
        memset(adj, 0, sizeof(adj));
        memset(temp, 0, sizeof(temp));
        memset(deleted, 0, sizeof(deleted));
        memset(degree, 0, sizeof(degree));
        memset(answer, 0, sizeof(answer));
        if(x < y)
            begin = x;
        else
            begin = y;

        scanf("%d", &z);
        degree[x]++;
        degree[y]++;
        in[now].first = x;
        in[now].last = y;
        in[now].value = z;
        now++;
        in[now].first = y;
        in[now].last = x;
        in[now].value = z;
        now++;

        while(scanf("%d%d", &x, &y) && x && y)
        {
            scanf("%d", &z);
            degree[x]++;
            degree[y]++;
            in[now].first = x;
            in[now].last = y;
            in[now].value = z;
            now++;
            in[now].first = y;
            in[now].last = x;
            in[now].value = z;
            now++;
        }
        qsort(in, now, sizeof(edge), comp);

        /*int i;
        for(i=0; i < now; i++){
            printf("%d %d %d!\n",in[i].first, in[i].last, in[i].value);
        }*/

        for(i = 0 ; i <= now; i++){
            if(degree[in[i].first]%2 != 0){
                printf("Round trip does not exist.\n\n" );
                solution = 0;
                break;
            }
        }

        adj[1] = 0;
        for(i = 2; i < 45; i++){
            adj[i] = adj[i-1] + degree[i-1];
        }

       /*for(i=0; i <45; i++){
            printf("%d ", adj[i]);
        }printf("!!!\n");*/

        if(solution == 1){
            DFS(begin);
            for(i = num-1; i >= 0; i --){
                if(i == 0)
                    printf("%d\n", answer[i]);
                else
                    printf("%d ", answer[i]);
            }
            printf("\n");
        }
    }
    return 0;
}
