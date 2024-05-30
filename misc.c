#include"global.h"

int factorial(int x){
	int res=1;
	for(int i=x; i>=0; i--){
		res*=i;
	}
	return res;
}
