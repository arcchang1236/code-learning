#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXN 6

int n, m;
int pat[3][3];
int i, j;
int path[MAXN*MAXN], mat[MAXN], minx;

int checkRow(int r){
    if(mat[r] != (1<<m)-1) return 0;
    return 1;
}

int checkAll(){
    if(n>1 && checkRow(n-1) && checkRow(n-2) || n==1 && checkRow(0))
        return 1;
    return 0;
}

void cover(int r,int c){
    for(i=r-1; i<=r+1; ++i){
        if(i<0 || i>=n) continue;
        for(j=c-1; j<=c+1; ++j){
            if(j<0 || j>=m) continue;
            if(pat[i-r+1][j-c+1])
                mat[i] ^= (1<<j);
        }
    }
}

int dfs(int cur, int pathNum){
    int r=cur/m;
    int c=cur-r*m;
    if(r-2>=0 && !checkRow(r-2))
        return 0 ;
    if(r>=n-2 || cur==n*m){
        if(checkAll()){
            minx = pathNum;
            return 1;
        }
        if(cur==n*m) return 0;

    }
    if(dfs(cur+1, pathNum)) return 1;
    cover(r, c);
    path[pathNum] = cur+1;
    if(dfs(cur+1, pathNum+1)) return 1;
    cover(r, c);
    return 0;
}

int main(){
    int testcase = 1;
    char input[10];
    while(~scanf("%d%d%*c",&n,&m) && n+m) {
        memset(mat,0, sizeof(mat));
        scanf("%s", input);
        for(i = 0; i < 3; i++){
            if(input[i] == '*'){
                pat[0][i] = 1;
            } else{
                pat[0][i] = 0;
            }
        }
        scanf("%s", input);
        for(i = 0; i < 3; i++){
            if(input[i] == '*'){
                pat[1][i] = 1;
            } else{
                pat[1][i] = 0;
            }
        }
        scanf("%s", input);
        for(i = 0; i < 3; i++){
            if(input[i] == '*'){
                pat[2][i] = 1;
            } else{
                pat[2][i] = 0;
            }
        }

        /*for(i=0; i<3; ++i){
            for(j=0; j<3; ++j){
                printf("%d", pat[i][j]);
            } printf("\n");
        }*/

        printf("Case #%d\n", testcase);
        testcase++;
        int judge = dfs(0,0);

        if(judge == 1){
            printf("%d", path[0]);
            for(i=1; i<minx; ++i)
                printf(" %d", path[i]);
            printf("\n");
        }else
            printf("Impossible.\n");
    }
    return 0;
}
