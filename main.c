#include <stdio.h> 
#include <stdlib.h>
#include <math.h>	

#define PI 3.14 
#define TAILLE_TAB 100

typedef enum{
	RLS, RLP,RCP,RCS,LCS,LCP
} circuit_t; 


// --------------------------
// 	Fonctions : API 
// --------------------------

void val_components(unsigned char *circuit, double *R, double *L,double *C);
void val_freq(float *fMin, float *fMax, int *num_freq); 
void calc_module(unsigned char *circuit, int *num_freq, double *mod, double *R, double *L, double *C, const float *fMax, const float *fMin, double mod_tab[], double omegas_tab[]);
void calc_phase(void); 
void print(void);

// ---------------------------------------
// 	Fonctions internes au programme 
// ---------------------------------------

void list_circuits(unsigned char *circuit); 

// Fonctions calcul de modules 
void modRLS(double *R, double *L, int *num_freq, const float *fMax, const float *fMin, double omegas_tab[], double mod_tab[]);
void modRLP(double *R, double *L, int *num_freq, const float *fMax, const float *fMin, double omegas_tab[], double mod_tab[]);

void modRCS(double *R, double *C, double *mod);
void modRCP(double *R, double *C, double *mod);

void modLCS(double *L, double *C, double *mod);
void modLCP(double *L, double *C, double *mod);
 
int main(){

	char circuit = 0; 
	double R,C,L = 0; 
	float fMin=0,fMax=0;
	int num_freq=0; 
	double mod = 0; 
	double phase = 0; 
	
	double mod_tab[TAILLE_TAB] = {0};
	double omegas_tab[TAILLE_TAB] = {0};
	
	
	
	// Main logic 
	val_components(&circuit,&R,&L,&C); 
	val_freq(&fMin,&fMax,&num_freq);
	calc_module(&circuit,&num_freq,&mod,&R,&L,&C, &fMax, &fMin, mod_tab, omegas_tab);


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
		printf("Vous avez choisi R = %.2lf et C = %.2lf\n",*R,*C);
	} else {
		printf("Valeur de L : \n");
		scanf("%lf",L);
		printf("Valeur de C : \n");
		scanf("%lf",C);
		printf("Vous avez choisi L = %.2lf et C = %.2lf\n",*L,*C);
	}
	
}

void val_freq(float *fMin, float *fMax, int *num_freq){

	// Variable logique boolean pour le choix d'une plage de frequence ou une seule 
	int plage_freq = 0; 

	printf("*********************************************************************************************************\n");
	printf("* Vous voulez calculer l'impedance pour une frequence specifique ou une plage de frequences ?           *\n");
	printf("* 	Tappez 0 pour une frequence ou 1 pour une plage de frequences :                                     *\n");
	printf("*********************************************************************************************************\n");

	scanf("%d",&plage_freq);

	if (plage_freq){ 
		printf("Indiquez votre frequence maximale souhaitee\n");
		scanf("%f",fMax);
		printf("Indiquez votre frequence minimale souhaitee\n");
		scanf("%f",fMin);
		printf("Nombre de frequences a calculer entre la frequence maximale et minimale\n");
		scanf("%d",num_freq);
		printf("Vous avez choisi une plage entre %.2f et %.2f et un pas de %d\n",*fMax,*fMin,*num_freq); 
	}else{ 
	
		printf("Indiquez la frequence souhaitee\n");
		scanf("%f",fMax);
		printf("Vous avez choisi une frequence a %.2f \n",*fMax);
	}
	
}

void calc_module(unsigned char *circuit, int *num_freq, double *mod, double *R, double *L, double *C, const float *fMax, const float *fMin, double mod_tab[], double omegas_tab[]){

	// Valeurs des impedances au carre X1
	double R1 = (*R)*(*R);
	double L1 = (*L)*(*L);
	double C1 = (*C)*(*C);
	
	// Cas num_freq = 0 -> Une seule frequence 
	double omega0 = (2.0)*PI*(*fMax);
	
	
	
	if (*num_freq){
		
		// Plusiers frequences 
		
		switch (*circuit){
			
			case 1 : 
				modRLS(R, L, num_freq, fMax, fMin, mod_tab, omegas_tab);
				break; 
			case 2 : 
				modRLP(R, L, num_freq, fMax, fMin, mod_tab, omegas_tab);
				break;
			default : 
				printf("ERROR : Circuit parallel non identifie\n");	
				break;
		}
	}else{
		
		// Une frequence unique 
		switch (*circuit){
			// RL series 
			case 1 : 
				L1 = L1*((omega0*omega0));
				*mod = sqrt(L1+R1);
				printf("***		Circuit RL serie 		***\n");
				printf("Le module calculee est : %.4lf\n", *mod);
				break;
			// RC serie
			case 3 : 
				C1 = 1/(C1*((omega0*omega0)));
				*mod = sqrt(C1+R1);
				printf("***		Circuit RC serie 		***\n");
				printf("Le module calculee est : %.4lf\n", *mod);
				break;
			// LC serie 
			case 5 : 
				L1 = L1*((omega0*omega0));
				C1 = 1/(C1*((omega0*omega0)));
				*mod = sqrt(L1+R1);
				printf("***		Circuit LC serie 		***\n");
				printf("Le module calculee est : %.4lf\n", *mod);
				break;
				
			// RL Parallel 
			case 2 : 
				L1 = L1*((omega0*omega0));
				*mod = fabs(((*R)*(*L)*(omega0)))/sqrt(L1+R1);
				printf("***		Circuit RL Parallel 		***\n");
				printf("Le module calculee est : %.4lf\n", *mod);
				break;
				
			// RC Parallel 
			case 4 : 
				*mod = fabs((*R)/sqrt(1+((R1*C1*omega0*omega0))));
				printf("***		Circuit RC Parallel 		***\n");
				printf("Le module calculee est : %.4lf\n", *mod);
				break;
			
			// LC Parallel 
			case 6 : 
				*mod = fabs(((*L)*(omega0))/(1-(omega0*omega0)*((*L)*(*C))));
				printf("***		Circuit LC Parallel 		***\n");
				printf("Le module calculee est : %.4lf\n", *mod);
				break;
			
			default : 
				printf("ERROR : Circuit serie non identifie\n");
				break;
		}	
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

// Fonctions calcul de modules 

void modRLS(double *R, double *L, int *num_freq, const float *fMax, const float *fMin, double omegas_tab[], double mod_tab[])
{
	
	
	double R1 = (*R)*(*R);
	double L1 = (*L)*(*L);
	
	double omega0 = (2.0)*PI*(*fMin);
	double omega1 = (2.0)*PI*(*fMax);

	double pas_omega = fabs((omega1-omega0)/(*num_freq));
	
		
	// Tableaux avec pulsations 
	for (int i = 0; i < *num_freq ; i++){
		*(omegas_tab + i) = pas_omega*(i+1);  
	}
	
	// Tableaux avec modules
	for (int i = 0; i< *num_freq; i++){
		*(mod_tab + i) = sqrt( ((*R)*(*R)) + (omegas_tab[i]*((*L)*(*L))) );

	}
	
	// Affichage modules
	printf("Modules pour le RL series : \n");

	for (int i = 0 ; i< *num_freq; i++){
		printf("Freq : %.2lf et Module : %.2lf\n",(omegas_tab[i])/(2*(3.14)),mod_tab[i]);
	}
	
	
}


void modRLP(double *R, double *L, int *num_freq, const float *fMax, const float *fMin, double omegas_tab[], double mod_tab[])
{
	double R1 = (*R)*(*R);
	double L1 = (*L)*(*L);
	
	double omega0 = (2.0)*PI*(*fMin);
	double omega1 = (2.0)*PI*(*fMax);

	double pas_omega = fabs((omega1-omega0)/(*num_freq));
	
		
	// Tableaux avec pulsations 
	for (int i = 0; i < *num_freq ; i++){
		*(omegas_tab + i) = pas_omega*(i+1);  
	}
	
	// Tableaux avec modules
	for (int i = 0; i< *num_freq; i++){
		*(mod_tab + i) = fabs(((*R)*(*L)*(omegas_tab[i])))/sqrt(L1+R1);
	}
	
	// Affichage modules
	printf("Modules pour le RL series : \n");

	for (int i = 0 ; i< *num_freq; i++){
		printf("Freq : %.2lf et Module : %.2lf\n",(omegas_tab[i])/(2*(3.14)),mod_tab[i]);
	}
}

/*
void modRCS(double *R, double *C, double *mod);
void modRCP(double *R, double *C, double *mod){



				*(mod_tab+i) = fabs((*R)/sqrt(1+((R1*C1*(omega_tab[i]*omega_tab[i]))));


};

void modLCS(double *L, double *L, double *mod);
void modLCP(double *L, double *L, double *mod);
*/