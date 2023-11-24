#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define TAMANHO_TABELA 53
#define TAMANHO_PALAVRA 50

typedef struct No {
    char *palavra;
    struct No *proximo;
    struct No *anterior;
} No;
typedef struct TabelaHash {
    No *slots[TAMANHO_TABELA];
} TabelaHash;

int hash(char palavra[]);
void inicializarTabelaHash(TabelaHash *tabela);
void inserirFunction(TabelaHash *tabela, char palavra[]);
void insercaoInicial(TabelaHash *tabela);
void insercaoPalavras(TabelaHash *tabela);
void excluirDaTabela(TabelaHash *tabela);
void imprimirTabelaHash(TabelaHash *tabela);
void buscarNaTabela(TabelaHash *tabela);
void exibirMenu();
void trocarPalavras(No *a, No *b);
No *particionar(No *inicio, No *fim);
void quickSort(No *inicio, No *fim);
void sortSlot(TabelaHash *tabela, int indiceSlot);
void sortTabela(TabelaHash *tabela);
void imprimirSlot(TabelaHash *tabela);
void mediaDesvioPadrao(TabelaHash *tabela);

int main() {
    TabelaHash minhaTabela;
    inicializarTabelaHash(&minhaTabela);
    insercaoInicial(&minhaTabela);

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
                buscarNaTabela(&minhaTabela);
                break;

            case 5:
                imprimirSlot(&minhaTabela);
                break;

            case 6:
                mediaDesvioPadrao(&minhaTabela);
                break;

            case 7:
                printf("Saindo do programa.\n");
                break;

            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 7);
    return 0;
}

int hash(char palavra[]) {
    int soma = 0;
    for (int i = 0; palavra[i] != '\0'; i++) {
        soma += palavra[i];
    }
    return soma % TAMANHO_TABELA;
}

void inicializarTabelaHash(TabelaHash *tabela) {
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        tabela->slots[i] = NULL;
    }
}

void inserirFunction(TabelaHash *tabela, char palavra[]) {
    int indice = hash(palavra);

    No *novoNo = (No *) malloc(sizeof(No));

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

void insercaoInicial(TabelaHash *tabela) {

    FILE *fptr = fopen("../nomes.txt", "r");
    if (fptr == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo.\n");
        exit(EXIT_FAILURE);
    }

    char palavra[TAMANHO_PALAVRA];

    while (fgets(palavra, sizeof(palavra), fptr) != NULL) {

        size_t len = strlen(palavra);
        if (len > 0 && palavra[len - 1] == '\n') {
            palavra[len - 1] = '\0';
        }

        inserirFunction(tabela, palavra);
    }

    fclose(fptr);

    sortTabela(tabela);
}

void insercaoPalavras(TabelaHash *tabela) {
    int tamanho;

    printf("\nDigite quantas palavras deseja adicionar: ");
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


    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; palavras[i][j] != '\0'; j++) {
            palavras[i][j] = toupper(palavras[i][j]);
        }
    }

    for (int i = 0; i < tamanho; i++) {
        inserirFunction(tabela, palavras[i]);
        sortSlot(tabela, hash(palavras[i]));
    }

    printf("Palavras adicionadas!\n");
}

void excluirDaTabela(TabelaHash *tabela) {

    char palavra[TAMANHO_PALAVRA];

    printf("\nDigite a palavra a ser excluida:");
    scanf("%s", palavra);

    for (int i = 0; palavra[i] != '\0'; i++) {
        palavra[i] = toupper(palavra[i]);
    }

    int indice = hash(palavra);

    if (indice < 0 || indice >= TAMANHO_TABELA) {
        fprintf(stderr, "Índice fora dos limites da tabela.\n");
        exit(EXIT_FAILURE);
    }

    No *atual = tabela->slots[indice];

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

void imprimirTabelaHash(TabelaHash *tabela) {
    printf("\n");
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        int contador = 0;
        No *atual = tabela->slots[i];
        while (atual != NULL) {
            contador++;
            atual = atual->proximo;
        }
        printf("Slot %d: %d palavras\n", i, contador);
    }
}

void buscarNaTabela(TabelaHash *tabela) {

    char palavra[TAMANHO_PALAVRA];

    printf("\nDigite a palavra a ser buscada: ");
    scanf("%s", palavra);

    for (int i = 0; palavra[i] != '\0'; i++) {
        palavra[i] = toupper(palavra[i]);
    }

    int indice = hash(palavra);
    int posicaoSlot = 0;

    if (indice < 0 || indice >= TAMANHO_TABELA) {
        fprintf(stderr, "Índice fora dos limites da tabela.\n");
        exit(EXIT_FAILURE);
    }

    No *atual = tabela->slots[indice];

    while (atual != NULL) {
        if (strcmp(atual->palavra, palavra) == 0) {
            printf("A palavra '%s' foi encontrada no slot '%d' na posição '%d'\n", palavra, indice, posicaoSlot);
            return;
        }

        atual = atual->proximo;
        posicaoSlot++;
    }
    printf("Palavra não econtrada\n");
}

void exibirMenu() {
    printf("\nMenu:\n");
    printf("1. Inserir palavras\n");
    printf("2. Excluir palavra\n");
    printf("3. Imprimir tabela\n");
    printf("4. Buscar na tabela\n");
    printf("5. Imprimir slot da tabela\n");
    printf("6. Imprimir média e desvio padrão\n");
    printf("7. Sair\n");
}

void trocarPalavras(No *a, No *b) {
    char *temp = a->palavra;
    a->palavra = b->palavra;
    b->palavra = temp;
}

No *particionar(No *inicio, No *fim) {
    char *pivo = fim->palavra;
    No *i = inicio->anterior;

    for (No *j = inicio; j != fim; j = j->proximo) {
        if (strcmp(j->palavra, pivo) < 0) {
            i = (i == NULL) ? inicio : i->proximo;
            trocarPalavras(i, j);
        }
    }

    i = (i == NULL) ? inicio : i->proximo;
    trocarPalavras(i, fim);

    return i;
}

void quickSort(No *inicio, No *fim) {
    if (fim != NULL && inicio != fim && inicio != fim->proximo) {
        No *pivo = particionar(inicio, fim);
        quickSort(inicio, pivo->anterior);
        quickSort(pivo->proximo, fim);
    }
}

void sortSlot(TabelaHash *tabela, int indiceSlot) {
    No **slot = &(tabela->slots[indiceSlot]);

    No *fim = *slot;
    while (fim != NULL && fim->proximo != NULL) {
        fim = fim->proximo;
    }

    quickSort(*slot, fim);
}

void sortTabela(TabelaHash *tabela) {
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        sortSlot(tabela, i);
    }
}

void imprimirSlot(TabelaHash *tabela) {
    int indiceSlot;

    printf("\nDigite qual slot deseja imprimir: ");
    scanf("%d", &indiceSlot);

    if (indiceSlot < 0 || indiceSlot >= TAMANHO_TABELA) {
        printf("Índice de slot inválido.\n");
        return;
    }

    No *atual = tabela->slots[indiceSlot];

    printf("Palavras no slot %d:\n", indiceSlot);

    if(atual ==  NULL){
        printf("Nenhuma palavra encontrada.\n");
    } else {
        while (atual != NULL) {
            printf("%s\n", atual->palavra);
            atual = atual->proximo;
        }
    }
}

void mediaDesvioPadrao(TabelaHash *tabela){

    float media = 0;

    for (int i = 0; i < TAMANHO_TABELA; i++) {
        int contador = 0;
        No *atual = tabela->slots[i];
        while (atual != NULL) {
            contador++;
            atual = atual->proximo;
        }
        media += contador;
    }
    media = media / TAMANHO_TABELA;
    printf("\nMédia: %.2f\n", media);

    float desvioPadrao = 0;

    for (int i = 0; i < TAMANHO_TABELA; i++) {
        int contador = 0;
        No *atual = tabela->slots[i];
        while (atual != NULL) {
            contador++;
            atual = atual->proximo;
        }
        desvioPadrao += fabs(media - contador);
    }
    desvioPadrao = desvioPadrao / TAMANHO_TABELA;
    printf("Desvio padrão: %.2f\n", desvioPadrao);
}