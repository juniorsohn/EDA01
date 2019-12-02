typedef struct Info{
	int x,y;
}Info;

typedef struct Elemento{
	struct Elemento *acima;
	struct Elemento *abaixo;
	struct Info dados;

}Elemento;

typedef struct Pilha{
	Elemento *topo;
	int Taminfo;

}Pilha;

int vazia(struct Pilha *p);
void empilha (Pilha *p, Info dado);
int desempilha(Pilha *p, Info *dado);
void reinicia (Pilha *p);
void destroi (Pilha *p);
struct Pilha* cria();
