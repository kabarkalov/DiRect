#include <limits>
#include <stdio.h>
#include <stdlib.h>

#include "genopt.h"

#include "direct.h"
#define PI 3.14159265359
struct objective_info {
  double alpha;
  double beta;
};

double objective(int N, const double *x, int *undefinedFlag, void *data) 
{

    //int j;
    //double sum = 0.;
    //for (j = 0; j < N; j++)
    //    sum += x[j] * x[j] - 10. * cos(2.0 * PI * x[j]) + 10.0;
    return genopt_evaluate(x);
}

int main(int argc, char **argv)
{
  if (argc >= 3)
    genopt_init(atoi(argv[1]), atoi(argv[2]));
  else
    genopt_init(0, 0);
  int max_feval = 1000; // Maximum number of function evaluation
  genopt_set_maximum_number_of_evaluations(max_feval+100);
  objective_info info;
  info.alpha = 1;
  info.beta = 2;

  int dimension = genopt_get_dimension();
  double* lower_bounds = new double[dimension];//[2] = { -1, -1 };
  double* upper_bounds = new double[dimension];// [2] = { 1, 1 };
  for (int i = 0; i < dimension; i++)
  {
      lower_bounds[i] = genopt_get_lower_limits()[i];
      upper_bounds[i] = genopt_get_upper_limits()[i];
  }
  double* minx = new double[dimension];// [2];
  double minf = -std::numeric_limits<double>::infinity(); // include <limits>
  
  int max_iter = 10000; // Maximum number of algorithm iterations (different from max);
  double magic_eps = 0.00001;
  double magic_eps_abs = 0.0001;
  double volume_reltol = 0.0;
  double sigma_reltol = 0.0;
  int force_stop = false;

  direct_return_code retcode = direct_optimize(
    objective, 
    &info,
    dimension,
    lower_bounds, 
    upper_bounds,
    minx,
    &minf,
    max_feval, 
    max_iter,
    0.0, 0.0,
    magic_eps, 
    magic_eps_abs,
    volume_reltol, 
    sigma_reltol,
    &force_stop,
    DIRECT_UNKNOWN_FGLOBAL,
    DIRECT_UNKNOWN_FGLOBAL,
    NULL,
    DIRECT_ORIGINAL);
  //printf("min f = %g at (%g,%g) after %d evals, return value %d\n",
  //              minf, x[0], x[1], cnt, info);

  for (int i = 0; i < dimension; i++)
      printf("x[%d]=%lf\n", i, minx[i]);
  printf("min f = %lf\n", minf);
  printf("retcode = %d\n", retcode);
  printf("dif = %lf\n", fabs(minf -  genopt_get_global_minimum()));
  genopt_terminate();
  return 0;
}