#include <stdio.h> 

typedef enum{
	RLS, RLP,RCP,RCS,LCS,LCP
} circuit_t; 


// --------------------------
// 	Fonctions : API 
// --------------------------

void val_components(unsigned char *circuit, double *R, double *L,double *C);
void val_freq(int *fMin, int *fMax, int *num_freq); 
void calc_module(void);
void calc_phase(void); 
void print(void);

// ---------------------------------------
// 	Fonctions internes au programme 
// ---------------------------------------

void list_circuits(unsigned char *circuit); 
 
int main(){

	char circuit = 0; 
	double R,C,L = 0; 
	int fMin=0,fMax=0,num_freq=0; 
	
	
	// Main logic 
	val_components(&circuit,&R,&L,&C); 


	return 0; 
}

// --------------------------
// 	Fonctions : API 
// --------------------------

void val_components(unsigned char *circuit, double *R, double *L, double *C){

	// Affichage des circuits et saisie de circuit
	list_circuits(circuit); 
	// Choix des composants 
	
	if ((*circuit) <= 2){
		printf("Valeur de R : \n");
		scanf("%lf",R);
		printf("Valeur de L : \n");
		scanf("%lf",L);
		printf("Vous avez choisi R = %.2lf et L = %.2lf\n",*R,*L);
	}else if ((*circuit == 3) || (*circuit == 4)){
		printf("Valeur de R : \n");
		scanf("%lf",R);
		printf("Valeur de C : \n");
		scanf("%lf",C);
		printf("Vous avez choisi R = %.2lf et C = %.2lf\n",*R,*L);
	} else {
		printf("Valeur de L : \n");
		scanf("%lf",C);
		printf("Valeur de C : \n");
		scanf("%lf",C);
		printf("Vous avez choisi L = %.2lf et C = %.2lf\n",*L,*C);
	}
	
}

void val_freq(int *fMin, int *fMax, int *num_freq){

	// Variable logique boolean pour le choix d'une plage de frequence ou une seule 
	int plage_freq = 0; 

	printf("*********************************************************************************************************\n");
	printf("* Vous voulez calculer l'impedance pour une frequence specifique ou une plage de frequences ? *\n");
	printf("* 	Tappez 0 pour une frequence ou 1 pour une plage de frequences                             *\n");
	printf("*********************************************************************************************************\n");


	if (plage_freq){ 
		printf("Indiquez votre frequence maximale souhaitee"\n);
		scanf("%d",fMax);
		printf("Indiquez votre frequence minimale souhaitee"\n);
		scanf("%d",fMin);
		printf("Nombre de frequences a calculer entre la frequence maximale et minimale\n");
		scanf("d",num_freq);
		printf("Vous avez choisi une plage entre %d et %d\n",*fMax,*fMin); 
	}else{ 
	
		printf("Indiquez la frequence souhaitee"\n);
		scanf("%d",fMax);
		printf("Vous avez choisi une frequence a %d \n",*fMax);
	}
	
}


// ---------------------------------------
// 	Fonctions internes au programme 
// ---------------------------------------


void list_circuits(unsigned char *circuit){
	printf("*********************************\n");
	printf("*	Calcul d'impedance	*\n"); 
	printf("*	Liste des circuits :	*\n");
	printf("*********************************\n");
	printf("\n");
	printf("Choix du circuit\n");
	printf("	1. RL serie	\n");
	printf("	2. RL parallel	\n");
	printf("	3. RC serie	\n");
	printf("	4. RC parallel	\n");
	printf("	5. LC serie	\n");
	printf("	6. LC parralel	\n");
	printf("Choissisez un circuit :   ");
	// On peut securiser plus cette saisie
	printf("\n");
	scanf("%hhu",circuit); 
	printf("Circuit choisi : %hhu\n",*circuit);
}
