#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estrutura.h"
#define MAX 100

void guardaViagem();
void guardaPessoa();
void guardaPessoasViagem();
void guardaPessoasViagemEspera();
void actualizaFicheiroViagem();

ViagemList cria_listaV(){
    ViagemList aux;
    aux = (ViagemList) malloc(sizeof(Viagem_node));
    if(aux !=NULL){
        aux->next = NULL;
    }
    return aux;
}
List cria_lista(){
    List aux;
    aux = (List) malloc(sizeof(List_node));
    aux->infor.bi = 0;
    if(aux !=NULL){
        aux->next = NULL;
    }
    return aux;
}

int lista_vazia(List lista){
    return(lista->next == NULL ? 1 : 0);

}

int lista_vaziaV(ViagemList lista){
    return(lista->next == NULL ? 1 : 0);

}

List destroi_lista(List lista){
    List aux;
    while(lista_vazia(lista)==0){
        aux = lista;
        lista = lista->next;
        free(aux);
    }
    free(lista);
    return NULL;
}

ViagemList destroi_listaV(ViagemList lista){
    ViagemList aux;
    while(lista_vaziaV(lista)==0){
        aux = lista;
        lista = lista->next;
        free(aux);
    }
    free(lista);
    return NULL;
}

void imprimePessoa(List lista){
    List novo;
    novo = lista->next;
    while(novo!=NULL){
        printf("Nome: %s\nBi: %d\n",novo->infor.nome,novo->infor.bi);
        novo = novo->next;
    }
}

void imprimeViagem(ViagemList listaV){

    ViagemList novo;
    novo = listaV->next;
    while(novo!=NULL){
        printf("Origem: %s\nDestino: %s\nLotacao: %d\nNumero: %d\n%d/%d/%d , %d:%d\n\n",novo->infor.origem,novo->infor.destino,novo->infor.lotacao,novo->infor.nr,novo->infor.data.dia,novo->infor.data.mes,novo->infor.data.ano,novo->infor.data.hora,novo->infor.data.minuto);
        novo = novo->next;
    }
}

void procuraViagem(ViagemList lista,int nr,ViagemList *antV, ViagemList *actV){

    *antV = lista;
    *actV = lista->next;
    while ((*actV) != NULL && (*actV)->infor.nr!= nr)
    {
        *antV = *actV;
        *actV= (*actV)->next;
    }
    if ((*actV) != NULL && (*actV)->infor.nr != nr)
        *actV= NULL;


}

void imprimePessoasViagem(ViagemList listaV){
    ViagemList ant,act;
    List actAux;

    int i,nr;

    printf("Nr da viagem que pretende mostrar: ");
    scanf("%d",&nr);
    procuraViagem(listaV,nr, &ant, &act);
    i = 0;
    if(act!=NULL){
        actAux = act->infor.filaEspera->next;
        printf("Lista de Passageiros:\n");
        while(i<act->infor.lotacao){
            if(act->infor.arrayPessoa[i].bi!=0){
                printf("Nome: %s\nBi: %d\n",act->infor.arrayPessoa[i].nome,act->infor.arrayPessoa[i].bi);
            }
            i++;
        }
        printf("\n\n");
        if(actAux!=NULL && actAux->infor.bi!=0){
            printf("Lista de Espera:\n");
            while(actAux!=NULL){
                printf("Nome: %s\nBi: %d\n",actAux->infor.nome,actAux->infor.bi);
                actAux = actAux->next;
            }

        }
    }else{
        printf("Viagem n encontrada!");
    }


}



void imprimeViagemDestinoContrario (ViagemList listaV,char *destino)
{
    int ret;
    ret = strcmp(destino,listaV->infor.destino);
    if(listaV->next== NULL && ret == 0){
        printf("Origem: %s\nDestino: %s\nLotacao: %d\nNumero: %d\n%d/%d/%d , %d:%d\n\n",listaV->infor.origem,listaV->infor.destino,listaV->infor.lotacao,listaV->infor.nr,listaV->infor.data.dia,listaV->infor.data.mes,listaV->infor.data.ano,listaV->infor.data.hora,listaV->infor.data.minuto);
    }
    else if(listaV->next== NULL && ret !=0){
        return;
    }
    else if(ret==0){
        imprimeViagemDestinoContrario(listaV->next,destino);
        printf("Origem: %s\nDestino: %s\nLotacao: %d\nNumero: %d\n%d/%d/%d , %d:%d\n\n",listaV->infor.origem,listaV->infor.destino,listaV->infor.lotacao,listaV->infor.nr,listaV->infor.data.dia,listaV->infor.data.mes,listaV->infor.data.ano,listaV->infor.data.hora,listaV->infor.data.minuto);
    }
    else{
        imprimeViagemDestinoContrario(listaV->next,destino);
    }
}

void imprime_lista_inverte (ViagemList listaV)
{
    char *destino;
    destino = (char*) malloc (MAX * sizeof(char));
    fflush(stdin);
    printf("Destino das viagens a mostrar: ");
    gets(destino);
    printf("\n");
    imprimeViagemDestinoContrario(listaV->next,destino);
}

void criaPessoa(List lista){
    List aux,aux2;
    char *nome;
    int bi,flag;
    flag = 0;
    aux = (List) malloc(sizeof(List_node));
    nome = (char *) malloc(MAX * sizeof(char));
    aux->infor.nome = (char * ) malloc(MAX * sizeof(char));
    fflush(stdin);
    printf("Insira o seu nome: ");
    gets(nome);
    strcpy(aux->infor.nome,nome);
    fflush(stdin);
    do{
        aux2 = lista->next;
        flag = 0;
        printf("Insira o seu bi: ");
        scanf("%d",&bi);
        fflush(stdin);
        while(aux2!=NULL){
            if(aux2->infor.bi==bi)
                flag = 1;
            aux2 = aux2->next;
        }

    }while(bi<9999999 || bi>99999999 || flag==1);

    aux->infor.bi = bi;
    aux->infor.flag = 0;

    while(lista->next!=NULL){
        lista = lista->next;

    }
    aux->next = NULL;
    lista->next = aux;
    guardaPessoa(aux);
    printf("Pessoa criada com sucesso!");
}

void insereViagemFicheiro(ViagemList listaV,char *origem,char *destino,int lotacao,int nr,int dia,int mes,int ano,int hora,int minuto){
    ViagemList aux,ant,act;
    int j= 0;
    ant = listaV;
    act = listaV->next;
    aux = (ViagemList) malloc(sizeof(Viagem_node));
    aux->infor.filaEspera = cria_lista();
    aux->infor.destino = (char*) malloc(MAX * sizeof(char));
    aux->infor.origem = (char*) malloc(MAX * sizeof(char));
    aux->infor.arrayPessoa = malloc(lotacao * sizeof(Pessoa));
    strcpy(aux->infor.origem,origem);
    strcpy(aux->infor.destino,destino);
    aux->infor.nr = nr;
    aux->infor.lotacao = lotacao;
    aux->infor.data.dia = dia;
    aux->infor.data.mes = mes;
    aux->infor.data.ano = ano;
    aux->infor.data.hora = hora;
    aux->infor.data.minuto = minuto;

    while((act!=NULL) && (((act->infor.data.ano) * 100000000 +  (act->infor.data.mes) * 1000000 + (act->infor.data.dia)*10000 + (act->infor.data.hora) * 100 + (act->infor.data.minuto)) <((aux->infor.data.ano) * 100000000 + (aux->infor.data.mes) * 1000000 + (aux->infor.data.dia)*10000 + (aux->infor.data.hora) * 100 + (aux->infor.data.minuto)))){

            ant = ant->next;
            act = act->next;
    }
    ant->next = aux;
    aux->next = act;

    for(j=0;j<lotacao;j++){
        aux->infor.arrayPessoa[j].bi = 0;
        aux->infor.arrayPessoa[j].nome = "EMPTY";
        aux->infor.arrayPessoa[j].flag = 0;
    }




}

void insereCliente(List lista,char *nome,int bi){
    List aux;
    aux = (List) malloc(sizeof(List_node));
    aux->infor.nome = (char*) malloc(MAX * sizeof(char));
    aux->infor.bi = bi;
    strcpy(aux->infor.nome,nome);
    while(lista->next!=NULL){
        lista = lista->next;
    }
    aux->next = NULL;
    lista->next = aux;

}

void criaViagem(ViagemList listaV){
    ViagemList aux,novo;
    ViagemList act,ant;
    int i,j;
    char *origem;
    char *destino;
    int lotacao,dia,mes,ano,hora,minuto;
    i = 0;
    ant = listaV;
    act = listaV->next;
    novo = listaV;
    aux = (ViagemList) malloc(sizeof(Viagem_node));
    origem = (char *) malloc(MAX * sizeof(char));
    destino = (char *) malloc(MAX * sizeof(char));
    aux->infor.origem = (char *) malloc(MAX * sizeof(char));
    aux->infor.destino = (char *) malloc(MAX * sizeof(char));
    aux->infor.filaEspera = cria_lista();
    fflush(stdin);
    printf("Origem da Viagem:");
    gets(origem);
    strcpy(aux->infor.origem,origem);
    fflush(stdin);
    printf("Destino da viagem:");
    gets(destino);
    strcpy(aux->infor.destino,destino);
    fflush(stdin);
    printf("Lotacao: ");
    while(scanf("%d",&lotacao)==0){
        printf("Erro! Insira um numero valido!\n");
        fflush(stdin);
        printf("Lotacao: ");
        fflush(stdin);
    }
    aux->infor.lotacao = lotacao;
    aux->infor.arrayPessoa = malloc(lotacao * sizeof(Pessoa));
    fflush(stdin);
    do{
    printf("Insira a data(DIA/MES/ANO): ");
    scanf("%d %d %d",&dia,&mes,&ano);
    printf("Insira as horas da viagem(HORA:MINUTO):");
    scanf("%d:%d",&hora,&minuto);
    }while(dia<0 || dia>31 || mes<0 || mes>12 || ano<0 || hora<0 || hora>24 || minuto<0 || minuto>59 );

    aux->infor.data.dia = dia;
    aux->infor.data.mes = mes;
    aux->infor.data.ano = ano;
    aux->infor.data.hora = hora;
    aux->infor.data.minuto = minuto;

    while((act!=NULL) && (((act->infor.data.ano) * 100000000 +  (act->infor.data.mes) * 1000000 + (act->infor.data.dia)*10000 + (act->infor.data.hora) * 100 + (act->infor.data.minuto)) <((aux->infor.data.ano) * 100000000 + (aux->infor.data.mes) * 1000000 + (aux->infor.data.dia)*10000 + (aux->infor.data.hora) * 100 + (aux->infor.data.minuto)))){

            ant = ant->next;
            act = act->next;
    }
    ant->next = aux;
    aux->next = act;

    for(j=0;j<lotacao;j++){
        aux->infor.arrayPessoa[j].nome = "EMPTY";
        aux->infor.arrayPessoa[j].bi = 0;
        aux->infor.arrayPessoa[j].flag = 0;
    }
    while(novo!= NULL){
        novo->infor.nr = i;
        novo = novo->next;
        i++;

    }
    guardaViagem(aux);
    printf("Viagem criada com sucesso!\n");


}

void procuraPessoa(List lista, int chaveBi, List *ant, List *act){
    *ant = lista;
    *act = lista->next;
    while ((*act) != NULL && (*act)->infor.bi!= chaveBi)
    {
        *ant = *act;
        *act= (*act)->next;
    }
    if ((*act) != NULL && (*act)->infor.bi != chaveBi)
        *act= NULL;

}

void adicionaPessoaViagem(List lista, ViagemList listaV, int chaveBi, int nr){
    List ant,act,novo,aux;
    ViagemList antV,actV;
    int i;
    novo = (List) malloc(sizeof(List_node));
    i = 0;
    procuraPessoa(lista,chaveBi,&ant,&act);
    procuraViagem(listaV,nr,&antV,&actV);
    if(actV!=NULL && act != NULL){
            act->infor.flag = 1;
            aux = actV->infor.filaEspera;
            while(i!=actV->infor.lotacao && actV->infor.arrayPessoa[i].bi!=0){
                i++;
            }
            if(i == actV->infor.lotacao){
                novo->infor.nome = act->infor.nome;
                novo->infor.bi = act->infor.bi;
                novo->next = NULL;
                while(aux->next!=NULL){
                   aux = aux->next;
                }
                aux->next = novo;
                guardaPessoasViagemEspera(novo,actV);
                printf("Adicionado a fila de espera!\n");

            }else{
                actV->infor.arrayPessoa[i].bi = chaveBi;
                actV->infor.arrayPessoa[i].nome = act->infor.nome;
                guardaPessoasViagem(actV,chaveBi);
                printf("Adicionado a viagem!\n");
            }
    }else{
        printf("Pessoa ou viagem nao encontrada!\n");
    }


}

void adicionaViagem(List lista, ViagemList listaV, int chaveBi, int nr){
    ViagemList antV,actV;
    List ant,act;
    int i;
    i=0;
    procuraViagem(listaV,nr,&antV,&actV);
    procuraPessoa(lista,chaveBi,&ant,&act);
    act->infor.flag = 1;
    while(i!=actV->infor.lotacao && actV->infor.arrayPessoa[i].bi!=0){
        i++;
    }
    if(i !=(actV->infor.lotacao)){
        actV->infor.arrayPessoa[i].bi = chaveBi;
        actV->infor.arrayPessoa[i].nome = act->infor.nome;
    }
}

void adicionaListaEspera(List lista,ViagemList listaV,int chaveBi,int nr){
    List novo,aux,ant,act;
    ViagemList antV,actV;
    procuraPessoa(lista,chaveBi,&ant,&act);
    procuraViagem(listaV,nr,&antV,&actV);
    if(actV!=NULL && act != NULL){
        act->infor.flag =1;
        aux = actV->infor.filaEspera;
        novo = (List) malloc(sizeof(List_node));
        novo->infor.nome = act->infor.nome;
        novo->infor.bi = act->infor.bi;
        novo->next = NULL;
        while(aux->next!=NULL){
            aux = aux->next;
        }
        aux->next = novo;
        printf("Adicionado a fila de espera!\n");

    }
    else{
        printf("Nao encontrado!");
    }

}
void insereListaEspera(List lista,ViagemList listaV){
    int bi, nr;
    printf("Nr de bi a adicionar a viagem:");
    scanf("%d",&bi);
    fflush(stdin);
    printf("Nr da viagem: ");
    scanf("%d",&nr);
    fflush(stdin);
    adicionaListaEspera(lista,listaV,bi,nr);


}

void insereViagem(List lista, ViagemList listaV){
    int bi, nr;
    printf("Nr de bi a adicionar a viagem:");
    scanf("%d",&bi);
    fflush(stdin);
    printf("Nr da viagem: ");
    scanf("%d",&nr);
    fflush(stdin);
    adicionaPessoaViagem(lista,listaV,bi,nr);


}

void eliminaNoListaEspera(ViagemList listaV,int chaveBi, int nr){
    ViagemList antV,actV;
    List auxAct,antAct;
    procuraViagem(listaV,nr,&antV,&actV);
    if(actV!=NULL){
        auxAct = actV->infor.filaEspera->next;
        antAct = actV->infor.filaEspera;
        while(auxAct!=NULL && auxAct->infor.bi != chaveBi){
            auxAct = auxAct->next;
            antAct = antAct->next;
        }
        if(auxAct!=NULL){
            antAct->next = auxAct->next;
            actualizaFicheiroViagem(actV,chaveBi,nr);
            free(auxAct);
        }else{
            printf("Bi inexistente!\n");
        }
    }else{
        printf("Viagem n encontrada");
    }





}

void imprimeClientesAdquiridos(List lista){
    List aux;
    aux = lista->next;
    printf("Clientes com viagens adquiridas ou em lista de espera:\n");
    while(aux!=NULL){
        if(aux->infor.flag==1){
            printf("Nome:%s\nBi:%d\n",aux->infor.nome,aux->infor.bi);
        }
        aux = aux->next;
    }
}
void imprimeViagemCliente(ViagemList listaV){
    ViagemList aux;
    int bi,i, flag;
    aux = listaV->next;
    i=0;
    flag = 0;
    printf("Nr do bi: ");
    scanf("%d",&bi);
    while(aux!=NULL){
        for(i=0;i<aux->infor.lotacao;i++){
            if(aux->infor.arrayPessoa[i].bi == bi){
                printf("Viagem adquirida: %s ----> %s\n",aux->infor.origem,aux->infor.destino);
                flag = 1;
            }
        }
        aux = aux->next;

    }
    if(flag==0){
        printf("O cliente nao adquiriu nenhumas viagens");
    }

}

void eliminaListaEspera(ViagemList listaV){
    int nr,bi;
    printf("Nr do bi a eliminar da lista de espera:");
    scanf("%d",&bi);
    printf("Nr da viagem: ");
    scanf("%d",&nr);
    eliminaNoListaEspera(listaV,bi,nr);
}

void eliminaPessoaViagem(ViagemList listaV, int chaveBi, int nr){
    ViagemList antV,actV;
    int i,j,lot,h,flag;
    procuraViagem(listaV,nr,&antV,&actV);
    h=0;
    flag = 0;
    if(actV!=NULL){
        lot = actV->infor.lotacao;
        for(i=0;i<lot;i++){
            if(actV->infor.arrayPessoa[i].bi == chaveBi){
                j = i;
                flag = 1;
                while(j<lot){
                    actV->infor.arrayPessoa[j].nome = actV->infor.arrayPessoa[j+1].nome;
                    actV->infor.arrayPessoa[j].bi = actV->infor.arrayPessoa[j+1].bi;
                    j++;
                }

                if(actV->infor.filaEspera->next!=NULL){
                    printf("\nExiste alguem a espera! A inserir...\n");
                    actV->infor.arrayPessoa[lot-1].nome = "EMPTY";
                    actV->infor.arrayPessoa[lot-1].bi = 0;
                    while(actV->infor.arrayPessoa[h].bi!=0){
                        h++;
                    }
                    actV->infor.arrayPessoa[h].bi = actV->infor.filaEspera->next->infor.bi;
                    actV->infor.arrayPessoa[h].nome = actV->infor.filaEspera->next->infor.nome;
                    eliminaNoListaEspera(listaV,actV->infor.filaEspera->next->infor.bi,nr);

                }
                else{
                    printf("\nNao existe Ninguem na fila de espera!\n");
                    actV->infor.arrayPessoa[lot-1].nome = "EMPTY";
                    actV->infor.arrayPessoa[lot-1].bi = 0;
                    actualizaFicheiroViagem(actV,chaveBi,nr);


                }

            }


        }
        if(flag ==0){
                printf("Bi invalido");
        }
    }
    else{
        printf("Viagem nao existente!");
    }
}

void eliminaViagem(ViagemList listaV){
    int bi, nr;
    printf("Nr de bi a eliminar da Viagem:");
    scanf("%d",&bi);
    fflush(stdin);
    printf("Nr da viagem: ");
    scanf("%d",&nr);
    fflush(stdin);
    eliminaPessoaViagem(listaV,bi,nr);
}
