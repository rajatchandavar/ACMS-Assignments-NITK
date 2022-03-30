#include<iostream>
#include<cmath>
#include<time.h>
#define pi 3.14159
using namespace std;
double Area(float theta,int index)
{
    switch (index)
    {
        case 0:return(4*sin(theta)+2*sin(2*theta));break;//Area
        case 1:return(4*(cos(theta)+cos(2*theta)));break;//first derivative
        case 2:return(-4*(sin(theta)+2*sin(2*theta)));break;//second derivative
    }
}
main()
{
    clock_t start=clock();
    int choice=1,itrn=0;
    float x;
    if(!choice)
    {
        cout<<"GOLDEN SECTION SEARCH METHOD\n";
        float xl=0,xu=pi/2,d,x1,x2;
        while((xu-xl)>0.05)
        {
            ++itrn;
            d=(sqrt(5)-1)*(xu-xl)/2;
            x1=xl+d;
            x2=xu-d;
            if(Area(x1,0)>Area(x2,0))
                xl=x2;
            else
                xu=x1;
        }
        x=(xu+xl)/2;
    }
    else
    {
        cout<<"NEWTON'S METHOD\n";
        float x0;x=pi/4;
        do
        {
            ++itrn;
            x0=x;
            x=x-(Area(x,1)/Area(x,2));
        }while(abs(x-x0)>0.05);
    }
    cout<<"Angle in degrees:"<<x*180/pi<<"\nIterations:"<<itrn<<"\nMax Area:"<<Area(x,0);
    clock_t stop=clock();
    double timespent = (double)(stop-start)/(double)CLOCKS_PER_SEC;
    cout<<"\nCPU Time:"<<timespent<<" seconds";
}
