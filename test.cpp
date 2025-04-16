#include "adcpp/adcpp.hpp"
#include <vector>


// tictoc
#include <chrono>
double tictoc()
{
  double t = std::chrono::duration<double>(
      std::chrono::system_clock::now().time_since_epoch()).count();
  static double t0 = t;
  double tdiff = t-t0;
  t0 = t;
  return tdiff;
}

template <typename T, int N>
T simple_func()
{
  // O(n²)
  std::vector<T> A(N*N,0);
  // O(n³)
  for(int i = 0; i < N; i++)
  {
    for(int k = 0; k < N; k++)
    {
      for(int j = 0; j < N; j++)
      {
        A[k*N+j] = A[k*N+i]*A[i*N+j];
      }
    }
  }
  // O(n²)
  T y = 0;
  for(int i = 0; i < N; i++)
    for(int j = 0; j < N; j++)
      y += A[i*N+j];
  return y;
}

template <int N, int max_N>
void benchmark()
{
  tictoc();
  const int max_iter = 10/N;
  for(int iter = 0; iter < max_iter; iter++)
  {
    adcpp::bwd::Double y = simple_func<adcpp::bwd::Double,N>();
    adcpp::bwd::Double::DerivativeMap derivative;
    y.derivative(derivative);
  }
  printf("%d %g \n",N,tictoc()/max_iter);
  if constexpr (N<max_N)
  {
    benchmark<N+1,max_N>();
  }
}



int main()
{
  benchmark<1,10>();
  return 0;
}
