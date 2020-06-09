#include "grafo_1.c"

int main(){
	;
	char *nome1 = "Ruan";
	char *nome2 = "Django";
	char *nome3 = "Kung fury";
	char *nome4 = "Machete";
	
	GRAFO* grafo = criarGrafo(10);
	
	criarVertice(grafo, nome1, 5);
	criarVertice(grafo, nome2, 5);
	criarVertice(grafo, nome3, 5);
	criarVertice(grafo, nome4, 5);
	
	criarAresta(grafo, nome1, nome2);
	criarAresta(grafo, nome1, nome3);
	criarAresta(grafo, nome1, nome4);
	criarAresta(grafo, nome2, nome1);
	criarAresta(grafo, nome3, nome1);
	criarAresta(grafo, nome4, nome1);
	
	criarAresta(grafo, nome3, nome2);
	criarAresta(grafo, nome2, nome3);
	
	criarAresta(grafo, nome4, nome3);
	criarAresta(grafo, nome4, nome2);
	criarAresta(grafo, nome3, nome4);
	criarAresta(grafo, nome2, nome4);
	exibirGrafo(grafo);
	
	printf("\nApos duas exclusoes de %s\n", nome1);
	
	excluirAresta(grafo, nome1, nome2);
	excluirAresta(grafo, nome1, nome3);
	
	exibirGrafo(grafo);
	return 0;
}
