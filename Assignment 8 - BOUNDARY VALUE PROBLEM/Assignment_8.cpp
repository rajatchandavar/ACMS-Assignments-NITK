#include<iostream>
#include<fstream>
#include<cmath>
using namespace std;
main()
{
    float gamma=0.1,dx=0.01,l=1,x;
    int N=int(l/dx)+1,choice=1,i;
    float phi[N],a,b_value,c,b[N-2],factor,phi_anly[N],B[N-2]={ };
    //Boundary conditions
    phi[0]=1;
    phi[N-1]=0;
    //Central difference scheme
    if(choice==1)
    {
        a=1+dx/(2*gamma);
        b_value=-(2+dx*dx/gamma);
        c=1-dx/(2*gamma);
    }
    //Forward difference scheme
    else if(choice==2)
    {
        a=1+dx/gamma;
        b_value=-(2+dx/gamma*(1+dx));
        c=1;
    }
    //Backward difference scheme
    else
    {
        a=1;
        b_value=-(2+dx/gamma*(-1+dx));
        c=1-dx/gamma;
    }
    B[0]=-c*phi[0];
    B[N-3]=-a*phi[N-1];
    //Thomas algorithm
    for(i=0;i<N-2;++i)
        b[i]=b_value;
    for(i=1;i<N-2;++i)
    {
        factor = c/b[i-1];
        b[i]=b[i]-factor*a;
        B[i]=B[i]-factor*B[i-1];
    }
    phi[N-2]=B[N-3]/b[N-3];
    //Numerical solution
    for(i=N-3;i>0;--i)
        phi[i]=(B[i-1]-a*phi[i+1])/b[i-1];
    //Analytical solution
    for(i=0;i<N;++i)
    {
        x=i*dx;
        phi_anly[i]=exp(-10.916*x);
    }
    //Writing to Data file
    fstream f;
    f.open("DATA.txt",ios::out);
    for(i=0;i<N;++i)
        f<<i*dx<<" "<<phi[i]<<" "<<phi_anly[i]<<"\n";
    f.close();
}
