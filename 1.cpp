#include <string.h>
#include <stdio.h>
#include <cstdlib>
#include <chrono> 


using namespace std;
using namespace std::chrono;

double func(double x)
{
    return 1 / (1 + x * x);
}

double integr(double a, double b, int n, double (*g)(double))
{
  int i;
  double s, h;

  s = 0.;
  h = (b - a) / n;
  for(i = 0; i < n; i ++){
    s += g(a + i * h);
  }
  return s * h;
}

int main()
{
  double A, B, v;
  int N;
  auto start = high_resolution_clock::now();
  clock_t tStart = clock();
  A = 0.0;
  B = 1.0;
  N = 100000000; 
  v = integr(A, B, N, func);
  printf("%lf\n", v);
  auto stop = high_resolution_clock::now(); 
  auto duration = duration_cast<microseconds>(stop - start);
  printf("microseconds = %li\n", duration.count());
  printf("N = %i\n", N);
  return 0;
}