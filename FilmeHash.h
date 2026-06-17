#ifndef FILMEHASH_H
#define FILMEHASH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FH_NOME_MAX  128   //tamanho máximo do nome dos atores
#define FH_ROLE_MAX  128    //tamanho máximo do nome dos personagens
#define FH_REL_MAX    32   //ACTED_IN, DIRECTED

//registro gravado no arquivo de dados
typedef struct tfregistro {
    char   pessoa[FH_NOME_MAX]; 
    char   relacao[FH_REL_MAX]; 
    char   papel[FH_ROLE_MAX];  
    int    prox;                
    int    status;  //1=ativo, 0=removido
} TF;

//calcula o índice da hash de um filme
int CalculoDeHash(const char *titulo, int ano, int m);

//inicializa os arquivos de índice e dados
void FH_inicializa(const char *tabHash, const char *dados, int m);

//insere uma relação entre filme e pessoa na hash
void FH_insere(const char *tabHash, const char *dados, int m,
               const char *titulo, int ano,
               const char *pessoa, const char *relacao,
               const char *papel);

//busca uma pessoa em um filme
int FH_busca_pessoa(const char *tabHash, const char *dados, int m,
                    const char *titulo, int ano,
                    const char *pessoa, TF *out);

//remove uma pessoa de um filme 
int FH_retira_pessoa(const char *tabHash, const char *dados, int m,
                     const char *titulo, int ano,
                     const char *pessoa);

//imprime todas as pessoas que participaram de um filme
void FH_listar_filme(const char *tabHash, const char *dados, int m,
                     const char *titulo, int ano);

//lê um arquivo e insere na hash 
int FH_carregar_arquivo(const char *tabHash, const char *dados, int m,
                        const char *relFile, int ano_padrao);

//imprime a tabela inteira
void FH_imprime_tudo(const char *tabHash, const char *dados, int m);

#endif
