#include "lista.h"
#include "funcoes.h"
extern void MostrarLivro(Livro *V);
///// criar listas e elementos
ptFAIXA Criar_faixa(){
    ptFAIXA L = (ptFAIXA )malloc(sizeof(ptFAIXA));
    L->Inicio = NULL;
    L->NEL = 0;
    return L;
}

Elemento criar_elemento(){ 
  Elemento E = (Elemento)malloc(sizeof(Elemento));
  if (!E) return NULL;
  E->info = (ptLivro)malloc(sizeof(struct livro));
  E->Prox = NULL;
  return E;
}

ptLISTA criar_lista(){
  ptLISTA ls = (ptLISTA )malloc(sizeof(struct Lista));
	if (!ls) return NULL;
	ls->inicio = NULL;
	ls->nelementos = 0;
	return ls;
}

No criar_no(){ 
  No E = (No) malloc(sizeof(struct no));
  if (!E) return NULL;
  E->inf = (ptPessoa) malloc(sizeof(struct pessoa));
  E->seg = NULL;
  return E;
}
ptLISTA_req criar_listareq(){
  ptLISTA_req ls = (ptLISTA_req )malloc(sizeof(struct Lista_req));
	if (!ls) return NULL;
	ls->inicio = NULL;
	ls->nelementos = 0;
	return ls;
}

No_req criar_no_req(){ 
  No_req E = (No_req) malloc(sizeof(struct no_req));
  if (!E) return NULL;
  E->inf = (ptRequisicoes) malloc(sizeof(struct requisicoes));
  E->seg = NULL;
  return E;
}
///////////////////////////////////////////////////////////////
void Mostrar_Lista(ptFAIXA L){
    if (!L) return;
    ELEMENTO *P = L->Inicio;
    while (P)
    {
        MostrarLivro(P->info);
        P = P->Prox;
    }
}
void Mostrar_Lista_requisitados(ptFAIXA L){
		if (!L) return;
    ELEMENTO *P = L->Inicio;
    while (P)
    {
				if(P->info->requisitado==1)
        MostrarLivro(P->info);
        P = P->Prox;
    }
}
void Inserir_Lista(Faixa *L, Livro *V){
    if (!L) return;
    ELEMENTO *X = (ELEMENTO *)malloc(sizeof(ELEMENTO));
    X->info = V;
    X->Prox = L->Inicio;
    L->Inicio = X;
    L->NEL++;
}

void inserir_elemento_fim(ptLISTA L, No E){
  E->seg = NULL;  
  if(!L) return;
  if (!L->inicio) 
    L->inicio = E;
  else {
    No p = L->inicio;
    while(p->seg)
      p=p->seg;
    p->seg = E;
  }
   L->nelementos ++;
}

void inserirrequisicoes(ptLISTA_req L, No_req E)
{
  E->seg = NULL;  
  if(!L) return;
  if (!L->inicio) 
    L->inicio = E;
  else {
    No_req p = L->inicio;
    while(p->seg)
      p=p->seg;
    p->seg = E;
  }
   L->nelementos ++;
}
void mostrar_elemento(No ele_mostrar){ 
  printf("\n Id: %d", ele_mostrar->inf->id);
  printf("\n Nome: %s", ele_mostrar->inf->nome);
  printf("\n Data: %d-%-d-%d",ele_mostrar->inf->data.dia,ele_mostrar->inf->data.mes, ele_mostrar->inf->data.ano);
	printf("\n Nrequisicoes: %d", ele_mostrar->inf->nrequisicoes);
  printf("\n Localizacao: %d", ele_mostrar->inf->local);
	printf("\n Distrito: %s", ele_mostrar->inf->cidade);
	printf("\n Concelho: %s", ele_mostrar->inf->vila);
	printf("\n Freguesia: %s\n", ele_mostrar->inf->freguesia);
}

void mostrar_ordenado(ptLISTA Lista){ 
  if (!Lista) return;
  No p = Lista->inicio;  
  while (p) {
    mostrar_elemento(p);  
    p = p->seg;   
  }
}

void mostrar_ordenado_id(ptLISTA Lista) { 
				int n,verifica=0;
				char escolha[10];
        ptLISTA current = Lista;
				printf("\nOrdernar por:");
        printf("\nID->1");
        printf("\nNome->2");
        printf("\nFreguesia->3");
        do{
					printf("\nEscolha:");
					scanf("%s",escolha);
					verifica=detetarnumb(escolha);
        }while(atoi(escolha)<1 || atoi(escolha)>3 || verifica == 0);
        int temp;
				n=atoi(escolha);
        No temp1;
        No temp2 ;
        if(Lista == NULL) {
            return;
        }
        for(temp1 = current->inicio; temp1 != NULL; temp1 = temp1->seg){
          for(temp2 = temp1->seg; temp2 != NULL; temp2 = temp2->seg){
            if(n==1){
            if(temp2->inf->id<temp1->inf->id){
              ptPessoa a = temp1->inf;
              temp1->inf = temp2->inf;
              temp2->inf = a;
            }
            }
            if(n==2){
            if(strcasecmp(temp2->inf->nome,temp1->inf->nome)<0){
              ptPessoa a = temp1->inf;
              temp1->inf = temp2->inf;
              temp2->inf = a;
            }
            }
            if(n==3){
            if(temp2->inf->local<temp1->inf->local){
              ptPessoa a = temp1->inf;
              temp1->inf = temp2->inf;
              temp2->inf = a;
            }
            }
          }
        }
  mostrar_ordenado(current);
}
void mostrar_elemento_req(No_req ele_mostrar){ 
  printf("\n Id: %d", ele_mostrar->inf->pessoa.id);
  printf("\n Nome: %s", ele_mostrar->inf->pessoa.nome);
  printf("\n Isbn: %d", ele_mostrar->inf->livro.isbn);
  printf("\n Titulo: %s", ele_mostrar->inf->livro.titulo);
  printf("\n Requisição: %d", ele_mostrar->inf->nreq);
}

void mostrarrequisicoes(ptLISTA_req Lista){
  if (!Lista) return;
  No_req p = Lista->inicio;  
  while (p) {
    mostrar_elemento_req(p);  
    p = p->seg;   
  }  
}

void libertar_no(No ele_libertar) { 
  if (!ele_libertar) return;
// free(ele_libertar->inf->nome);
//  free(ele_libertar->inf->local);
  free(ele_libertar->inf);  // eliminar o conteudo
  free(ele_libertar);       // eliminar o proprio NO
}
//libertar tudo o que tem *
void Destruir_Lista(ptLISTA L){
  if (!L) return;
  
  // percorrer a lista e libertar todos os elementos
  No p = L->inicio;  // p no primeiro elemento
  while (p) {
    No ant = p;
    p = p->seg;   // avançar para o elemento seguinte
    libertar_no(ant);
  }
  // inicializar a lista
  free(L);
}

void libertar_elemento(ELEMENTO *ele_libertar){ 
  if (!ele_libertar) return;
//  free(ele_libertar->info->titulo);
//  free(ele_libertar->info->area);
//  free(ele_libertar->info->autor);
  free(ele_libertar->info);  
  free(ele_libertar);       
}

void Destruir_Faixa(ptFAIXA L){
  if (!L) return;
  ELEMENTO *p = L->Inicio;  
  while (p) {
    ELEMENTO *ant = p;
    p = p->Prox;
    libertar_elemento(ant);
  }
  free(L);
}

void libertar_req(No_req ele_libertar){ 
  if (!ele_libertar) return;
//  free(ele_libertar->inf->livro.titulo);
//  free(ele_libertar->inf->pessoa.nome);
  free(ele_libertar->inf);  
  free(ele_libertar);       
}

void Destruir_req(ptLISTA_req L){
  if (!L) return;
  No_req p = L->inicio;  
  while (p) {
    No_req ant = p;
    p = p->seg;   
    libertar_req(ant);
  }
  
  free(L);
}
////////////////////////////////////////////////////////////////////


ptLOCALIZACAO Criar_localizacao(){
    ptLOCALIZACAO L = (ptLOCALIZACAO )malloc(sizeof(ptLOCALIZACAO));
    L->inicio = NULL;
    L->nelementos = 0;
    return L;
}

Nodo criar_nodo(){ 
  Nodo E = (Nodo)malloc(sizeof(Nodo));
  if (!E) return NULL;
  E->inf = (localizacao *)malloc(sizeof(struct sitio));
  E->seg = NULL;
  return E;
}
void inserir_nodo_fim(ptLOCALIZACAO L, Nodo E){
  E->seg = NULL;  
  if(!L) return;
  if (!L->inicio) 
    L->inicio = E;
  else {
    Nodo p = L->inicio;
    while(p->seg)
      p=p->seg;
    p->seg = E;
  }
   L->nelementos ++;
}

void mostrar_nodo(Nodo ele_mostrar){ 
  printf("\n Localizacao: %d", ele_mostrar->inf->local);
	printf("\n Distrito: %s", ele_mostrar->inf->cidade);
	printf("\n Concelho: %s", ele_mostrar->inf->vila);
	printf("\n Freguesia: %s\n", ele_mostrar->inf->freguesia);
}

void mostrar_local(ptLOCALIZACAO Lista){ 
  if (!Lista) return;
  Nodo p = Lista->inicio;  
  while (p) {
    mostrar_nodo(p);  
    p = p->seg;   
  }
}

/////////////////////////////////////////////////função apelidos
ptLISTA_ape criar_lista_ape(){
  ptLISTA_ape ls = (ptLISTA_ape )malloc(sizeof(struct Lista_ape));
	if (!ls) return NULL;
	ls->inicio = NULL;
	ls->nelementos = 0;
	return ls;
}

No_ape criar_no_ape(){ 
  No_ape E = (No_ape) malloc(sizeof(struct no_ape));
  if (!E) return NULL;
  E->inf = (APELIDOS) malloc(sizeof(struct apelidos));
  E->seg = NULL;
  return E;
}

void libertar_ape(No_ape ele_libertar){ 
  if (!ele_libertar) return;
//  free(ele_libertar->inf->livro.titulo);
//  free(ele_libertar->inf->pessoa.nome);
  free(ele_libertar->inf);  
  free(ele_libertar);       
}

void Destruir_ape(ptLISTA_ape L){
  if (!L) return;
  No_ape p = L->inicio;  
  while (p) {
    No_ape ant = p;
    p = p->seg;   
    libertar_ape(ant);
  }
  
  free(L);
}
void inserir_apelidos(ptLISTA_ape L, No_ape E){
  E->seg = NULL;  
  if(!L) return;
  if (!L->inicio) 
    L->inicio = E;
  else {
    No_ape p = L->inicio;
    while(p->seg)
      p=p->seg;
    p->seg = E;
  }
   L->nelementos ++;
}