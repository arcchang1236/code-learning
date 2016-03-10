#include <stdio.h>
#include <stdlib.h>
int main()
{
    int i, j;
    int N;
    scanf("%d", &N);
    int testCase = 0;
    while(testCase < N)
    {
        int Book;
        int Man;
        scanf("%d%d", &Book, &Man);
        int Page[510] = {0};
        long long int L = 0, U = 0;
        /**
            L = min(Page);
            U = sum(Page);
        **/
        for(i = 0; i < Book; i++){
            scanf("%d", &Page[i]);
            if(Page[i] > L){
                L = Page[i];
            }
            U += Page[i];
        }
        while(L<U)
        {
            long long int M = (L+U) / 2;
            int part = 1;
            long long int sum = 0;
            for(i = 0; i < Book; i++){
                if(sum + Page[i] > M){
                    part++;
                    sum = 0;
                }
                sum += Page[i];
            }
            if(part > Man)  L = M + 1;
            else U = M;
        }
        long long summ = 0;
        int slash[510] = {0};
        int ans[510][510];
        /** Start from the last because the latter should be more books. **/
        for(i = Book - 1, j = Man -1; i >= 0; i--){
            /** j>i: every Man must have one book. **/
            if(j>i || summ+Page[i] > U){
                j--;
                summ = 0;
            }
            summ += Page[i];
            ans[j][slash[j]++] = Page[i];
        }
        for(i = 0; i < Man; i++){
            for(j = slash[i] - 1; j >= 0; j--){
                if(i != 0 || j != slash[0]-1){
                    printf(" ");
                }
                printf("%d", ans[i][j]);
            }
            if(i != Man-1)  printf(" /");
        }
        printf("\n");
        testCase++;
    }
    return 0;
}
