#include "hashing.h"
#include "lista.h"
#include "funcoes.h"
void lerlivro(ptFAIXA L,Hashing *HV);
void lerreq(ptLISTA_req L, Hashing *HV);
void lerficheiro(ptLISTA L,ptLOCALIZACAO lista);
void inserenoficheiro(ptLISTA_req L);
//
void inserirNrequsicoeslivro(Hashing *HV);
void inserirNrequsicoespessoa(ptLISTA L);
void lerrequisicoeslivros(Hashing *HV);
void lerrequisicoespessoas(ptLISTA L);
void lerlocais(ptLOCALIZACAO l);
void inserirxml(ptLISTA L,ptLISTA_req req,Hashing *HV);