#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include "lista.h"
#include "texto.h"
#include "hashing.h"
#include "funcoes.h"

int menu_pessoas(ptLISTA lista,ptLOCALIZACAO local) { 
  int x,n,escolha;
	No ele_novo;
  do {
  printf("\n\n   # MENU REQUISITANTES ---------------------------------------#");
	printf("\n   | --------------------------------------------------------- |");
	printf("\n   | (1) Mostrar Pessoas(Escolha da ordem)                     |");
  printf("\n   | (2) Inserir Pessoas                                       |");
  printf("\n   | (3) Media da idade das pessoas                            |");
  printf("\n   | (4) Idade maior existente                                 |");
  printf("\n   | (5) Numero de pessoas com idade superior à inserida       |");
  printf("\n   | (6) Verificar Requisitante por nome                       |");
  printf("\n   | (7) Idade com mais requisitantes                          |");
	printf("\n   | (8) Verificar apelido que aparece mais vezes              |");
	printf("\n   | (9) Mostrar Pessoas que nunca requisitaram nada           |");
	printf("\n   | (10) Apelidos por distritos                               |");
	printf("\n   | (11) Pessoas que nasceram ao domingo                      |");
	printf("\n   | (12) Pessoas que nasceram na quaresma                     |");
  printf("\n   | --------------------------------------------------------- |");
  printf("\n   | (0) Voltar atrás                                          |");
  printf("\n   #-----------------------------------------------------------#\n");
    fflush(stdin);
		printf("\n   Qual a sua opcao ? ");
    scanf("%d",&x);
  switch (x) {
		case 1: 			
      mostrar_ordenado_id(lista);
			x=-1;
		break;
		case 2:
		  ele_novo=criar_no();
      ler_pessoa(lista, ele_novo,local);
			x=-1;
			break;
		case 3:
			media_idade(lista);
			x=-1;
			break;
		case 4:
			idade_maxima(lista);
			x=-1;
			break;
		case 5:
      idade_superior(lista);
				x=-1;
		break;
		case 6:
			verificanome(lista);
			x=-1;
			break;
		case 7:
			idade_mais_repetida(lista);
			x=-1;
			break;
		case 8:
			apelido_mais_usado(lista);
			x=-1;
			break;
		case 9:
			mostrarPsemrequisicoes(lista);
			x=-1;
			break;
		case 10:
			determinarLocalcomNome(lista);
			x=-1;
			break;
		case 11:
			listarreqdomingo(lista);
			x=-1;
			break;
		case 12:
			listarreqquaresma(lista);
			x=-1;
			break;
		case 13:
			apelido_mais_usado(lista);
			x=-1;
			break;
		case 0:
			return 6;
		break;
	 }
	 } while (x<0 || x>11);
	 return 1;
}

int menu_livros(Hashing *HV) { 
  int x,z;
	fflush(stdin);
  do {
  printf("\n\n   # MENU LIVROS ----------------------------------------------#");
	printf("\n   | --------------------------------------------------------- |");
	printf("\n   | (1) Inserir Livros                                        |");
  printf("\n   | (2) Mostrar Livros                                        |");
  printf("\n   | (3) Area com mais livros                                  |");
  printf("\n   | (4) Verificar por Isbn                                    |");
  printf("\n   | (5) Verificar data mais recente dos livros                |");
	printf("\n   | (6) Mostrar Livros Requisitados                           |");
  printf("\n   | --------------------------------------------------------- |");
  printf("\n   | (0) Voltar atrás                                          |");
  printf("\n   #-----------------------------------------------------------#\n");
    fflush(stdin);
		printf("\n   Qual a sua opcao ? ");
    scanf("%d",&x);
  switch (x) {
		case 1:
			inserir_livro(HV);
			x=-1;
		break;
		case 2:
			Mostrar_Hashing_PRO(HV);
			x=-1;
		break;
		case 3:
			areamaisvezes(HV);
			x=-1;
		break;
		case 4:
    	isbnexiste(HV);
			x=-1;
		break;
		case 5:
			livro_mais_recente(HV);
			x=-1;
		break;
		case 6:
			Mostrar_livros_requisitados(HV);
			x=-1;
		break;
		case 0:
			return 6;
		break;
	 }
	 } while (x<=0 || x>23);
	 return 1;
}

int menu_requisitantes(ptLISTA_req req,ptLISTA lista,Hashing *HV) { 
  int x;
	No_req novo;
	do {
  printf("\n\n   # MENU REQUISIÇÔES -----------------------------------------#");
	printf("\n   | --------------------------------------------------------- |");
	printf("\n   | (1) Inserir requisição                                    |");
  printf("\n   | (2) Mostrar Requisições                                   |");
  printf("\n   | (3) Devolver Livro                                        |");
  printf("\n   | (4) Mostrar Livros Requisitados                           |");
	printf("\n   | (5) Mostrar Livros Requisitados por uma pessoa            |");
	printf("\n   | (6) Livro mais requisitado                                |");
	printf("\n   | (7) Area mais requisitada                                 |");
  printf("\n   | --------------------------------------------------------- |");
  printf("\n   | (0) Voltar atrás                                          |");
  printf("\n   #-----------------------------------------------------------#\n");
  fflush(stdin);
	printf("\n   Qual a sua opcao ? ");
  scanf("%d",&x);
	switch (x) {
		case 1:
			novo = criar_no_req();
  	  inserir_req(req,lista,HV,novo);
			x=-1;
		break;
		case 2:
			mostrarrequisicoes(req);
			x=-1;
		break;
		case 3:
			devolverrequisicao(req,HV);
			x=-1;
		break;
		case 4:
			Mostrar_livros_requisitados(HV);
			x=-1;
		break;
		case 5:
			mostarrequisicoesrequisitante(req);
			x=-1;
		break;
		case 6:
			livromaisrequisitado(HV);
			x=-1;
		break;
		case 7:
			areamaisrequisitada(HV);
			x=-1;
		break;
		case 0:
			return 6;
		break;
	 }
	 } while (x<0 || x>8);
	 return 1;
}


int menu_principal2() { 
  int x;
	int n,z,escolha=0,id;
  No ele_novo; 
  No_req novo;
  ptLISTA_req req = criar_listareq();
	ptLOCALIZACAO local = Criar_localizacao();
  ptLISTA lista = criar_lista();
	Hashing *HV = CriarHashing_PRO();
  ptFAIXA L = Criar_faixa();
	lerlocais(local);
  lerficheiro(lista,local);	
  lerlivro(L,HV);
	lerreq(req,HV);
	lerrequisicoeslivros(HV);
	lerrequisicoespessoas(lista);
	do {
  printf("\n\n   # MENU PRINCIPAL -------------------------------------------#");
	printf("\n   | --------------------------------------------------------- |");
  printf("\n   | (1) Requisitantes                                         |");
  printf("\n   | (2) Livros                                                |");
  printf("\n   | (3) Requisições                                           |");
	printf("\n   | (4) Tamanho das struct                                    |");
	printf("\n   | (5) Guardar em xml(escolha do nome)                       |");
	
  printf("\n   | --------------------------------------------------------- |");
  printf("\n   | (0) SAIR                                                  |");
  printf("\n   #-----------------------------------------------------------#\n");
  fflush(stdin);
    int op;
		printf("\n   Qual a sua opcao ? ");
		scanf("%d",&op);
		switch (op) {
		case 1:x=menu_pessoas(lista,local);break;
		case 2:x=menu_livros(HV);break;
		case 3:x=menu_requisitantes(req,lista,HV);break;
		case 4:tamanhostruct();break;
		case 5:inserirxml(lista,req,HV);break;
		case 0:
		printf("Fim do programa!\n");
		inserenoficheiro(req);
		inserirNrequsicoeslivro(HV);
		inserirNrequsicoespessoa(lista);
  	Destruir_Hashing_PRO(HV);
  	Destruir_Faixa(L);
  	Destruir_Lista(lista);
  	Destruir_req(req);
    exit(0);
		break;
	 }
  } while (x<0 || x>5);
  return x;
}
