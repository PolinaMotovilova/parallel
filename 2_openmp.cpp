#include <iostream>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <cstdlib>
#include <omp.h>
#include <chrono> 


using namespace std;
using namespace std::chrono;

  double f(double x)
  {
    return 1 / (1 + x * x);
  }

	double I(double a, double b, int n, double y)
  {
    return ((b - a) / (2 * n) * y);
  }


int main() {

	int n, number; double a, b, y, dy, In;

    a = 0.0;
    b = 1.0;
    n = 100000000; 

  auto start = high_resolution_clock::now();

	if (n > 1)
  {

    y = 0.;
		dy = (b - a) / n;
		y += f(a) + f(b);
    number = 16;
    #pragma omp parallel for reduction(+:y) num_threads(number)
		for (int i = 1; i < n; i++) 
    {
      y += 2 * (f(a + dy * i));
    }

		In = I(a, b, n, y);
		cout << In << "\n";
	}
    
	else {cout << "Wrong data";}

  auto stop = high_resolution_clock::now(); 
  auto duration = duration_cast<microseconds>(stop - start);
  printf("microseconds = %li\n", duration.count());
  printf("THREADS = %i N = %i\n", number, n);
}