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
    stergeExact3CifreEgale(v,n,m);
    afisareMatrice(v,n,m);
}

 void solutiej()
 {
     int v[100][100] , n,m;
     int nr=0;
     int poz=-1;
     citireMatrice(v,n,m);

     for(int j=0; j<m && poz==-1 ; j++)
    {
        int exista=0;
         for(int i =0; i<n;i++)
         {
             if(isNumarPp(v[i][j])==1)
             {
                 exista=1;
             }
         }

     if(exista==1)
     {
         nr++;
         if(nr==2)
         {
             poz=j;
         }
     }
    }
     if(poz==-1)
     {
         cout<<"Nu exista";
     }else
     {
         inserareColoana(v,n,m,poz+1);
         for(int i=0;i<n;i++)
         {
             v[i][poz+1]=v[i][poz];
         }
         rastoarnaColoana(v,n,m,poz+1);
         afisareMatrice(v,n,m);
     }


 }


void solutiep()
{
    int v[100][100],n,m;
    citireMatrice(v,n,m);
    int poz=-1;
    for(int i=0; i<n-1; i++)
    {
        if(isLinieCrescatoare(v,m,i)==1)
        {
           poz=i;
        }
    }
    if(poz!=-1)
    {
        interschimbareLinii(v,m,poz,poz+1);
    }else
    {
        sortareCrescLinie(v,m,0);
        interschimbareLinii(v,m,0,n-1);
    }
    afisareMatrice(v,n,m);
}

#endif // SOLUTII_H_INCLUDED
