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
        if(delC[i]){
            stergereLinie(a,n,m,i);
        }
    }

    for(int j=0;j<m;j++)
    {
        if(delL[j])
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




















#endif // FUNCTII_H_INCLUDED
