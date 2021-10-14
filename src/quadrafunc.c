#include "quadrafunc.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static const int N_POINTS = 3;
static const double EPS = 1e-8;

static double **create_matrix(Point *a, Point *b, Point *c) {
  Point points[] = {*a, *b, *c};
  double **result = (double **)malloc(N_POINTS * sizeof(double *));
  for (int i = 0; i < N_POINTS; i++) {
    result[i] = (double *)malloc((N_POINTS + 1) * sizeof(double));
    for (int j = 0; j < N_POINTS; j++) {
      result[i][j] = pow(points[i].x, 2 - j);
    }
    result[i][N_POINTS] = points[i].y;
  }
  return result;
}

static void free_matrix(double **m) {
  for (int i = 0; i < N_POINTS; i++) {
    free(m[i]);
  }
  free(m);
}

Solution gauss_jordan(Point *a, Point *b, Point *c, double *alpha, double *beta,
                      double *gamma) {

  double **matrix = create_matrix(a, b, c);
  int where[] = {-1, -1, -1};
  for (int col = 0, row = 0; col < N_POINTS && row < N_POINTS; ++col) {
    int select = row;
    for (int i = row; i < N_POINTS; ++i) {
      if (fabs(matrix[i][col]) > fabs(matrix[select][col]))
        select = i;
    }
    if (fabs(matrix[select][col]) < EPS)
      continue;
    for (int i = col; i <= N_POINTS; ++i) {
      double tmp = matrix[select][i];
      matrix[select][i] = matrix[row][i];
      matrix[row][i] = tmp;
    }
    where[col] = row;
    for (int i = 0; i < N_POINTS; ++i)
      if (i != row) {
        double d = matrix[i][col] / matrix[row][col];
        for (int j = col; j <= N_POINTS; ++j)
          matrix[i][j] -= matrix[row][j] * d;
      }
    ++row;
  }

  double ans[] = {0, 0, 0};
  for (int i = 0; i < N_POINTS; ++i)
    if (where[i] != -1)
      ans[i] = matrix[where[i]][N_POINTS] / matrix[where[i]][i];
  for (int i = 0; i < N_POINTS; ++i) {
    double sum = 0;
    for (int j = 0; j < N_POINTS; ++j)
      sum += ans[j] * matrix[i][j];
    if (fabs(sum - matrix[i][N_POINTS]) > EPS) {
      *alpha = NAN, *beta = NAN, *gamma = NAN;
      free_matrix(matrix);
      return NOT_EXIST;
    }
  }

  for (int i = 0; i < N_POINTS; ++i)
    if (where[i] == -1) {
      *alpha = INFINITY, *beta = INFINITY, *gamma = INFINITY;
      free_matrix(matrix);
      return INF_N;
    }
  *alpha = ans[0], *beta = ans[1], *gamma = ans[2];
  free_matrix(matrix);
  return UNIQUE;
}

void find_coeffs(Point *a, Point *b, Point *c, double *alpha, double *beta,
                 double *gamma) {
  Solution result = gauss_jordan(a, b, c, alpha, beta, gamma);
  switch (result) {
  case NOT_EXIST:
    printf("System solution does not exist! \n");
    printf("There are no any quadratic functions \n");
    break;
  case UNIQUE:
    if (fabs(*alpha) < EPS)
      printf("It is not quadratic function alpha = 0 \n");
    else
      printf("y = %lf x^2 + %lf x + %lf \n", *alpha, *beta, *gamma);
    break;

  case INF_N:
    printf("System has infinite numbers of solutions! \n");
    printf("There are infinite number of quadratic functions \n");
    break;
  }
}
