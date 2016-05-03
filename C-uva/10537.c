#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define BIGNUM 1000000000000

long long matrix[53][53];
int N[53];
long long d[53];
int Q[53];

long long p;
int staNum, endNum;

char toChar(int in)
{
    if(in <= 25)
        return ('a' + in);
    else
        return ('A' + in - 26);
}

int Min_d()
{
    int i;
    long long minimum = BIGNUM;
    int ans = -1;
    for(i = 0; i < 52; i++){
        if(d[i] < minimum && Q[i] == 1){
            minimum = d[i];
            ans = i;
        }
    }
    return ans;
}

void Dijkstra()
{
    int i, v;
    d[endNum] = p;
    long long tmp;
    for(i = 0; i < 52; i++){
        int u = Min_d();
        Q[u] = 0;
        if(u == -1)
            break;
        for(v = 0; v < 52; v++){
            if(matrix[u][v] != 0){
                if(u <= 25)
                    tmp = d[u] + 1;
                else{
                    long long pmax = BIGNUM, pmin = -1;
                    long long temp, temp_ans;
                    while(pmax-1>pmin)
                    {
                       temp = (pmax+pmin) / 2;
                       temp_ans = temp - (temp+19)/20;
                       if(temp_ans < d[u])
                            pmin = temp;
                       else
                            pmax = temp;
                    }
                    tmp = pmax;
                }

                if(d[v] == tmp && (toChar(N[v]) > toChar(u))){
                    N[v] = u;
                } else if(d[v] > tmp){
                    d[v] = tmp;
                    N[v] = u;
                }
            }
        }
    }
}

int toInt(char in)
{
    if(islower(in))
        return (in - 'a');
    else
        return (in - 'A' + 26);
}

int main()
{
    int i, j;
    int roads;
    char fir, la;
    int now = 1;
    while(1)
    {
        for(i = 0; i < 53; i++){
            N[i] = -1;
            d[i] = BIGNUM;
            Q[i] = 0;
            for(j = 0; j < 53; j++){
                matrix[i][j] = 0;
            }
        }

        scanf("%d", &roads);
        if(roads==-1)
            break;

        while(roads--)
        {
            scanf(" %c %c", &fir, &la);
            Q[toInt(fir)] = 1;
            Q[toInt(la)] = 1;
            matrix[toInt(fir)][toInt(la)] = 1;
            matrix[toInt(la)][toInt(fir)] = 1;
        }

        char start, end;
        scanf("%lld %c %c", &p, &start, &end);
        staNum = toInt(start);
        endNum = toInt(end);
        Dijkstra();

        printf("Case %d:\n", now);
		printf("%lld\n", d[staNum]);
		printf("%c", toChar(staNum));
		while(staNum != endNum)
        {
			staNum = N[staNum];
			printf("-%c", toChar(staNum));
		}
		printf("\n");
        now++;
    }
    return 0;
}
