# nsga3
Implementation of the nsga3 algorithm in C

La implementación de NSGA-III consiste de los siguientes archivos
- nsga3.c # main loop de NSAG-III
- evop.c # operadores de evolución y mutación
- pop.c  # archivo con las estructura de la poblacion,
	  funciones para inicialiazar
- sort.c # archivo con el ordenamiento no dominado
- misc.c # miscelaneos: generar los puntos con el método Das-Dennis
	  normalizar objetivos, calculo de distancia, asociacion con puntos de
	  referencia

La estructura principal sería un arreglo unidimensional de tamaño N * m 
