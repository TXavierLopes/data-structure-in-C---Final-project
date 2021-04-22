#ifndef FUNCOES_H_INCLUDED
#define FUNCOES_H_INCLUDED

#include "hashing.h"
#include "lista.h"
int idvalidoler(ptLISTA L,char *pt);
int bisexto(int year);
int detetarnumb(char *s);
int dataexiste(char *ptr,int tipo);
 int idvalido(ptLISTA L,No E);
 void ler_pessoa(ptLISTA L,No E,ptLOCALIZACAO l);
 int idade_maxima(ptLISTA L);
 float media_idade(ptLISTA L);
 int idade_superior(ptLISTA L);
 void verificanome(ptLISTA L);
 int idade_mais_repetida(ptLISTA L);
/*livros*/
 void areamaisvezes(Hashing *HV);
 void isbnexiste(Hashing *HV);
 void livro_mais_recente(Hashing *HV);
 void apelido_mais_usado(ptLISTA L);
 void inserir_req(ptLISTA_req L, ptLISTA lista, Hashing *HV,No_req E);
 void devolverrequisicao(ptLISTA_req L, Hashing *HV);
 void mostarrequisicoesrequisitante(ptLISTA_req L);
 void livromaisrequisitado(Hashing *HV);
 void areamaisrequisitada(Hashing *HV);
Livro *CriarLivros2(int cod,  char *area,char *autor ,  char *titulo,char *date);
 void mostrarPsemrequisicoes(ptLISTA L);
 void tamanhostruct();
 void determinarLocalcomNome(ptLISTA l);
 void MostrarLivro(Livro *V);
 void listarreqdomingo(ptLISTA L);
 void listarreqquaresma(ptLISTA l);
 void apelido_mais_usado(ptLISTA L);
 void inserir_livro(Hashing *HV);
 #endif 