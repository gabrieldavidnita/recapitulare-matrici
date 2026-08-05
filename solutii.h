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
    int v[100][100]={{222,32,12},{12,13,14},{22,12,64},{32,25,64}};
    int n=4;
    int m=3;
    stergeExact3CifreEgale(v,n,m);
    afisareMatrice(v,n,m);
}

 void solutiej()
 {
     int v[100][100]={{25,32,12},{64,81,14},{16,12,64},{32,25,64}};
     int n=4;
     int m=3;
     int nr=0;
     int poz=-1 ;
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
// 12,32,12
// 12,13,14
// 22,12,64
// 32,25,64

void solutiep()
{
    int v[100][100]={{12,32,12},{12,13,14},{22,12,64},{32,25,64}};
    int n=4;
    int m=3;

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

void solutiee()
{
    int v[100][100]={{11,32,12},{12,5,14},{22,12,64},{32,25,64}};
    int n=4;
    int m=3;
    int ct=0;
    int linie=-1;
    int coloana=-1;
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            if(isNumarPrim(v[i][j])==1)
            {
                ct++;
                if(ct==2)
                {
                    linie=i;
                    coloana=j;
                }
            }
        }
    }
    if(ct<2)
    {
        cout<<"Nu exista";
    }
    else
    {
        stergereLinie(v,n,m,linie);
        stergereColoana(v,n,m,coloana);
    }
    afisareMatrice(v,n,m);
}


void solutief()
{
    int a[100][100]={{11,32,12},{12,5,14},{22,12,64},{32,25,64}};
    int n=4;
    int m=3;
    int k=3;
    int poz=0;
    int minim=aparitiiCifraLinie(a,m,0,k);
    for(int i=1;i<n;i++)
    {
        int nr=aparitiiCifraLinie(a,m,i,k);
        if(nr<minim)
        {
            minim=nr;
            poz=i;
        }
    }
    stergereLinie(a,n,m,poz);
    afisareMatrice(a,n,m);
}

void solutieg()
{
    int a[100][100]={{11,33,12},{12,5,14},{22,12,64},{32,25,64}};
    int n=4;
    int m=3;
    int linie=0;
    int coloana=0;
    int frecventaMaxima;
    frecventaMaxima=frecventaElement(a,n,m,a[0][0]);
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            int f=frecventaElement(a,n,m,a[i][j]);
            if(f>frecventaMaxima)
            {
                frecventaMaxima=f;
                linie=i;
                coloana=j;
            }
        }
    }
    stergereLinie(a,n,m,linie);
    stergereColoana(a,n,m,coloana);
    afisareMatrice(a,n,m);
}

void solutieh()
{
    int a[100][100]={{11,32,12},{12,5,14},{22,12,64},{32,25,64}};
    int n=4;
    int m=3;
    int i=0;
    while(i<n)
    {
        if(linieCrescatoare(a,m,i)==0&&
                linieDescrescatoare(a,m,i)==0)
        {
            stergereLinie(a,n,m,i);
        }
        else
        {
            i++;
        }
    }
    afisareMatrice(a,n,m);
}

void solutiek()
{
    int a[100][100]={{22,42,12},{12,5,14},{22,12,64},{32,25,64}};
    int n=4;
    int m=3;
    int poz=0;
    int maxim;
    maxim=numarPareLinie(a,m,0);
    for(int i=1;i<n;i++)
    {
        int nr=numarPareLinie(a,m,i);

        if(nr>maxim)
        {
            maxim=nr;
            poz=i;
        }
    }
    inserareLinie(a,n,m,poz+1);
    for(int j=0;j<m;j++)
    {
        a[poz+1][j]=2*a[poz][j];
    }
    afisareMatrice(a,n,m);
}
void solutieL()
{
    int a[100][100]={{11,32,12},{52,87,97},{22,12,64},{32,25,64}};
    int n=4;
    int m=3;
    int cifraMaxima=cifraMaximaMatrice(a,n,m);
    int cifraMinima=cifraMinimaMatrice(a,n,m);
    int poz=0;
    int maxim=aparitiiCifraColoana(a,n,0,cifraMaxima);
    for(int j=1;j<m;j++)
    {
        int nr=aparitiiCifraColoana(a,n,j,cifraMaxima);
        if(nr>=maxim)
        {
            maxim=nr;
            poz=j;
        }
    }
    inserareColoana(a,n,m,poz);
    for(int i=0;i<n;i++)
    {
        a[i][poz]=cifraMinima;
    }
    afisareMatrice(a,n,m);
}

void solutieM()
{
    int a[100][100]={{11,32,12},{52,87,97},{22,12,64},{32,25,64}};
    int n=4;
    int m=3;
    int j=0;
    while(j<m)
    {
        if(coloanaValidaM(a,n,j)==1)
        {
            inserareColoana(a,n,m,j+1);

            for(int i=0;i<n;i++)
            {
                a[i][j+1]=cifraControl(a[i][j]);
            }

            j=j+2;
        }
        else
        {
            j++;
        }
    }
    afisareMatrice(a,n,m);
}

void solutieq()
{
    int a[100][100]={{11,32,12},{52,87,97},{22,12,64},{32,25,64}};
    int n=4;
    int m=3;
    int minim,maxim;
    int linieMinim=0;
    int linieMaxim=0;
    minim=a[0][0];
    maxim=a[0][0];
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            if(a[i][j]<minim)
            {
                minim=a[i][j];
                linieMinim=i;
            }

            if(a[i][j]>maxim)
            {
                maxim=a[i][j];
                linieMaxim=i;
            }
        }
    }
    if(linieMinim==linieMaxim)
    {
        cout<<"Nu putem interschimba!";
    }
    else
    {
        interschimbareLinii(a,m,linieMinim,linieMaxim);
        afisareMatrice(a,n,m);
    }
}

void solutieR()
{
    int a[100][100]={{11,32,12},{52,87,97},{22,12,64},{32,25,64}};
    int n=4;
    int m=3;
    for(int i=0;i<n-1;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            if(a[i][0]>a[j][0])
            {
                interschimbareLinii(a,m,i,j);
            }
        }
    }
    afisareMatrice(a,n,m);
}
#endif // SOLUTII_H_INCLUDED
