#include<iostream>
#include<cmath>
#include<time.h>
using namespace std;
int main()
{
	clock_t start=clock();
	double h=8,h0,rel_error;
	int iter=0;
	cout<<"\nInitial guess:"<<h;
	do
	{
		++iter;
		h0=h;
		h=h-(9*3.14*pow(h,2)-3.14*pow(h,3)-90)/(18*3.14*h-3*3.14*pow(h,2));
		rel_error=(abs(h-h0)/abs(h))*100;
		cout<<"\nIteration:"<<iter<<" Relative error:"<<rel_error;
	}while(rel_error!=0);
	cout<<"\nFinal Depth:"<<h<<"\nFinal Iteration:"<<iter;
	clock_t stop=clock();
	double timespent = (double)(stop-start)/(double)CLOCKS_PER_SEC;
	cout<<"\nCPU Time:"<<timespent<<" seconds";
}
		