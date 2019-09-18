#include <stdio.h>
#include <stdlib.h>

typedef struct no {
	int data;
	struct no *filho_esq;
	struct no *filho_dir;
} no;

no* buscarElemento(no *no, int x, int *f);
no* inserirElemento(no *no, int x);

void preOrdem(no *arvore);

int main(){
	no *raiz = NULL;
	int x;
	preOrdem(raiz);
	
	printf("\ndigite: ");
	scanf("%d", &x);
	if(raiz == NULL){
	raiz = inserirElemento(raiz, x);
	}
	printf("\ndigite: ");
	scanf("%d", &x);
	inserirElemento(raiz, x);
	
	printf("\ndigite: ");
	scanf("%d", &x);
	inserirElemento(raiz, x);
	
	preOrdem(raiz);
	return 0;
}

no* buscarElemento(no *NO, int x, int *f){
	printf("\n\nbuscando na arvore...");
	if(NO == NULL){             //verifica se o n� raiz (n� de onde a busca ir� partir) � null ou se contem o pr�prio elemento
		*f = 0;
		printf("\narvore vazia\n\n");
		return NULL;
	} else if(NO->data == x){
		*f = 1;
		printf("\nelemento ja inserido\n\n");
		return NO;
	}
	if (x < NO->data){			//verifica se a busca vai para a esquerda e se o filho da esquerda � null, se n�o entra numa outra chamada recursiva
		if (NO->filho_esq == NULL){
			*f = 2;
			printf("\nFolha encontrado!\n\n");
			return NO;
		} else{
			buscarElemento(NO->filho_esq, x, f);
		}
	}else{
		if( NO->filho_dir == NULL){			//verifica se a busca vai para a direita e se o filho da direita � null, se n�o entra numa outra chamada recursiva
			*f = 2;
			printf("\nelemento encontrado!\n\n", NO->data);
			return NO;
		} else{
			buscarElemento(NO->filho_dir, x, f);
		}
	}
}

no* inserirElemento(no *NO, int x){  //nao usar o nome da variavel com a mesma da struct, pois ir� haver conflito na declara��o de outras structs com o nome da variavel. Ex: no* no
	no *newNo;
	no *aux;
	int f;
	aux = buscarElemento(NO, x, &f);
	if(f == 1){
		printf("elemento j� inserido");
		return NULL;
	} else {
		newNo = malloc(sizeof(no));
		newNo->data = x;
		newNo->filho_dir = NULL;
		newNo->filho_esq = NULL;	
		if(f == 0){
			printf("elemento inserido na raiz\n\n");
			return newNo;		
		} else if(f == 2){
			if(newNo->data < aux->data){
				aux->filho_esq = newNo;
			}else{
				aux->filho_dir = newNo;
			}
		}
	}
}

void preOrdem(no *arvore){
	if(arvore != NULL){
		printf("%d\n", arvore->data);
		preOrdem(arvore->filho_esq);
		preOrdem(arvore->filho_dir);
	}
}
