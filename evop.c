#include"global.h"
#define _EPS 1.2e-7

void SBX(double *parent1, double *parent2, double *child1, double *child2, int nvar, double Pc, 
	 double lim_inf, double lim_sup, double eta_c){
	
  double alpha, beta, betaq;
  double y1, y2, yl, yu;
  double c1, c2;
  double rnd;
  int i;
  //for(i=0; i<nvar; i++) printf("%lf ", parent1[i]);
  //printf("\n");
  if (rndreal(0.0,1.0) <= Pc) {

    for (i = 0; i < nvar; i++) {
      
	    if (rndreal(0.0,1.0) <= 0.5) {
        	if (fabs(parent1[i] - parent2[i]) > _EPS) {
          		if (parent1[i] < parent2[i]) {
            			y1 = parent1[i];
            			y2 = parent2[i];
          		}
          	else {
            		y1 = parent2[i];
            		y2 = parent1[i];
          	}

          	yl = lim_inf;
          	yu = lim_sup;
          
	  	rnd = rndreal(0.0,1.0);
          
	  	if((y2 - y1) == 0){
            		beta = 1.0 + (2.0*(y1-yl)/1e-4);
	  	}else{
            		beta = 1.0 + (2.0*(y1-yl)/(y2-y1));
	  	}
		alpha = 2.0 - pow(beta,-(eta_c+1.0));

          	if (rnd <= (1.0/alpha)){
            		betaq = pow ((rnd*alpha),(1.0/(eta_c+1.0)));
	  	}else{
            		betaq = pow ((1.0/(2.0 - rnd*alpha)),(1.0/(eta_c+1.0)));
	  	}
          	
		c1 = 0.5*((y1+y2)-betaq*(y2-y1));
          	
		if((y2 - y1) == 0){
            		beta = 1.0 + (2.0*(yu-y2)/1e-4);
	  	}else{
            		beta = 1.0 + (2.0*(yu-y2)/(y2-y1));
	  	}alpha = 2.0 - pow(beta,-(eta_c+1.0));

          if (rnd <= (1.0/alpha)){
            betaq = pow ((rnd*alpha),(1.0/(eta_c+1.0)));
	  }else{
            betaq = pow ((1.0/(2.0 - rnd*alpha)),(1.0/(eta_c+1.0)));
	  }
          c2 = 0.5*((y1+y2)+betaq*(y2-y1));

          if (c1 < yl) c1 = yl;
          if (c2 < yl) c2 = yl;
          if (c1 > yu) c1 = yu;
          if (c2 > yu) c2 = yu;
          
	  if (rndreal(0.0,1.0)<=0.5) {
            child1[i] = c2;
            child2[i] = c1;
          }
          else {
            child1[i] = c1;
            child2[i] = c2;
          }
        }
        else {
          child1[i] = parent1[i];
          child2[i] = parent2[i];
       	}
      }
      else {
        child1[i] = parent1[i];
        child2[i] = parent2[i];
      }
    }
  }
  else {
    for (i = 0; i < nvar; i++) {
      child1[i] = parent1[i];
      child2[i] = parent2[i];
    }
  }
}



void poly_mutation(double *x, int num_var, double pm, double eta_m, double lim_inf, double lim_sup){
	int j;
	double rnd, delta1, delta2, mut_pow, deltaq;
	double y, yl, yu, val, xy;
	for (j = 0; j < num_var; j++){
            /* Mutación aritmetica o parameter based mutation Deb 1995 */
            if (flip(pm)){
		    y = x[j];
            	yl = lim_inf;
            	yu = lim_sup;
            	delta1 = (y-yl)/(yu-yl);
            	delta2 = (yu-y)/(yu-yl);
            	rnd = rndreal(0.0,1.0);
            	mut_pow = 1.0/(eta_m+1.0);
            if (rnd <= 0.5)
            {
                xy = 1.0-delta1;
                val = 2.0*rnd+(1.0-2.0*rnd)*(pow(xy,(eta_m+1.0)));
                deltaq =  pow(val,mut_pow) - 1.0;
            }
            else
            {
                xy = 1.0-delta2;
                val = 2.0*(1.0-rnd)+2.0*(rnd-0.5)*(pow(xy,(eta_m+1.0)));
                deltaq = 1.0 - (pow(val,mut_pow));
            }
            y = y + deltaq*(yu-yl);
            if (y<yl) y = yl;
            if (y>yu) y = yu;
            x[j] = y;
	    }
	}

}

void recombination(double **gen, int n, int k, int m, double Pc, double eta_c, double *lim){
	int id1, id2;
	int i=n;
	while(i< 2*n){
		id1 = rnd(0, n-1);
		id2 = rnd(0, n-1);
		while(id1 == id2){
			id2 = rnd(0, n-1);
		}
		//printf("indices cruza: %d y %d poner en %d y %d\n", id1, id2, i, i+1);
		SBX(gen[id1]+m, gen[id2]+m, gen[i]+m, 
		    gen[i+1]+m, k, Pc, eta_c, lim[0], lim[1]);
		i+=2;
	}
}

void mutation(double **gen, int n, int k, int m, double pm, double nm, double*lim){
	for(int i=n; i<2*n; i++){
		poly_mutation(gen[i]+m, k, pm, nm, lim[0], lim[1]);
	}
}
