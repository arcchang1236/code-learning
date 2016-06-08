#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int m[6][6];
int ans[6][6] =
{
    {1, 1, 1, 1, 1},
    {0, 1, 1, 1, 1},
    {0, 0, 2, 1, 1},
    {0, 0, 0, 0, 1},
    {0, 0, 0, 0, 0}
};
int dx[]={-2, -2, -1, 1, -1, 1, 2, 2};
int dy[]={-1, 1, 2, 2, -2, -2, -1, 1};
int i, j;
int min;

void swap(int* a, int* b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

void BFS(int x, int y, int moves, int prev)
{
	int num = 0;
	int dir;
	int next_x, next_y;

	if (moves >= min)   return;
	for (i = 0; i < 5; i++){
        for (j = 0; j < 5; j++){
            if (m[i][j] != ans[i][j])
				num++;
        }
	}
	if (num == 0) {
		min = moves;
		return;
	} else if (num / 2 + moves >= min)
		return;

	for (dir = 0; dir < 8; dir++) {
		next_x = x + dx[dir];
		next_y = y + dy[dir];
		if (next_x < 0 || next_x >= 5 || next_y < 0 || next_y >= 5 || dir + prev == 7)
			continue;
		swap(&m[x][y], &m[next_x][next_y]);
		BFS(next_x, next_y, moves+1, dir);
		swap(&m[x][y], &m[next_x][next_y]);
	}
}

int main()
{
    int testcase;
    scanf("%d", &testcase);
    char c;
    int flag = 1;
    int x0, y0;
    while(testcase--)
    {
        min = 11;
        if(flag == 1){
            getchar();
            flag = 0;
        }

        for(i = 0; i < 5; i++){
            for(j = 0; j < 6; j++){
                c = getchar();
                if(c == '1'){
                    m[i][j] = 1;
                } else if(c == '0'){
                    m[i][j] = 0;
                } else{
                    m[i][j] = 2;
                }
            }
        }

        /*for(i = 0; i < 5; i++){
            for(j = 0; j < 6; j++){
                printf("%d", m[i][j]);
            } printf("\n");
        }*/

        for (i = 0; i < 5; i++){
            for (j = 0; j < 5; j++){
                if (m[i][j] == 2) {
                    x0 = i;
                    y0 = j;
                }
            }
        }

        BFS(x0, y0, 0, 8);

        if (min == 11)
			printf("Unsolvable in less than 11 move(s).\n");
		else
			printf("Solvable in %d move(s).\n", min);
    }
    return 0;
}
