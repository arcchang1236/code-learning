#include <stdio.h>
#include <stdlib.h>

int degree[30000];
int adj[30000];
int node[60000];
int tree[30000];
int ans;

void DFS(int v)
{
    int i;
    tree[v] = 1;
    ans++;
    for(i = adj[v]; i < adj[v+1]; i++){
        if(tree[node[i]-1] == 0){
            DFS(node[i]-1);
        }
    }
    tree[v] = 2;
}

int main()
{
    int i, j;
    int testcase;
    scanf("%d", &testcase);
    int first, two;
    while(testcase--)
    {
        for(i = 0; i < 30000; i++){
            degree[i] = 0;
            adj[i] = 0;
            tree[i] = 0;
        }
        for(i = 0; i < 60000; i++){
            node[i] = 0;
        }
        int N, M;
        scanf("%d%d", &N, &M);
        for(i = 0; i < M; i++){
            scanf("%d%d", &first, &two);
            int repeat = 0;
            for(j = adj[first-1]; j < adj[first]; j++){
                if(node[j] == two){
                    repeat = 1;
                }
            }
            for(j = adj[two-1]; j < adj[two]; j++){
                if(node[j] == first){
                    repeat = 1;
                }
            }
            if(repeat == 1){
                continue;
            }

            int index = adj[first];
            for(j = 59998; j >= index ; j--){
                node[j+1] = node[j];
            }
            node[index] = two;
            degree[first-1]++;
            int add = 0;
            for(j = 0; j <= N ; j++){
                adj[j] = add;
                add += degree[j];
            }

            index = adj[two];
            for(j = 59998; j >= index ; j--){
                node[j+1] = node[j];
            }
            node[index] = first;
            degree[two-1]++;
            add = 0;
            for(j = 0; j <= N ; j++){
                adj[j] = add;
                add += degree[j];
            }
        }

        int max = 0;
        for(i = 0; i < N; i++){
            ans = 0;
            if(degree[i] == 0){
                tree[i] = 2;
            }
            if(tree[i] == 0){
                DFS(i);
                if(ans > max){
                    max = ans;
                }
            }
        }
        printf("%d\n", max);
    }
    return 0;
}
