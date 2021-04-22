#include "hashing.h"


extern ptFAIXA Criar_faixa();
extern void Inserir_Lista(Faixa *L, Livro *V);
extern void Destruir_Faixa(ptFAIXA L);
extern void Mostrar_Lista(Faixa *L);

Hashing *CriarHashing_PRO()
{
    Hashing *H = (Hashing *)malloc(sizeof(Hashing));
    if (!H) return NULL;
    H->Inicio = NULL;
    H->NUM_CHAVES = 0;
    return H;
}

NO_HAS *FuncaoHashing_Vector_Cidade(Hashing *H, const char *area)
{
    if (!H) return NULL;
    NO_HAS *P = H->Inicio;
    while (P)
    {
        if (strcmp(P->CHAVE, area) == 0)
            return P;
        P = P->Prox_Chave;
    }
    return NULL;
}

NO_HAS *FuncaoHashing_Vector(Hashing *H, Livro *V)
{
    /*
    if (!H) return NULL;
    NO_HAS *P = H->Inicio;
    while (P)
    {
        if (strcmp(P->CHAVE, V->CIDADE) == 0)
            return P;
        P = P->Prox_Chave;
    }
    return NULL;
    */
    return FuncaoHashing_Vector_Cidade(H, V->area);
}

void Add_Hashing_PRO(Hashing *H, Livro *X)
{
    if (!H) return;
    NO_HAS *P = FuncaoHashing_Vector(H, X);
    if (P == NULL)
    {
        P = (NO_HAS *)malloc(sizeof(NO_HAS));
        strcpy(P->CHAVE, X->area);
        P->LLivros = Criar_faixa();
        P->Prox_Chave = H->Inicio;
        H->Inicio = P;
        H->NUM_CHAVES++;
    }
    Inserir_Lista(P->LLivros, X);
}

void Mostrar_Hashing_PRO(Hashing *H)
{
    if (!H) return;
    NO_HAS *P = H->Inicio;
    printf("NUMERO-Areas = %d\n", H->NUM_CHAVES);
    while (P)
    {
        printf("\n[%s]\n", P->CHAVE);
        Mostrar_Lista(P->LLivros);
        P = P->Prox_Chave;
    }
}

void Mostrar_livros_requisitados(Hashing *H)
{
    if (!H) return;
    NO_HAS *P = H->Inicio;
    printf("NUMERO-Areas = %d\n", H->NUM_CHAVES);
    while (P)
    {
        printf(" [%s]\n", P->CHAVE);
        Mostrar_Lista_requisitados(P->LLivros);
        P = P->Prox_Chave;
    }
}

void Destruir_Hashing_PRO(Hashing *H)
{
    if (!H) return;
    NO_HAS *Aux = NULL;
    NO_HAS *P = H->Inicio;
    while (P)
    {
        Aux = P->Prox_Chave;
        Destruir_Faixa(P->LLivros);
        free(P);
        P = Aux;
    }
    free(H);
}
//-----------------------------
int ContarVirusCidade(Hashing *H, const char *nome_cid)
{
    if (!H) return 0;
    NO_HAS *P = FuncaoHashing_Vector_Cidade(H, nome_cid);
    if (!P) return 0;
    return P->LLivros->NEL;
}