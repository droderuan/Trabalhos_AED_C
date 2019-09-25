#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

typedef struct no {
	int ID, idade;
	char sexo[1];
	struct no *filho_esq;
	struct no *filho_dir;
} no;

no* buscarElemento(no *NO, int x, int *f);
no* inserirElemento(no *NO);
no* deletarNo(no *NO, int x);

void preOrdem(no *arvore);

int main(){
	no *raiz = NULL;
	int op = 1, x, f;
	while(op != 0){
		system("cls");
		printf("Escolha a operacao");
		printf("\n1- Imprimir pre ordem\n");
		printf("\n2- Inserir\n");
		printf("\n3- Deletar\n\n");
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
		}
		getch();
	}
	return 0;
}

no* buscarElemento(no *NO, int x, int *f){
	if(NO == NULL){             //verifica se o nó raiz (nó de onde a busca irá partir) é null ou se contem o próprio elemento
		*f = 0;
		return NULL;
	} else if(NO->ID == x){
		*f = 1;
		return NO;
	} else if (x < NO->ID){			//verifica se a busca vai para a esquerda e se o filho da esquerda é null, se não entra numa outra chamada recursiva
		if (NO->filho_esq == NULL){
			*f = 2;
			return NO;
		} else{
			buscarElemento(NO->filho_esq, x, f);
		}
	}else if( NO->filho_dir == NULL){			//verifica se a busca vai para a direita e se o filho da direita é null, se não entra numa outra chamada recursiva
			*f = 2;
			return NO;
		} else{
			buscarElemento(NO->filho_dir, x, f);
		}
}

no* inserirElemento(no *NO){  //nao usar o nome da variavel com a mesma da struct, pois irá haver conflito na declaração de outras structs com o nome da variavel. Ex: no* no
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
		if (NO->filho_dir == NO->filho_esq){   // se for uma folha parte pro abraço
			free(NO);
			NO = NULL;
			return NULL;

		} else if(NO->filho_esq == NULL){   // se tiver só filho a direita, o no recebe o seu filho e é deletado
			printf("\nEsq == null");
			pt = NO;
			NO = NO->filho_dir;
			free(pt);
			return NO;
		} else if (NO->filho_dir == NULL){   // se tiver só filho a esquerda, o no recebe o seu filho e é deletado
			printf("\nDir == null");
			pt = NO;
			NO = NO->filho_esq;
			free(pt);
			return NO;
		}else if (NO->filho_esq->filho_esq == NO->filho_dir->filho_dir){
			NO->ID = NO->filho_esq->ID;
			free(NO->filho_esq);
			NO->filho_esq = NULL;
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
	if(arvore->filho_esq != NULL){
		preOrdem(arvore->filho_esq);
	}
	if(arvore->filho_dir != NULL){
		preOrdem(arvore->filho_dir);
	}
}

