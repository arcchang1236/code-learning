#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
    int dir[4][4];
} node;

typedef struct queue{
    int x;
    int y;
    int opcode;
} queue;

node matrix[10][10];
queue imp[20000];
int visit[10][10][4][4];
int q_list[20000];
char name[50];
int Next[4][2];

int sta_x, sta_y, end_x, end_y;
char sta_way;
int find, find_num;

int check (int x, int y, int in, int d) {
    if (x>0&&x<10&&y>0&&y<10 && matrix[y][x].dir[in][d]==1) {
        if (visit[y][x][in][d]==0)
            return 1;
        return 0;
    }
    return 0;
}

void BFS()
{
    int i;
    int q_num = 1;
    int now = 0;
    while(now<q_num){
        int nx, ny, nd;
        nx = imp[now].x;
        ny = imp[now].y;
        nd = imp[now].opcode;
        int nxx = nx + Next[nd][1];
        int nyy = ny + Next[nd][0];
        if(nxx == end_x && nyy == end_y){
            find = 1;
            find_num = now;
            break;
        }
        for(i = 0; i < 4; i++){
            if(check(nxx, nyy, nd, i) == 1){
                if(matrix[nyy][nxx].dir[nd][i] == 1){
                    visit[nyy][nxx][nd][i] = 1;
                    q_list[q_num] = now;
                    imp[q_num].x = nxx;
                    imp[q_num].y = nyy;
                    imp[q_num].opcode = i;
                    q_num++;
                }
            }
        }
        now++;
    }
    return;
}

int change(char a)
{
    int ans;
    if(a == 'N'){
        ans = 0;
    } else if(a == 'E'){
        ans = 1;
    } else if(a == 'S'){
        ans = 2;
    } else{
        ans = 3;
    }
    return ans;
}

int FLR(int a, char c)
{
    int ans;
    if(c == 'F'){
        ans = a;
    } else if(c == 'L'){
        ans = (a+3) % 4;
    } else{
        ans = (a+1) % 4;
    }
    return ans;
}

int main()
{
    Next[0][0] = -1; Next[0][1] = 0;
    Next[1][0] = 0; Next[1][1] = 1;
    Next[2][0] = 1; Next[2][1] = 0;
    Next[3][0] = 0; Next[3][1] = -1;

    int i;
    int x, y;
    char in[10];
    int now;
    while(1)
    {
        scanf("%s", name);
        if(!strcmp(name, "END"))    break;

        memset(matrix, 0, sizeof(matrix));
        memset(visit, 0, sizeof(visit));
        memset(q_list, -1, sizeof(q_list));

        scanf("%d %d %c %d %d", &sta_y, &sta_x, &sta_way, &end_y, &end_x);

        while(1)
        {
            scanf("%d", &x);
            if(x==0)    break;
            scanf("%d", &y);
            while(1)
            {
                scanf("%s", in);
                if(!strcmp(in, "*"))   break;
                int tmp = change(in[0]);
                now = 1;
                while(1)
                {
                    if(now == strlen(in))   break;
                    matrix[x][y].dir[tmp][FLR(tmp, in[now])] = 1;
                    now++;
                }
            }
        }

        imp[0].x = sta_x;
        imp[0].y = sta_y;
        imp[0].opcode = change(sta_way);
        find = 0;
        find_num = -1;

        BFS();

        printf("%s\n", name);
        if(find == 1){
            int now2 = 0;
            int Temp[500];
            int st = find_num;
            while(st != -1){
                Temp[now2] = st;
                st = q_list[st];
                now2++;
            }

            int Ans[500];
            for(i = now2-1; i >= 0; i--){
                Ans[now2-1-i] = Temp[i];
            }

            printf("  ");
            for(i = 0; i < now2; i++){
                printf("(%d,%d)", imp[Ans[i]].y, imp[Ans[i]].x);
                if(!((i+1)%10))     printf("\n  ");
                else    printf(" ");
            }
            printf("(%d,%d)\n", end_y, end_x);
        } else{
            printf("  No Solution Possible\n");
        }
    }
    return 0;
}
