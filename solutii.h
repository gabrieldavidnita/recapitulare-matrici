#ifndef SOLUTII_H_INCLUDED
#define SOLUTII_H_INCLUDED
#include "functii.h"

//n=5 ,m=4
 // 0    1     2     3

//  444    3     2      1
//   2    444    7      2
//   5     4    333     3
//   7     8    999     4

// i  i<n    j    j<m      treicifre==1  i  j   i  j
// 0  0<5    0    0<4           da      -1 -1   0  0
// 0  0<4    0    0<3
void solutied()
{
    int v[100][100], n,m;
    citireMatrice(v,n,m);
    for(int i =0; i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            if(treiCifre(v[i][j])==1)
            {
                stergereLinie(v,n,m,i);
                stergereColoana(v,n,m,j);
                i--;
                j--;
            }

        }
    }
    afisareMatrice(v,n,m);
}

#endif // SOLUTII_H_INCLUDED
