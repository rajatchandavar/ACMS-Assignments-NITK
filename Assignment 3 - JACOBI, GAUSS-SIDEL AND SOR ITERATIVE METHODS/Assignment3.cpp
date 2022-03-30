#include<iostream>
#include<cmath>
#include<time.h>
using namespace std;
main()
{
	clock_t start=clock();
	int i,j,n=4,itrn=0,b[n]={6,25,-11,15},flag=1,choice=3;
	int a[n][n]={{10,-1,2,0},{-1,11,-1,3},{2,-1,10,-1},{0,3,-1,8}};
	float x0[n],x[n]={0},sum,omega=1.04,max_error;
	switch(choice)
	{
		case 1:cout<<"JOCOBI ITERATION METHOD";break;
		case 2:cout<<"GAUSS SIDEL ITERATION METHOD";break;
		case 3:cout<<"SUCCESSIVE OVER-RELAXATION METHOD\nOmega = "<<omega;break;
	}
	for(i=0;i<n;++i)
	{
		sum=0;
		for(j=0;j<n;j++)
		{
			if(j!=i)
				sum+=abs(a[i][j]);
		}
		if(sum<=abs(a[i][i]))
		{
			flag=0;
			break;
		}
	}
	if(flag)
		cout<<"\nMatrix is not diagonally dominant";
	else
	{
		do
		{
			++itrn;
			for(i=0;i<n;++i)
				x0[i]=x[i];
			for(i=0;i<n;++i)
			{
				sum=0;
				for(j=0;j<n;++j)
				{
					if(j==i)
						continue;
					if(choice==1)
						sum+=a[i][j]*x0[j];
					else
						sum+=a[i][j]*x[j];
				}
				if(choice==3)
					x[i]=(1-omega)*x[i]+(omega/a[i][i])*(b[i]-sum);
				else
					x[i]=(b[i]-sum)/a[i][i];
				if(i==0)
					max_error=abs(x[i]-x0[i]);
				else if(abs(x[i]-x0[i])>max_error)
					max_error=abs(x[i]-x0[i]);
				cout<<x[i]<<"\n";
			}
		}while(max_error>1e-4);
		cout<<"\nNo.of Iterations:"<<itrn;
		for(i=0;i<n;i++)
			cout<<"\nx"<<i+1<<" = "<<x[i];
		clock_t stop=clock();
		double timespent = (double)(stop-start)/(double)CLOCKS_PER_SEC;
		cout<<"\nCPU Time:"<<timespent<<" seconds";
	}
}




