#ifndef FISA2_H_INCLUDED
#define FISA2_H_INCLUDED
#include <iostream>
using namespace std;

int sumaChenar(int a[100][100], int n , int m , int chenar)
{
    int i1=chenar;
    int j1=chenar;
    int i2=n-1-chenar;
    int j2=m-1-chenar;
    int s=0;


    for(int j=j1; j<=j2; j++)
    {
      s+=a[i1][j];

    }

    for(int i=i1+1; i<=i2;i++)
       {
            s+=a[i][j2];

       }


    if(i1!=i2)
    {
        for(int j=j2-1;j>=j1;j--){
           s+=a[i2][j];

        }
    }

    if(j1!=j2)
    {
        for(int i=i2-1;i>i1;i--){
                s+=a[i][j1];


        }
    }

    return s;
}
//5x

void prob1()
{
    int  a[100][100] = {
    {12, 32, 10, 11, 42, 18},
    {32, 14, 64, 87, 53, 90},
    {15, 24, 64, 34, 71, 22},
    {64, 76, 24, 75, 88, 63},
    {55, 29, 41, 13, 67, 81},
    {30, 92, 47, 85, 19, 54}
}, n=6 , m=6;

    int chenar=0;
    int i1=chenar;
    int j1=chenar;
    int i2=n-1-chenar;
    int j2=m-1-chenar;

    for(int i=0;i<=n/2;i++){

         cout<<sumaChenar(a,n,m,i)<<endl;
    }
}



#endif // FISA2_H_INCLUDED
