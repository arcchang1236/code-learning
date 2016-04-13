#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define MAX 150000

typedef struct man {
    int id;
    int next;
} man;

int m[MAX];
char is_prime[MAX+1];
void primetable()
{
    int i, j;
    int num = 0;
    memset(is_prime, 1, MAX+1);
    for(i = 2; i <= MAX; i++){
        if(is_prime[i] == 1){
            m[num] = i;
            num++;
            for(j = i*2; j <= MAX; j = j+i){
                is_prime[j] = 0;
            }
        }
    }
}

int main()
{
    int i, j;
    primetable();
    int k = 0, x, tmp;
    man *z;
    while(scanf("%d",&k) && k)
    {
        z = (man*)malloc(k*sizeof(man));

        for(i=0;i<k;i++){
            z[i].id = i;
            z[i].next = i+1;
        }
        z[k-1].next = 0;
        i=0;
        j=0;
        for(k;k>1;k--){
            if(m[j]%k == 0) x=k;
            else x=m[j]%k;

            for(x;x>1;x--){
                tmp = i;
                i = z[i].next;
            }
            z[tmp].next = z[i].next;
            i = z[i].next;
            j++;
        }
        printf("%d\n",z[i].id+1);
    }
    return 0;
}
