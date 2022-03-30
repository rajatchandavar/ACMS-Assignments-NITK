#include<iostream>
#include<time.h>
using namespace std;
main()
{
    clock_t start=clock();
    int l=10,i,j,dx=1,n=l/dx+1,Ta=20;
    float T[n],h=0.02,k1=2+h*dx*dx,k2=h*dx*dx*Ta,d[n-2],a[n-3],b[n-2],c[n-3];
    T[0]=40;
    T[n-1]=200;
    for(i=0;i<n-3;i++)
    {
        a[i]=c[i]=-1;
        b[i]=k1;
        if(!i)
            d[i]=k2+T[0];
        else
            d[i]=k2;
    }
    d[n-3]=k2+T[n-1];
    b[n-3]=k1;
    for(i=0;i<n-3;++i)
    {
        a[i]=a[i]/b[i];
        b[i+1]=b[i+1]-a[i]*c[i];
        d[i+1]=d[i+1]-a[i]*d[i];
    }
    T[n-2]=d[n-3]/b[n-3];
    for(i=n-3;i>0;--i)
        T[i]=(d[i-1]-c[i-1]*T[i+1])/b[i-1];
    cout<<"solution Vector:";
    for(i=0;i<n;i++)
        cout<<"\nT_"<<i<<" = "<<T[i]<<" Deg. C";
    clock_t stop=clock();
	double timespent = (double)(stop-start)/(double)CLOCKS_PER_SEC;
	cout<<"\nCPU Time:"<<timespent<<" seconds";
}
