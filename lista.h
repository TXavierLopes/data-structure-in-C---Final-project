#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct date{
  int dia;
  int mes;
  int ano;
}DATA;

typedef struct sitio{
	int local;
	char *freguesia;
	char *vila;
	char *cidade;
}localizacao;

typedef struct nodo {
   localizacao *inf;
   struct nodo *seg;
} *Nodo;

typedef struct Localizacao {
   int nelementos;    
   Nodo inicio;             
} *ptLOCALIZACAO, LOCALIZACAO;

typedef struct pessoa { 
  int nrequisicoes;
	int id;
  DATA data;
  char *nome;
  int local;
	char *freguesia;
	char *vila;
	char *cidade;
}Pessoa,*ptPessoa;

typedef struct no {
   ptPessoa inf;
   struct no *seg;
} *No;

typedef struct Lista {
   int nelementos;    
   No inicio;             
} *ptLISTA, LISTA;

typedef struct livro
{
    int isbn;
		int nreq;
    char *titulo;
    char *autor;
    char *area;
    int requisitado;//0=requisitado 1=ñ requisitado
    DATA data;
}Livro,*ptLivro;

typedef struct elemento{
  Livro *info;
  struct elemento *Prox;
}ELEMENTO,*Elemento;

typedef struct faixa
{
    elemento *Inicio;
    int NEL;
}Faixa ,*ptFAIXA;

typedef struct requisicoes{
  DATA data;
  Pessoa pessoa;
  Livro livro;
  int nreq;
}Requisicoes,*ptRequisicoes;

typedef struct no_req{
   ptRequisicoes inf;
   struct no_req *seg;
} *No_req;

typedef struct Lista_req{
   int nelementos;
   No_req inicio;          
} *ptLISTA_req, LISTA_req;

//esta estrutura será usada também para a idade com mais requisitantes
typedef struct apelidos{
	char *nome;
	int idade;
	int total;
}*APELIDOS,Apelidos;

typedef struct no_ape{
   APELIDOS inf;
   struct no_ape *seg;
} *No_ape;

typedef struct Lista_ape{
   int nelementos;
   No_ape inicio;          
} *ptLISTA_ape, LISTA_ape;


///////////////////////////
ptFAIXA Criar_faixa();
No criar_no();
Elemento criar_elemento();
void Destruir_Faixa(ptFAIXA L);
void Mostrar_Lista(ptFAIXA L);
void Inserir_Lista(Faixa *L, Livro *V);
ptLISTA criar_lista();
void inserir_elemento_fim(ptLISTA L, No E);
void mostrar_elemento(No ele_mostrar);
void mostrar_ordenado(ptLISTA Lista);
void mostrar_ordenado_id(ptLISTA Lista);
void Destruir_Lista(ptLISTA L);
ptLISTA_req criar_listareq();
No_req criar_no_req();
void inserirrequisicoes(ptLISTA_req L, No_req E);
void mostrarrequisicoes(ptLISTA_req Lista);
void Destruir_req(ptLISTA_req L);
void libertar_req(No_req ele_libertar);
void Mostrar_Lista_requisitados(ptFAIXA L);
ptLOCALIZACAO Criar_localizacao();
Nodo criar_nodo();
void inserir_nodo_fim(ptLOCALIZACAO L, Nodo E);
void mostrar_local(ptLOCALIZACAO Lista);
ptLISTA_ape criar_lista_ape();
No_ape criar_no_ape();
void libertar_ape(No_ape ele_libertar);
void Destruir_ape(ptLISTA_ape L);
void inserir_apelidos(ptLISTA_ape L, No_ape E);
#endif // LISTA_H_INCLUDED