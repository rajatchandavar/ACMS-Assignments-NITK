#include<iostream>
#include<cmath>
#include<fstream>
#include<time.h>
using namespace std;
main()
{
    clock_t start=clock();
    fstream f;
    f.open("DATA.txt",ios::out);
    int n=51,i;
    double rho=1,u=1,T=0.02,l=1,r=1,dx0,dxi,dxi_1,Ap[n-2],Aw[n-2],Ae[n-2],B[n-2]={ },phi[n],factor,dist=0;
    phi[0]=0;
    phi[n-1]=1;
    dx0=0.02;
    //dx0=l*(1-r)/(1-pow(r,n-1));
    for(i=1;i<n-1;++i)
    {
        dxi=pow(r,i)*dx0;
        dxi_1=pow(r,i-1)*dx0;
        Aw[i-1]=(1/(dxi+dxi_1))*(-rho*u-(2*T/dxi_1));
        Ae[i-1]=(1/(dxi+dxi_1))*(rho*u-(2*T/dxi));
        Ap[i-1]=2*T/(dxi+dxi_1)*(1/dxi+1/dxi_1);
        if(i==1)
            B[0]=-phi[0]*Aw[0];
        if(i==n-2)
            B[n-3]=-phi[n-1]*Ae[n-3];
    }
    for(i=1;i<n-2;++i)
    {
        factor=Aw[i]/Ap[i-1];
        Ap[i]=Ap[i]-factor*Ae[i-1];
        B[i]=B[i]-factor*B[i-1];
    }
    phi[n-2]=B[n-3]/Ap[n-3];
    for(i=n-3;i>=1;--i)
        phi[i]=(B[i-1]-Ae[i-1]*phi[i+1])/Ap[i-1];
    f<<'0'<<" "<<phi[0];
    for(i=1;i<n-1;++i)
    {
        dist+=pow(r,i-1)*dx0;
        f<<"\n"<<dist<<" "<<phi[i];
    }
    f<<"\n"<<l<<" "<<phi[n-1];
    f.close();
    clock_t stop=clock();
	double timespent = (double)(stop-start)/(double)CLOCKS_PER_SEC;
	cout<<"\nCPU Time:"<<timespent<<" seconds";
}
