#include"dominancia/tarea01.h"

/* normaliza la población general y los puntos de referencia */
double **normalize(double **pop, int * elite_arr, int curr_size, int m, double **ref_points, 
		   int H){
	int i,j;
        double	min, scl;
	double *ideal_point = (double *)calloc(m, sizeof(double));
	double **norm = (double **)calloc(current_size, sizeof(double *));
	double *a = (double *)calloc(m, sizeof(double));
	/*identify the ideal point for each objective function*/
	for(i=0; i<m; i++){
		min = pop[elite_arr[0]][i]
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
	for(i=0; i<m; i++){
		min = 1e20;
		memset(w, 0, sizeof(w));
		w[i] = 1;
		for(j=0; j<curr_size; j++){ 
			scl = scl_fun(pop[elite_arr[j]], w); 
			if(min > scl) min = scl;
		}
		a[i] = min;
	}
	/* Normalize objectives f_i^n(x) = f_i'(x)/a_i */
	for(i=0; i<curr_size; i++){
		for(j=0; j<m; j++){
			norm[i][j] /= a[j];
		}
	}

	free(a);
	free(ideal_point);

	/*Generar H puntos de referencia*/
	ref_points = archivo_a_arreglo("ref.txt", H, m);

}

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

/* asocia un punto en normalized con un punto de referencia y calcula su distancia al mismo  */
void associate(double **normalized, Node* elite, int curr_size, int m, double **ref_points, int H);
//void associate(double **normalized, int curr_size, int m, double **ref_points, int H){
	       //int *closest_refpoint, double *distances, int H){
	double menor=1e20, dst, index;
	//closest_refpoint = (int *)calloc(curr_size, sizeof(int));
	//distances = (double *)calloc(curr_size, sizeof(double));
	/* para cada punto s en normalized */
	
	for(int i=0; i<curr_size; i++){
		/*para punto de referncia*/
		for(int j=0; j<H; j++){
			dst = dist(ref_point[j], normalized[i],m)
			if(menor > dst){
				menor = dst; 
				index = j;
			}
		}
		set_info_list(elite, i+1, index, menor);
		//closest_refpoint[i] = index;
		//distances[i] = menor;
	}	 
}

double dist(double *w, double *s, int m){
	int res=0;
	double wsw[m];
	for(int i=0; i<m; i++){
		for(int j=0; j<m; j++){
			res += w[i] * s[j];	
		}
	}
	for(int i=0; i<m; i++){
		wsw[i] = res * w[i];
		wsw[i] /= norm2(w[i], m);
	}
	return norm2(wsw, m);

}

double norm2(double *w, int m){
	double res=0;
	for(int i=0; i<m; i++){
		res += fabs(w[i])*fabs(w[i]);
	}
	return sqrt(res);
}

/* seleccionar los elementos faltantes para llevar nextpop */
void niching(int *niche_count, Node *elite, int H, int size_nondom, 
	     double **pop, double **next_pop, int n, int m){
	
	int k = 0, K = n - (curr_size-size_nondom), pi=0;
	int i, j, jbar;
	Node *jmin, *ijbar, *jexcluded; 
	jmin = crear_lista(-1);
	ijbar = crear_lista(-1);
	jexcluded = crear_lista(-1);
	
	while(k<K){
		// Buscar los miembros de ref_point con niche_count == pi
		// y ponerlos en una lista (jmin)
		liberar_lista(&jmin->next);
		for(i=0; i<H; i++){
			if(buscar(jexclude, i) == 0){
				if(niche_count[i] == pi) agregar(jmin, i);
			}
		}
		int size_jmin = size(jmin)-1;

		if(size_jmin > 0){
		// si jmin no está vacío, elegir un miembro al azar 
			jbar = indice(jmin, rnd(1, size_jmin+1));
			//jbar es el indice de un punto de referencia
		}else{
		// si jmin está vacío, aumentar pi (niche count)
		// y volver a armar jmin
			pi++;
			continue;
		}
		// buscar las posiciones de elite que corresponda(n) a jbar
		liberar_lista(&ijbar->next);
		Node *temp = elite->next;
		int il =0;
		while(il<current_size-non_dom){
			temp = temp->next;
		}
		for(i=current_size-non_dom+1;i<current_size+1; i++){
			if(temp->c_point == jbar) agregar(ijbar, i);
			temp= temp->next;
		}

		int size_ijbar = size(ijbar)-1;
		if(size_ijbar != 0){
			if (pj == 0) {
				int min = 1e20;
				int idx;
				// buscar en ijbar el elemento con menor
				// distancia, agregar a next_pop
				for(i=0; i<size_ijbar; i++){
					int ijbar_ind = indice(ijbar, i+1); 
					int ldist = get_dist_list(lista, ijbar_ind);
					if(min > ldist){
						min = ldist;
						idx = ijbar_ind;
					}
				}
				int index_real = indices(elite, idx+1);
				copiar_ind(next_pop, m, n-K-1, pop[index_real]);
			}else{
				// agregar aleatorio a next_pop
				int add_ind = indice(ijbar, rnd(1, size_ijbar+1));
				int index_elite = indice(elite, add_ind+1);
				//         next_pop, n_obj, pos, individuo
				copiar_ind(next_pop, m, n-K+k, pop[index_elite] );
				eliminar(elite, add_ind+1)
			}
			k++;
			pi++;
		}else{
			// excluir jbar de las proximas busquedas
			agregar(jexcluded, jbar);
		}
	}
	
}

/* fast non-dominated sort, deb, 14 */

void non_dominanted_sort(double **pop, double **nextpop, int n, int m, int H){
	
	int *dominadas = (int *)calloc(2*n, int); 
	int *nodominadas = (int *)calloc(2*n, int);
	int size_dom, size_nondom, current_size=0;
	Node *elite;
	//int *elite_arr;
	int i, j;
	
	crear_lista(elite);
	agregar(elite, -1);
	// la población pop es la unión de la población actual y la
	// desendencia
	size_nondom =algoritmo3(pop, 2*n, m, nodominadas, dominadas);
	size_dom = n-size_nondom;
	
	while( current_size < n ){
		for(i=0; i<size_nondom; i++){
			agregar(elite, nodominadas[i]);
		}
		current_size += size_nondom;
		
		if(current_size >= n) break;

		double **frente_dom = (double **)calloc(size_dom, sizeof(double*));
		for(i=0; i<size_dom; i++){
			frente_dom = (double *)calloc(m, sizeof(double));
		}
		
		for(i=0; i<size_dom; i++){ 
			for(j=0; j<m; j++)
				frente_dom[i][j] = datos[dominadas[i]][j];
		}
		
		size_nondom = algoritmo3(frente_dom, size_dom, m, 
				nodominadas, dominadas);
		
		for(i=0; i<size_dom; i++)free(frente_dom[i]);
		free(frente_dom);
		
		size_dom = n-size_nondom;
	}
	
	//pop(&elite);
	//elite_arr = lista_a_arreglo(elite); 
	///*contiene los indices de los frentes no dominados, siendo los últimos 
	//los que pertenecen al frente F_l*/
	//liberar_lista(elite);

	if (current_size == n){
		copiar(pop, next_pop, n, m, elite);
	}else{
		double **ref_points, *distances;
		int *closest_refpoint;
		int *niche_count = (int *)calloc(H, sizeof(int));
		
		/* copiar los l-1 primeros frentes no dominados*/
		copiar(pop, next_pop, current_size-size_nondom, 
				m, elite);
		/* normalizar los puntos de S_t(elite)*/
		double **normalized = normalize(pop, elite, 
				current_size, m, ref_points, H);
		/* asociar los punto de S_t(elite) con los
		 * puntos de referencia */
		associate(normalized, elite, current_size, m, ref_points, H);
				//closest_refpoint,distances);
		/* Niche count */
		for(j=0; j<current_size; j++){
			niche_count[closest_refpoint[j]]++;
		}
		/* copiar los n-current_size miembros restantes en next_pop
		 * de entre los K elementos del frente F_l */
		niching(niche_count, closest_refpoint, distances,  H, 
			elite, size_nondom,  pop, next_pop, n, m);

		free(ref_points);
		free(closest_refpoint);
		free(distances);
		free(niche_count);

	}

	free(dominadas);
	free(nodominadas);
	for(i=0; i<current_size; i++){
		free(normalized[i]);
	}
	free(normalized);
}
