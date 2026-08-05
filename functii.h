#ifndef FUNCTII_H_INCLUDED
#define FUNCTII_H_INCLUDED
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

void citireMatrice(int v[100][100], int&n, int&m)
{
    ifstream read("data.txt");
    read>>n;
    read>>m;
    for(int i=0;i<n;i++)
    {
        for(int j=0; j<m;j++)
        {
            read>>v[i][j];
        }
    }
}

void afisareMatrice(int v[100][100],int n, int m )
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m; j++)
        {
            cout<<v[i][j]<<" ";
        }
        cout<<endl;
    }
}
void inserareLinie(int a[100][100],int &n,int m,int poz)
{
    for(int i=n;i>poz;i--)
    {
        for(int j=0;j<m;j++)
        {
            a[i][j]=a[i-1][j];
        }
    }
    n++;
}
void stergereLinie(int a[100][100], int&n,int m , int linie)
{
    for(int i=linie; i<n-1;i++)
    {
        for(int j=0;j<m;j++)
        {
            a[i][j]=a[i+1][j];
        }
    }
    n--;
}

void stergereColoana(int a[100][100], int n , int&m, int coloana)
{
    for(int j=coloana;j<m-1;j++)
    {
        for(int i=0;i<n;i++)
        {
            a[i][j]=a[i][j+1];
        }
    }
    m--;
}

bool treiCifre(int n)
{
    int f[10]{};
    while(n!=0)
    {
        int uc=n%10;
        f[uc]++;
        n=n/10;
    }
    int ok=0;
    for(int i=0;i<=9;i++)
    {
        if(f[i]==3)
        {
            ok=1;
        }
    }
    return ok;
}

int oglindit(int n)
{
    int ogl=0;
    while(n!=0)
    {
        int uc=n%10;
        ogl=ogl*10+uc;
        n=n/10;
    }
    return ogl;
}

void inserareColoana(int v[100][100],int n , int&m , int poz)
{
    for(int j=m-1;j>=poz;j--)
    {
        for(int i=0;i<n;i++)
        {
            v[i][j+1]=v[i][j];
        }
    }
    m++;
}

bool isNumarPp(int n)
{
    return  n!=0&&sqrt(n)==(int)sqrt(n);
}
void rastoarnaColoana(int v[100][100], int n ,int&m, int col)
{
    for(int i=0;i<n; i++)
    {
        v[i][col]=oglindit(v[i][col]);
    }
}
//n=5 m=4  linie=1
//0 1 2 3

//1 2 3 4     0
//2 2 3 4     1
//1 2 4 7     2
//7 5 4 3     3
//6 7 8 9     4

//j  j<m-1     if(v[linie][j]>v[linie][j+1])     ok
//0  0<3                    nu
bool isLinieCrescatoare(int v[100][100], int m, int linie)
{
    int ok=1;
    for(int j=0;j<m-1;j++)
    {
        if(v[linie][j]>v[linie][j+1])
        {
            ok=0;
        }
    }
    return ok;
}

void interschimbareLinii(int v[100][100], int m , int linie1, int linie2)
{
    for(int j=0;j<m;j++)
    {
        int aux=v[linie1][j];
        v[linie1][j]=v[linie2][j];
        v[linie2][j]=aux;
    }
}

void sortareCrescLinie(int v[100][100],int m , int linie)
{
    for(int i=0;i<m-1;i++)
    {
        for(int j=0;j<m-i-1;j++)
        {
            if(v[linie][j]>v[linie][j+1])
            {
                int aux=v[linie][j];
                v[linie][j]=v[linie][j+1];
                v[linie][j+1]=aux;
            }
        }
    }
}

//5 4
//0 1 2 3

//1 2 3 4        0
//1 22 3 4       1
//1 2 444 7      2
//7 5 4 3        3
//6 67 8 9       4


//i  i<n  j  j<m    if(treiCifre(a[i][j]))      delL[i]     delC[j]   i   j
//0  0<5  0  0<4             nu                                           1
//        1  1<4             nu
//        2  2<4
//        3  3<4
//        4  4<4
//
//
//3 3<5  0  0<4             nu
//       1  1<4             nu
//       2  2<4             da                    true        true
void stergeExact3CifreEgale(int a[100][100], int &n, int &m){

    bool delL[100] = {false};
    bool delC[100] = {false};
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(treiCifre(a[i][j]))
            {
                delL[i] = true;
                delC[j] = true;
            }
        }
    }
    for(int i=0;i<n;i++){
        if(delL[i]){
            stergereLinie(a,n,m,i);
        }
    }

    for(int j=0;j<m;j++)
    {
        if(delC[j])
        {
            stergereColoana(a,n,m,j);
        }
    }

}

bool isNumarPrim(int n )
{
     if(n==1||n==0){
        return false;
     }
    int ok=1;
    for(int d=2;d*d<=n;d++)
    {
        if(n%d==0)
        {
            ok=0;
        }
    }
    return ok;
}

int numerePareLinie(int v[100][100],int m, int linie)
{
    int nr=0;
    for(int j=0;j<m;j++)
    {
        if(v[linie][j]%2==0)
        {
            nr++;
        }
    }
    return nr;
}

int aparitiiCifraNumar(int x,int k)
{
    int nr=0;

    if(x==0&&k==0)
    {
        return 1;
    }
    while(x>0)
    {
        if(x%10==k)
        {
            nr++;
        }
        x=x/10;
    }
    return nr;
}

int aparitiiCifraLinie(int a[100][100],int m,int linie,int k)
{
    int nr=0;
    for(int j=0;j<m;j++)
    {
        nr=nr+aparitiiCifraNumar(a[linie][j],k);
    }
    return nr;
}
int frecventaElement(int a[100][100],int n,int m,int x)
{
    int nr=0;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            if(a[i][j]==x)
            {
                nr++;
            }
        }
    }
    return nr;
}

int linieCrescatoare(int a[100][100],int m,int linie)
{
    for(int j=0;j<m-1;j++)
    {
        if(a[linie][j]>a[linie][j+1])
        {
            return 0;
        }
    }
    return 1;
}

int linieDescrescatoare(int a[100][100],int m,int linie)
{
    for(int j=0;j<m-1;j++)
    {
        if(a[linie][j]<a[linie][j+1])
        {
            return 0;
        }
    }
    return 1;
}

int numarPareLinie(int a[100][100],int m,int linie)
{
    int nr=0;

    for(int j=0;j<m;j++)
    {
        if(a[linie][j]%2==0)
        {
            nr++;
        }
    }

    return nr;
}

int cifraMaximaMatrice(int a[100][100],int n,int m)
{
    int cifraMaxima=0;

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            int x=a[i][j];

            while(x>0)
            {
                if(x%10>cifraMaxima)
                {
                    cifraMaxima=x%10;
                }

                x=x/10;
            }
        }
    }

    return cifraMaxima;
}

int cifraMinimaMatrice(int a[100][100],int n,int m)
{
    int cifraMinima=9;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            int x=a[i][j];
            while(x>0)
            {
                if(x%10<cifraMinima)
                {
                    cifraMinima=x%10;
                }
                x=x/10;
            }
        }
    }
    return cifraMinima;
}

int aparitiiCifraColoana(int a[100][100],int n,int coloana,int cifra)
{
    int nr=0;

    for(int i=0;i<n;i++)
    {
        nr=nr+aparitiiCifraNumar(a[i][coloana],cifra);
    }

    return nr;
}

int toateCifrele(int x)
{
    int f[10]={0};

    while(x>0)
    {
        f[x%10]=1;
        x=x/10;
    }

    for(int c=0;c<=9;c++)
    {
        if(f[c]==0)
        {
            return 0;
        }
    }

    return 1;
}

int cifraControl(int x)
{
    while(x>9)
    {
        int s=0;

        while(x>0)
        {
            s=s+x%10;
            x=x/10;
        }

        x=s;
    }
    return x;
}

int coloanaValidaM(int a[100][100],int n,int coloana)
{
    for(int i=0;i<n;i++)
    {
        if(toateCifrele(a[i][coloana])==0)
        {
            return 0;
        }
    }
    return 1;
}


void algoritmSpirala(int a[100][100],int n,int m)
{
    for(int i1=0 ,j1=0 ,i2=n-1,j2=m-1 ;i1<=i2 && j1<=j2; i1++,j1++,i2--,j2--)
    {
        for(int k=j1;k<=j2;k++){
            cout<<a[i1][k]<<" ";
        }
        cout<<endl;
        for(int k=i1+1;k<=i2;k++){
            cout<<a[k][j2]<<" ";
        }
        cout<<endl;
        for(int k=j2-1;k>=j1;k--){
            cout<<a[i2][k]<<" ";
        }
        cout<<endl;
        for(int k=i2-1;k>i1;k--){
            cout<<a[k][j1]<<" ";
        }
        cout<<endl;
    }
}

void afisareChenar(int a[100][100],int n , int m,int chenar)
{
    int i1=chenar;
    int j1=chenar;
    int i2=n-1-chenar;
    int j2=m-1-chenar;

    if(i1>i2 || j1>j2)
    {
        cout<<"Nu exista ";
    }

        for(int k=j1;k<=j2;k++){
            cout<<a[i1][k]<<" ";
        }

        for(int k=i1+1;k<=i2;k++){
            cout<<a[k][j2]<<" ";
        }
    if(i1!=i2)
    {
        for(int k=j2-1;k>=j1;k--){
            cout<<a[i2][k]<<" ";
        }
    }
    if(j1!=j2)
    {
        for(int k=i2-1;k>i1;k--){
            cout<<a[k][j1]<<" ";
        }
    }

}


void produsChenar(int a[100[100],int n , int m , int chenar)
{
     int i1=chenar;
    int j1=chenar;
    int i2=n-1-chenar;
    int j2=m-1-chenar;
    int produs=1;

      for(int k=j1;k<=j2;k++)
        {
          if(a[i1][k]!=0)
          {
              produs*=a[i1][k];
          }
        }

        for(int k=i1+1;k<=i2;k++)
        {
            {
                if(a[k][j2]!=0)
                {
                    produs*=a[k][j2];
                }
            }

        }
    if(i1!=i2)
    {
        for(int k=j2-1;k>=j1;k--)
        {
           if(a[i2][k]!=0)
           {
               produs*=a[i2][k];
           }
        }
    }
    if(j1!=j2)
    {
        for(int k=i2-1;k>i1;k--)
        {
            if(a[k][j1]!=0)
            {
                produs*=a[k][j1];
            }
        }
    }

     return produs;
}
#endif // FUNCTII_H_INCLUDED
