/*
 * genopt.h (version 20160214)
 *
 * (C) 2015-2016 Roberto Battiti and Mauro Brunato, all rights reserved.
 *
 * Benchmark functions for the Genopt contest.
 *
 * Usage: See README.txt
 *
 */

#ifndef _H_GENOPT_
#define _H_GENOPT_

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Error codes. Returned by genopt_init() and genopt_terminate().
 *
 */
typedef enum {
	GENOPT_OK = 0,                 /* No error */
	GENOPT_ERROR_INDEX,            /* see genopt_init */
	GENOPT_ERROR_SEED,             /* see genopt_init */
	GENOPT_ERROR_FILE,             /* see genopt_init, genopt_terminate */
} GENOPT_ERROR;

/*
 * Initialize the library. To be called once, before any other function in the library.
 * Opens report file "genopt_[index]_[seed].txt" for writing.
 *
 * Parameters:
 * function_index: function type ID; see the genopt.pdf manifesto for details.
 * function_seed: positive integer that identifies an instance.
 *
 * Returns:
 * GENOPT_OK if no error
 * GENOPT_ERROR_INDEX if function with declared function_index does not exist
 * GENOPT_ERROR_SEED if seed provided is not positive.
 * GENOPT_ERROR_FILE if filename "genopt_[index]_[seed].txt" cannot be created or written.
 *
 * Preconditions:
 * - no other genopt_*() call has been issued (unchecked);
 * - function_index must refer to an existing function (checked; returns GENOPT_ERROR_INDEX);
 * - function_seed must be positive (checked; returns GENOPT_ERROR_SEED)
 * - file "genopt_[index]_[seed].txt" must have create, read, and write permissions (checked; returns GENOPT_ERROR_FILE)
 *
 */
GENOPT_ERROR genopt_init (int function_index, unsigned int function_seed);

/*
 * Get the number of dimensions in function domain.
 *
 * Returns:
 * number of dimensions, depending on function_id on init.
 *
 * Preconditions:
 * - genopt_init must have been called returning GENOPT_OK (unchecked).
 *
 */
int genopt_get_dimension (void);

/*
 * Get the domain limits.
 *
 * Returns:
 * constant array with minimum (resp. maximum) admissible value
 * of coordinates in function domain.
 *
 * Preconditions:
 * - genopt_init must have been called returning GENOPT_OK (unchecked).
 * 
 * Notes:
 * - The code is 0-based: element at index 0 corresponds to the first dimension.
 * - the buffer returned by the two functions will be valid until next function call:
 *   don't assume that a new buffer will be returned every time.
 *
 */
const double *genopt_get_lower_limits (void);
const double *genopt_get_upper_limits (void);

/*
 * Get the global minimum value.
 *
 * Returns:
 * the global minimum.
 *
 * Preconditions:
 * - genopt_init must have been called returning GENOPT_OK (unchecked).
 * 
 */
double genopt_get_global_minimum (void);

/*
 * Get the number of evaluations performed up to now.
 *
 * Returns:
 * number of evaluations, increases by one each time genopt_evaluate() is called.
 *
 * Preconditions:
 * - genopt_init must have been called returning GENOPT_OK (unchecked).
 *
 */
int genopt_get_number_of_evaluations (void);

/*
 * Evaluate the function at the given point in the domain.
 *
 * Parameters:
 * - x: evaluation point.
 *
 * Returns:
 * Function value
 *
 * Preconditions:
 * - genopt_init must have been called returning GENOPT_OK (unchecked).
 * - input array x must contain (at least) as many values as domain dimension (unchecked).
 * - input array x must be within the function's domain (unchecked).
 *
 * Notes:
 * - Although we try to ensure a nice behavior, the outcome of the function
 *   for values of x outside the domain is undefined
 *   (may include NaN, Inf, illegal or random value could be returned; function may not terminate)
 * - If less that "dimension" cells are allocated for x, memory faults could be generated.
 * - The code is 0-based: the first component of x, of index 0, is the first dimension.
 *
 */
double genopt_evaluate (const double *x);

/*
 * Set the maximum number of evaluations; when the limit is reached,
 * the report is written and the program is terminated.
 *
 * Parameters:
 * - nev: maximum number of evaluations. Originally set to 0 (unlimited)
 *
 * Preconditions:
 * - genopt_init must have been called returning GENOPT_OK (unchecked).
 * - nev >= 0 (unchecked).
 *
 */
void genopt_set_maximum_number_of_evaluations (int nev);

/*
 * Complete the report file and free all genopt resources.
 *
 * Returns:
 * GENOPT_OK if no error
 * GENOPT_ERROR_FILE if report file cannot be written.
 *
 * Preconditions:
 * - genopt_init must have been called returning GENOPT_OK (unchecked).
 * - filename must have write permissions (checked; returns GENOPT_ERROR_FILE)
 *
 */
GENOPT_ERROR genopt_terminate (void);

#ifdef __cplusplus
}
#endif


#endif /*_H_GENOPT_*/
