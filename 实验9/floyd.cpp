int a[200][200];
#include <stdio.h>  
int main()  
{  
    int n, m, q, i, j, k, t1, t2, t3;  
  
    int inf = 99999999;//这里定义的正无穷  
  
    //读入n m q,n为顶点数，m为边的条数, q为查询数
    scanf("%d %d %d", &n, &m, &q);  
  
    //初始化矩阵  
    for (i = 1; i <= n; i++)  
        for(j = 1; j <= n; j++)  
            if(i == j)a[i][j] = 0;  
            else a[i][j] = inf;  
  
  
    //读入边  
    for(i = 1; i <= m; i++)  
    {  
        scanf("%d %d %d", &t1, &t2, &t3);  
        a[t1][t2] = t3;  
    }  
  
    //Floyd-Warshall算法核心代码  
    for(i = 1; i <= n; i++)  
        for(j = 1; j <= n; j++)  
            for(k = 1; k <= n; k++)  
                if(a[j][i] < inf && a[i][k] < inf && a[j][k] > a[j][i] + a[i][k])  
                    a[j][k] = a[j][i] + a[i][k];  
  
    //输出最终结果  
    for(i = 1; i <= q; i++){
        scanf("%d %d", &t1, &t2);
        if(a[t1][t2] < inf)
            printf("%d\n", a[t1][t2]);
        else
            printf("inf\n");
    }
    return 0;  
} 