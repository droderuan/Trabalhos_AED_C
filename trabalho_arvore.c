#include <stdio.h>
#include <stdlib.h>

typedef struct no {
	int data;
	struct no *filho_esq;
	struct no *filho_dir;
} no;

no* buscarElemento(no *no, int x, int *f);
no* inserirElemento(no *no, int x);

int main(){
	no *no = NULL;
	
	return 0;
}

no* buscarElemento(no *no, int x, int *f){
	if(no == NULL){             //verifica se o nó raiz (nó de onde a busca irá partir) é null ou se contem o próprio elemento
		*f = 0;
		return NULL;
	} else if(no->data == x){
		*f = 1;
		return no;
	}
	if (x < no->data){			//verifica se a busca vai para a esquerda e se o filho da esquerda é null, se não entra numa outra chamada recursiva
		if (no->filho_esq == NULL){
			*f = 2;
			return no;
		} else{
			buscarElemento(no->filho_esq, x, f);
		}
	}else{
		if( no->filho_dir == NULL){			//verifica se a busca vai para a direita e se o filho da direita é null, se não entra numa outra chamada recursiva
			*f = 2;
			return no;
		} else{
			buscarElemento(no->filho_dir, x, f);
		}
	}
}

no* inserirElemento(no *NO, int x){  //nao usar o nome da variavel com a mesma da struct, pois irá haver conflito na declaração de outras structs com o nome da variavel. Ex: no* no
	no *newNo;
	no *aux;
	int f;
	aux = buscarElemento(NO, x, &f);
	if(f == 1){
		printf("elemento já inserido");
		return NULL;
	}
	newNo = malloc(sizeof(no));
	newNo->data = x;
	newNo->filho_dir = NULL;
	newNo->filho_esq = NULL;
	
	if(f == 0){
		return newNo;
	} else if(f == 2){
		if(newNo->data < NO->data){
			NO->filho_esq = newNo;
		}else{
			NO->filho_dir = newNo;
		}
	}
}
