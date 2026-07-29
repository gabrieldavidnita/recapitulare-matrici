#ifndef FUNCTII_H_INCLUDED
#define FUNCTII_H_INCLUDED
#include <iostream>
#include <fstream>
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
#endif // FUNCTII_H_INCLUDED
