#include <iostream>
#include <math.h>
#include <chrono> 


using namespace std;
using namespace std::chrono;


	double f(double x){return 1 / (1 + x * x);}
	double I(double a,double b,int n,double y){return ((b-a)/(2*n)*y);}


int main() {

	int n; double a,b,y,dy,In;
	auto start = high_resolution_clock::now();

	a = 0.0;
    b = 1.0;
    n = 100000000; 

	if (n>1){

		dy=(b-a)/n;
		y+=f(a)+f(b);
		for (int i=1; i<n; i++) {y+=2*(f(a+dy*i));}
		In=I(a,b,n,y);
		cout << In << "\n";

	}
    
	else {cout << "Wrong data";}
	auto stop = high_resolution_clock::now(); 
    auto duration = duration_cast<microseconds>(stop - start);
    printf("microseconds = %li\n", duration.count());
    printf("N = %i\n", n);
}