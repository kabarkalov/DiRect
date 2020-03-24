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
double objective(int N, const double *x, int *undefinedFlag, void *data) 
{
  if (points != 0)
  {
    points[trialCount] = new double [N];
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

  double Epsilon = 0.01;
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

int main(int argc, char **argv)
{

  TProblemManager manager;
  if (argc > 1)
  {
    std::string problemName = argv[1];
    std::string problepConf = "";
    if (argc > 2)
    {
      problepConf = argv[2]; 
    }

    int err;
    if (manager.LoadProblemLibrary(problemName) != TProblemManager::OK_)
      return 0;
    IProblem* problem = manager.GetProblem();


    err = problem->SetDimension(2);
    err = problem->SetConfigPath(problepConf);
    err = problem->Initialize();
    
    int dimension = problem->GetDimension();
    double* lower_bounds = new double[dimension];//[2] = { -1, -1 };
    double* upper_bounds = new double[dimension];// [2] = { 1, 1 };
    problem->GetBounds(lower_bounds, upper_bounds);

    //Возвращаемое значение
    double* minx = new double[dimension];// [2];
    double minf = -std::numeric_limits<double>::infinity(); // include <limits>
    //Параметры
    int max_feval = 10000; // Maximum number of function evaluation
    int max_iter = 10000; // Maximum number of algorithm iterations (different from max);
    double magic_eps     = 0.0001;
    double magic_eps_abs = 0.0001;
    double volume_reltol = 0.0001; // объем
    double sigma_reltol  = 0.00000;//9; // 
    int force_stop = false;

    if (argc > 3)
    {
      points = new double* [max_feval * 2];
    }

    //Запуск
    FILE* f = fopen("outDirect.txt", "w");
    direct_return_code retcode = direct_optimize(
      objective, 
      problem,
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
      f,
      DIRECT_ORIGINAL);
    fclose(f);
    //printf("min f = %g at (%g,%g) after %d evals, return value %d\n",
    //              minf, x[0], x[1], cnt, info);

    for (int i = 0; i < dimension; i++)
      printf("x[%d] = %lf\n", i, minx[i]);
    printf("min = %lf\n", minf);
    printf("retcode = %d\n", retcode);
    printf("Point = %d\n", trialCount);
    if (((retcode == 1) || (retcode == 4) || (retcode == 5)) && (isFindOptim))
    {
      printf("Global optimum FOUND!\n");
    }

    if (argc > 3)
    {
      printf("Iteration = %d\n", iter);
      std::string pointLogName = argv[3];
      FILE* pointLog = fopen(pointLogName.c_str(), "w");

      fprintf(pointLog, "%d\n", iter);
      for (int i = 0; i < iter; i++)
      {
        for (int j = 0; j < dimension; j++)
          fprintf(pointLog, "%lf ", points[i][j]);
        fprintf(pointLog, "\n");
      }

      //for (int j = 0; j < dimension; j++)
      //  fprintf(pointLog, "%lf ", minx[j]);
      //fprintf(pointLog, "\n");

      for (int j = 0; j < dimension; j++)
        fprintf(pointLog, "%lf ", points[iter - 1][j]);
      fprintf(pointLog, "\n");

      double* BestTrialy = new double [dimension];
      int err = problem->GetOptimumPoint(BestTrialy);

      for (int j = 0; j < dimension - 1; j++)
        fprintf(pointLog, "%lf ", BestTrialy[j]);
      fprintf(pointLog, "%lf", BestTrialy[dimension - 1]);

      fclose(pointLog);
      delete [] points;
    }
  }
  //printf("dif = %lf\n", fabs(minf -  genopt_get_global_minimum()));
  //genopt_terminate();
  return 0;
}