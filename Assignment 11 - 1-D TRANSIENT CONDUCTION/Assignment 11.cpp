#include<iostream>
#include<conio.h>
#include<fstream>
#include<time.h>
using namespace std;
main()
{
    clock_t start=clock();
    fstream f;
    f.open("DATA.txt",ios::out);
    int i,n=91,choice=3;
    float l=0.05,total_time=9,current_time=0,dx=l/(n-1),k=54,rho=7800,cp=490,alpha=k/(rho*cp),T[n],Told[n],dt=0.01,a,b,c,diag[n-2],B[n-2],factor;
    if(alpha*dt/(dx*dx)>0.5)
    {
        cout<<"Improper time step";
        getch();
    }
    //Initial condition
    for(i=1;i<n-1;++i)
        T[i]=20;
    //Boundary condition
    T[0]=100;
    T[n-1]=25;
    //Grid
    f<<"Grid\n";
    for(i=0;i<n;++i)
        f<<i*dx<<" ";
    f<<"\nTime=0s\n";
    for(i=0;i<n;++i)
        f<<T[i]<<" ";
    if(choice==1)//EXPLICIT
    {
        do
        {
            for(i=0;i<n;++i)
                Told[i]=T[i];
            current_time+=dt;
            for(i=1;i<n-1;++i)
                T[i]=alpha*dt/(dx*dx)*(Told[i+1]-2*Told[i]+Told[i-1])+Told[i];
            f<<"\nTime="<<current_time<<"s\n";
            for(i=0;i<n;++i)
                f<<T[i]<<" ";
        }while(current_time<total_time);
    }
    else if(choice==2)//IMPLICIT
    {
        a=-alpha*dt/(dx*dx);
        b=-2*a+1;
        c=a;
        do
        {
            //for(i=0;i<n;++i)
              //  Told[i]=T[i];
            current_time+=dt;
            for(i=0;i<n-2;++i)
                diag[i]=b;
            B[0]=T[1]-c*T[0];
            B[n-3]=T[n-2]-a*T[n-1];
            for(i=1;i<n-3;++i)
                B[i]=T[i+1];
            for(i=1;i<n-2;++i)
            {
                factor=c/diag[i-1];
                diag[i]=diag[i]-factor*a;
                B[i]=B[i]-factor*B[i-1];
            }
            T[n-2]=B[n-3]/diag[n-3];
            for(i=n-3;i>0;--i)
                T[i]=(B[i-1]-a*T[i+1])/diag[i-1];
            f<<"\nTime="<<current_time<<"s\n";
            for(i=0;i<n;++i)
                f<<T[i]<<" ";
        }while(current_time<total_time);
    }
    else if(choice==3)//CRANK-NICOLSON SCHEME
    {
        a=-alpha*dt/(2*dx*dx);
        b=-2*a+1;
        c=a;
        do
        {
            //for(i=0;i<n;++i)
              //  Told[i]=T[i];
            current_time+=dt;
            for(i=0;i<n-2;++i)
                diag[i]=b;
            B[0]=T[1]-a*T[2]-(b-1)*T[1]-2*c*T[0];
            B[n-3]=T[n-2]-2*a*T[n-1]-(b-1)*T[n-2]-c*T[n-3];
            for(i=1;i<n-3;++i)
                B[i]=T[i+1]-a*T[i+2]-(b-1)*T[i+1]-c*T[i];
            for(i=1;i<n-2;++i)
            {
                factor=c/diag[i-1];
                diag[i]=diag[i]-factor*a;
                B[i]=B[i]-factor*B[i-1];
            }
            T[n-2]=B[n-3]/diag[n-3];
            for(i=n-3;i>0;--i)
                T[i]=(B[i-1]-a*T[i+1])/diag[i-1];
            f<<"\nTime="<<current_time<<"s\n";
            for(i=0;i<n;++i)
                f<<T[i]<<" ";
        }while(current_time<total_time);
    }
    clock_t stop=clock();
    double timespent = (double)(stop-start)/(double)CLOCKS_PER_SEC;
    cout<<"\nCPU Time:"<<timespent<<" seconds";
}
