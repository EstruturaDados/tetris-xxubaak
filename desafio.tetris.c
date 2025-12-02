#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO_FILA 5

// Estrutura que representa uma peça do Tetris
typedef struct {
    char nome;
    int id;
} Peca;

// Estrutura da fila circular
typedef struct {
    Peca pecas[TAMANHO_FILA];
    int frente;
    int tras;
    int quantidade;
} FilaCircular;

// Contador global para IDs únicos
int contadorId = 1;

// Protótipos das funções
void inicializarFila(FilaCircular *fila);
Peca gerarPeca();
int filaCheia(FilaCircular *fila);
int filaVazia(FilaCircular *fila);
void enqueue(FilaCircular *fila, Peca peca);
Peca dequeue(FilaCircular *fila);
void visualizarFila(FilaCircular *fila);
void exibirMenu();
void limparBuffer();

int main() {
    FilaCircular fila;
    int opcao;
    
    srand(time(NULL));
    
    printf("===========================================\n");
    printf("   BEM-VINDO AO TETRIS STACK - NIVEL NOVATO\n");
    printf("===========================================\n\n");
    
    inicializarFila(&fila);
    
    printf("Fila inicializada com 5 pecas!\n\n");
    visualizarFila(&fila);
    
    do {
        exibirMenu();
        printf("Escolha uma opcao: ");
        
        if (scanf("%d", &opcao) != 1) {
            limparBuffer();
            printf("\n[ERRO] Entrada invalida! Digite um numero.\n\n");
            continue;
        }
        limparBuffer();
        
        printf("\n");
        
        switch(opcao) {
            case 1:
                visualizarFila(&fila);
                break;
                
            case 2: {
                if (filaVazia(&fila)) {
                    printf("[AVISO] A fila esta vazia! Nao ha pecas para jogar.\n\n");
                } else {
                    Peca pecaJogada = dequeue(&fila);
                    printf(">>> PECA JOGADA <<<\n");
                    printf("Tipo: %c | ID: %d\n\n", pecaJogada.nome, pecaJogada.id);
                    visualizarFila(&fila);
                }
                break;
            }
                
            case 3: {
                if (filaCheia(&fila)) {
                    printf("[AVISO] A fila esta cheia! Nao e possivel adicionar mais pecas.\n\n");
                } else {
                    Peca novaPeca = gerarPeca();
                    enqueue(&fila, novaPeca);
                    printf(">>> NOVA PECA ADICIONADA <<<\n");
                    printf("Tipo: %c | ID: %d\n\n", novaPeca.nome, novaPeca.id);
                    visualizarFila(&fila);
                }
                break;
            }
                
            case 0:
                printf("===========================================\n");
                printf("   Obrigado por jogar Tetris Stack!\n");
                printf("   Ate a proxima, jogador!\n");
                printf("===========================================\n");
                break;
                
            default:
                printf("[ERRO] Opcao invalida! Tente novamente.\n\n");
        }
        
    } while(opcao != 0);
    
    return 0;
}

// Inicializa a fila com 5 peças automaticamente
void inicializarFila(FilaCircular *fila) {
    fila->frente = 0;
    fila->tras = -1;
    fila->quantidade = 0;
    
    for (int i = 0; i < TAMANHO_FILA; i++) {
        Peca novaPeca = gerarPeca();
        enqueue(fila, novaPeca);
    }
}

// Gera uma peça aleatória com ID único
Peca gerarPeca() {
    Peca novaPeca;
    char tipos[] = {'I', 'O', 'T', 'L', 'J', 'S', 'Z'};
    int indice = rand() % 7;
    
    novaPeca.nome = tipos[indice];
    novaPeca.id = contadorId++;
    
    return novaPeca;
}

// Verifica se a fila está cheia
int filaCheia(FilaCircular *fila) {
    return fila->quantidade == TAMANHO_FILA;
}

// Verifica se a fila está vazia
int filaVazia(FilaCircular *fila) {
    return fila->quantidade == 0;
}

// Adiciona uma peça no final da fila
void enqueue(FilaCircular *fila, Peca peca) {
    if (filaCheia(fila)) {
        printf("[ERRO] Fila cheia! Nao foi possivel adicionar a peca.\n");
        return;
    }
    
    fila->tras = (fila->tras + 1) % TAMANHO_FILA;
    fila->pecas[fila->tras] = peca;
    fila->quantidade++;
}

// Remove e retorna a peça da frente da fila
Peca dequeue(FilaCircular *fila) {
    Peca pecaRemovida;
    
    if (filaVazia(fila)) {
        printf("[ERRO] Fila vazia! Nao ha pecas para remover.\n");
        pecaRemovida.nome = '\0';
        pecaRemovida.id = -1;
        return pecaRemovida;
    }
    
    pecaRemovida = fila->pecas[fila->frente];
    fila->frente = (fila->frente + 1) % TAMANHO_FILA;
    fila->quantidade--;
    
    return pecaRemovida;
}

// Visualiza o estado atual da fila
void visualizarFila(FilaCircular *fila) {
    printf("===========================================\n");
    printf("        ESTADO ATUAL DA FILA\n");
    printf("===========================================\n");
    printf("Pecas na fila: %d/%d\n\n", fila->quantidade, TAMANHO_FILA);
    
    if (filaVazia(fila)) {
        printf("  [VAZIA] Nenhuma peca na fila.\n");
    } else {
        printf("  Posicao | Tipo | ID\n");
        printf("  --------+------+----\n");
        
        int pos = fila->frente;
        for (int i = 0; i < fila->quantidade; i++) {
            if (i == 0) {
                printf("  [PROX]  |  %c   | %d\n", 
                       fila->pecas[pos].nome, 
                       fila->pecas[pos].id);
            } else {
                printf("   %d      |  %c   | %d\n", 
                       i + 1, 
                       fila->pecas[pos].nome, 
                       fila->pecas[pos].id);
            }
            pos = (pos + 1) % TAMANHO_FILA;
        }
    }
    
    printf("===========================================\n\n");
}
