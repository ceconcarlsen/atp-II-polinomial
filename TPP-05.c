#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <string.h>
#include <time.h>


//TPP-05  GABRIEL CECON CARLSEN  15/12/2019



// STRUCT
typedef struct no {
	double coef;
	int expo;
	struct no *prox, *ant;
}NO;
//*************************************************************


// FUNÇÕES
NO* InserePolinomio(NO *atual){

	int n,i=0;

	do{
		printf("\nInsira o grau do polinômio (0<=n<=100): ");
		scanf("%i",&n);
		if (n>100 || n<0){
			printf("\nERRO !!!\n");
		}
	}while(n>100 || n<0);


	NO *novo =(NO*)malloc(sizeof(NO)); //alocando espaço de memória
	printf("\nCoef. do grau º%i:",i);
	scanf("%lf",&novo->coef);
	novo->expo=i;
	novo->ant=NULL;
	novo->prox=NULL;
	atual=novo;


	for(int j=1; j<=n;j++){
		NO *novo = (NO*)malloc(sizeof (NO));
		printf("Coef. do grau º%i:", j);
		scanf("%lf", &novo->coef);
		novo->expo= j;
		novo->ant= atual;
		atual->prox = novo;
		novo->prox=NULL;
		atual = novo;
	}

	printf("\n\n");

	return(atual);
}
//*************************************************************


//*************************************************************
NO* Insere_Com_Parametro(NO *atual, int exp, double cf){
		NO *novo = (NO*)malloc(sizeof (NO));
		novo->coef= cf;
		novo->expo= exp;

	if(atual == NULL){
		novo->ant= NULL;
		novo->prox=NULL;
	}
	else {
		novo->ant= atual;
		atual->prox = novo;
		novo->prox=NULL;
	}

	atual = novo;

	return atual;
}
//*************************************************************


//*************************************************************
void ImprimePolinomio(NO *atual){

	NO *aux=atual;

	while(aux!=NULL){
	 	if (aux->ant!=NULL){
		printf("|%lf x^%i|  (+)",aux->coef,aux->expo);
	}
		else printf("|%lf x^%i|  ",aux->coef,aux->expo);
		aux=aux->ant;

	}
	printf("\n\n");
}
//*************************************************************


//*************************************************************
void SomaPolinomio(NO *atual, NO *atual2){
	int j=0, i=0;

	if (atual->expo > atual2->expo) j = atual->expo;

	else if (atual->expo <= atual2->expo) j = atual2->expo;

	NO *aux =atual;
	NO *aux2 =atual2;
	NO *aux3 = NULL;

	for (i = 0; i<=j; i++) {
		while((aux!= NULL) && (aux2!=NULL) ){
	        if(aux->expo == aux2->expo){
				aux3 = Insere_Com_Parametro(aux3, aux->expo, aux->coef + aux2->coef);
				aux= aux->ant;
				aux2= aux2->ant;
	        }
	        else if(aux->expo > aux2->expo) {
	        	aux3 = Insere_Com_Parametro(aux3, aux->expo, aux->coef);
	            aux = aux->ant;
	        }
			else if (aux->expo < aux2->expo) {
				aux3 = Insere_Com_Parametro(aux3, aux2->expo, aux2->coef);
				aux2 = aux2->ant;
			}
	    }
	}

	printf("\n O polinômio SOMA é: ");
	ImprimePolinomio(aux3);

    return;
}
//*************************************************************


//*************************************************************
void MultiplicaPolinomio(NO *atual, NO *atual2){

	NO *aj=NULL;

    	for(NO *aux =atual; aux != NULL; aux= aux->ant){
     		for(NO *aux2 =atual2; aux2 != NULL; aux2= aux2->ant){
     			aj=Insere_Com_Parametro(aj, aux->expo + aux2->expo, aux->coef * aux2->coef);
			}
		}

		NO *aux3= aj;

		for(; aux3 != NULL; aux3= aux3->ant){
			NO *aux4= aux3->ant;
			for(; aux4 != NULL; aux4= aux4->ant){
				if(aux3->expo == aux4->expo){
					aux3->coef= aux3->coef + aux4->coef;
					aux4->ant->prox= aux4->prox;
					aux4->prox->ant= aux4->ant;
				}
			}
		}


    printf("\n O polinômio MULTIPLICAÇÃO é: ");
    ImprimePolinomio(aj);

    return;
}
//*************************************************************


//*************************************************************
void MultiplicaConstante (NO *atual){
	int k;

	printf("\n Insira a constante K:");
	scanf("%i", &k);

	NO *aux =atual;

	while (aux!=NULL){  //passeando pelo polinômio
		aux->coef = aux->coef * k;
		aux = aux->ant; //atualizando o aux
	}

	ImprimePolinomio(atual);

    return;
}
//*************************************************************


//*************************************************************
void Pol_X (NO *atual){
	int x, resultado=0;

	printf("\n\n Insira o X para o cálculo: ");
	scanf("%i",&x);
	NO *aux=atual;

	while(aux!=NULL){
		resultado+=aux->coef*(pow (x,aux->expo));
		aux=aux->ant;
	}

	printf("\n\n Resultado do polinômio em %i: %i",x,resultado);

    return;
}
//*************************************************************

//*************************************************************
void TermoGrau (NO *atual){

	NO *aux =atual;
	int grau=aux->expo,termos=0;

	while (aux != NULL){
		aux = aux->ant;
		termos++;
	}

	printf("\n Contém %i termos com grau %i !!!", termos,grau);

    return;
}
//*************************************************************


//*************************************************************
void DerivadaPolinomio (NO *atual){
	NO *aux =atual;

	while (aux->ant != NULL){
		aux->coef = aux->coef * aux->expo;
		aux->expo = aux->expo - 1;
	    aux = aux->ant;

		if (aux->ant == NULL){
	   	aux->prox->ant = NULL;
	   	free(aux);
	   }
	}

    printf("\n");

	ImprimePolinomio(atual);

    return;
}
//*************************************************************

//*************************************************************
void IntegralPolinomio(NO *atual){
		NO *aux =atual;

	while (aux != NULL){
		aux->expo = aux->expo  +1;
		aux->coef = aux->coef / aux->expo;
		aux = aux->ant;
	}

	  printf("\n");

	ImprimePolinomio(atual);

	return;
}
//*************************************************************


// MAIN
int main (void){
	setlocale(LC_ALL,"Portuguese");

    NO *atual=NULL;
	NO *atual2=NULL;

	int m=0,repete=0;
	printf("TPP-05\t\t\t\tSistema de manipulação polinomial\t\t\t\t*Gabriel Cecon Carlsen\n");
	printf("\n");
	atual = InserePolinomio(atual);
	atual2 = InserePolinomio(atual2);



	do{
            system ("cls");

	printf("\n [MENU] - MANIPULAÇÃO\n");
	printf("\n 1 - Impressão de polinômios");
	printf("\n 2 - Somar polinômios");
	printf("\n 3 - Multiplicar polinômios");
	printf("\n 4 - Calcular polinômio em um X específico");
	printf("\n 5 - Multiplicar um polinômio por uma constante K");
	printf("\n 6 - Calcular derivada de um polinômio");
	printf("\n 7 - Calcular integral de um polinômio");
	printf("\n 8 - Determinar o grau e número de termos do polinômio\n");

	printf("\n Escolha uma opção: ");
	scanf("%i",&m);


		switch (m){

   		case 1:
                printf("\n Imprimir o polinômio 1 ou 2 ?: ");
                scanf("%i",&m);

                printf("\n");

                if (m==1){
                    ImprimePolinomio(atual);
                   }
                else if (m==2){
                    ImprimePolinomio(atual2);
                   }
                   else printf("ERRO !!! - Opção invalida");
                break;


		case 2:
                SomaPolinomio(atual,atual2);
                break;


		case 3:
                 MultiplicaPolinomio(atual,atual2);
                break;


		case 4:
                printf(" Calcular o polinômio 1 ou 2?:");
                scanf("%i", &m);

                if (m==1){
   				Pol_X(atual);
			   }
                else if (m==2){
   				Pol_X(atual2);
			   }
			   else printf("ERRO !!! - Opção invalida");
               break;


		case 5:

                printf(" Multiplicar o polinômio 1 ou 2?:");
                scanf("%i",&m);

                if(m==1){
                    MultiplicaConstante(atual);
                }
                else if(m==2){
                    MultiplicaConstante(atual2);
			   }
			   else printf("ERRO !!! - Opção invalida");
               break;


		case 6:

                printf(" Calcular a derivada 1 ou 2?:");
                scanf("%i",&m);

                if(m==1){
                    DerivadaPolinomio(atual);
                   }
                else if(m==2){
                    DerivadaPolinomio(atual2);
                   }
                   else printf("ERRO !!! - Opção invalida");
                   break;



		case 7:
                printf(" Calcular a integral 1 ou 2?:");
                scanf("%i", &m);

                if(m==1){
                    IntegralPolinomio(atual);
                   }
                else if(m==2){
                    IntegralPolinomio(atual2);
                   }

                   else printf("ERRO !!! - Opção invalida");
                   break;


		case 8:
                printf(" Grau e número de termos do 1 ou 2?:");
                scanf("%i",&m);

                if(m==1){
                    TermoGrau(atual);
                   }
                else if(m==2){
                    TermoGrau(atual2);
                   }

                   else printf("Opção inválida");
                   break;

		default:
			printf("\n\n ERRO !!! - Opção invalida\n\n");
			system("pause");
			repete=1;
            break;
}

}while(repete);


printf("\n\n\n");
system("pause");
return 0;
}
