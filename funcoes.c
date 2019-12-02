#include "header.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Pilha* cria(){
	Pilha *p =(Pilha*) malloc(sizeof(Pilha));
	p->topo = NULL;
	p->Taminfo = 0;
	return p;
}

void empilha (Pilha *p, Info dado){
	Elemento *novo=malloc(sizeof(Elemento));
	memcpy(&(novo->dados),&dado,sizeof(Info));
	
	if (p->Taminfo == 0){
		p->topo = novo;
		p->Taminfo++;
		novo->acima = NULL;
		novo->abaixo = NULL;
	}
	else{
		p->topo->acima = novo;
		novo->abaixo = p->topo;
		p->topo = novo;
		p->topo->acima = NULL;
		p->Taminfo++;			
		
	}	
}

int desempilha(Pilha *p, Info *dado){
	Elemento *aux;
	if (p->Taminfo == 0){
		return 0;
	}
	else{
		if(p->Taminfo == 1){
			memcpy(dado,&(p->topo->dados),sizeof(Info));
			free(p->topo);
			(p->Taminfo)--;
		}
		else{
			aux = p->topo;
			memcpy(dado,&(aux->dados),sizeof(Info));
			p->topo = p->topo->abaixo;
			free(aux);
			p->topo->acima = NULL;
			(p->Taminfo)--;
			return 1;	
		}
	}
}

int vazia (Pilha *p){
	if (p->Taminfo == 0){
		return 1;
	}
	else
		return 0;
}

void reinicia (Pilha *p){
	int i;
	Info *dado;
	for (i=p->Taminfo;i>0;i--){
		desempilha(p,dado);
	}
}

void destroi(Pilha *p){
	reinicia(p);
	free(p);
}

