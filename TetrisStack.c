#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5  

// Estrutura que representa uma peça do Tetris
typedef struct {
    char nome;  
    int id;     
} Peca;

// Estrutura da fila circular
typedef struct {
    Peca pecas[TAM_FILA];
    int frente;
    int tras;
    int quantidade;
} Fila;

// Inicializa a fila vazia
void inicializarFila(Fila *fila) {
    fila->frente = 0;
    fila->tras = -1;
    fila->quantidade = 0;
}

// Verifica se a fila está cheia
int filaCheia(Fila *fila) {
    return fila->quantidade == TAM_FILA;
}

// Verifica se a fila está vazia
int filaVazia(Fila *fila) {
    return fila->quantidade == 0;
}

// Gera uma nova peça
Peca gerarPeca(int id) {
    Peca nova;
    char tipos[] = {'I', 'O', 'T', 'L'};
    nova.nome = tipos[rand() % 4];
    nova.id = id;
    return nova;
}

// Insere nova peça no final da fila 
void inserirPeca(Fila *fila, Peca nova) {
    if (filaCheia(fila)) {
        printf("\n A fila está cheia! Não é possível inserir nova peça.\n");
        return;
    }
    fila->tras = (fila->tras + 1) % TAM_FILA;
    fila->pecas[fila->tras] = nova;
    fila->quantidade++;
}

// Remove peça da frente da fila
void jogarPeca(Fila *fila) {
    if (filaVazia(fila)) {
        printf("\n A fila está vazia! Nenhuma peça para jogar.\n");
        return;
    }
    Peca removida = fila->pecas[fila->frente];
    printf("\n🎮 Peça jogada: [%c %d]\n", removida.nome, removida.id);
    fila->frente = (fila->frente + 1) % TAM_FILA;
    fila->quantidade--;
}

// Exibe todas as peças da fila
void exibirFila(Fila *fila) {
    if (filaVazia(fila)) {
        printf("\n(Fila vazia)\n");
        return;
    }
    printf("\nFila de peças:\n");
    int i, idx;
    for (i = 0; i < fila->quantidade; i++) {
        idx = (fila->frente + i) % TAM_FILA;
        printf("[%c %d] ", fila->pecas[idx].nome, fila->pecas[idx].id);
    }
    printf("\n");
}

// Função principal 
int main() {
    Fila fila;
    int opcao, contadorID = 0;

    srand(time(NULL)); 
    inicializarFila(&fila);

    // Inicializa a fila com 5 peças
    for (int i = 0; i < TAM_FILA; i++) {
        inserirPeca(&fila, gerarPeca(contadorID++));
    }

    do {
        printf("\n--------------------------");
        printf("\n       TETRIS STACK       ");
        printf("\n--------------------------");
        exibirFila(&fila);
        printf("\nOpções de ação:\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                jogarPeca(&fila);
                break;
            case 2:
                inserirPeca(&fila, gerarPeca(contadorID++));
                break;
            case 0:
                printf("\nEncerrando o programa...\n");
                break;
            default:
                printf("\nOpção inválida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}
