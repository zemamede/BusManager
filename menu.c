#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include "estrutura.h"

List cria_lista();
ViagemList cria_listaV();
void criaPessoa();
void criaViagem();
int lista_vazia();
int lista_vaziaV();
List destroi_lista();
ViagemList destroi_listaV();
void imprimeClientesAdquiridos();
void imprimePessoa();
void imprimePessoasViagem();
void imprimeViagem();
void imprimeViagemCliente();
void imprimeViagemDestinoContrario();
void imprime_lista_inverte();
void procuraPessoa();
void procuraViagem();
void adicionaListaEspera();
void adicionaPessoaViagem();
void insereViagem();
void insereListaEspera();
void eliminaListaEspera();
void eliminaNoListaEspera();
void eliminaPessoaViagem();
void eliminaViagem();
void guardaPessoa();
void guardaViagem();
void menuListagem();
void insereCliente();



void menu(List lista, ViagemList listaV){
    int input;

    system("cls");
    do
    {
        printf("\n\n\n\n");
        printf( "\t1. INSERIR DADOS DE CLIENTE\n" );
        printf( "\t2. CRIAR VIAGEM\n");
        printf( "\t3. ADQUIRIR UMA VIAGEM\n" );
        printf( "\t4. CANCELAR UMA VIAGEM\n" );
        printf( "\t5. COLOCAR EM FILA DE ESPERA PARA UMA VIAGEM\n" );
        printf( "\t6. ELIMINAR CLIENTE DE UMA FILA DE ESPERA\n" );
        printf( "\t7. FUNCOES DE LISTAMENTO\n" );
        printf( "\t0. SAIR\n");
        printf( "\n\tOPCAO: " );
        fflush(stdin);
        input=0;
        scanf( "%d",&input);

        switch(input)
        {
        case 1:
            fflush(stdin);
            criaPessoa(lista);
            Sleep(1000);
            system("cls");
            break;
        case 2:
            fflush(stdin);
            criaViagem(listaV);
            Sleep(1000);
            system("cls");
            break;
        case 3:
            fflush(stdin);
            imprimeViagem(listaV);
            insereViagem(lista,listaV);
            Sleep(1000);
            system("cls");
            break;
        case 4:
            fflush(stdin);
            imprimeViagem(listaV);
            eliminaViagem(listaV);
            Sleep(1000);
            system("cls");
            break;
        case 5:
            fflush(stdin);
            imprimeViagem(listaV);
            insereListaEspera(lista,listaV);
            Sleep(1000);
            system("cls");
            break;
        case 6:
            fflush(stdin);
            eliminaListaEspera(listaV);
            Sleep(1000);
            system("cls");
            break;
        case 7:
            fflush(stdin);
            menuListagem(lista,listaV);
            system("cls");
            break;
        case 0:
            return;
        default:
            fflush(stdin);
            system("cls");
            break;
        }
    }
    while(input!=0);
}


void menuListagem(List lista, ViagemList listaV){
    int input;
    system("cls");
    do
    {
        printf("\n\n\n\n");
        printf( "\t1. LISTAR TODAS AS VIAGENS PARA UM DETERMINADO DESTINO\n");
        printf( "\t2. LISTAR TODAS AS VIAGENS ADQUIRIDAS DE UM CLIENTE\n" );
        printf( "\t3. LISTAR TODOS CLIENTES COM VIAGENS ADQUIRIDAS OU EM ESPERA\n");
        printf( "\t4. LISTAR CLIENTES BASE DE DADOS\n");
        printf( "\t5. LISTAR VIAGENS\n");
        printf( "\t6. LISTAR CLIENTES NUMA VIAGEM\n");
        printf( "\t0. MENU INICIAL\n");
        printf( "\n\tOPCAO: " );
        fflush(stdin);
        input=0;
        scanf( "%d",&input);

        switch(input)
        {
        case 1:
            fflush(stdin);
            printf("\n");
            imprime_lista_inverte(listaV);
            Sleep(3000);
            system("cls");
            break;
        case 2:
            fflush(stdin);
            printf("\n");
            imprimeViagemCliente(listaV);
            Sleep(3000);
            system("cls");
            break;
        case 3:
            fflush(stdin);
            printf("\n");
            imprimeClientesAdquiridos(lista);
            Sleep(3000);
            system("cls");
            break;
        case 4:
            fflush(stdin);
            printf("\n");
            imprimePessoa(lista);
            Sleep(3000);
            system("cls");
            break;
        case 5:
            fflush(stdin);
            printf("\n");
            imprimeViagem(listaV);
            Sleep(3000);
            system("cls");
            break;
        case 6:
            fflush(stdin);
            printf("\n");
            imprimePessoasViagem(listaV);
            Sleep(3000);
            system("cls");
            break;
        case 0:
            return;
        default:
            fflush(stdin);
            system("cls");
            break;
        }
    }
    while(input!=0);
}




