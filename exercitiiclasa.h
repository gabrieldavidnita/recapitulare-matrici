#ifndef EXERCITIICLASA_H_INCLUDED
#define EXERCITIICLASA_H_INCLUDED
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;


//2
//	NrMaxim
//Să se scrie o funcție care are ca parametru un număr natural n și returnează cel mai mare număr care poate fi obținut mutând, pe rând, prima cifră a numărului n și
//a celor obținute pe parcurs, pe ultima poziție. Nu se vor folosi șiruri de caractere și tablouri auxiliare.


void afisareVector(int v[100], int n )
{
    for(int i =0; i<n; i++)
    {
        cout<<v[i];
    }
}


//1234  2341  3412 4123
int nrCif(int n )
{
    int nr=0;
    do
    {
        nr++;
        n=n/10;
    }while(n!=0);
    return nr;
}

int mutaPrimaCif(int n )
{
    int nr=nrCif(n);
    int p=pow(10,nr-1);
    int maxim=n;
    for(int i=1; i<nr; i++)
    {
        int prima=n/p;
        int rest=n%p;
        n=rest*10+prima;
        if(n>maxim)
        {
            maxim=n;
        }
    }
    return maxim;
}


int sumaDiv(int n )
{
    int s=0;
    for(int d=1;d*d<=n; d++)
    {
        if(n%d==0)
        {
            s=s+d;
            if(d!= n/d)
            {
                  s+=n/d;
            }
        }
    }
    return s;
}


int pNr(int n )
{
    int s=sumaDiv(n);
    if(n%2==s%2)
        return 1;
    return 0;
}

int kpn(int a , int b , int k )
{
    int nr=0;
    for(int i=a; i<=b;i++)
    {
        if(pNr(i))
        {
            nr++;
            if(nr==k)
                return i;
        }
    }
    return -1;
}

int isPrim(int n )
{
    if(n<2)
        return 0;
    for(int d=3; d*d<=n; d+=2)
    {
        if(n%d==0)
        {
            return 0;
        }
    }
    return 1;
}

//functie ce returneaza cel mai mare numar prim mai mic  ca n


//functie ce returneaza cel mai mic numar prim  mai mare n
int i_prim(int n )
{
    int p1=n;

    while(isPrim(p1)==0)
    {
        p1--;
    }
     cout<<p1<<endl;
    int p2=n;
    while(isPrim(p2)==0)
    {
        p2++;
    }
    cout<<p2<<endl;
    return p2-p1;
}

#endif // EXERCITIICLASA_H_INCLUDED
