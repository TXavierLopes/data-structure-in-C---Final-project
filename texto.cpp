#include "texto.h"
#include "hashing.h"
#include "lista.h"

#include <ctype.h>

//para remover o \n e o \r para a leitura dos ficheiros
char* RemoveCRLF(char * str){
	  if (str[strlen(str)-1]=='\n')
			str[strlen(str)-1] = '\0';
	  if (str[strlen(str)-1]=='\r')
			str[strlen(str)-1] = '\0';
	 return str;
 }

 char *strtok_new(char * string, char const * delimiter){
   static char *source = NULL;
   char *p, *riturn = 0;
   if(string != NULL)         source = string;
   if(source == NULL)         return NULL;

   if((p = strpbrk (source, delimiter)) != NULL) {
      *p  = 0;
      riturn = source;
      source = ++p;
   }
return riturn;
}
//ler o ficheiro livros
void lerlivro(ptFAIXA L,Hashing *HV){
	char casoErro[350];
	int count=0,val=1,z=0,livr=0,verifica;
	FILE* F = fopen("livro.txt", "r");
	FILE *f;
  f = fopen("logs.txt","a");	
	char buffer[400];
	fgets(buffer, 500, F);
	fgets(buffer, 500, F);
//	while (!feof(F)){
	while(fgets ( buffer, sizeof buffer, F ) != NULL){
	 	count=0;
		char *Area;
		char *Autor;
		char *ISBN;
		char *Titulo;
		char *data;
		verifica=1;
//		char buffer[400];
//	 	fgets(buffer, 500, F);
		strcpy(casoErro, buffer);
		RemoveCRLF(buffer);
		char delimiter[] = "\t";
 		char * p = strtok_new(buffer, delimiter);
		if(!p){//para negar o caso do 2º semestre
			continue;
		}
		while(p){
	 		if(count==1){
      	if(*p) {
					if(p[2]== '/'){
						verifica=0;
						break;//para o caso de em vez da area aparacer uma data
					}
					if(p[0] == '-'){
						Area = 	((char*)"None");
					}
					else{
						Area = (char *)malloc((strlen(p)+1) * sizeof(char));
						strcpy(Area,p);
					}
				}
        else{
					Area = ((char*)"None");
				} 
			}
			if (count==2){//foi utilizado o forn como autor
				if(*p){
					if(p[0] == '-'){
							Autor = ((char*)"None");
						}
					else{
						Autor = (char *)malloc((strlen(p)+1) * sizeof(char));
						strcpy(Autor,p);
					}
				}
				else{
					Autor = ((char*)"None");
				}
			}
			else if(count==7){
				if(*p) {
					if(p[0] == '-')
						data = 	((char*)"100");
					else{
						data = (char *)malloc((strlen(p)+1) * sizeof(char));
						strcpy(data,p);
						z=dataexiste(data,livr);
						if(data==0)
              fprintf(f,"Error!Linha->%s Data->Dia superior a 31\n", casoErro);
            else if(z==(-1))
              fprintf(f,"Error!Linha->%s Data->Dia superior a 30\n", casoErro);
            else if(z==(-2))
              fprintf(f,"Error!Linha->%s Data->Dia superior a 29(ano bissexto)\n", casoErro);
            else if(z==(-3))
              fprintf(f,"Error!Linha->%s Data->Dia superior a 28(ano não bissexto)\n", casoErro);
            else if(z==(-4))
              fprintf(f,"Error!Linha->%s Data->Erro nas - - -\n", casoErro);
					} 
				}		
				else
						data = 	((char*)"None"); 
				}
				else if(count==10){
					if(!*p){
						verifica=0;
						break;
					}
						ISBN = (char *)malloc((strlen(p)+1) * sizeof(char));
						strcpy(ISBN,p);
						
				}
				else if(count==11){
					Titulo = (char *)malloc((strlen(p)+1) * sizeof(char));
					strcpy(Titulo,p);	
				}
				count++;     
				p = strtok_new(NULL, delimiter);
   		}
			if(verifica==1){
				Add_Hashing_PRO(HV, CriarLivros2(atoi(ISBN),Area,Autor,Titulo,data));
			}
	 }
	 fclose(F);
	 fclose(f);
}
//ler o ficheiro de requisicoes
void lerreq(ptLISTA_req L, Hashing *HV){
  char delim[] = "\t";
  int x=0,y=0;
  No_req E;
	NO_HAS *P = HV->Inicio;
	ELEMENTO *X = P->LLivros->Inicio;
  FILE *fptr;
  if ((fptr = fopen("requisicoes.txt", "r")) == NULL) {
        printf("Error! opening file");
  }
	else{
    char line[200];
    while ( fgets ( line, sizeof line, fptr ) != NULL )
    	{
				strcpy(line,RemoveCRLF(line));
        char q[30],w[30],r[100],date[20];
        E=criar_no_req();     
        char *ptr = strtok(line, delim);
        int count = 0;
        while(ptr != NULL)
        {
            if(count==0){
                x=atoi(ptr);
                E->inf->pessoa.id=x;
            }
            else if(count == 1){
                 E->inf->pessoa.nome = (char *)malloc((strlen(ptr)+1) * sizeof(char));
                strcpy(E->inf->pessoa.nome,ptr);
            }
            else if(count == 2){
              y=atoi(ptr);
              E->inf->livro.isbn=y;
            }
            else if(count == 3){
              E->inf->livro.titulo = (char *)malloc((strlen(ptr)+1) * sizeof(char));
                strcpy(E->inf->livro.titulo,ptr);
            }
            count++;
            ptr = strtok(NULL, delim);
				}
				while(P){ 
					X = P->LLivros->Inicio; 
					while(X){ 
						if(X->info->isbn == E->inf->livro.isbn) {
							X->info->requisitado=1; 
						}
						X=X->Prox; 
					} 
					P=P->Prox_Chave; 
				} 
				P = HV->Inicio; 
				E->inf->nreq=1; 
				inserirrequisicoes(L, E);
   	}
	fclose (fptr);
	}
}
int divide(int str,int n){
	if(n==4){
      str = str / 100;
			return str;
			}
	else if(n==2){
      str = str / 10000;
			return str;
			}
	return 0;
}
// ler locais 
void lerlocais(ptLOCALIZACAO l){
	Nodo E;
	char delim[] = "\t";
	char line[128];
	char *id,*name;
	int num=0;
	int z=0;
	FILE *freg;
	FILE *concelho;
	FILE *distrito;
	freg = fopen("freguesias.txt", "r");
	while ( fgets ( line, sizeof line, freg ) != NULL ){
		E=criar_nodo();
		strcpy(line,RemoveCRLF(line));
		id=strtok(line,"\t");
		E->inf->local=atoi(id);
    name=strtok(NULL,"\t");		
		E->inf->freguesia = (char *)malloc((strlen(name)+1) * sizeof(char));
		strcpy(E->inf->freguesia,name);
  	int count = 0;
		inserir_nodo_fim(l,E);
	}
	fclose(freg);
	E=l->inicio;
	while(E){
		num=0;
		int x;
		x=E->inf->local;
		num=divide(x,4);
		concelho = fopen("concelhos.txt", "r");
		while ( fgets ( line, sizeof(line), concelho ) != NULL ){
			strcpy(line,RemoveCRLF(line));
  		id=strtok(line,"\t");
			name=strtok(NULL,"\t");
			if(num==atoi(id)){
				E->inf->vila = (char *)malloc((strlen(name)+1) * sizeof(char));
        strcpy(E->inf->vila,name);
				break;
			}    
		}
		fclose(concelho);
		E=E->seg;
	}
	E=l->inicio;
	while(E){
		num=0;
		int x;
		x=E->inf->local;
		num=divide(x,2);
		distrito = fopen("distritos.txt", "r");
		while ( fgets ( line, sizeof(line), distrito ) != NULL ){
			strcpy(line,RemoveCRLF(line));
  		id=strtok(line,"\t");
			name=strtok(NULL,"\t");
			if(num==atoi(id)){
				E->inf->cidade = (char *)malloc((strlen(name)+1) * sizeof(char));
        strcpy(E->inf->cidade,name);
				break;
			}    
		}
	fclose(distrito);
	E=E->seg;
	}
}
//erro das localidades nao existirem
int detetarerro(char *s){
	int x;
	int z=0;
	x=atoi(s);
	for(int i =0; i<strlen(s);i++){
		if(strlen(s)!=6){
			z=1;
			break;
		}
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
//ler pessoas
void lerficheiro(ptLISTA L,ptLOCALIZACAO lista){
  int data=0,df,ver,final=0;
	int novo=3,pess=1;
  No E;
	Nodo P;
	char delim[] = "\t";
  FILE *fptr;
  FILE *f;
  f = fopen("logs.txt","a");
  if ((fptr = fopen("Requisitantes.txt", "r")) == NULL) {
        printf("Error! opening file");
  }
	else{
    char line[128],linha[128];
    while ( fgets ( line, sizeof line, fptr ) != NULL )
    {
				
				strcpy(line,RemoveCRLF(line));
				strcpy(linha,line);
        E=criar_no();
        char *ptr = strtok(line, delim);
        int count = 0;
        while(ptr != NULL)
        {
            if(count == 0){
              df=idvalidoler(L, ptr);
                if(df==1){
                E->inf->id = atoi(ptr); 
                }
                else{
                  if(df==0)
                  fprintf(f,"Error!Linha->%s Id->Não é divisivel por 10\n", linha);
                  else if(df==(-1))
                  fprintf(f,"Error!Linha->%s Id->Não tem 9 digitos\n", linha);
                  else if(df==(-2))
                  fprintf(f,"Error!Linha->%s Id->Já existente\n", linha);
                }
            }
            else if(count == 1){
                E->inf->nome = (char *)malloc((strlen(ptr)+1) * sizeof(char));
                strcpy(E->inf->nome,ptr);
            }
            else if(count == 2){
                data=dataexiste(ptr,pess);
                if(data == 1){
                char de[] = "-";
                int count1 = 0;
                char *car;
                while((car = strtok_r(ptr,"-",&ptr))){
                    if(count1 == 0){
                    E->inf->data.dia=atoi(car);
                    }
                    if(count1 == 1){
                    E->inf->data.mes=atoi(car);
                    }
                    if(count1 == 2){
                    E->inf->data.ano=atoi(car); 
                    }
                    count1++;
                }
              }
                else{
                  if(data==0)
                    fprintf(f,"Error!Linha->%s Data->Dia superior a 31\n", linha);
                  else if(data==(-1))
                      fprintf(f,"Error!Linha->%s Data->Dia superior a 30\n", linha);
                  else if(data==(-2))
                    fprintf(f,"Error!Linha->%s Data->Dia superior a 29(ano bissexto)\n", linha);
                  else if(data==(-3))
                    fprintf(f,"Error!Linha->%s Data->Dia superior a 28(ano não bissexto)\n", linha);
                    else if(data==(-4))
                    fprintf(f,"Error!Linha->%s Data->Erro nas ////\n", linha);
                }
            }
            else if(count == 3){
                P=lista->inicio;				
								int teste;
								novo=detetarerro(ptr);
								if(novo==1){
									while(P){
										if(P->inf->local==atoi(ptr)){
							  			E->inf->local=P->inf->local;
											E->inf->freguesia = (char *)malloc((strlen(P->inf->freguesia)+1) * sizeof(char));
											strcpy(E->inf->freguesia,P->inf->freguesia);
											E->inf->vila = (char *)malloc((strlen(P->inf->vila)+1) * sizeof(char));
											strcpy(E->inf->vila,P->inf->vila);
											E->inf->cidade = (char *)malloc((strlen(P->inf->cidade)+1) * sizeof(char));
											strcpy(E->inf->cidade,P->inf->cidade);
										break;
									}
									else if(P->seg==NULL){
										novo=0;
										fprintf(f,"Error!Linha->%s Localidade não existente->%s\n", linha,ptr);
										break;
									}
									P=P->seg;
								}
							}
							else if(novo==0){
								fprintf(f,"Error!Linha->%s Localidade não existentes->%s\n", linha,ptr);
							}
						}
            count ++;
            ptr = strtok(NULL, delim);
        }
        if(data==1 && df==1 && novo==1){//se alguma das verificações anteriores der mal nao insere
				E->inf->nrequisicoes=0;
        inserir_elemento_fim(L,E);
        }
        printf("\n");
		}
    fclose(f);
    fclose (fptr);
	}
}

//insere requisições feitas
void inserenoficheiro(ptLISTA_req L){
	No_req E = L->inicio;
	FILE *f;
	f = fopen("requisicoes.txt","w");
	while(E){
		fprintf(f,"%d\t%s\t%d\t%s\t%d\n", E->inf->pessoa.id,E->inf->pessoa.nome,E->inf->livro.isbn,E->inf->livro.titulo,E->inf->nreq);
		E=E->seg;
	}
  fclose(f);
}

//NUMERO REQUISICOES desde sempre
void inserirNrequsicoeslivro(Hashing *HV){
	NO_HAS *X = HV->Inicio;
	ELEMENTO *E;
	FILE *f;
	f = fopen("requisicoeslivros.txt","w");
	while (X){
		E = X->LLivros->Inicio;
		while(E){
			if(E->info->nreq>0)
				fprintf(f,"%d\t%d\n", E->info->isbn,E->info->nreq);
			E=E->Prox;
		}
		X=X->Prox_Chave;
	}
	fclose(f);
}
//guarda o numero de requições desde sempre
void inserirNrequsicoespessoa(ptLISTA L){
	No X = L->inicio;
	FILE *f;
	f = fopen("requisicoespessoa.txt","w");
	while (X){
		if(X->inf->nrequisicoes>0)
			fprintf(f,"%d\t%d\n", X->inf->id,X->inf->nrequisicoes);	
		X=X->seg;
	}
	fclose(f);
}
//ler as requisições dos livros
void lerrequisicoeslivros(Hashing *HV){
	NO_HAS *X;
	ELEMENTO *E;
	int isbn=0,nrequisicoes=0;
	char delim[] = "\t";
	FILE *f;
	if ((f = fopen("requisicoeslivros.txt", "r")) == NULL) {
      printf("Error! opening file");
  }
	else{
		char line[128],linha[128];
    while ( fgets ( line, sizeof line, f ) != NULL ){
			strcpy(line,RemoveCRLF(line));
			X = HV->Inicio;
      strcpy(linha, line);
      char *ptr = strtok(line, delim);
      int count = 0;
      while(ptr != NULL)
      {
				if(count == 0){
						isbn=atoi(ptr);
					}
				if(count == 1){
						nrequisicoes=atoi(ptr);
					}
				count++;
				ptr = strtok(NULL, delim);
			}
			while(X){
				E= X->LLivros->Inicio;
				while(E){
					if(E->info->isbn==isbn){
						E->info->nreq=nrequisicoes;
					}
					E=E->Prox;				
				}
				X=X->Prox_Chave;
			}
			
		}
		fclose(f);
	}
}
//ler as requisições das pessoas
void lerrequisicoespessoas(ptLISTA L){
	No X;
	char delim[] = "\t";
	FILE *f;
	int nrequisicoes=0,id=0;
	if ((f = fopen("requisicoespessoa.txt", "r")) == NULL) {
      printf("Error! opening file");
  }
	else{
		char line[128],linha[128];
    while ( fgets ( line, sizeof line, f ) != NULL ){
			strcpy(line,RemoveCRLF(line));
			X=L->inicio;
      strcpy(linha, line);
      char *ptr = strtok(line, delim);
      int count = 0;
      while(ptr != NULL)
      {
				if(count == 0){
						id=atoi(ptr);
					}
				if(count == 1){
						nrequisicoes=atoi(ptr);
					}
				count++;
				ptr = strtok(NULL, delim);
			}
			while(X){
				if(X->inf->id==id){
						X->inf->nrequisicoes=nrequisicoes;
				}
				X=X->seg;
			}
		}
		fclose(f);
	}
}
//ficheiro xml
void inserirxml(ptLISTA L,ptLISTA_req req,Hashing *HV){
	No X = L->inicio;
	NO_HAS *P = HV->Inicio;
	ELEMENTO *E;
	No_req Z = req->inicio;
	FILE *f;
	char name[20];
	printf("\nIntroduza o nome que deseja:");
	scanf(" %[^'\n']s",name);
	strcat(name,".xml");
	f = fopen(name,"w");
	fprintf(f,"<BIBLIOTECA>\n");
	fprintf(f,"\t<REQUISITANTES>\n");
	while (X){
			fprintf(f,"\t\t<REQUISITANTE>\n");
			fprintf(f,"\t\t\t<ID>%d</ID>\n",X->inf->id);
			fprintf(f,"\t\t\t<Nome>%s</Nome>\n",X->inf->nome);
			fprintf(f,"\t\t\t<DATA>%d-%d-%d</DATA>\n",X->inf->data.dia,X->inf->data.mes,X->inf->data.ano);
			fprintf(f,"\t\t\t<NREQUISICOES>%d</NREQUISICOES>\n",X->inf->nrequisicoes);
			fprintf(f,"\t\t\t<LOCALIZACAO>%d</LOCALIZACAO>\n",X->inf->local);
			fprintf(f,"\t\t\t<DISTRITO>%s</DISTRITO>\n",X->inf->cidade);
			fprintf(f,"\t\t\t<CONCELHO>%s</CONCELHO>\n",X->inf->vila);
			fprintf(f,"\t\t\t<FREGUESIA>%s</FREGUESIA>\n",X->inf->freguesia);
			X=X->seg;
			fprintf(f,"\t\t</REQUISITANTE>\n");
	}
	fprintf(f,"\t</REQUISITANTES>\n");
	fprintf(f,"\t<LIVROS>\n");
	while(P){
		E=P->LLivros->Inicio;
		fprintf(f,"\t\t<AREA name='%s'>\n",P->CHAVE);
		while(E){
			fprintf(f,"\t\t\t<LIVRO>\n");
			fprintf(f,"\t\t\t\t<ISBN>%d</ISBN>\n",E->info->isbn);
				fprintf(f,"\t\t\t\t<TITULO>%s</TITULO>\n",E->info->titulo);
			fprintf(f,"\t\t\t\t<ESTADO>%d</ESTADO>\n",E->info->requisitado);
			fprintf(f,"\t\t\t\t<DATALIVRO>%d/%d/%d</DATALIVRO>\n",E->info->data.dia,E->info->data.mes,E->info->data.ano);
			fprintf(f,"\t\t\t\t<NREQUISICOESLIVRO>%d</NREQUISICOESLIVRO>\n",E->info->nreq);
			E=E->Prox;
			fprintf(f,"\t\t\t</LIVRO>\n");
		}
		P=P->Prox_Chave;
		fprintf(f,"\t\t</AREA>\n");
	}
	fprintf(f,"\t</LIVROS>\n");
	fprintf(f,"\t<REQUISICOES>\n");
	while (Z){
		fprintf(f,"\t\t<REQUISICAO>\n");
		fprintf(f,"\t\t\t<IDREQ>%d</IDREQ>\n",Z->inf->pessoa.id);
		fprintf(f,"\t\t\t<NOMEREQ>%s</NOMEREQ>\n",Z->inf->pessoa.nome);
		fprintf(f,"\t\t\t<ISBNREQ>%d</ISBNREQ>\n",Z->inf->livro.isbn);
		fprintf(f,"\t\t\t<TITULOREQ>%s</TITULOREQ>\n",Z->inf->livro.titulo);
		fprintf(f,"\t\t</REQUISICAO>\n");
		Z=Z->seg;
	}
	fprintf(f,"\t</REQUISICOES>\n");
	fprintf(f,"</BIBLIOTECA>\n");
	fclose(f);
}