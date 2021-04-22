#include <locale.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <ctype.h>//para o isdigit
#include "funcoes.h"
#include "lista.h"
#include "hashing.h"

int detetarnumb(char *s){//serve para inserir so numeros
	int x;
	int z=0;
	x=atoi(s);
	for(int i =0; i<strlen(s);i++){
		if(isdigit(s[i]) == 0 ){
			z=1;
			break;
		}
	}
	if(z==0)
		return 1;
	else
		return 0;
}
int soletras(char *s){//serve para inserir so letras
	int x;
	int z=0;
	char c[] = " ";
	x=atoi(s);
	for(int i =0; i<strlen(s);i++){
		if(isalpha(s[i]) == 0 ){
			if(s[i] == *c){
				continue;
			}
			z=1;
			break;
		}
	}
	if(z==0)
		return 1;
	else
		return 0;
}

void MostrarLivro(Livro *V)//função para mostrar livros
{
    printf("Livro: Titulo->[%s] Autor->%s ISBN->%d  Requisitado->%d  Ano->%d Nrequisições->%d\n", V->titulo,V->autor ,V->isbn,V->requisitado,V->data.ano,V->nreq);
}
//função para criar um livro na lista hashing
Livro *CriarLivros2(int cod,  char *area,char *autor ,char *titulo,char *date)
{
    Livro *X = (Livro *)malloc(sizeof(Livro));
    X->requisitado=0;
    X->area = (char *)malloc((strlen(area)+1) * sizeof(char));  
    strcpy(X->area,area);    
    X->isbn=cod;
		X->autor = (char *)malloc((strlen(autor)+1) * sizeof(char));  
    strcpy(X->autor,autor);
    X->titulo = (char *)malloc((strlen(titulo)+1) * sizeof(char));
    strcpy(X->titulo,titulo);
    char de[] = "/";
    int count1 = 0;
    char *car = strtok(date, de);
    while(car != NULL){
    if(count1 == 0){
		 if(atoi(car)==100){
			 	X->data.dia=0;
				X->data.mes=0;
				X->data.ano=0;
				 break;
		 }
		 else
     		X->data.dia=atoi(car);
    }
    if(count1 == 1){
     X->data.mes=atoi(car);
     }
     if(count1 == 2){
     X->data.ano=atoi(car); 
  }
   count1++;
   car = strtok(NULL, de);
  }
    X->nreq=0;
    return X;
}
//função para calcular a area que aparece mais vezes
void areamaisvezes(Hashing *HV){
  int nvezes = 0;
  char x[20];
  NO_HAS *P = HV->Inicio;
  while (P){
  if(P->LLivros->NEL > nvezes){
    nvezes=P->LLivros->NEL;
    strcpy(x, P->CHAVE);
  }
  P=P->Prox_Chave;
  }
  printf("\nArea->%s",x);
  printf("\nNumero livros->%d",nvezes);
	nvezes=0;
	if(strcmp(x,"None")==0){//No caso de a area ser "None"="sem area" é calculado a segunda area com mais
		P = HV->Inicio;
		while(P){
			if(strcmp(P->CHAVE,"None")==0)
			{
				P=P->Prox_Chave;
				continue;
			}
			if(P->LLivros->NEL > nvezes){
    		nvezes=P->LLivros->NEL;
    		strcpy(x, P->CHAVE);
  		}
			P=P->Prox_Chave;
		}
		printf("\nSegunda Area com mais livros->%s",x);
  	printf("\nNumero livros->%d",nvezes);
	}
}

//função para procurar uma pessoa por isbn
void isbnexiste(Hashing *HV){
  NO_HAS *P = HV->Inicio;
	int n,verifica=0;
	char x[20];
	do{
		printf("\nIntroduza o ISBN:");
		scanf("%s",x);
		n=detetarnumb(x);
		if(n==1){
			verifica=1;
		}
		else
			printf("\nInsira só numeros");
	}while(!verifica);
  int z = 0;
  while(P){
    Elemento Z = P->LLivros->Inicio;
    while(Z){
      if(Z->info->isbn == atoi(x)){
      printf("Livro:Area->%s Titulo->[%s] Isbn->%d\n",P->LLivros->Inicio->info->area, P->LLivros->Inicio->info->titulo, P->LLivros->Inicio->info->isbn);
      z++;
  }
    Z=Z->Prox;
  }
    P=P->Prox_Chave;
  }
  if (z==0){
  printf("\nNão existe nenhum!");
  }
}
/*pessoa*/
//////////////////////////////////
//verificação se o id respeita o pedido
int idvalidoler(ptLISTA L,char *pt){
   int tam = strlen(pt);
    if (tam != 9) return -1;
    int soma = 0;
    for (int i = 0; i < tam; i++)
    {
        soma += pt[i] - '0';
    }
    if ((soma % 10)!=0){
      return 0;
    }
    return 1; 
}
//verificação se o ano é bisexto
int bisexto(int year){
    if (year % 4 == 0) {
        if (year % 100 == 0) {
            if (year % 400 == 0){
                return 1;
            }
            else{
                return 0;
            }
        } else{
            return 1;
        }
    } else{
        return 0;
    }
    return 0;
}
//verificação da existencia da data
int dataexiste(char *ptr,int tipo){
  int x,y,z,k=0;
  char *novo;
  //printf("\nData->%s",ptr);
	if(tipo==1){
  	sscanf(ptr,"%d-%d-%d", &x, &y,&z);
	}
	else{
		sscanf(ptr,"%d/%d/%d", &x, &y,&z);
	}
  if(y==1 || y==3 || y==5 || y==7 || y==8 || y==10 || y==12){
		if(x>31){
			return 0;
		}
		else{
			return 1;
		}
  }
  else if(y==4 || y==6 || y==9 || y==11){
		if(x>30){
			return -1;
		}
		else{
			return 1;

		}
  }
  else if(y==2){
		k=bisexto(z);
		if(k==1 && x>29){
		// printf("\nErro->Ano bisexto mas com dias a mais");
			return -2;
		}
		else if(k==0 && x>28){
		// printf("\nErro->Ano nao bisexto mas com dias a mais");
			return -3;
		}
		else{
			//printf("\nMes de 29 com 29 corretos");
			return 1;
		}
  }
  else{
    return -4;
  }
  return 0;
}
//verificação do id valido porem para outra função.(inserir pessoas)
int idvalido(ptLISTA L,char *s){
   No p=L->inicio;
   int x=0,soma=0,rem,final,num;
	 num=detetarnumb(s);//verificação se tem letras
	 if(num==0){
	 	printf("\nInsira só numeros");
		return 0;
	 }
	 x=atoi(s);
	 final=x;
  while(x!=0){
      rem = x % 10;
      soma = soma+rem;
      x= x / 10;
  }
   if(soma % 10 != 0){
     printf("\nNão é divisivel por 10");
     return 0;
   }
   int nDigits = floor(log10(abs(final))) + 1;
   if(nDigits != 9){
     printf("\nInsira 9 digitos!!");
     return 0;
   }
   
   while(p!=NULL){
     if(final == p->inf->id){
       printf("\nExiste um");
       return 0;
     }
     p=p->seg;
   }
   printf("\nNao existe nenhum");
   return 1;
}
char* upper_string(char s[]) //Colocar a string com letras grandes
	{
   int c = 0;

   while (s[c] != '\0') {
      if (s[c] >= 'a' && s[c] <= 'z') {
         s[c] = s[c] - 32;
      }
      c++;
   }
	 return s;
}
//função para inserir pessoas
void ler_pessoa(ptLISTA L,No E,ptLOCALIZACAO l){
    char nom[100];
		Nodo X=l->inicio;
    int local,y,x,z=0,diafinal;
		char s[10],dia[3],mes[3],ano[5];
    FILE *f;
    f = fopen("Requisitantes.txt","a");
    E->inf->nome = (char *)malloc((strlen(nom)+1) * sizeof(char));
    do{
			printf("\n Introduza IDss: ");
			scanf(" %s", s);
			z=idvalido(L,s);
    }while(!z);
		E->inf->id=atoi(s);
    printf("\nNome->");
    scanf(" %[^'\n']s",nom);
    E->inf->nome = (char *)malloc((strlen(nom)+1) * sizeof(char));
    strcpy(E->inf->nome,nom);
		z=0;//para a verificação seguinte
		do{
			printf("\nData de nascimento");
			do{
				printf("\nDia:");
				scanf("%s",dia);
				x=detetarnumb(dia);
				if(x==0){
					printf("\nInsira só numeros");
				}
				else
					z=1;
			}while(!z);
			z=0;
			do{
    		printf("\nMês:");
    		scanf("%s",mes);
				x=detetarnumb(mes);
				if(x==0){
					printf("\nInsira só numeros");
				}
				else
					z=1;
			}while(!z);
			z=0;
			do{
				printf("\nAno:");
				scanf("%s",ano);
				x=detetarnumb(ano);
				if(x==0){
					printf("\nInsira só numeros");
				}
				else
					z=1;
			}while(!z);
			diafinal=atoi(dia);
			strcat(dia,"-");
			strcat(dia,mes);
			strcat(dia,"-");
			strcat(dia,ano);
			x=dataexiste(dia,1);
			if(x==1){
				z=1;
			}
			else{
				z=0;
				printf("\nData inexistente");
			}
		}while(!z);
		E->inf->data.dia=diafinal;
		E->inf->data.mes=atoi(mes);
		E->inf->data.ano=atoi(ano);
		printf("%d-%d-%d",E->inf->data.dia,E->inf->data.mes,E->inf->data.ano);
    printf("\nLocal:");
    scanf("%d", &E->inf->local);
		while(X){
			if(X->inf->local==E->inf->local){
				E->inf->vila = X->inf->vila;
				E->inf->cidade = X->inf->cidade;
				E->inf->freguesia = X->inf->freguesia;
			}
			X=X->seg;
		}
		E->inf->nrequisicoes=0;
    fprintf(f,"%d\t%s\t%d-%d-%d\t%d", E->inf->id,nom,E->inf->data.dia,E->inf->data.mes,E->inf->data.ano,E->inf->local);
    fclose(f);
		inserir_elemento_fim(L,E);
}
//verificar se o isbn existe se a data existe
void inserir_livro(Hashing *HV){
	char area[20],autor[20],areanova[20],titulo[20],dia[3],teste[30],mes[3],ano[5];
	char data[20] = "";
  int isbn,x,z=0,i=0;
	FILE *f;
  f = fopen("livro.txt","a");
  printf("\nArea->");
  scanf(" %[^'\n']s",area);
	strcpy(areanova, upper_string(area));
	do{
		printf("\nAutor->");
		scanf(" %[^'\n']s",autor);
		x=soletras(autor);
		if(x==0){
			printf("\nInsira só letras");
		}
		else{
			z=1;
		}
	}while(!z);
	z=0;
  printf("\nTitulo->");
  scanf(" %[^'\n']s",titulo);
  printf("\nIsbn->");
  scanf("%d",&isbn);
	do{
			printf("\nData de publicação");
			do{
				printf("\nDia:");
				scanf("%s",dia);
				x=detetarnumb(dia);
				if(x==0){
					printf("\nInsira só numeros");
				}
				else
					z=1;
			}while(!z);
			z=0;
			do{
    		printf("\nMês:");
    		scanf("%s",mes);
				x=detetarnumb(mes);
				if(x==0){
					printf("\nInsira só numeros");
				}
				else
					z=1;
			}while(!z);
			z=0;
			do{
				printf("\nAno:");
				scanf("%s",ano);
				x=detetarnumb(ano);
				if(x==0){
					printf("\nInsira só numeros");
				}
				else
					z=1;
			}while(!z);			
			strcpy(teste,dia);
			strcat(teste,"/");
			strcat(teste,mes);
			strcat(teste,"/");
			strcat(teste,ano);
			x=dataexiste(teste,0);
			if(x==1){
				z=1;
			}
			else{
				z=0;
				printf("\nData inexistente");
			}
		}while(!z);
		strcat(data,dia);
		strcat(data,"/");
		strcat(data,mes);
		strcat(data,"/");
		strcat(data,ano);
		fprintf(f,"---\t%s\t%s\t----\t----\t-----\t--\t%s\t--\t--\t%d\t%s\t----\n",areanova,autor,data,isbn,titulo);
	  Add_Hashing_PRO(HV, CriarLivros2(isbn, areanova,autor,titulo,data));
		fclose(f);
}

//função para inserir requisições
void inserir_req(ptLISTA_req L, ptLISTA lista, Hashing *HV,No_req E){
  int x=1,num=0,verifica=0,z=0;
	char id[10],isbn[20];
  No P = lista->inicio;
  NO_HAS *X = HV->Inicio;
  ELEMENTO *Z = X->LLivros->Inicio;
  while(x==1){
    No P = lista->inicio;
		do{
			printf("\nIntroduza o id válido:");
			scanf("%s",id);
			z=detetarnumb(id);
			if(z==1)
				verifica=1;
			else{
				printf("\nIntroduza só numeros");
			}
		}while(!verifica);
    while(P != NULL){
      if(P->inf->id==atoi(id)){
        E->inf->pessoa.id=P->inf->id;
        E->inf->pessoa.nome=P->inf->nome;
				P->inf->nrequisicoes++;
        x=0; //verificação para o caso de nao existir
				P=NULL;
      }
			else{
      	P=P->seg;
			}
    }
  }
	verifica=0;
  	x=1;
 	 	while(x==1){
			do{
				printf("\nIntroduza o código do isbn:");
				scanf("%s",isbn);
				z=detetarnumb(isbn);
				if(z==1)
					verifica=1;
				else{
					printf("\nIntroduza só numeros");
				}
			}while(!verifica);
   	 	X = HV->Inicio;
    	while(X){     
      	Z = X->LLivros->Inicio;
      	while(Z){      
        	if(Z->info->isbn==atoi(isbn)){
						E->inf->livro.isbn=Z->info->isbn;
						E->inf->livro.titulo=Z->info->titulo;
						if(Z->info->requisitado == 1){
							printf("\nLivro ja se encontra requisitado!Insira outro!");
							x=1;
						}
						else{
							x=0;//para o caso de existir um livro
							Z->info->requisitado=1;
							Z->info->nreq++;
							E->inf->nreq = 1;
						}
        	}
        Z=Z->Prox;
      }
      X=X->Prox_Chave;
    }
  }
  inserirrequisicoes(L, E);
}

//idade maxima existente
int idade_maxima(ptLISTA L){
  int max=2020;
  //  if (!L) return NULL;
  No p = L->inicio; 
  while (p) {
    if(p->inf->data.ano<max)//quanto maior o ano mais novo é a pessoa
    {
      max=p->inf->data.ano;
    }  
    p = p->seg;   
  }
  printf("\nIdade maxima->%d",2020-max);
  return max;
}

//media das idades existentes
float media_idade(ptLISTA L){
  float media=0,x,y,z;
  int soma=0;
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  z=float(tm.tm_year + 1900);//calculo do ano em que estamos
  No p = L->inicio; 
  while (p) {
    soma+=p->inf->data.ano;
    p = p->seg;   
  }
  x=float(soma);
  y=float(L->nelementos);
  printf("\nMedia->%0.2f",x/y);
  printf("\nIdade->%0.2f",z-(x/y));
  return ((float(soma/L->nelementos)));
}

//idade superior a um dado numero
int idade_superior(ptLISTA L){
  int x=0,z=0,y=0,verifica=0;
	char n[3];
	do{
		printf("\nInsira a idade->");
  	scanf("%s",n);
		x=detetarnumb(n);
		if(x==1){
			verifica=1;
		}
		else
			printf("\nInsira só numeros");
	}while(!verifica);
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  x=tm.tm_year + 1900;//calculo do ano em que estamos
  No p = L->inicio; 
  while(p){
    z=x-p->inf->data.ano;
    if(z>atoi(n)){
     y++;
    }
    p = p->seg;  
  }
  printf("\nExistem->%d", y);
  return x;
}

//verificar quando pessoas existem com o nome
void verificanome(ptLISTA L){
  int y=0,ret,x;
  char z[50],nome[50];
  No p = L->inicio;
  printf("\nName:");
  scanf(" %[^'\n']s",nome);
  //printf("%s",nome);
  int res;
  while(p){
  strcpy(z, p->inf->nome);
  int res=strcmp(upper_string(z),upper_string(nome));//upper para comparar só o nome e ignorar letras maisculas ou minusculas
  if(res==0){
     y++;
   }  
  p = p->seg;  
  }
  printf("\nExistem->%d",y);
}

//idade que aparece mais vezes
int idade_mais_repetida(ptLISTA L){
  No p = L->inicio;
	No_ape E;
	ptLISTA_ape lista;
	lista = criar_lista_ape();
	E = criar_no_ape();
  int temp,x=0,z=0,res=0,total=0,ano=0,verifica;
  No temp1;
  No temp2;
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  ano=tm.tm_year + 1900;
	while(p){
		verifica=0;
				if(z==0){
					E = criar_no_ape();
					E->inf->idade=ano-p->inf->data.ano;
					E->inf->total=1;
					inserir_apelidos(lista, E);
					z++;
					verifica=1;				
				}
				else{
					E=lista->inicio;
					while(E){						
						if(ano-p->inf->data.ano==E->inf->idade)
						{
							E->inf->total++;
							verifica=1;
						}
						E=E->seg;
					}		
				if(verifica==0){
					E = criar_no_ape();
					E->inf->idade=ano-p->inf->data.ano;
					E->inf->total=1;
					inserir_apelidos(lista, E);
					}
				}
		p=p->seg;
	}
	E=lista->inicio;
	while(E)
	{
		if(E->inf->total>total){
			res=E->inf->idade;
			total=E->inf->total;
		}
		E=E->seg;
	}
	printf("\nIdade->%d\nTotal->%d",res,total);
	Destruir_ape(lista);
  return 0;
}
//Apelido mais usado pelos requisitantes
void apelido_mais_usado(ptLISTA L){ 
	No X=L->inicio;
	No_ape E;
	ptLISTA_ape lista;
	lista = criar_lista_ape();
	E = criar_no_ape();
	E=lista->inicio;
	int count,z=0,total=0,verifica=0;
	char delim[] = " ";
	char *ptr;
	char nome[20];
	while(X){
		count=0;
		char name[20];
		strcpy(name,X->inf->nome);
		char *ptr = strtok(name, delim);
		while(ptr)
		{
			if(count == 0){
				count ++;
			}
			else{
				verifica=0;
				if(z==0){
					E = criar_no_ape();
					E->inf->nome = (char *)malloc((strlen(ptr)+1) * sizeof(char));
					strcpy(E->inf->nome,ptr);
					E->inf->total=1;
					inserir_apelidos(lista, E);
					z++;
					verifica=1;				
				}
				else{
					E=lista->inicio;
					while(E){						
						if(strcmp(ptr, E->inf->nome)==0)
						{
							E->inf->total++;
							verifica=1;
						}

						E=E->seg;
					}		
				if(verifica==0){
					E = criar_no_ape();
					E->inf->nome = (char *)malloc((strlen(ptr)+1) * sizeof(char));
					strcpy(E->inf->nome,ptr);
					E->inf->total=1;
					inserir_apelidos(lista, E);
					}
				}
			}
			ptr = strtok(NULL, delim);
		}
		X=X->seg;
	}
	E=lista->inicio;
	while(E)
	{
		if(E->inf->total>total){
			strcpy(nome, E->inf->nome);
			total=E->inf->total;
		}
		E=E->seg;
	}
	printf("\nNome->%s\nTotal->%d",nome,total);
	Destruir_ape(lista);
}

void livro_mais_recente(Hashing *HV){
  NO_HAS *P = HV->Inicio;
  int year=20;
  int mes=0;
  int dia=0;
  while(P){
    Elemento K = P->LLivros->Inicio;
    while(K){
      if(K->info->data.ano > year){
        year=K->info->data.ano;
      }
      K=K->Prox;
    }
    P=P->Prox_Chave;
  }
  NO_HAS *X = HV->Inicio;
  while(X){
    Elemento Z = X->LLivros->Inicio;
    while(Z){
      if(Z->info->data.ano == year){
       printf("\nLivro: Titulo->[%s] ISBN->%d  Ano->%d\n",Z->info->titulo, Z->info->isbn,Z->info->data.ano);
      }
      Z=Z->Prox;
    }
    X=X->Prox_Chave;
  }
}
//devolver um livro
void devolverrequisicao(ptLISTA_req L, Hashing *HV){
	char isbn[20],id[10];
	int procurar = 1,x,verifica=0;
	No_req P;
	No_req ant;
	ant = P = L->inicio;
  NO_HAS *X = HV->Inicio;
  ELEMENTO *Z;
	do{
		printf("\nID da pessoa:");
		scanf("%s",id);
		x=detetarnumb(id);
		if(x==1){
			verifica=1;
		}
		else
			printf("\nInsira só numeros");
	}while(!verifica);
	verifica=0;
	do{
		printf("\nIsbn do livro:");
		scanf("%s",isbn);
		x=detetarnumb(isbn);
		if(x==1){
			verifica=1;
		}
		else
			printf("\nInsira só numeros");
	}while(!verifica);
	while(procurar){
		if (!P){
			procurar=0;
		}
		else if(P->inf->pessoa.id==atoi(id)){
			procurar = 0;
		}
		else{
		ant = P;
		P=P->seg;
		}
	}
	if(!P){
		printf("\nNada a remover!");
	}
	else{
		if(P == L->inicio)
			L->inicio=P->seg;
		else
			ant->seg=P->seg;

		L->nelementos--;
	}
	while(X){
		Z = X->LLivros->Inicio;
		while(Z){
			if(Z->info->isbn==atoi(isbn)){
				Z->info->requisitado=0;
			}
			Z=Z->Prox;
		}
		X=X->Prox_Chave;
	}
}
//mostrar as requisições
void mostarrequisicoesrequisitante(ptLISTA_req L){
	No_req E = L->inicio;
	int x;
	printf("\nIntroduza o Id da pessoa:");
	scanf("%d",&x);
	while(E){
		if(E->inf->pessoa.id==x){
			printf("\nId->%d\nPessoa->%s,\nIsbn->%d\nLivro->%s",E->inf->pessoa.id,E->inf->pessoa.nome,E->inf->livro.isbn,E->inf->livro.titulo);
		}
		E=E->seg;
	}
}

// mostrar o livro mais requisitado
void livromaisrequisitado(Hashing *HV){
	NO_HAS *P = HV->Inicio;
	Elemento X = P->LLivros->Inicio;
	int max=0;
	while(P){
		Elemento K = P->LLivros->Inicio;
		while(K){
			if(K->info->nreq > max){
				max = K->info->nreq;
				X=K;
			}
			K=K->Prox;
		}
		P=P->Prox_Chave;
	}
	printf("\nIsbn->%d\nTitulo->%s\nNumero de requisicoes->%d",X->info->isbn,X->info->titulo,X->info->nreq);
}

//mostrar a area mais requisitada
void areamaisrequisitada(Hashing *HV){
	NO_HAS *P = HV->Inicio;
	NO_HAS *X =HV->Inicio;
	int count=0,max=0;
	while(P){
		count=0;
		Elemento K = P->LLivros->Inicio;
		while(K){
			count += K->info->nreq;
			K=K->Prox;
		}
		if(count>max){
			max=count;
			X=P;
		}
		P=P->Prox_Chave;
	}
	printf("\nA area com mais requisições é -> [%s]",X->CHAVE);
}

//pessoas que nunca requisitaram nada
void mostrarPsemrequisicoes(ptLISTA L){
	No E = L->inicio;
	while(E){
		if(E->inf->nrequisicoes==0)
			mostrar_elemento(E);
	E=E->seg;
	}
}

//calculo dos tamanhos das structs
void tamanhostruct(){
	long x=0;
	x=sizeof(struct date)+sizeof( struct pessoa)+sizeof( struct Lista)+sizeof( struct livro)+sizeof( struct faixa)+sizeof( struct requisicoes)+sizeof( struct Lista_req)+sizeof( struct Lista_req)+sizeof( struct no_has)+sizeof( Hashing)+sizeof(struct no)+ sizeof(struct elemento)+sizeof(struct no_req)+sizeof(localizacao)+sizeof(nodo)+sizeof(Localizacao)+sizeof(struct apelidos)+sizeof(struct no_ape)+sizeof(struct Lista_ape);
	printf("\nTamanho das structs -> %ld",x);
}
//num dado local quantas vezes aparece um dado apelido
void determinarLocalcomNome(ptLISTA l){
	No E=l->inicio;
	int count=0,res,fim,x=0,esco,z;
	char delim[] = " ";
	char line[50],escolha[2];
	char local[12],localnovo[12];
	char apelido[20];
	do{
		z=0;
		do{
		printf("\nQuer verificar por concelho ou distrito? (distrito->1 concelho->2)->");
		scanf(" %[^'\n']s",escolha);
		esco=detetarnumb(escolha);
		if(esco==0){
					printf("\nInsira só numeros");
				}
				else
					z=1;
			}while(!z);
	}while(atoi(escolha)<1 || atoi(escolha) >2);
	printf("\nLocal->");
  scanf(" %[^'\n']s",localnovo);
	if(atoi(escolha)==1)
		strcpy(local, upper_string(localnovo));
	else 
		strcpy(local, localnovo);
	printf("\nApelido->");
  scanf("%s",apelido);
	if(atoi(escolha)==1){
		while(E){	
			if(strcmp(E->inf->cidade,local)==0){	
					strcpy(line, E->inf->nome);
					char *ptr = strtok(line, delim);
					while(ptr != NULL){
							if (count>0){
								if (strcmp(ptr, apelido)==0)
									x++;
							}
							count ++;
							ptr = strtok(NULL, delim);
					}
			}
			E=E->seg;
		}
	}
	else{
		while(E){	
			if(strcmp(E->inf->vila,local)==0){	
					strcpy(line, E->inf->nome);
					char *ptr = strtok(line, delim);
					while(ptr != NULL){
							if (count>0){
								if (strcmp(ptr, apelido)==0)
									x++;
							}
							count ++;
							ptr = strtok(NULL, delim);
					}
			}
			E=E->seg;
		}
	}
	printf("\n\nExistem-> %d",x);
}
//calculo de domingo retorna 0 se for domingo
int dayofweek(int d, int m, int y) 
{ 
    static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 }; 
    y -= m < 3; 
    return ( y + y/4 - y/100 + y/400 + t[m-1] + d) % 7; 
} 
//listar requisitantes que nasceram num domingo ou fazem anos
void listarreqdomingo(ptLISTA L){
	No E=L->inicio;
	int dia,mes,ano,ano_corrente,day;
	time_t t = time(NULL);
  struct tm tm = *localtime(&t);
	ano_corrente=tm.tm_year + 1900;
	while(E){
		dia=E->inf->data.dia;
		mes=E->inf->data.mes;
		ano=E->inf->data.ano;
		int encontrou=0;
		while(!encontrou){
			day = dayofweek(dia, mes, ano);
			if(day == 0){ // é domingo (mostra)
				if(E->inf->data.ano == ano) // identifica se é nascimento
					printf("\nNasceu num domingo");
				else
					printf("\nAniversario num domingo no ano->%d",ano);
				mostrar_elemento(E);
				encontrou=1;
			}
			else if(ano==ano_corrente)
				encontrou=1;
			ano++;
			}
			E=E->seg;
		}	
}



/////////////////////////////
//ano bisexto
bool isLeap(int y) 
{ 
    if ((y%100 != 0 && y%4 == 0) || y %400 == 0) 
        return true; 
  
    return false; 
} 
  
//retorna o número de dias decorridos
int offsetDays(int d, int m, int y) 
{ 
    int offset = d; 
  
    switch (m - 1) 
    { 
    case 11: 
        offset += 30; 
    case 10: 
        offset += 31; 
    case 9: 
        offset += 30; 
    case 8: 
        offset += 31; 
    case 7: 
        offset += 31; 
    case 6: 
        offset += 30; 
    case 5: 
        offset += 31; 
    case 4: 
        offset += 30; 
    case 3: 
        offset += 31; 
    case 2: 
        offset += 28; 
    case 1: 
        offset += 31; 
    } 
  
    if (isLeap(y) && m > 2) 
        offset += 1; 
  
    return offset; 
} 
  
//auxilio por causa do dias
void revoffsetDays(int offset, int y, int *d, int *m) 
{ 
    int month[13] = { 0, 31, 28, 31, 30, 31, 30, 
                      31, 31, 30, 31, 30, 31 }; 
  
    if (isLeap(y)) 
        month[2] = 29; 
  
    int i; 
    for (i = 1; i <= 12; i++) 
    { 
        if (offset <= month[i]) 
            break; 
        offset = offset - month[i]; 
    } 
  
    *d = offset; 
    *m = i; 
} 
  
// remove os 47 dias para o carnaval. 
void carnaval(int *d1, int *m1, int y1, int x) 
{ 
    int offset1 = offsetDays(*d1, *m1, y1); 
    int remDays = isLeap(y1)?(366-offset1):(365-offset1); 
    int y2, offset2; 
    if (x <= remDays) 
    { 
        y2 = y1; 
        offset2 = offset1 + x; 
    } 
  
    else
    { 
       
        x -= remDays; 
        y2 = y1 + 1; 
        int y2days = isLeap(y2)?366:365; 
        while (x >= y2days) 
        { 
            x -= y2days; 
            y2++; 
            y2days = isLeap(y2)?366:365; 
        } 
        offset2 = x; 
    } 
  
    int m2, d2; 
    revoffsetDays(offset2, y2, &d2, &m2); 
		*d1=d2;
		*m1=m2;
		y1=y2; 
} 
//calculo da pascoa 
void easter(int year, int *month, int *day)
{
    int Y,a,c,e,h,k,L;
    double b,d,f,g,i,m;
    Y = year;
    a = Y%19;
    b = floor(Y/100);
    c = Y%100;
    d = floor(b/4);
    e = (int)b%4;
    f = floor((b+8)/25);
    g = floor((b-f+1)/3);
    h = (19*a+(int)b-(int)d-(int)g+15)%30;
    i = floor(c/4);
    k = c%4;
    L = (32+2*e+2*(int)i-h-k)%7;
    m = floor((a+11*h+22*L)/451);
    *month = (int)floor((h+L-7*m+114)/31);
    *day = (int)((h+L-7*(int)m+114)%31)+1;
}
//função extra da quaresma
void listarreqquaresma(ptLISTA l) 
{ 
	No E;
	time_t tictoc;
	struct tm *now;
	int year,month,day,z,w,ano_n,dia_n,mes_n,day_n,month_n,year_n,dia,mes,ano,encontrou,nascimento,x = -47,ano_corrente; 
	time_t t = time(NULL);
  struct tm tm = *localtime(&t);
	ano_corrente=tm.tm_year + 1900;
	E=l->inicio;
	while(E){
		w=E->inf->data.dia;
		z=E->inf->data.mes;
		encontrou=0;
		nascimento=0;
		year=E->inf->data.ano;
		while(!encontrou){
			easter(year,&month,&day);
			dia=day;//dia==dia carnaval
			mes=month;
			ano=year; 
			carnaval(&dia, &mes, ano, x); 
			if(z>=mes && z<=month){
				if(z==mes && w>=dia){
					if(nascimento==0){
						printf("\nNasceu na quaresma");
						encontrou=1;
					}
					else{
						printf("\nFaz anos na quaresma->%d",year);
						encontrou=1;
					}
					mostrar_elemento(E);
				}
				else if(z==month && w<=day){
					if(nascimento==0)
					{
						printf("\nNasceu na quaresma");
						encontrou=1;
					}
					else
					{
						printf("\nFaz anos na quaresma->%d",year);
						encontrou=1;
					}
					mostrar_elemento(E);
				}
				else if(z==mes+1 && z!=month){
					if(nascimento==0)
					{
						printf("\nNasceu na quaresma");
						encontrou=1;
					}
					else
					{
						printf("\nFaz anos na quaresma->%d",year);
						encontrou=1;
					}
					mostrar_elemento(E);
				}
			}
			if(year==ano_corrente)
				encontrou=1;
			nascimento++;
			year++;
		}
	E=E->seg;
	}  
} 
