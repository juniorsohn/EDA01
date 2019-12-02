#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

#define ACIMA 0
#define DIREITA 1
#define ABAIXO 2
#define ESQUERDA 3

void avanca(int direcao, Info *leitor);
int marca(Info leitor, int nrotulo, int matrizrotulo[20][38]);
int verifica(Info leitor, int direcao, char matriz[20][40], int matrizrotulo[20][38]);

int main(){
	FILE *f = fopen("input.txt","r");
	if (f == NULL){
		printf("Erro no arquivo!\n");
    	return -1;
  	}

  	printf("Leitura de arquivo:\n---------------------\n");
  	char c;


  	do{
    	c = getc(f);
    	printf("%c",c);
  
  	}while (c != EOF);
	
	printf("---------------------\n");
	
	// Criacao da Pilha vazia //
	Pilha *p = cria();
	// limpa leitor do arquivo
	rewind(f);
	
	char matriz[20][40];
	int matrizrotulo[20][38];
	int i,j,nrotulo=0;
	// conversao da matriz do arquivo input para matriz declarada no codigo
	for(i=0; i<20; i++){
		fscanf(f,"%s",matriz[i]);
	}
	// print na tela da matriz
	for(i=0;i<20;i++){
		printf("\n");
		for(j=0;j<38;j++){
			printf("%c ",matriz[i][j]);	
		}
	}
	
	//preenche matriz de inteiros com 0
	for(i=0;i<20;i++){
		for(j=0;j<38;j++){
			matrizrotulo[i][j] = 0;
		}
	}
	
	// magia
	for(i=0;i<20;i++){
		for(j=0;j<38;j++){
			if (matriz[i][j] == '1' && matrizrotulo[i][j] == 0){
				Info leitor = {i,j};
				empilha(p,leitor);
				nrotulo++;
				
				printf("\n%d %d",i,j);
				
				while(!vazia(p)){
					printf("\n[%d][%d]",leitor.x,leitor.y);
					marca(leitor,nrotulo,matrizrotulo);	
					int k, direcao=-1;
					
					 for (k=ESQUERDA; k>=ACIMA; k--){
						if(verifica(leitor,k,matriz,matrizrotulo) == 1){
							direcao=k;
						}
						printf("\nk=%d dir=%d",k,direcao);
					}
					if(direcao == -1){
						desempilha(p,&leitor);
					}
					else{
						avanca(direcao,&leitor);
						empilha(p,leitor);
					}
				}		
			}
		}
	}
	// tenta printar aqui//	
	printf("\n------------------ MATRIZ SUPOSTAMENTE PRONTA AQUI -----------------------------\n");
	for (i=0; i<20; i++){
		printf("\n");
		for (j=0; j<38; j++){
			printf("%2d ",matrizrotulo[i][j]);
		}
	}
	
	// magia feita, agora eh so contar os rotulos e ver qual eh o maior
	//Achar maior valor 
	int maior = -1;
	
	for (i=0; i<20; i++){
		for (j=0; j<38; j++){
			if(matrizrotulo[i][j] >= maior){
				maior = matrizrotulo[i][j];
			}
		}
	}
	
	
	int v[15];
	//transformando em array de 0
	for(i=0; i<15; i++){
		v[i] = 0;
	}
	
	//Conta quantidade de cada rótulos
	int n=1;
	while(n <= maior){
		for (i=0; i<20; i++){
			for (j=0; j<38; j++){
				if(matrizrotulo[i][j] == n){
					v[n-1]++;
				}
			}
		}	
		n++;	
	}
	
	//Print teste de quantidade
	for(i=0; i<14; i++)
		printf("\nquantidade de numeros [%d]: %d\n ",i+1,v[i]);
	
	//Compara qual maior rótulo
	int quantmaior=v[0];
	for(i=0; i<maior; i++){
		if(v[i] > quantmaior)
			quantmaior = v[i];
	}	
	printf("\nMaior quantidade de rotulos eh [%d]: %d\n",i,quantmaior);

	
	//Zera matrizrotulo diferente do maior
	for (i=0; i<20; i++){
			for (j=0; j<38; j++){
				if(matrizrotulo[i][j] != maior){
					matrizrotulo[i][j] = 0;
				}
				else{
					matrizrotulo[i][j] = 1;
				}
			}
		}		
		
	//Print teste matriz zerada
	printf("\n------------ Matriz Zerada ------------\n");
	for (i=0; i<20; i++){
		printf("\n");
			for (j=0; j<38; j++){
				printf("%2d ", matrizrotulo[i][j]);
				}
			}
	
	// Transcricao pra arquivo
	
	FILE *fp = fopen("output.txt","w");
	
	for (i=0; i<20; i++){
		fprintf(fp,"\n");
		for (j=0; j<38; j++){
			fprintf(fp,"%d",matrizrotulo[i][j]);
		}
	}	
	fclose(f);
	fclose(fp);
	system("output.txt");	
	
	// Encontrar centro do maior objeto
	// como ja temos o maior rotulo e a quantidade deste rotulo, a metade deles seria maiorquant/2
	
	int contameio=0;
	for (i=0; i<20; i++){
		for (j=0; j<38; j++){
			if(matrizrotulo[i][j] == 1)
				contameio++;
			if(contameio == (quantmaior)/2){
				printf("O centro do objeto desejado eh: [%d] [%d]",i,j);
			}
		}
	}
	
 	//FIM
	return 0;
}

 
int marca(Info leitor, int nrotulo, int matrizrotulo[20][38]){
	matrizrotulo[leitor.x][leitor.y] = nrotulo;
	return 1;
}

int verifica(Info leitor, int direcao, char matriz[20][40], int matrizrotulo[20][38]){
	switch(direcao){
	
		case ACIMA:{
			if(matriz[(leitor.x)-1][leitor.y] == '1' && (matrizrotulo[(leitor.x)-1][leitor.y] == 0)){
				return 1;
			}
			else
				return 0;
		}
		
		case DIREITA:{
			if (matriz[leitor.x][(leitor.y)+1] == '1' && (matrizrotulo[leitor.x][(leitor.y)+1] == 0)){
				return 1;
			}
			else
				return 0;
		}
		
		case ABAIXO:{
			if (matriz[(leitor.x)+1][leitor.y] == '1' && (matrizrotulo[(leitor.x)+1][leitor.y] == 0)){
				return 1;
			}
			else
				return 0;	
		}
		
		case ESQUERDA:{
			if (matriz[leitor.x][(leitor.y)-1] == '1' && (matrizrotulo[leitor.x][(leitor.y)-1]) == 0){
				return 1;
			}
			else
				return 0;
		}	
	}
}

void avanca(int direcao, Info *leitor){
	switch(direcao){
		case 0:{
			leitor->x = (leitor->x)-1;
			break;
		}
		case 1:{
			leitor->y = (leitor->y)+1;
			break;
		}
		case 2:{
			leitor->x = (leitor->x)+1;
			break;
		}
		case 3:{
			leitor->y = (leitor->y)-1;
			break;
		}
		default:
			break;
	}
}

