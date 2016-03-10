#include <stdio.h>
#include <stdlib.h>

struct ADD{
    int a;
    int b;
    int sum;
};
int cmp(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}
int cmp2(const void *a, const void *b)
{
    struct ADD e1;
    struct ADD e2;
    e1 = *(struct ADD *)(a);
    e2 = *(struct ADD *)(b);
    if(e1.sum>e2.sum) return (1);
    else if(e1.sum==e2.sum) return (0);
    else return (-1);
}
struct ADD X[1000000];
int search(int v, int a, int b, int n)
{

	int M;
	int L = 0, U = n;
	int i;
	while(L <= U) {
		M = (L+U) / 2;
		if(X[M].sum > v)
			U = M-1;
		else if(X[M].sum < v)
			L = M+1;
		else {
			for(i = M; i <= U; i++) {
				if(X[i].sum != v)
					break;
				if(a != X[i].a && a != X[i].b
					&& b != X[i].a && b != X[i].b)
					return 1;
			}

			for(i = M-1; i >= L; i--) {
				if(X[i].sum != v)
					break;
				if(a != X[i].a && a != X[i].b
					&& b != X[i].a && b != X[i].b)
					return 1;
			}
			return 0;
		}
	}
	return 0;
}

int main()
{
    int i, j, k;
    int N;
    while(scanf("%d", &N) && N)
    {
        int input[1005] = {0};
        for(i = 0; i < N; i++){
            scanf("%d", &input[i]);
        }
        qsort(input, N, sizeof(int), cmp);

        int index = 0;
        for(i = 0; i < N; i++){
            for(j = i+1; j < N; j++){
                X[index].a = input[i];
                X[index].b = input[j];
                X[index].sum = input[i] + input[j];
                index++;
            }
        }
        qsort(X, index, sizeof(struct ADD), cmp2);

        int flag = 0;
        int max = -536870912*2;
        int test;
		for(i = N-1; i >= 0; i--)
		{
			if(flag)
                break;
			for(j = 0; j < N; j++)
			{
				if(flag)
					break;
				if(i == j)
					continue;
                test = search(input[i]-input[j], input[i], input[j], index-1);
				if(test == 1) {
					max = input[i];
					flag = 1;
				}
			}
		}
		if(flag == 0)
			printf("no solution\n");
		else
			printf("%d\n", max);
    }
    return 0;
}
