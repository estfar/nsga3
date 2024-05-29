#ifndef _GLOGAL_H
#define _GLOBAL_H

/*sort.c*/
double **normalize(double **pop, int * elite, int current_size, int m, double **ref_points, 
		   int H, double *a);
void associate(double **normalized, int * elite, int current_size, int m, double **ref_points, 
	       int *closest_refpoint, double *distances);
void niching(int size_nondom, int *niche_count, int *closest_refpoint, double *distances, 
	     double **ref_points, int *elite_arr, double **pop, double **next_pop, int n, int m);
void non_dominanted_sort(double **pop, double **nextpop, int n, int m, int H);

#endif
