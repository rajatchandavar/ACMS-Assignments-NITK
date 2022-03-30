#include<iostream>
#include<fstream>
#include<cmath>
#include<time.h>
using namespace std;
float fn(float theta_0)
{
    return(-2.2067e-12*(pow(theta_0,4)-81e8));
}
main()
{
    clock_t start=clock();
    fstream f;
    f.open("DATA.txt",ios::out);
    float theta,theta_0,theta_true=647.57,h,k1,k2,error,t=480;
    int j,no_time_steps=1,choice=2;
    do
    {
        ++no_time_steps;
        theta_0=1200;
        h=t/no_time_steps;
        if(choice==1)//EULER METHOD
        {
            for(j=0;j<no_time_steps;++j)
            {
                theta=theta_0+h*fn(theta_0);
                theta_0=theta;
            }
        }
        else//RUNGE-KUTTA METHOD
        {
            for(j=0;j<no_time_steps;++j)
            {
                k1=fn(theta_0);
                k2=fn(theta_0+k1*h);
                theta=theta_0+(k1+k2)/2*h;
                theta_0=theta;
            }
        }
        f<<h<<" "<<theta<<"\n";
        error=abs(theta-theta_true)/theta_true*100;
    }while(error>0.1);
    if(choice==1)
        cout<<"EULER'S METHOD";
    else
        cout<<"RUNGE KUTTA METHOD";
    cout<<"\nOptimum value of Timestep h:"<<h<<" s\nNo. of Timesteps:"<<no_time_steps<<"\nTemperature at "<<t<<" s:"<<theta<<" K\nError percentage:"<<error;
    clock_t stop=clock();
    double timespent = (double)(stop-start)/(double)CLOCKS_PER_SEC;
    cout<<"\nCPU Time:"<<timespent<<" seconds";
}
