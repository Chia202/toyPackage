#' @title Sum the elements of a matrix
#' @description Sum the elements of a matrix
#' @param X A matrix
#' @param n_threads The number of threads to use
#' @return The sum of the elements of the matrix
#' @examples
#' X <- matrix(1:10, 2, 5)
#' sum.matrix(X)
#' @export
sum.matrix <- function(X, n_threads = 4) {
    sum_matrix(X, n_threads)
}
