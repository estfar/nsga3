#include"global.h"

/* normaliza la población general y los puntos de referencia */
double **normalize(double **pop, int *elite_arr, int curr_size, int m){
	int i,j;
        double	min, scl;
	double *ideal_point = (double *)calloc(m, sizeof(double));
	double **norm = (double **)calloc(curr_size, sizeof(double *));
	double *a = (double *)calloc(m, sizeof(double));
	double w[m];
	/*identify the ideal point for each objective function*/
	for(i=0; i<m; i++){
		min = pop[elite_arr[0]][i];
		for(j=0; j<curr_size; j++){
			if(min > pop[elite_arr[j]][i]) min = pop[elite_arr[j]][i];
		}
		ideal_point[i] = min;
	}
	/*Each member of S_t(elite_arr) is translated by substracting objective f_i
	 * by ideal_point*/
	for(i=0; i<curr_size; i++) norm[i] = (double *)calloc(m, sizeof(double));

	for(i=0; i<curr_size; i++){
		for(j=0; j<m; j++) norm[i][j] = pop[elite_arr[i]][j] - ideal_point[j];
	}
	/*Compute extreme points*/
	int index;
	for(i=0; i<m; i++){
		min = 0.0;
		memset(w, 0, sizeof(w));
		w[i] = 1.0;
		for(j=0; j<curr_size; j++){ 
			scl = scl_fun(pop[elite_arr[j]], w, ideal_point, m); 
			if(min < scl){
				min = scl;
				index = elite_arr[j];
			}
		}
		a[i] = pop[index][i];
		if(a[i]==0) a[i]= 1e-8;
		printf("%lf\t", a[i]);
	}
	printf("a[]\n");
	/* Normalize objectives f_i^n(x) = f_i'(x)/a_i */
	for(i=0; i<curr_size; i++){
		for(j=0; j<m; j++){
			norm[i][j] /= a[j];
			//printf("%lf\t", norm[i][j]);
		}
		//printf("\n");
	}

	free(a);
	free(ideal_point);

	/*Generar H puntos de referencia*/
	return norm;
}
/*
void gen_ref_points(int m, int p, double **ref_points){
	int i, j, div, H = factorial(m-p-1)/(factorial(m-1)*factorial(p));
	double sigma, lim_inf, lim_sup;
	ref_points = (double **)calloc(H, sizeof(double*));
	for(i=0; i<H; i++){
		ref_points[i] = (double *)calloc(m, sizeof(double));
	}

	lim_inf = 0.0;
	lim_sup = 1.0;
	div = p+1;
	sigma = (double)1.0/p;
}
*/

/* asocia un punto en normalized con un punto de referencia y calcula su distancia al mismo  */
void associate(double **normalized, Node* elite, int curr_size, int m, double **ref_points, int H){
	double menor=1e30, dst;
	int index= 0;
	for(int i=0; i<curr_size; i++){
		/*para punto de referncia*/
		for(int j=0; j<H; j++){
			dst = dist(ref_points[j], normalized[i], m);
			if(menor > dst){
				menor = dst; 
				index = j;
			}
		}
		set_info_list(elite, i, index, menor);
	}	 
}

/* seleccionar los elementos faltantes para llevar nextpop */
void niching(int *niche_count, Node *elite, int H, int curr_size,
	     int size_nondom, double **pop, double **next_pop, int n, 
	     int m){
	
	int k = 0, K = n - (curr_size-size_nondom), pi=0;
	int i, j, jbar;
	Node *jmin, *ijbar, *jexcluded; 
	jmin = crear_lista(-1);
	ijbar = crear_lista(-1);
	jexcluded = crear_lista(-1);
	int times = 0;	
	while(k<K){
		// Buscar los miembros de ref_point con niche_count == pi
		// y ponerlos en una lista (jmin)
		liberar_lista(&jmin->next);

		for(i=0; i<H; i++){
			if(buscar(jexcluded, i) == 0){
				if(niche_count[i] == pi) agregar(jmin, i, 0, 0);
			}
		}
		int size_jmin = size(jmin)-1;
		
		/* saltar aquí si  */ 
		if(size_jmin > 0){
		// si jmin no está vacío, elegir un miembro al azar
			int rnd_i = rnd(1, size_jmin);
			jbar = indice(jmin, rnd_i);
			//jbar es el indice de un punto de referencia
		}else{
		// si jmin está vacío, aumentar pi (niche count)
		// y volver a armar jmin
			pi++;
			continue;
		}
		// buscar las posiciones de elite que corresponda(n) a jbar
		liberar_lista(&ijbar->next);
		Node *temp = elite;
		int il = 0;
		
		while(il<curr_size-size_nondom){
			temp = temp->next;
			il++;
		}
		for(i=curr_size-size_nondom;i<curr_size; i++){
			if(temp==NULL) break;
			if(temp->c_point == jbar) agregar(ijbar, i, 0, 0);
			temp= temp->next;
		}
		int size_ijbar = size(ijbar)-1;
		
		if(size_ijbar != 0){
			if (pi == 0) {
				double min = 1e20;
				int idx;
				// buscar en ijbar el elemento con menor
				// distancia, agregar a next_pop
				for(i=0; i<size_ijbar; i++){
					int ijbar_ind = indice(ijbar, i); 
					double ldist = get_dist_list(elite, ijbar_ind);
					if(min > ldist){
						min = ldist;
						idx = ijbar_ind;
					}
				}
				int index_real = indice(elite, idx);
				copiar_ind(next_pop, m, n-K+k, pop[index_real]);
			}else{
				// agregar aleatorio a next_pop
				int add_ind = indice(ijbar, rnd(1, size_ijbar));
				int index_elite = indice(elite, add_ind);
				//         next_pop, n_obj, pos, individuo
				copiar_ind(next_pop, m, n-K+k, pop[index_elite] );
				eliminar(&elite, index_elite);
				eliminar(&ijbar, add_ind);
				size_nondom--;
			}
			k++;
			if(size_ijbar<1)pi++; // <2
		}else{
			// excluir jbar de las proximas busquedas
			printf("ijbar vacio!, excluyendo %d\n", jbar);
			agregar(jexcluded, jbar, 0, 0);
			if(size_jmin == 0) pi++; // == 1
		}
		//if(times > 13) return;
		times++;
	}
	
}

/* fast non-dominated sort, deb, 14 */

void non_dominanted_sort(double **c_pop, double **nextpop, int n, int m, int H, char *fname){
	
	Rseed = 0.9;
	randomize();

	int *dominadas = (int *)calloc(2*n, sizeof(int)); 
	int *nodominadas = (int *)calloc(2*n, sizeof(int));
	int size_dom, size_nondom, current_size=0;
	Node *elite;
	int i, j;
	
	elite = crear_lista(-1);
	// la población pop es la unión de la población actual y la
	// desendencia
	size_nondom =algoritmo3(c_pop, 2*n, m, &nodominadas, &dominadas);
	size_dom = 2*n-size_nondom;

	while( current_size < n ){
		for(i=0; i<size_nondom; i++){
			agregar(elite, nodominadas[i], 0, 0);
		}
		current_size += size_nondom;

		if(current_size >= n) break;

		double **frente_dom = (double **)calloc(size_dom, sizeof(double*));
		for(i=0; i<size_dom; i++){
			frente_dom[i] = (double *)calloc(m, sizeof(double));
		}
		
		for(i=0; i<size_dom; i++){ 
			for(j=0; j<m; j++)
				frente_dom[i][j] = c_pop[dominadas[i]][j];
		}
		
		size_nondom = algoritmo3(frente_dom, size_dom, m, 
				&nodominadas, &dominadas);
		
		for(i=0; i<size_dom; i++)free(frente_dom[i]);
		free(frente_dom);
		
		size_dom -= size_nondom;
	}

	imprimir_lista(elite);
	
	pop(&elite);
	int *elite_arr = (int *)calloc(current_size, sizeof(int));
	lista_a_arreglo(elite, &elite_arr);
	///*contiene los indices de los frentes no dominados, siendo los últimos 
	//los que pertenecen al frente F_l
	//liberar_lista(elite)
	printf("cuurent_size: %d\n", current_size);

	if (current_size == n){
		copiar(c_pop, nextpop, n, m, elite);
	}else{
		double **ref_points;
		int *niche_count = (int *)calloc(H, sizeof(int));
		
		/* copiar los l-1 primeros frentes no dominados*/
		copiar(c_pop, nextpop, current_size-size_nondom, 
				m, elite);
		/* normalizar los puntos de S_t(elite)*/
		double **normalized = normalize(c_pop, elite_arr, current_size, m);
		/* asociar los punto de S_t(elite) con los
		 * puntos de referencia */
		ref_points = archivo_a_arreglo(fname, H, m);
		printf("Normalized\n");
		for(i=0; i<current_size; i++){
			for(j=0; j<m; j++) printf("%lf\t", normalized[i][j]);
			printf("\n");
		}
		printf("Reference points\n");
		for(i=0; i<H; i++){
			for(j=0; j<m; j++) printf("%lf\t", ref_points[i][j]);
			printf("\n");
		}
		associate(normalized, elite, current_size, m, ref_points, H);
				//closest_refpoint,distances);
		printf("ELITE con distancias\n");
		imprimir_lista(elite);
		/* Niche count */
		Node *temp = elite;
		while(temp != NULL){
			niche_count[temp->c_point]++;
			temp = temp->next;
		}
		printf("Niche count\n");
		for(j=0; j<H; j++) printf("%d\n", niche_count[j]);
		/* copiar los n-current_size miembros restantes en next_pop
		 * de entre los K elementos del frente F_l */
		niching(niche_count, elite, H, current_size, 
			size_nondom,  c_pop, nextpop, n, m);

		printf("niching\n");
		free(ref_points);
		free(niche_count);

		for(i=0; i<current_size; i++){
			free(normalized[i]);
		}
		free(normalized);
	}

	liberar_lista(&elite);
	free(dominadas);
	free(nodominadas);
	free(elite_arr);
}

void nsga3(int nvar, int nobj, int N){
	Rseed = 0.0;
	randomize();
	int i, j;
	double lim_inf, lim_sup;

	double **currentGen, **nextGen;
	currentGen = (double **)calloc(N, sizeof(double*));
	nextGen = (double **)calloc(N, sizeof(double*));
	for(i=0; i<nvar; i++){
		currentGen[i] = (double *)calloc(nvar+nobj, sizeof(double);
		nextGen[i] = (double *)calloc(nvar+nobj, sizeof(double);
	}

	init_pop(currentGen, N, nvar, nobj, lim_inf, lim_sup);
}
