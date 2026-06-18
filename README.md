# Trabalho-EDA

Trabalho de Estruturas de Dados e Algoritmos

Autores: João Victor de Castro, Pedro Kinupp, Felipe Mehiel

**Visão geral**
- **Objetivo:** Implementar uma árvore B+ em arquivo (TARVBM_bin) e uma tabela hash para relacionamentos de filmes (FilmeHash). O projeto fornece uma interface interativa (`Main.c`) para criar/abrir a árvore e inserir/remover/imprimir registros, além de utilitários para inspecionar folhas e manipular a tabela hash.

**Arquivos principais**
- **Código da árvore B+:** [TARVBM_bin.c](TARVBM_bin.c) / [TARVBM_bin.h](TARVBM_bin.h)
- **Tabela hash de filmes:** [FilmeHash.c](FilmeHash.c) / [FilmeHash.h](FilmeHash.h)
- **Interface interativa:** [Main.c](Main.c)
- **Leitor de arquivos de folha:** [leitor_folha.c](leitor_folha.c)
- **Arquivo de relações:** [Relationships.txt](Relationships.txt)


```bash
gcc -std=c99 -Wall -o main.exe Main.c TARVBM_bin.c FilmeHash.c
```

No Linux/macOS (gera `main`):

```bash
gcc -std=c99 -Wall -o main Main.c TARVBM_bin.c FilmeHash.c
```

Para compilar o utilitário de leitura de folha:

```bash
gcc -std=c99 -Wall -o leitor_folha.exe leitor_folha.c TARVBM_bin.c
```

OBS: Alguns exemplos abaixo compilam pequenos programas de teste que usam apenas `FilmeHash.c`.

**Testes (Árvore B+)**
1. Execute o binário compilado:

Windows:
```bash
.\main.exe
```
Linux/macOS:
```bash
./main
```

2. O menu interativo apresenta opções:
- `1 - Criar Arvore` : informe um nome (ex: `arvore1`) e o parâmetro `t` (grau mínimo, mínimo 2). Isso cria uma pasta com o nome da árvore e os arquivos internos (`folha_*.bin`, `PESSOAS`, arquivo de metadados).
- `2 - Abrir Arvore`  : abre uma árvore já criada pelo nome da pasta.
- `3 - Inserir`      : insere uma `PESSOA` (o `Main.c` usa apenas o `nome` e um valor fixo de data). Os dados da pessoa são gravados em `PESSOAS` e a chave é inserida na árvore.
- `4 - Remover`      : remove (marca) a pessoa da árvore e do arquivo `PESSOAS` (substitui nome por `*REMOVIDO*`).
- `5 - Imprimir arvore`: imprime a estrutura (ordem por nível) usando a função de impressão da árvore.
- `6 - Imprimir folhas`: imprime detalhes das folhas (arquivos `folha_*.bin`).
- `7 - Verificar tamanho do no`: mostra o tamanho calculado do nó para inspeção.
- `0 - Checar Hash`: abre um novo menu que contém todas as opções de manipulação de hash.
	- `1 - Iniciar hash de relações`: inicializa um hash vazia e carrega os dados de `Relationships.txt` para os arquivos de índice e dados
	- `2 - Cálculo de hash`: informe um nome de filme (ex: `The Matrix`) e o ano de lançamento (ex: `1995`) e retorna o valor do índice hash.
	- `3 - Inserir Relação`: informe um nome de filme (ex: `The Matrix`) e o ano de lançamento (ex: `1995`), o nome de uma pessoa (ex: `Keanu Reeves`), a função exercida (ACTED_IN, WROTE, DIRECTED, PRODUCED) e o nome do personagem (caso tenha atuado) e insere na hash.
	- `4 - Remover Relação`: informe um nome de filme (ex: `The Matrix`) e o ano de lançamento (ex: `1995`), o nome de uma pessoa (ex: `Keanu Reeves`) e remove a pessoa da hash.
	- `5 - Listar cast de um filme`: informe um nome de filme (ex: `The Matrix`) e o ano de lançamento (ex: `1995`) e imprime o todas as pessoas que participaram desse filme.
	- `6 - Busca individal`: informe um nome de filme (ex: `The Matrix`) e o ano de lançamento (ex: `1995`), o nome de uma pessoa (ex: `Keanu Reeves`) e retorna se a pessoa participa o não do filme, e se participar, retorna a função.
	- `7 - Sair das opções de hash`: retorna ao menu principal de árvores. 

Exemplo rápido:
- Criar árvore: nome `av1`, `t=2`.
- Inserir: `Alice`, `Bob`, `Carlos` (opção 3 repetidas vezes).
- Imprimir árvore (opção 5) — professor verifica se as chaves aparecem.
- Imprimir folhas (opção 6) — verificar arquivos `folha_*.bin` gerados.
- Remover `Bob` (opção 4) e imprimir novamente para confirmar remoção.

Arquivos gerados pela árvore:
- Pasta com o nome da árvore: contém o arquivo principal (metadados) e vários arquivos `folha_*.bin`.
- Arquivo `PESSOAS`: arquivo binário com os registros `PESSOA`.

**Testes (FilmeHash)**
O módulo `FilmeHash` implementa uma tabela hash em arquivos para armazenar relações (pessoa × filme). Para testar rapidamente, crie um pequeno programa de teste `fh_test.c` com o conteúdo abaixo e compile:

```c
#include <stdio.h>
#include "FilmeHash.h"

int main(){
	const char *tab = "tabhash.bin";
	const char *dados = "dados.bin";
	int m = 100; // buckets

	FH_inicializa(tab, dados, m);
	int n = FH_carregar_arquivo(tab, dados, m, "Relationships.txt", 0);
	printf("Inseridos: %d\n", n);
	// Lista um filme (coloque o título que existe em Relationships.txt)
	FH_listar_filme(tab, dados, m, "Some Movie Title", 0);
	FH_imprime_tudo(tab, dados, m);
	return 0;
}
```

Compilar e executar:

```bash
gcc -std=c99 -Wall -o fh_test.exe fh_test.c FilmeHash.c
./fh_test.exe
```

Saídas esperadas: o programa informa quantos registros foram carregados de `Relationships.txt` e mostra os buckets/entradas pelo `FH_imprime_tudo`.
