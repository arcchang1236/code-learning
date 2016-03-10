#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int main()
{
    double p, q, r, s, t, u;
    while(scanf("%lf%lf%lf%lf%lf%lf",&p, &q, &r, &s, &t, &u) != EOF)
    {
        double L = 0;
        double U = 1;
        int flag = 0;
        while(U - L > pow(10,-10))
        {
            double x = (L + U) / 2;
            double mid = p*exp(-1*x) + q*sin(x) + r*cos(x) + s*tan(x) + t*x*x + u;
            double up = p*exp(-1*U) + q*sin(U) + r*cos(U) + s*tan(U) + t*U*U + u;
            double low = p*exp(-1*L) + q*sin(L) + r*cos(L) + s*tan(L) + t*L*L + u;
            if(up*low > 0){
                printf("No solution\n");
                flag = 1;
                break;
            } else if(up*low == 0){
                if(up == 0){
                    printf("%.4lf\n", U);
                    flag =1;
                    break;
                } else{
                    printf("%.4lf\n", L);
                    flag =1;
                    break;
                }
            } else {
                if(mid == 0){
                    printf("%.4lf\n", x);
                    flag = 1;
                    break;
                } else{
                    if(mid*up < 0){
                        L = x;
                    } else if(mid*low < 0){
                        U = x;
                    }
                }
            }
        }
        if(!flag)
            printf("%.4lf\n", U);
    }

    return 0;
}
