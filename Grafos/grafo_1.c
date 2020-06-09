#include <stdio.h>
#include <stdlib.h>

// Grafos com lista de adjacência
// Realizado por: Nathan Munis e Ruan Ferreira

// O seguinte código consiste numa implementação de grafo
// usando uma lista de adjanc�ncia, onde cada v�rtice tem
// n amizades.
// A criação de arestas é direcionado, então é necessário
// criar duas arestas pra que seja de "mão dupla", como
// demonstrado no arquivo main.c
// Foi escolhida esse tipo de implementação e não matriz
// de adjacência por ser um grafo denso.

typedef struct pessoa{
	char *nome;
	int idade;
} PESSOA;

typedef struct vertice{
	int id;
	PESSOA pessoa;
	int usado;
	struct aresta* listaAdjacencia;
} VERTICE;

typedef struct aresta{
	struct vertice* v;
	struct aresta* prox;
}ARESTA;

typedef struct grafo{
	int quantVertices;
	struct vertice* listaVertices;
}GRAFO;

GRAFO* criarGrafo(int n){
	int i;
	GRAFO* g = (GRAFO*)malloc(sizeof(GRAFO));
	
	g->quantVertices = n;
	g->listaVertices = (VERTICE*)malloc(n*sizeof(VERTICE));
	
	for(i=0; i<n; i++){
		g->listaVertices[i].listaAdjacencia = NULL;
		g->listaVertices[i].usado = 0;
	}
	
	return g;
}

void criarVertice(GRAFO* g, char *n, int idad){
	int i;
	for(i=0; i < g->quantVertices; i++){
		if(g->listaVertices[i].usado == 0){
			g->listaVertices[i].pessoa.nome = n;
			g->listaVertices[i].pessoa.idade = idad;
			g->listaVertices[i].usado = 1;
			g->listaVertices[i].listaAdjacencia = NULL;
			break;
		}
	}
}

void criarAresta(GRAFO* g, char n1[], char n2[]){
	int i, trigger1, trigger2;
	int p =-1;
	int amigo = -1;
	for(i=0; i< g->quantVertices; i++){
		if(g->listaVertices[i].usado == 1){
			trigger1 = strcmp(g->listaVertices[i].pessoa.nome, n1);
			trigger2 = strcmp(g->listaVertices[i].pessoa.nome, n2);

			if(trigger1 == 0){
				p = i;
			} else if(trigger2 == 0){
				amigo = i;
			}
			if (p != -1 && amigo != -1){
				break;
			}
		}
	}
	//printf("%d %d", p, amigo);
	ARESTA* novaAresta = (ARESTA*)malloc(sizeof(ARESTA));
	novaAresta->v = &g->listaVertices[amigo];
	novaAresta->prox = g->listaVertices[p].listaAdjacencia;
	g->listaVertices[p].listaAdjacencia = novaAresta;
	
}

void exibirListaAdjacencia(VERTICE* v){
	int i=0;
	ARESTA* a = v->listaAdjacencia;
	while(i==0){
		if(a != NULL){
			printf("%s ->", a->v->pessoa.nome);
			a = a->prox;
		}else{
			i=1;
		}
	}
	printf("\n");
}

void exibirGrafo(GRAFO* g){
	int i; VERTICE* v;
	for(i=0; i<g->quantVertices; i++){
		v = &g->listaVertices[i];
		if(v->usado == 1){
			printf("Amigos de %s: ", v->pessoa.nome);
			exibirListaAdjacencia(v);
		}
	}
}

int excluirAresta(GRAFO* g, char n1[], char n2[]){
	int i, trigger1, trigger2;
	int p =-1;
	int amigo = -1;
	VERTICE* p0;
	VERTICE* amigo0;
	ARESTA* p1;
	ARESTA* amigo1;
	for(i=0; i< g->quantVertices; i++){
		if(g->listaVertices[i].usado == 1){
			trigger1 = strcmp(g->listaVertices[i].pessoa.nome, n1);
			trigger2 = strcmp(g->listaVertices[i].pessoa.nome, n2);

			if(trigger1 == 0){
				p = i;
			} else if(trigger2 == 0){
				amigo = i;
			}
			if (p != -1 && amigo != -1){
				break;
			}
		}
	}
	
	if(p == -1 || amigo == -1){
		printf("Nao possuem amizade");
		return 0;
	}
	
	p0 = &g->listaVertices[p];
	amigo0 = &g->listaVertices[amigo];
	
	p1 = p0->listaAdjacencia;
	amigo1 = amigo0->listaAdjacencia;
	
	ARESTA* aux = p1;
	while(p1 != NULL){
		if(strcmp(p1->v->pessoa.nome, amigo0->pessoa.nome) == 0){
			aux->prox = p1->prox;
			free(p1);
			if(p1 == NULL){
				p0->listaAdjacencia = p1;
			}
			break;
		}
		aux = p1;
		p1 = p1->prox;
	}
	aux = amigo1;
	while(amigo1 != NULL){
		if(strcmp(amigo1->v->pessoa.nome, p0->pessoa.nome) == 0){
			aux->prox = amigo1->prox;
			free(amigo1);
			if(amigo1==NULL){
				amigo0->listaAdjacencia = amigo1;
			}
			break;
		}
		aux = amigo1;
		amigo1 = amigo1->prox;
	}
}
