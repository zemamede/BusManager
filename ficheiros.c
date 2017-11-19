#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include "estrutura.h"
#define MAX 100

void insereCliente();
void insereViagemFicheiro();
void adicionaListaEspera();
void adicionaPessoaViagem();
void procuraViagem();
void adicionaViagem();
void cria_lista();

void guardaPessoa(List lista)
{
    FILE *fp;
    fp = fopen("clientes.txt", "a");
    fprintf(fp,"CLIENTE\n%s\n%d\n",lista->infor.nome,lista->infor.bi);
    fclose(fp);
}

void guardaViagem(ViagemList listaV){
    FILE *fp;
    fp = fopen("viagem.txt", "a");
    fprintf(fp,"VIAGEM\n%s\n%s\n%d\n%d\n%d/%d/%d\n%d:%d\n",listaV->infor.destino,listaV->infor.origem,listaV->infor.lotacao,listaV->infor.nr,listaV->infor.data.dia,listaV->infor.data.mes,listaV->infor.data.ano,listaV->infor.data.hora,listaV->infor.data.minuto);
    fclose(fp);
}

void guardaPessoasViagemEspera(List lista,ViagemList listaV){
    FILE *fp;
    fp = fopen("clientesviagem.txt","a");
    fprintf(fp,"%s\n%d-%d\n","ESPERA",listaV->infor.nr,lista->infor.bi);
    fclose(fp);
}

void guardaPessoasViagem(ViagemList listaV,int chaveBi){
    FILE *fp;
    fp = fopen("clientesviagem.txt","a");
    fprintf(fp,"%s\n%d-%d\n","VIAGEM",listaV->infor.nr,chaveBi);
    fclose(fp);
}

void LeFicheiroClientesViagem(List lista, ViagemList listaV){
    FILE *fp;
    int nr,bi;
    char line[MAX];
    fp = fopen("clientesviagem.txt","r");
    while(fgets(line,MAX,fp)!=NULL){
        fscanf(fp,"%d-%d\n",&nr,&bi);
        if(line[strlen(line)-1]=='\n'){
                line[strlen(line)-1] = '\0';
        }
        if(strcmp(line,"VIAGEM")==0){
            adicionaViagem(lista,listaV,bi,nr);
        }
        else if(strcmp(line,"ESPERA")==0){
            adicionaListaEspera(lista,listaV,bi,nr);
        }
    }
    fclose(fp);
}

void LeFicheiroClientes(List lista){
    FILE *fp;
    int bi;
    char *nome;
    char line[MAX];
    nome = (char*) malloc(MAX*sizeof(char));
    fp = fopen("clientes.txt","r");
    while(fgets(line,MAX,fp)!=NULL){
        fgets(nome,MAX,fp);
        fscanf(fp,"%d\n",&bi);
        if(nome[strlen(nome)-1]=='\n'){
                nome[strlen(nome)-1] = '\0';
        }
        insereCliente(lista,nome,bi);
    }
    fclose(fp);
}

void LeFicheiroViagem(ViagemList listaV){
    FILE *fp;
    char *origem;
    char *destino;
    int nr,lotacao,dia,mes,ano,hora,minuto;
    char line[MAX];
    origem = (char*) malloc(MAX*sizeof(char));
    destino =  (char*) malloc(MAX*sizeof(char));
    fp = fopen("viagem.txt","r");
    while(fgets(line,MAX,fp)!=NULL){
        fgets(origem,MAX,fp);
        fgets(destino,MAX,fp);
        fscanf(fp,"%d\n",&lotacao);
        fscanf(fp,"%d\n",&nr);
        fscanf(fp,"%d/%d/%d\n",&dia,&mes,&ano);
        fscanf(fp,"%d:%d\n",&hora,&minuto);
        if(origem[strlen(origem)-1]=='\n'){
                origem[strlen(origem)-1] = '\0';
        }
        if(destino[strlen(destino)-1]=='\n'){
                destino[strlen(destino)-1] = '\0';
        }
        insereViagemFicheiro(listaV,origem,destino,lotacao,nr,dia,mes,ano,hora,minuto);
    }
    fclose(fp);
}

void actualizaFicheiroViagem(ViagemList listaV,int biElim,int nrElim){
    FILE *fp,*fp2;
    int bi,nr,i;
    char line[MAX];
    fp = fopen("clientesviagem.txt","r");
    fp2 = fopen("clientesviagem2.txt","w");
    i=0;
    while(fgets(line,MAX,fp)!=NULL){
        fscanf(fp,"%d-%d\n",&nr,&bi);
        if(nr!= nrElim || bi != biElim){
            if(strcmp(line,"VIAGEM\n")==0 && nr == nrElim && listaV->infor.arrayPessoa[1].bi==0 && listaV->infor.filaEspera->next!=NULL){
                fprintf(fp2,"%s\n%d-%d\n","VIAGEM",nr,listaV->infor.arrayPessoa->bi);
            }
            else if(strcmp(line,"VIAGEM\n")==0 && nr == nrElim){
                fprintf(fp2,"%s\n%d-%d\n","VIAGEM",nr,listaV->infor.arrayPessoa[i].bi);
                i++;
            }
            else if(strcmp(line,"VIAGEM\n")==0 && nr != nrElim){
                fprintf(fp2,"%s\n%d-%d\n","VIAGEM",nr,bi);
            }
            else if(strcmp(line,"ESPERA\n")==0){
                fprintf(fp2,"%s\n%d-%d\n","ESPERA",nr,bi);
            }
        }


    }
    fclose(fp);
    fclose(fp2);
    remove("clientesviagem.txt");
    rename("clientesviagem2.txt","clientesviagem.txt");

}
