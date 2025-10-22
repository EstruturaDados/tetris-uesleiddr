#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5  // Tamanho fixo da fila de peças

// Estrutura que representa uma peça do jogo
typedef struct {
    char nome; // Tipo da peça: 'I', 'O', 'T', 'L'
    int id;    // Identificador único
} Peca;

// Estrutura que representa a fila circular de peças
typedef struct {
    Peca pecas[TAM_FILA];
    int inicio;
    int fim;
    int quantidade;
} Fila;

// Função para inicializar a fila
void inicializarFila(Fila *fila) {
    fila->inicio = 0;
    fila->fim = 0;
    fila->quantidade = 0;
}

// Função para verificar se a fila está cheia
int filaCheia(Fila *fila) {
    return fila->quantidade == TAM_FILA;
}

// Função para verificar se a fila está vazia
int filaVazia(Fila *fila) {
    return fila->quantidade == 0;
}

// Função que gera automaticamente uma nova peça com tipo aleatório e id único
Peca gerarPeca(int id) {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca novaPeca;
    novaPeca.nome = tipos[rand() % 4]; // Escolhe tipo aleatório
    novaPeca.id = id;
    return novaPeca;
}

// Função para inserir uma peça ao final da fila (enqueue)
void enqueue(Fila *fila, Peca peca) {
    if (filaCheia(fila)) {
        printf("\n⚠️  A fila está cheia! Não é possível adicionar nova peça.\n");
        return;
    }

    fila->pecas[fila->fim] = peca;
    fila->fim = (fila->fim + 1) % TAM_FILA;
    fila->quantidade++;
    printf("\n✅ Peça [%c %d] adicionada com sucesso!\n", peca.nome, peca.id);
}

// Função para remover a peça da frente da fila (dequeue)
void dequeue(Fila *fila) {
    if (filaVazia(fila)) {
        printf("\n⚠️  A fila está vazia! Nenhuma peça para jogar.\n");
        return;
    }

    Peca removida = fila->pecas[fila->inicio];
    fila->inicio = (fila->inicio + 1) % TAM_FILA;
    fila->quantidade--;
    printf("\n🎮 Peça jogada: [%c %d]\n", removida.nome, removida.id);
}

// Função para exibir o estado atual da fila
void exibirFila(Fila *fila) {
    printf("\n===== Fila de Peças =====\n");

    if (filaVazia(fila)) {
        printf("(vazia)\n");
        return;
    }

    int i, pos = fila->inicio;
    for (i = 0; i < fila->quantidade; i++) {
        Peca p = fila->pecas[pos];
        printf("[%c %d] ", p.nome, p.id);
        pos = (pos + 1) % TAM_FILA;
    }
    printf("\n=========================\n");
}

// Função principal
int main() {
    Fila fila;
    inicializarFila(&fila);
    srand(time(NULL));

    int idAtual = 0;
    int opcao;

    // Inicializa a fila com 5 peças
    for (int i = 0; i < TAM_FILA; i++) {
        enqueue(&fila, gerarPeca(idAtual++));
    }

    // Loop do menu principal
    do {
        exibirFila(&fila);

        printf("\nOpções:\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                dequeue(&fila);
                break;
            case 2:
                enqueue(&fila, gerarPeca(idAtual++));
                break;
            case 0:
                printf("\n👋 Encerrando o programa...\n");
                break;
            default:
                printf("\n❌ Opção inválida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}
