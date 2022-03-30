#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<math.h>
using namespace std;
int index,n=5,i,j,k,choice=2,d;
float *l,*u,z[5],x[5],sum,e;
int idxl(int i, int j)
{
	d=0;
	if(choice==1)
		d=i;
	index=(i*(i+1))/2+j-d;
	return index;
}
int idxu(int i, int j)
{
	d=0;
	if(choice==2)
		d=i+1;
	index=(i*(2*n+1-i))/2+(j-i)-d;
	return index;
}
void findz(float *l,float *z,int *b)
{
	e=1;
	for(i=0;i<n;++i)
	{
		sum=0;
		for(j=0;j<i;++j)
			sum+=l[idxl(i,j)]*z[j];
		if(choice==2)
			e=l[idxl(i,i)];
		z[i]=(b[i]-sum)/e;
	}
}
void findx(float *u,float *x,float *z)
{
	e=1;
	for(i=n-1;i>=0;--i)
	{
		sum=0;
		for(j=i+1;j<n;++j)
			sum+=u[idxu(i,j)]*x[j];
		if(choice!=2)
			e=u[idxu(i,i)];
		x[i]=(z[i]-sum)/e;
	}
}
main()
{
    clock_t start=clock();
	int b[n]={-2,4,3,-5,1}, flag=0;
	int a[n][n]={{2,1,1,3,2},{1,2,2,1,1},{1,2,9,1,5},{3,1,1,7,1},{2,1,5,1,8}};
	if(choice==1)//DOOLITTLE
	{
	    cout<<"DOOLITTLE METHOD\n";
		l=(float*)calloc(n*(n-1)/2,sizeof(float));
		u=(float*)calloc(n*(n+1)/2,sizeof(float));
		for(i=0;i<n;++i)
		{
			for(k=0;k<i;++k)
			{
				sum=0;
				for(j=0;j<k;++j)
					sum+=l[idxl(i,j)]*u[idxu(j,k)];
				l[idxl(i,k)]=(a[i][k]-sum)/u[idxu(k,k)];
			}
			for(j=i;j<n;++j)
			{
				sum=0;
				for(k=0;k<i;++k)
					sum+=l[idxl(i,k)]*u[idxu(k,j)];
				u[idxu(i,j)]=a[i][j]-sum;
			}
		}
		findz(l,z,b);
		findx(u,x,z);
	}
	else if(choice==2)//CROUT
	{
	    cout<<"CROUT METHOD\n";
		l=(float*)calloc(n*(n+1)/2,sizeof(float));
		u=(float*)calloc(n*(n-1)/2,sizeof(float));
		for(i=0;i<n;++i)
		{
			for(k=0;k<=i;++k)
			{
				sum=0;
				for(j=0;j<k;++j)
					sum+=l[idxl(i,j)]*u[idxu(j,k)];
				l[idxl(i,k)]=a[i][k]-sum;
			}
			for(j=i+1;j<n;++j)
			{
				sum=0;
				for(k=0;k<i;++k)
					sum+=l[idxl(i,k)]*u[idxu(k,j)];
				u[idxu(i,j)]=(a[i][j]-sum)/l[idxl(i,i)];
			}
		}
		findz(l,z,b);
		findx(u,x,z);
	}
	else//CHOLESKY
	{
	    cout<<"CHOLESKY METHOD\n";
		u=(float*)calloc(n*(n+1)/2,sizeof(float));
		for(i=0;i<n;++i)
		{
			if(a[i][i]<0)
			{
				flag=1;
				break;
			}
			for(j=0;j<n;++j)
			{
				if(a[i][j]!=a[j][i])
				{
					flag=1;
					break;
				}
			}
			if(flag)
				break;
		}
		if(flag)
			cout<<"Matrix is not symmetric or not positive definite. Hence Cholesky method cannot be used.";
		else
		{
			for(i=0;i<n;++i)
			{
				sum=0;
				for(k=0;k<i;++k)
					sum+=pow(u[idxu(k,i)],2);
				if(a[i][i]<sum)
				{
					cout<<"Hello"<<i;
					flag=1;
					break;
				}
				u[idxu(i,i)]=sqrt(a[i][i]-sum);
				for(j=i+1;j<n;++j)
				{
					sum=0;
					for(k=0;k<i;++k)
						sum+=u[idxu(k,i)]*u[idxu(k,j)];
					u[idxu(i,j)]=(a[i][j]-sum)/u[idxu(i,i)];
				}
			}
			for(i=0;i<n;i++)
			{
				sum=0;
				for(j=0;j<i;j++)
					sum+=u[idxu(j,i)]*z[j];
				z[i]=(b[i]-sum)/u[idxu(i,i)];
			}
			findx(u,x,z);
		}
	}
	if (!flag)
	{
	    cout<<"Solution Vector:";
		for(i=0;i<n;i++)
			cout<<"\nx_"<<i<<"="<<x[i];
	}
	delete(l);delete(u);
	clock_t stop=clock();
	double timespent = (double)(stop-start)/(double)CLOCKS_PER_SEC;
	cout<<"\nCPU Time:"<<timespent<<" seconds";
}
