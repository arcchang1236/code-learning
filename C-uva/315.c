#include <stdio.h>
#include <stdlib.h>

int degree[100];
int adj[100];
int node[10000];
int tree[100];
int ans;

void DFS(int v)
{
    int i;
    tree[v] = 1;
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
    int N;
    int first, two;
    char space;
    while(scanf("%d", &N) && N)
    {
        for(i = 0; i < 100; i++){
            degree[i] = 0;
            adj[i] = 0;
        }
        for(i = 0; i < 10000; i++){
            node[i] = 0;
        }

        while(scanf("%d", &first) && first)
        {
            while(scanf("%d%c", &two, &space) == 2)
            {
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

                if(repeat == 0){
                    int index = adj[first];
                    for(j = 9998; j >= index ; j--){
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
                    for(j = 9998; j >= index ; j--){
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

                if(space == '\n'){
                    break;
                }
            }
        }

        ans = 0;
        int count = 0;
        for(i = 0; i < N; i++) {
            for(j = 0; j < N; j++){
                tree[j]=0;
            }
            tree[i] = 2;
            for(j = 0; j < N; j++) {
                if (tree[j]==0){
                    DFS(j);
                    count++;
                }
            }
            if (count > 1){
                ans++;
            }
            count = 0;
        }
        printf("%d\n", ans);
    }
    return 0;
}
