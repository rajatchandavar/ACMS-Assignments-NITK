#include<iostream>
#include<time.h>
using namespace std;
main()
{
    clock_t begin = clock();
    double time_spent;
    int n=3,i,j,k;
    float rtio,sum,x[n];
    float a[n][n]={{25,5,1},{64,8,1},{144,12,1}};
    float b[n]={106.8,177.2,279.2};
    for(k=0;k<n-1;k++)
        for(i=k+1;i<n;i++)
        {
            rtio=a[i][k]/a[k][k];
            for(j=k+1;j<n;j++)
                a[i][j]=a[i][j]-rtio*a[k][j];
            b[i]=b[i]-rtio*b[k];
        }
		
    x[n-1]=b[n-1]/a[n-1][n-1];
    for(i=n-1;i>=0;i--)
    {
        sum=0;
        for(j=i+1;j<n;j++)
            sum=sum+a[i][j]*x[j];
        x[i]=(b[i]-sum)/a[i][i];
    }
    cout<<"Solution Vector:";
    for(i=0;i<n;i++)
        cout<<"\nx"<<i+1<<" = "<<x[i];
    cout<<"\n2nd order polynomial approximation of velocity (m/s):\n"<<x[0]<<"t^2+ "<<x[1]<<"t+"<<x[2]<<",where t-time(s)\nVelocity at 6s: "<<float(x[0]*36+x[1]*6+x[2])<<" m/s";
    clock_t end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    cout<<"\nCPU time:"<<time_spent<<" seconds";
}
