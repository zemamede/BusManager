#ifndef _estrutura_h
#define _estrutura_h

typedef struct vnode *ViagemList;
typedef struct lnode *List;
typedef struct{
    int dia;
    int mes;
    int ano;
    int hora;
    int minuto;
}Data;

typedef struct {
    char *nome;
    int bi;
    int flag;
}Pessoa;

typedef struct{
    char *destino;
    char *origem;
    int lotacao;
    int nr;
    Data data;
    List filaEspera;
    Pessoa *arrayPessoa;
}Viagem;

typedef struct vnode{
    Viagem infor;
    ViagemList next;
}Viagem_node;

typedef struct lnode{
    Pessoa infor;
    List next;
}List_node;

#endif
