#include <RcppArmadillo.h>
#include <Rcpp.h>

#ifdef _OPENMP
#include <omp.h>
#endif

// [[Rcpp::plugins(openmp)]]
// [[Rcpp::depends(RcppArmadillo)]]

//' @title Sum the elements of a matrix
//' @description Sum the elements of a matrix
//' @param X A matrix
//' @return The sum of the elements of the matrix
//' @examples
//' X <- matrix(1:10, 2, 5)
//' sum_matrix(X)
// [[Rcpp::export]]
double sum_matrix(const arma::mat &X, const int n_threads = 4)
{
    double sum = 0;
    int m = X.n_rows;
    int n = X.n_cols;
    if (n_threads == 1)
    {
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                sum += X(i, j);
            }
        }
    }
    else if (n_threads > 1)
    {
        omp_set_num_threads(n_threads);
        #pragma omp parallel for reduction(+ : sum)
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                sum += X(i, j);
            }
        }
    }
    return sum;
}