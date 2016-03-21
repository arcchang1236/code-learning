#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define MAX 47000
long long int plist[MAX];
char is_prime[MAX+1];
int list[1000000];
int primetable()
{
    int i, j;
    int num = 0;
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
    int L, U;
    int i, j;
    while((scanf("%d%d", &L, &U)) != EOF)
    {
        memset(list, 0, MAX);
        if(L == 1){
            list[0] = 1;
        }
        int now = 0;
        long long int ii;
        while(now<z && plist[now]<=U)
        {
            long long int tmp = L/plist[now];
            if(L%plist[now] != 0)
                tmp++;
            ii = tmp*plist[now];
            while(ii<=U)
            {
                if(tmp!=1){
                    list[ii-L]=1;
                }
                tmp++;
                ii = tmp*plist[now];
            }
            now++;
        }
        int num1, num2;
        int distant_clos = -1;
        int distant_most = -1;
        int ans_clos1, ans_clos2;
        int ans_most1, ans_most2;
        int flag = 1;
        int cool = 1;
        for(i = 0; i < U-L+1; i++){
            if(list[i] == 0){
                if(flag){
                   num1 = L+i;
                   flag = 0;
                } else{
                    if(cool){
                        num2 = L+i;
                        ans_clos1 = num1;
                        ans_clos2 = num2;
                        ans_most1 = num1;
                        ans_most2 = num2;
                        distant_clos = num2 - num1;
                        distant_most = num2 - num1;
                        cool = 0;
                    } else{
                        num1 = num2;
                        num2 = L+i;
                        if(num2-num1<distant_clos){
                            distant_clos = num2 - num1;
                            ans_clos2 = num2;
                            ans_clos1 = num1;
                        }
                        else if(num2-num1>distant_most){
                            distant_most = num2 - num1;
                            ans_most2 = num2;
                            ans_most1 = num1;
                        }
                    }
                }

            }
        }
        if(distant_clos == -1 && distant_most == -1){
            printf("There are no adjacent primes.\n");
        } else{
            printf("%d,%d are closest, %d,%d are most distant.\n", ans_clos1, ans_clos2, ans_most1, ans_most2);
        }
    }
    return 0;
}

