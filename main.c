#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include "estrutura.h"
#define MAX 100

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
void insereCliente();
void LeFicheiroClientes();
void LeFicheiroViagem();
void LeFicheiroViagem();
void LeFicheiroClientesViagem();
void menu();

int main()
{

    List ListaPessoas;
    ViagemList ListaViagens;
    ListaPessoas = cria_lista();
    ListaViagens = cria_listaV();
    LeFicheiroClientes(ListaPessoas);
    LeFicheiroViagem(ListaViagens);
    LeFicheiroClientesViagem(ListaPessoas,ListaViagens);
    menu(ListaPessoas,ListaViagens);
    ListaPessoas = destroi_lista(ListaPessoas);
    ListaViagens = destroi_listaV(ListaViagens);
    return 0;
}
