#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argv, char **argc){

	FILE *input;
	input=fopen(argc[1], "r");

	int par1, par2;
	float par3, par4, par5, par6, par7;
	char cmd[100], teste[100];
	int a,b;

	a=128;
	while(a--){
		fscanf(input, "%d %d %f %f %f %f %f", &par1, &par2, &par3, &par4, &par5, &par6, &par7);
		sprintf(cmd, "./simulation ../graph/facebook %d %d %.2f %.2f %.2f %.2f %.2f\n", par1, par2, par3, par4, par5, par6, par7);
		//printf("-------\n\n%s", cmd);
		for(b=0;b<20;b++){
		system(cmd);
		sleep(1);
		}
	}

//	printf("\n\nData from default values. \n\n");
	sprintf(cmd, "./simulation ../graph/facebook 5 1 0.5 0.5 0.5 0.5 0.5\n");
	for(a=0;a<20;a++){
		system(cmd);
		sleep(1);
	}


	return 0;
}
