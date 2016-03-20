#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX 32000
int plist[MAX];
int store[10000][MAX];
int primetable()
{
    int i, j;
    int num = 0;
    char is_prime[MAX+1];
    memset(is_prime, 1, MAX+1);
    for(i = 2; i <= MAX; i++){
        if(is_prime[i] == 1){
            plist[num] = i;
            num++;
            for(j = i*2; j <= MAX; j = j+i){
                is_prime[j] = 0;
            }
        }
    }
    return num;
}
int main()
{
    int z = primetable();
    int i, j;
    int T;
    scanf("%d", &T);
    while(T--)
    {
        memset(store, 0, MAX);
        int L, U;
        scanf("%d%d", &L, &U);
        int length = U-L+1;
        int now = 0;
        while(now < z)
        {
            int tmp = L / plist[now];
            if(L%plist[now] != 0)
                tmp++;
            i = tmp*plist[now];
            while(i<=U)
            {
                int x = i;
                while(1)
                {
                    if(x%plist[now] || (x%plist[now]==0 && x/plist[now]==0))
                        break;
                    store[i-L][now]++;
                    x /= plist[now];
                }
                tmp++;
                i = tmp*plist[now];
            }
            now++;
        }
        int ans = L;
        int max_num = 1;
        int max = 1;
        int N = U-L+1;
        for(i = 0; i < N; i++){
            max_num = 1;
            for(j = 0; j < MAX; j++){
                if(store[i][j]!=0){
                    max_num *= (store[i][j]+1);
                    store[i][j] = 0;
                }
                if(i == 0)
                    max = max_num;
            }
            if(i!=0 && max_num > max){
                 max = max_num;
                 ans = L+i;
            }
        }

        printf("Between %d and %d, %d has a maximum of %d divisors.\n", L, U, ans, max);
    }
    return 0;
}
