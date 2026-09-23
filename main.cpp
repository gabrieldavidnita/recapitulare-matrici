
#include "functii.h"

int main()
{
int a[100][100]={{11,32,12,23,53},
                 {52,87,97,53,75},
                 {22,12,64,98,67},
                 {32,25,64,76,54},
                 {45,75,35,23,53} };
    int n=5;
    int m=5;
    int ceva = sumaChenar(a,n,m,0);
    cout<<ceva;
}
