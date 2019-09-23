#include <stdio.h>
#include <stdlib.h>

typedef struct no {
	int data;
	struct no *filho_esq;
	struct no *filho_dir;
} no;

no* buscarElemento(no *NO, int x, int *f);
no* inserirElemento(no *NO, int x);
no* deletarNo(no *NO, int x);

void preOrdem(no *arvore);

int main(){
	no *raiz = NULL;
	int x, op;
	while(op != 0){
		system("cls");
		printf("Escolha a operacao");
		printf("\n1- Imprimir pre ordem\n");
		printf("\n2- Inserir\n");
		printf("\n3- Deletar\n");
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
				printf("\nDigite o elemento: ");
				scanf("%d", &x);
				if(raiz == NULL){
					raiz = inserirElemento(raiz, x);
				}else{
				inserirElemento(raiz, x);
				}
				break;
			case 3:
				printf("\nDigite o elemento para deletar: ");
				scanf("%d", &x);
				deletarNo(raiz, x);
				break;
		}
		getch();
	}
	return 0;
}

no* buscarElemento(no *NO, int x, int *f){
	if(NO == NULL){             //verifica se o nó raiz (nó de onde a busca irá partir) é null ou se contem o próprio elemento
		*f = 0;
		printf("\narvore vazia\n\n");
		return NULL;
	} else if(NO->data == x){
		*f = 1;
		printf("\nelemento ja inserido\n\n");
		return NO;
	}
	if (x < NO->data){			//verifica se a busca vai para a esquerda e se o filho da esquerda é null, se não entra numa outra chamada recursiva
		if (NO->filho_esq == NULL){
			*f = 2;
			return NO;
		} else{
			buscarElemento(NO->filho_esq, x, f);
		}
	}else{
		if( NO->filho_dir == NULL){			//verifica se a busca vai para a direita e se o filho da direita é null, se não entra numa outra chamada recursiva
			*f = 2;
			return NO;
		} else{
			buscarElemento(NO->filho_dir, x, f);
		}
	}
}

no* inserirElemento(no *NO, int x){  //nao usar o nome da variavel com a mesma da struct, pois irá haver conflito na declaração de outras structs com o nome da variavel. Ex: no* no
	no *newNo;
	no *aux;
	int f;
	printf("\n\nbuscando na arvore...");
	aux = buscarElemento(NO, x, &f);
	if(f == 1){
		printf("elemento já inserido");
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
				printf("Elemento inserido como filho esquerdo de : %d", aux->data);
				aux->filho_esq = newNo;
			}else{
				printf("Elemento inserido como filho direito de : %d", aux->data);
				aux->filho_dir = newNo;
			}
		}
	}
}

no* deletarNo(no *NO, int x){
	no *aux, *aux2;
	if (NO == NULL){    //se o nó for null já apaga
		return NULL;
	} else if( NO->data == x){
		if (NO->filho_dir == NO->filho_esq){   // se for uma folha parte pro abraço
			free(NO);
			return NULL;

		} else if(NO->filho_esq == NULL){   // se tiver só filho a direita, o no recebe o seu filho e é deletado
			aux = NO;
			NO = NO->filho_dir;
			free(aux);
			return NO;
		} else if (NO->filho_dir == NULL){   // se tiver só filho a esquerda, o no recebe o seu filho e é deletado
			aux = NO;
			NO = NO->filho_esq;
			free(aux);
			return NO;
		}else if (NO->filho_esq->filho_esq == NO->filho_dir->filho_dir){
			NO->data = NO->filho_esq->data;
			free(NO->filho_esq);
			NO->filho_esq = NULL;
		}else{
			aux = NO;
			aux2 = NO->filho_esq;
			if(aux2->filho_dir == NULL){
				NO->data = aux->data;
				NO->filho_esq = aux->filho_esq;
			}else{
				while(aux2->filho_dir != NULL){
					aux = aux2;
					aux2 = aux2->filho_dir;
				}
				
				NO->data = aux2->data;
				aux->filho_dir = aux2->filho_esq;
				free(aux2); 
			}
		}
	}
	if(x > NO->data){
		NO->filho_dir = deletarNo(NO->filho_dir, x);
	}else{
		NO->filho_esq = deletarNo(NO->filho_esq, x);
	}	
}

void preOrdem(no *arvore){
	printf("%d\n", arvore->data);
	if(arvore->filho_esq != NULL){
		preOrdem(arvore->filho_esq);
	}
	if(arvore->filho_dir != NULL){
		preOrdem(arvore->filho_dir);	
	}
	
}
