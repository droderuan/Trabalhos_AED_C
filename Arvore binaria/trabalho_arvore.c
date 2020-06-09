#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

typedef struct no {
	int ID, idade;
	char sexo[1];
	float salario;
	struct no *filho_esq;
	struct no *filho_dir;
} no;

no* buscarElemento(no *NO, int x, int *f);
no* inserirElemento(no *NO);
no* deletarNo(no *NO, int x);
float mediaSalarial(no *arvore, float salario,int cont,int contNumM,int contNumF);
void abaixoMediaSalaria(no *arvore,float media,int cont,int contNum,int contSal1,int contSal2,int contSal3);
void preOrdem(no *arvore);

int main(){
	no *raiz = NULL;
	int op = 1, x, f;
	while(op != 0){
		system("cls");
		printf("Escolha a operacao");
		printf("\n1- Imprimir pre ordem");
		printf("\n2- Inserir");
		printf("\n3- Deletar");
		printf("\n4- Estatistica");
		printf("\n Escolha um item:");
		scanf("%d", &op);
		switch(op){
			case 1:
				if(raiz != NULL){
					preOrdem(raiz);
				}else{
					printf("\nArvore vazia!");
				}
				break;
			case 2:
				if(raiz == NULL){
					raiz = inserirElemento(raiz);
					printf("\nPessoa inserida na raiz");
				} else {
					inserirElemento(raiz);
				}
				break;
			case 3:
				printf("\nDigite a ID para deletar: ");
				scanf("%d", &x);
				buscarElemento(raiz, x, &f);
	            if (f == 1)
	            {
	                raiz = deletarNo(raiz, x);
	                printf("\nPessoa deletada");
	            }
	            else{
	                printf("\nPessoa nao encontrada");
	        	}
				break;
			case 4:
				if(raiz != NULL){
					//mediaSalarial(raiz,0,0,0,0);
					abaixoMediaSalaria(raiz,mediaSalarial(raiz,0,0,0,0),0,0,0,0,0);
				}else{
					printf("\nArvore vazia!");
				}
				break;
		}
		getch();
	}
	return 0;
}

/*
	Essa fun��o retorna f=0 caso o n� seja nulo
						f=1 caso tenha achado o n�
						f=2 caso tenha achado o n� pai e o elemento ser� um filho
*/
no* buscarElemento(no *NO, int x, int *f){
	if(NO == NULL){             //verifica se o n� raiz (n� de onde a busca ir� partir) � null ou se contem o pr�prio elemento
		*f = 0;
		return NULL;
	} else if(NO->ID == x){
		*f = 1;
		return NO;
	} else if (x < NO->ID){			//verifica se a busca vai para a esquerda e se o filho da esquerda � null, se n�o entra numa outra chamada recursiva
		if (NO->filho_esq == NULL){
			*f = 2;
			return NO;
		} else{
			buscarElemento(NO->filho_esq, x, f);
		}
	}else if( NO->filho_dir == NULL){			//verifica se a busca vai para a direita e se o filho da direita � null, se n�o entra numa outra chamada recursiva
			*f = 2;
			return NO;
		} else{
			buscarElemento(NO->filho_dir, x, f);
		}
}

no* inserirElemento(no *NO){  //nao usar o nome da variavel com a mesma da struct, pois ir� haver conflito na declara��o de outras structs com o nome da variavel. Ex: no* no
	no *newNo, *aux;
	int f, ID;
	printf("\n\nDigite a ID: ");
	scanf("%d", &ID);
	aux = buscarElemento(NO, ID, &f);

	if(f == 1){
		return NULL;
	} else {
		
		newNo = malloc(sizeof(no));
		printf("\nIdade: ");
		scanf("%d", &newNo->idade);
		printf("\nSexo M ou F: ");
		scanf("%s", &newNo->sexo);
		while((strcmp(newNo->sexo, "F") != 0) && (strcmp(newNo->sexo, "M") != 0)){
			printf("\nSexo invalido\nDigite novamente: ");
			scanf("%s", &newNo->sexo);
		}
		printf("\nSalario: ");
		scanf("%f", &newNo->salario);
		newNo->ID = ID;
		newNo->filho_dir = NULL;
		newNo->filho_esq = NULL;
		
		
		if(f == 0){
			return newNo;
		} else if(f == 2){
			if(newNo->ID < aux->ID){
				printf("\nPessoa inserido como filho esquerdo da ID : %d", aux->ID);
				aux->filho_esq = newNo;
			}else{
				printf("\nPessoa inserido como filho direito da ID : %d", aux->ID);
				aux->filho_dir = newNo;
			}
		}
	}
}

no* deletarNo(no *NO, int x){
	no *pt, *pt1;
	if (NO == NULL){
		return NULL;
	} else if( NO->ID == x){
		if (NO->filho_dir == NO->filho_esq){   // se for uma folha parte pro abra�o
			free(NO);
			NO = NULL;
			return NULL;

		} else if(NO->filho_esq == NULL){   // se tiver s� filho a direita, o no recebe o seu filho e � deletado
			printf("\nEsq == null");
			pt = NO;
			NO = NO->filho_dir;
			free(pt);
			return NO;
		} else if (NO->filho_dir == NULL){   // se tiver s� filho a esquerda, o no recebe o seu filho e � deletado
			printf("\nDir == null");
			pt = NO;
			NO = NO->filho_esq;
			free(pt);
			return NO;
		}else{
			pt = NO;
			pt1 = NO->filho_esq;
			if(pt1->filho_dir == NULL){
				NO->ID = pt1->ID;
				NO->filho_esq = pt1->filho_esq;
				free(pt);
			}else{
				while(pt1->filho_dir != NULL){
					pt = pt1;
					pt1 = pt1->filho_dir;
				}

				NO->ID = pt1->ID;
				pt->filho_dir = pt1->filho_esq;
				free(pt1);
			}
		}
	}
	if(x > NO->ID){
		NO->filho_dir = deletarNo(NO->filho_dir, x);
	}else{
		NO->filho_esq = deletarNo(NO->filho_esq, x);
	}
	return(NO);
}

void preOrdem(no *arvore){
	printf("\n**********");
	printf("\nID: %d\n", arvore->ID);
	printf("\nIdade: %d\n", arvore->idade);
	printf("\nSexo: %s\n", arvore->sexo);
	printf("\nSalario: R$%.2f", arvore->salario); //o .2 no %.2f delimita a exibi��o para 2 casas decimais
	if(arvore->filho_esq != NULL){
		preOrdem(arvore->filho_esq);
	}
	if(arvore->filho_dir != NULL){
		preOrdem(arvore->filho_dir);
	}
}


float mediaSalarial(no * pt,float salario,int cont, int contNumM,int contNumF){
	cont++;
	salario = salario + pt->salario;
	
	if(strcmp(pt->sexo, "M") == 0){
		contNumM = contNumM + 1;
	}else{
		contNumF = contNumF + 1;	
	}
	
	
	if (pt->filho_esq != NULL){
		mediaSalarial(pt->filho_esq,salario,cont,contNumM,contNumF);
	} 
   	if (pt->filho_dir != NULL){
   		mediaSalarial(pt->filho_dir,salario,cont,contNumM,contNumF);
   	}
   
   if(pt->filho_dir == NULL && pt->filho_esq == NULL ){
   		salario = salario/cont;
		printf("\nA m�dia salarial dos trabalhadores R$%.2f",salario);
		printf("\nHomens: %i",contNumM);
		printf("\nMulheres: %i",contNumF);
   		return salario;
   }
   
}

void abaixoMediaSalaria(no *pt,float media,int cont,int contNum,int contSal1,int contSal2,int contSal3){
	cont++;
	
	if(pt ->salario <= 2000){
		contSal1++;
	}
	
	if(pt ->salario > 2000 && pt->salario <= 4000){
		contSal2++;
	}
	
	if(pt ->salario > 4000){
		contSal3++;
	}
	
	if(pt->salario < media){
		contNum = contNum + 1;
	}
	
	if (pt->filho_esq != NULL){
		abaixoMediaSalaria(pt->filho_esq,media,cont,contNum,contSal1,contSal2,contSal3);
	} 
   	if (pt->filho_dir != NULL){
   		abaixoMediaSalaria(pt->filho_dir,media,cont,contNum,contSal1,contSal2,contSal3);
   	}
   
   if(pt->filho_dir == NULL && pt->filho_esq == NULL ){
   		contNum = (contNum * 100)/cont;
   		contSal1 =(contSal1 * 100)/cont;
		contSal2 =(contSal2 * 100)/cont;
		contSal3 =(contSal3 * 100)/cont ;  
	printf("\nAbaixo da Media Salarial: %i%s\n",contNum,"%");
	printf("Ganham menos que R$2000,00: %i%s\n",contSal1,"%");
	printf("Ganham entre R$2000,00 e R$4000,00: %i%s\n",contSal2,"%");
	printf("Ganham mais que R$4000,00: %i%s\n",contSal3,"%");
   	}
}	
