#include<iostream>
#include<cmath>
#include<fstream>
using namespace std;
main()
{
    fstream f;
    f.open("DATA.txt",ios::out);
    int Nr=11,Nc=9,i,j,iter=0;
    float T[Nr][Nc]={ },dx,dy,error,Ae,Ap,An,Tleft=75,Ttop=300,Tbottom=50,Tright=100,omega=0.5,max_error,temp,l=3.0,b=2.4;
    dx=b/(Nc-1);
    dy=l/(Nr-1);
    Ae=1/(pow(dx,2));
    An=1/(pow(dy,2));
    Ap=-(2*Ae+2*An);
    for(j=0;j<Nc;++j)
    {
        T[0][j]=Tbottom;
        T[Nr-1][j]=Ttop;
    }
    for(i=1;i<Nr-1;++i)
    {
        T[i][0]=Tleft;
        T[i][Nc-1]=Tright;
    }
    do
    {
        ++iter;
        for(i=1;i<Nr-1;++i)
        {
            for(j=1;j<Nc-1;++j)
            {
                temp=T[i][j];
                T[i][j]=(1-omega)*T[i][j]-omega*(Ae*(T[i][j+1]+T[i][j-1])+An*(T[i+1][j]+T[i-1][j]))/Ap;
                error=abs(temp-T[i][j])/T[i][j];
                if(i==1 && j==1)
                    max_error=error;
                else
                {
                    if(error>max_error)
                        max_error=error;
                }
            }
        }
        cout<<max_error<<"\n";
    }while(max_error>1e-6);
    for(i=Nr-1;i>=0;--i)
    {
        for(j=0;j<Nc;++j)
            f<<T[i][j]<<" ";
        f<<"\n";
    }
    cout<<"\nNo. of iterations: "<<iter;
}
