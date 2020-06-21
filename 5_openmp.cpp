#include <iostream>
#include <string.h>
#include <stdio.h>
#include <cstdlib>
#include <time.h>
#include <omp.h>
#include <chrono> 


using namespace std;
using namespace std::chrono;


float RandomFloat(float a, float b) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}


int N = 1000;
int NUM_THREADS = 8;

int main()
{
  auto start = high_resolution_clock::now();
  srand(time(NULL));
  int row1, row2, col1, col2;
  double** a, ** b, ** c;
  row1 = N;
  col1 = N;
  row2 = N;
  col2 = N;
  double s = 1.; 
  if (col1 != row2)
  {
    cout << "Умножение невозможно!";
    cin.get(); cin.get();
    return 0;
  }

  a = new double* [row1];
  #pragma omp parallel for reduction(+:s) num_threads(NUM_THREADS)
  for (int i = 0; i < row1; i++)
  {
    a[i] = new double[col1];
    for (int j = 0; j < col1; j++)
    {
      a[i][j] = RandomFloat(1, 5);
    }
  }

  b = new double* [row2];
  #pragma omp parallel for reduction(+:s) num_threads(NUM_THREADS)
  for (int i = 0; i < row2; i++)
  {
    b[i] = new double[col2];
    for (int j = 0; j < col2; j++)
    {
      b[i][j] = RandomFloat(1, 5);
    }
  }

  c = new double* [row1];
  #pragma omp parallel for reduction(+:s) num_threads(NUM_THREADS)
  for (int i = 0; i < row1; i++)
  {
    c[i] = new double[col2];
    for (int j = 0; j < col2; j++)
    {
      c[i][j] = 0;
      for (int k = 0; k < col1; k++)
        c[i][j] += a[i][k] * b[k][j];
    }
  }

  auto stop = high_resolution_clock::now(); 
  auto duration = duration_cast<microseconds>(stop - start);
  printf("microseconds = %li\n", duration.count());
  printf("N = %i THREADS = %i\n", N, NUM_THREADS);
  return 0;
}