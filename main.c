#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_TABELA 53
#define TAMANHO_PALAVRA 50

typedef struct No {
    char* palavra;
    struct No* proximo;
    struct No* anterior;
} No;

typedef struct TabelaHash {
    No* slots[TAMANHO_TABELA];
} TabelaHash;

int hash(char chave[]) {
    int soma = 0;
    for (int i = 0; chave[i] != '\0'; i++) {
        soma += chave[i];
    }
    return soma % TAMANHO_TABELA;
}

void inicializarTabelaHash(TabelaHash* tabela) {
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        tabela->slots[i] = NULL;
    }
}

void inserirFunction(TabelaHash* tabela, char* palavra) {
    int indice = hash(palavra);

    No* novoNo = (No*)malloc(sizeof(No));
    if (novoNo == NULL) {
        fprintf(stderr, "Erro na alocação de memória.\n");
        exit(EXIT_FAILURE);
    }

    novoNo->palavra = strdup(palavra);
    if (novoNo->palavra == NULL) {
        fprintf(stderr, "Erro na alocação de memória.\n");
        free(novoNo);
        exit(EXIT_FAILURE);
    }

    novoNo->proximo = tabela->slots[indice];
    novoNo->anterior = NULL;

    if (tabela->slots[indice] != NULL) {
        tabela->slots[indice]->anterior = novoNo;
    }

    tabela->slots[indice] = novoNo;
}

void insercaoInicial(TabelaHash* tabela) {
    FILE* fptr = fopen("../nomes.txt", "r");
    if (fptr == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo.\n");
        exit(EXIT_FAILURE);
    }

    char palavra[TAMANHO_PALAVRA];

    while (fgets(palavra, sizeof(palavra), fptr) != NULL) {
        // Remover a quebra de linha, se existir
        size_t len = strlen(palavra);
        if (len > 0 && palavra[len - 1] == '\n') {
            palavra[len - 1] = '\0';
        }

        inserirFunction(tabela, palavra);
    }

    fclose(fptr);
}

void insercaoPalavras(TabelaHash* tabela) {
    int tamanho;

    printf("Digite quantas palavras deseja adicionar: ");
    scanf("%d", &tamanho);

    if (tamanho <= 0) {
        printf("Você não pode adicionar 0 palavras.\n");
        return;
    }
    char palavras[tamanho][TAMANHO_PALAVRA];

    for (int i = 0; i < tamanho; i++) {
        printf("Digite a palavra %d: ", i + 1);
        scanf("%s", palavras[i]);
    }

    printf("\nConteúdo do vetor de strings:\n");
    for (int i = 0; i < tamanho; i++) {
        inserirFunction(tabela, palavras[i]);
    }

    return;  // Sair do programa com sucesso
}

void excluirDaTabela(TabelaHash* tabela) {

    char palavra[TAMANHO_PALAVRA];

    printf("Digite a palavra a ser excluida:");
    scanf("%s", palavra);

    int indice = hash(palavra);

    if (indice < 0 || indice >= TAMANHO_TABELA) {
        fprintf(stderr, "Índice fora dos limites da tabela.\n");
        exit(EXIT_FAILURE);
    }

    No* atual = tabela->slots[indice];

    while (atual != NULL) {
        if (strcmp(atual->palavra, palavra) == 0) {
            if (atual->anterior != NULL) {
                atual->anterior->proximo = atual->proximo;
            } else {
                tabela->slots[indice] = atual->proximo;
            }

            if (atual->proximo != NULL) {
                atual->proximo->anterior = atual->anterior;
            }

            free(atual->palavra);
            free(atual);

            printf("Palavra \"%s\" excluída com sucesso no slot %d.\n", palavra, indice);
            return;
        }

        atual = atual->proximo;
    }

    printf("Palavra \"%s\" não encontrada na tabela.\n", palavra);
}

void imprimirTabelaHash(TabelaHash* tabela) {
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        int contador = 0;
        No* atual = tabela->slots[i];
        while (atual != NULL) {
            contador++;
            atual = atual->proximo;
        }
        printf("Slot %d: %d palavras\n", i, contador);
    }
}

void exibirMenu() {
    printf("\nMenu:\n");
    printf("1. Inserir palavras\n");
    printf("2. Excluir palavra\n");
    printf("3. Imprimir tabela\n");
    printf("4. Sair\n");
}

int main() {
    TabelaHash minhaTabela;
    inicializarTabelaHash(&minhaTabela);

//    insercaoInicial(&minhaTabela);

    int opcao;

    do {
        exibirMenu();
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                insercaoPalavras(&minhaTabela);
                break;

            case 2:
                excluirDaTabela(&minhaTabela);
                break;

            case 3:
                imprimirTabelaHash(&minhaTabela);
                break;

            case 4:
                printf("Saindo do programa.\n");
                break;

            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 4);

    return 0;
}
