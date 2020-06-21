#include <iostream>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <cstdlib>
#include <omp.h>
#include <chrono> 


using namespace std;
using namespace std::chrono;

double func(double x)

{

return pow(x, 3) - 3*sin(x);

}

int main()

{

double a=0, b=3;

double x, y;

int n;
int threads = 16;

auto start = high_resolution_clock::now();

cout << "n = ";

n = 100000000;

y=func(a);

#pragma omp parallel for reduction(+:y) num_threads(threads)
for (int i=1; i<=n; i++)

{

x=a+i*(b-a)/(n+1);

if(func(x)<y)

y=func(x);

}

cout << endl;

cout << "e = " << (b-a)/(n+1) << endl;

cout << "x = " << x << endl;

cout << "y = " << y << endl;

cout << "threads = " <<threads;
auto stop = high_resolution_clock::now(); 
auto duration = duration_cast<microseconds>(stop - start);
printf("microseconds = %li\n", duration.count());

return 0;

}