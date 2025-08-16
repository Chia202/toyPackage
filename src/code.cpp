#include <RcppArmadillo.h>
#include <Rcpp.h>

#ifdef _OPENMP
#include <omp.h>
#endif

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