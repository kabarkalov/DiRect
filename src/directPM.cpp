#include <limits>
#include <stdio.h>
#include <stdlib.h>

#include <string>

#include "direct.h"
#include "problem_manager.h"
#include "parameters/baseParameters.h"


#define PI 3.14159265359

int trialCount = 0;
bool isFindOptim = false;
int iter = 0;
double** points = 0;

/*
// Целевая функция для DIRECT, в которой значения функции вычисляются через dll
double objective(int N, const double *x, int *undefinedFlag, void *data)
{
  if (points != 0)
  {
    points[trialCount] = new double [N + 1];
    for (int k = 0; k < N; k++)
    {
      points[trialCount][k] = x[k];
    }
  }
  trialCount++;
  IProblem* problem = (IProblem*)data;

  int j;
  double sum = 0.;
  double* BestTrialy = new double [N];
  int err = problem->GetOptimumPoint(BestTrialy);
  double* lower_bounds = new double[N];
  double* upper_bounds = new double[N];
  problem->GetBounds(lower_bounds, upper_bounds);

  sum = problem->CalculateFunctionals(x, 0);
  if (points != 0)
  {
    points[trialCount - 1][N] = sum;
  }
  double Epsilon = methodAccuracy;
  bool res = true;
  if (err != 0)
    res = false;
  for (int i = 0; i < N; i++)
  {
    double fabsx = fabs(BestTrialy[i] - x[i]);
    double fm = Epsilon * (upper_bounds[i] - lower_bounds[i]);
    if (fabsx > fm)
    {
      res = false;
      break;
    }
  }

  if ((res == true) && (isFindOptim == false))
  {
    isFindOptim = true;
    iter = trialCount;
    printf("Iteration = %d\n", trialCount);
    //printf("Global optimum FOUND!\n");
  }

  delete [] BestTrialy;
  delete [] lower_bounds;
  delete [] upper_bounds;
  //return genopt_evaluate(x);
  return sum;
}
*/


//Простая одномерная целевая функция для DIRECT, в которой реализовано вычисление значения функции
double simple_objective(int N, const double* x, int* undefinedFlag, void* data)
{
    trialCount++;//счетчик числа испытаний - реализован как глобальная переменная
    return x[0] * x[0] - cos(18 * x[0]);
}

int main(int argc, char **argv)
{
    int dimension = 1;  //размерность
    double* lower_bounds = new double[dimension]; 
    double* upper_bounds = new double[dimension];
    lower_bounds[0] = -2.5;//нижняя границе интервала поиска
    upper_bounds[0] =  1.5;//верхняя граница интервала поиска

    //Возвращаемое значение
    double* minx = new double[dimension];
    double minf = -std::numeric_limits<double>::infinity(); // include <limits>
    //Параметры
    int max_feval = 1000; // Maximum number of function evaluation
    int max_iter = 1000; // Maximum number of algorithm iterations (different from max);
    double magic_eps     = 0.0001; //Параметр eps метода DIRECT
    double magic_eps_abs = 0.0001;
    double volume_reltol = 0.001; //Точность поиска
    double sigma_reltol  = 0.00000;
    int force_stop = false;


    //Запуск метода; результаты работы выводятся в файл
    FILE* f = fopen("outDirect.txt", "w");
    direct_return_code retcode = direct_optimize(
        simple_objective,
        NULL,
        dimension,
        lower_bounds, 
        upper_bounds,
        minx,
        &minf,
        max_feval, 
        max_iter,  
        0.0, 0.0,  //ограничение по времени работы?
        magic_eps, 
        magic_eps_abs,
        volume_reltol, 
        sigma_reltol,
        &force_stop,
        DIRECT_UNKNOWN_FGLOBAL,
        DIRECT_UNKNOWN_FGLOBAL,
        f,
        DIRECT_ORIGINAL);
    fclose(f);
    //printf("min f = %g at (%g,%g) after %d evals, return value %d\n",
    //              minf, x[0], x[1], cnt, info);

    for (int i = 0; i < dimension; i++)
    {
        printf("x[%d] = %lf\n", i, minx[i]);
    }
    printf("min = %lf\n", minf);
    printf("retcode = %d\n", retcode);
    printf("Point = %d\n", trialCount);
    if (((retcode == 1) || (retcode == 4) || (retcode == 5)) && (isFindOptim))
    {
        printf("Global optimum FOUND!\n");
    }
  return 0;
}