#include "FilmeHash.h"

#define ARQUIVO_HASH  "filmes.hash"
#define ARQUIVO_DADOS "filmes.dat"
#define TAM_TABELA    101         

int main(void) {

    //Inicializa a tabela zerada
    FH_inicializa(ARQUIVO_HASH, ARQUIVO_DADOS, TAM_TABELA);

    //Carrega o Relationships.txt
    printf("Carregando arquivo...\n");
    int n = FH_carregar_arquivo(ARQUIVO_HASH, ARQUIVO_DADOS,
                                TAM_TABELA, "Relationships.txt", 0);
    printf("Registros inseridos: %d\n\n", n);

    //Demonstração: CalculoDeHash
    printf("=== CalculoDeHash ===\n");
    int h1 = CalculoDeHash("The Matrix", 0, TAM_TABELA);
    int h2 = CalculoDeHash("The Matrix", 0, TAM_TABELA);
    int h3 = CalculoDeHash("A Few Good Men", 0, TAM_TABELA);
    printf("Hash(\"The Matrix\", 0)     = %d\n", h1);
    printf("Hash(\"The Matrix\", 0)     = %d  \n", h2);
    printf("Hash(\"A Few Good Men\", 0) = %d  \n\n", h3);

    //Listar cast completo de alguns filmes
    FH_listar_filme(ARQUIVO_HASH, ARQUIVO_DADOS, TAM_TABELA, "The Matrix", 0);
    putchar('\n');
    FH_listar_filme(ARQUIVO_HASH, ARQUIVO_DADOS, TAM_TABELA, "A Few Good Men", 0);
    putchar('\n');

    //Busca individual
    printf("=== Buscas individuais ===\n");
    TF resultado;
    const char *filmes[] = {"The Matrix", "A Few Good Men", "Top Gun"};
    const char *pessoas[] = {"Keanu Reeves", "Tom Cruise", "Tom Hanks"};
    for (int i = 0; i < 3; i++) {
        int achou = FH_busca_pessoa(ARQUIVO_HASH, ARQUIVO_DADOS, TAM_TABELA,
                                    filmes[i], 0, pessoas[i], &resultado);
        if (achou)
            printf("ENCONTRADO: %-20s em \"%s\"  [%s]  papel: %s\n",
                   pessoas[i], filmes[i], resultado.relacao, resultado.papel);
        else
            printf("NAO ENCONTRADO: %s em \"%s\"\n", pessoas[i], filmes[i]);
    }

    //Busca de alguém que não está no filme
    int achou = FH_busca_pessoa(ARQUIVO_HASH, ARQUIVO_DADOS, TAM_TABELA,
                                "The Matrix", 0, "Tom Hanks", &resultado);
    printf("Tom Hanks em \"The Matrix\": %s\n\n",
           achou ? "ENCONTRADO" : "NAO ENCONTRADO");

    //Remoção
    printf("=== Remoção ===\n");
    int ret = FH_retira_pessoa(ARQUIVO_HASH, ARQUIVO_DADOS, TAM_TABELA,
                               "The Matrix", 0, "Hugo Weaving");
    printf("Retira Hugo Weaving de \"The Matrix\": %s\n", ret ? "OK" : "nao encontrado");

    //Verifica que sumiu da lista
    FH_listar_filme(ARQUIVO_HASH, ARQUIVO_DADOS, TAM_TABELA, "The Matrix", 0);
    putchar('\n');

    //Re-inserção (reaproveitamento de slot inativo)
    printf("=== Re-inserção de Hugo Weaving ===\n");
    FH_insere(ARQUIVO_HASH, ARQUIVO_DADOS, TAM_TABELA,
              "The Matrix", 0,
              "Hugo Weaving", "ACTED_IN", "Agent Smith");
    FH_listar_filme(ARQUIVO_HASH, ARQUIVO_DADOS, TAM_TABELA, "The Matrix", 0);
    putchar('\n');

    //Inserção de um registro novo
    printf("=== Inserção manual de novo registro ===\n");
    FH_insere(ARQUIVO_HASH, ARQUIVO_DADOS, TAM_TABELA,
              "The Matrix", 0,
              "Andy Wachowski", "DIRECTED", "");
    FH_listar_filme(ARQUIVO_HASH, ARQUIVO_DADOS, TAM_TABELA, "The Matrix", 0);

    return 0;
}
