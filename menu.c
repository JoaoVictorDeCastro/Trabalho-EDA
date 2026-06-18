#include "FilmeHash.h"

#define ARQUIVO_HASH  "filmes.hash"
#define ARQUIVO_DADOS "filmes.dat"
#define TAM_TABELA    101

//Descarta tudo que sobrou no stdin até o próximo
static void _limpa_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

//Esta função remove o '\n'
static void _remove_quebra_linha(char *s) {
    int len = strlen(s);
    while (len > 0 && (s[len-1] == '\n' || s[len-1] == '\r')) {
        s[len-1] = '\0';
        len--;
    }
}

static void solicitarNomeFilme(char *out) {
    printf("Digite o nome do filme: ");
    fgets(out, FH_NOME_MAX, stdin);
    _remove_quebra_linha(out);
}

static int solicitarAnoFilme(void) {
    int ano;
    printf("Digite o ano de lançamento do filme: ");
    scanf("%d", &ano);
    _limpa_buffer();
    return ano;
}

static void solicitarNomePessoa(char *out) {
    printf("Digite o nome da pessoa: ");
    fgets(out, FH_NOME_MAX, stdin);
    _remove_quebra_linha(out);
}

static void solicitarFuncaoEPapel(char *funcao, char *papel) {
    int tempOp;
    printf("Selecione a função:\n");
    printf("1 - ACTED_IN\n");
    printf("2 - DIRECTED\n");
    printf("3 - PRODUCED\n");
    printf("4 - WROTE\n");
    printf("Opcao: ");
    scanf("%d", &tempOp);
    _limpa_buffer();

    papel[0] = '\0';   // papel vazio por padrão 

    switch (tempOp) {
        case 1:
            strcpy(funcao, "ACTED_IN");
            printf("Digite o nome do personagem: ");
            fgets(papel, FH_ROLE_MAX, stdin);
            _remove_quebra_linha(papel);
            break;
        case 2:
            strcpy(funcao, "DIRECTED");
            break;
        case 3:
            strcpy(funcao, "PRODUCED");
            break;
        case 4:
            strcpy(funcao, "WROTE");
            break;
        default:
            funcao[0] = '\0';
            printf("Opcao invalida\n");
            break;
    }
}

void hash(void) {
    int opcao;

    printf("O que deseja fazer?\n");
    while (1) {
        printf("=================================\n");
        printf("1 - Iniciar hash de Relações\n");
        printf("2 - Cálculo de Hash\n");
        printf("3 - Inserir relação\n");
        printf("4 - Remover relação\n");
        printf("5 - Listar cast de um filme\n");
        printf("6 - Busca Individual\n");
        printf("-1 - Sair das opções de Hash\n");
        printf("Opcao: ");

        if (scanf("%d", &opcao) != 1) {
            _limpa_buffer();
            continue;
        }
        _limpa_buffer();

        if (opcao == -1)
            break;
        
        char nomeFilme[FH_NOME_MAX];
        char nomePessoa[FH_NOME_MAX];
        char funcao[FH_REL_MAX];
        char papel[FH_ROLE_MAX];
        int ano;
        TF resultado;
        int h1, ret, achou, n;

        switch (opcao) {
            case 1:
                //Inicializa a tabela zerada
                FH_inicializa(ARQUIVO_HASH, ARQUIVO_DADOS, TAM_TABELA);

                //Carrega o Relationships.txt
                printf("Carregando arquivo...\n");
                n = FH_carregar_arquivo(ARQUIVO_HASH, ARQUIVO_DADOS,
                                        TAM_TABELA, "Relationships.txt", 0);
                printf("Registros inseridos: %d\n\n", n);
                break;

            case 2:
                printf("=== CalculoDeHash ===\n");
                solicitarNomeFilme(nomeFilme);
                ano = solicitarAnoFilme();

                h1 = CalculoDeHash(nomeFilme, ano, TAM_TABELA);
                printf("Hash(\"%s\", %d) = %d\n", nomeFilme, ano, h1);
                break;

            case 3:
                printf("=== Inserção de novo registro ===\n");
                solicitarNomeFilme(nomeFilme);
                ano = solicitarAnoFilme();
                solicitarNomePessoa(nomePessoa);
                solicitarFuncaoEPapel(funcao, papel);

                FH_insere(ARQUIVO_HASH, ARQUIVO_DADOS, TAM_TABELA,
                         nomeFilme, ano, nomePessoa, funcao, papel);
                FH_listar_filme(ARQUIVO_HASH, ARQUIVO_DADOS, TAM_TABELA,
                               nomeFilme, ano);
                break;

            case 4:
                printf("=== Remoção ===\n");
                solicitarNomeFilme(nomeFilme);
                ano = solicitarAnoFilme();
                solicitarNomePessoa(nomePessoa);

                ret = FH_retira_pessoa(ARQUIVO_HASH, ARQUIVO_DADOS, TAM_TABELA,
                                       nomeFilme, ano, nomePessoa);
                printf("Retira %s de \"%s\": %s\n",
                       nomePessoa, nomeFilme, ret ? "OK" : "nao encontrado");

                //Verifica que sumiu da lista
                FH_listar_filme(ARQUIVO_HASH, ARQUIVO_DADOS, TAM_TABELA,
                               nomeFilme, ano);
                putchar('\n');
                break;

            case 5:
                solicitarNomeFilme(nomeFilme);
                ano = solicitarAnoFilme();
                FH_listar_filme(ARQUIVO_HASH, ARQUIVO_DADOS, TAM_TABELA,
                               nomeFilme, ano);
                putchar('\n');
                break;

            case 6:
                printf("=== Buscas individuais ===\n");
                solicitarNomeFilme(nomeFilme);
                ano = solicitarAnoFilme();
                solicitarNomePessoa(nomePessoa);

                achou = FH_busca_pessoa(ARQUIVO_HASH, ARQUIVO_DADOS, TAM_TABELA,
                                        nomeFilme, ano, nomePessoa, &resultado);
                if (achou)
                    printf("ENCONTRADO: %-20s em \"%s\"  [%s]  papel: %s\n",
                           nomePessoa, nomeFilme, resultado.relacao, resultado.papel);
                else
                    printf("NAO ENCONTRADO: %s em \"%s\"\n", nomePessoa, nomeFilme);
                break;

            default:
                printf("Opcao invalida!\n");
        }
    }
}

int main(void) {
    hash();
    return 0;
}