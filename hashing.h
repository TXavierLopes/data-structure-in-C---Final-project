#ifndef HASHING_H_INCLUDED
#define HASHING_H_INCLUDED
#include "lista.h"


typedef struct no_has
{
    char CHAVE[20];
    struct no_has *Prox_Chave;
    Faixa *LLivros;
}NO_HAS;

typedef struct
{
    NO_HAS *Inicio;
    int NUM_CHAVES;
}Hashing;

Hashing *CriarHashing_PRO();
void Add_Hashing_PRO(Hashing *H, Livro *X);
void Mostrar_Hashing_PRO(Hashing *H);
void Destruir_Hashing_PRO(Hashing *H);
int ContarVirusCidade(Hashing *H, const char *nome_cid);
void Mostrar_livros_requisitados(Hashing *H);
#endif // HASHING_H_INCLUDED
