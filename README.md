
                     🎮 TETRIS STACK - NÍVEL NOVATO 🎮
                    Sistema de Gerenciamento de Peças

📋 DESCRIÇÃO DO PROJETO
------------------------
Sistema de gerenciamento de peças inspirado no Tetris, desenvolvido como 
desafio educacional pela ByteBros. Implementa uma fila circular para controlar
as próximas 5 peças do jogo.

🎯 OBJETIVO
-----------
Simular uma fila circular de 5 peças com funcionalidades de:
  • Visualizar fila atual
  • Jogar (remover) peça da frente
  • Inserir nova peça no final
  • Manter fila circular reaproveitando espaço

🏗️ ESTRUTURAS DE DADOS


// Representa uma peça do Tetris
typedef struct {
    char nome;  // Tipo: I, O, T, L, J, S, Z
    int id;     // Identificador único
} Peca;

// Controla a fila circular
typedef struct {
    Peca pecas[5];
    int frente;
    int tras;
    int quantidade;
} FilaCircular;

/*
🎲 TIPOS DE PEÇAS
-----------------
O sistema trabalha com 7 tipos clássicos de peças do Tetris:
  • I - Barra reta (4 blocos em linha)
  • O - Quadrado (2x2 blocos)
  • T - Forma de T
  • L - L normal
  • J - L invertido
  • S - Zigue-zague S
  • Z - Zigue-zague Z

Cada peça recebe um ID único sequencial para rastreamento individual.

🔄 FUNCIONAMENTO DA FILA CIRCULAR
----------------------------------
A fila circular utiliza a operação módulo (%) para reaproveitar espaços:
  1. Enqueue (Inserir): tras = (tras + 1) % 5
  2. Dequeue (Remover): frente = (frente + 1) % 5

Isso permite que, ao remover uma peça da frente, o espaço liberado possa ser
reutilizado quando uma nova peça for adicionada, mantendo sempre até 5 peças.

🛡️ CONTROLES E VALIDAÇÕES
--------------------------
O sistema implementa verificações robustas:
  ✅ Verifica se a fila está cheia antes de inserir
  ✅ Verifica se a fila está vazia antes de remover
  ✅ Valida entradas do usuário no menu
  ✅ Exibe mensagens claras de erro e sucesso
  ✅ Limpa buffer de entrada para evitar comportamentos indesejados

🎨 INTERFACE DO USUÁRIO
-----------------------
O programa oferece uma interface textual clara e organizada:

===========================================
   BEM-VINDO AO TETRIS STACK - NIVEL NOVATO
===========================================

Fila inicializada com 5 pecas!

             MENU PRINCIPAL 
  [1] Visualizar fila de pecas
  [2] Jogar peca (remover da frente)
  [3] Adicionar nova peca (no final)
  [0] Sair do jogo
-------------------------------------------

Após cada operação, o estado atualizado da fila é exibido automaticamente,
mostrando:
  • Quantidade de peças atual
  • Posição de cada peça (destacando a próxima a ser jogada)
  • Tipo e ID de cada peça

💡 CONCEITOS APLICADOS
----------------------
  • Fila circular      • Structs personalizadas
  • Arrays             • Modularização
  • Validação de dados • Geração aleatória
  • Interface de menu  • Tratamento de entrada

🚀 COMPILAÇÃO E EXECUÇÃO
------------------------
Compilação:
  gcc tetris_stack.c -o tetris_stack

Execução:
  ./tetris_stack

📊 FLUXO DE EXECUÇÃO
--------------------
  1. Sistema inicializa fila com 5 peças aleatórias
  2. Exibe menu de opções ao usuário
  3. Usuário escolhe ação (visualizar, jogar, adicionar, sair)
  4. Sistema valida operação e executa
  5. Exibe feedback e estado atualizado
  6. Retorna ao menu até usuário sair

🎓 APRENDIZADOS
---------------
Este projeto exercita:
  ✓ Implementação de fila circular com array
  ✓ Uso de structs para organização de dados
  ✓ Modularização através de funções especializadas
  ✓ Validação robusta de operações
  ✓ Interface de usuário clara e intuitiva

🚀 PRÓXIMOS NÍVEIS
------------------
  • Aventureiro: Adicionar pilha de reserva (3 peças)
  • Mestre: Operações avançadas (troca, inversão, desfazer)

================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO_FILA 5

// ============================================================================
// VARIÁVEIS GLOBAIS
// ============================================================================

int contadorId = 1;  // Contador para gerar IDs únicos

// ============================================================================
// PROTÓTIPOS DAS FUNÇÕES
// ============================================================================

void inicializarFila(FilaCircular *fila);
Peca gerarPeca();
int filaCheia(FilaCircular *fila);
int filaVazia(FilaCircular *fila);
void enqueue(FilaCircular *fila, Peca peca);
Peca dequeue(FilaCircular *fila);
void visualizarFila(FilaCircular *fila);
void exibirMenu();
void limparBuffer();

// ============================================================================
// FUNÇÃO PRINCIPAL
// ============================================================================

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

// ============================================================================
// IMPLEMENTAÇÃO DAS FUNÇÕES
// ============================================================================

/*
 * inicializarFila
 * ---------------
 * Inicializa a fila com 5 peças geradas automaticamente
 */
void inicializarFila(FilaCircular *fila) {
    fila->frente = 0;
    fila->tras = -1;
    fila->quantidade = 0;
    
    for (int i = 0; i < TAMANHO_FILA; i++) {
        Peca novaPeca = gerarPeca();
        enqueue(fila, novaPeca);
    }
}

/*
 * gerarPeca
 * ---------
 * Gera uma peça aleatória com ID único
 */
Peca gerarPeca() {
    Peca novaPeca;
    char tipos[] = {'I', 'O', 'T', 'L', 'J', 'S', 'Z'};
    int indice = rand() % 7;
    
    novaPeca.nome = tipos[indice];
    novaPeca.id = contadorId++;
    
    return novaPeca;
}

/*
 * filaCheia
 * ---------
 * Verifica se a fila está cheia (5 peças)
 */
int filaCheia(FilaCircular *fila) {
    return fila->quantidade == TAMANHO_FILA;
}

/*
 * filaVazia
 * ---------
 * Verifica se a fila está vazia
 */
int filaVazia(FilaCircular *fila) {
    return fila->quantidade == 0;
}

/*
 * enqueue
 * -------
 * Adiciona peça no final da fila circular
 */
void enqueue(FilaCircular *fila, Peca peca) {
    if (filaCheia(fila)) {
        printf("[ERRO] Fila cheia! Nao foi possivel adicionar a peca.\n");
        return;
    }
    
    fila->tras = (fila->tras + 1) % TAMANHO_FILA;
    fila->pecas[fila->tras] = peca;
    fila->quantidade++;
}

/*
 * dequeue
 * -------
 * Remove e retorna peça da frente da fila
 */
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

/*
 * visualizarFila
 * --------------
 * Exibe o estado atual da fila formatado
 */
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

/*
 * exibirMenu
 * ----------
 * Exibe o menu principal com opções disponíveis
 */
void exibirMenu() {
    printf("-------------------------------------------\n");
    printf("              MENU PRINCIPAL\n");
    printf("-------------------------------------------\n");
    printf("  [1] Visualizar fila de pecas\n");
    printf("  [2] Jogar peca (remover da frente)\n");
    printf("  [3] Adicionar nova peca (no final)\n");
    printf("  [0] Sair do jogo\n");
    printf("-------------------------------------------\n");
}

/*
 * limparBuffer
 * ------------
 * Limpa o buffer de entrada
 */
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

✅ FIM DO PROGRAMA - TETRIS STACK NÍVEL NOVATO

Desenvolvido por Widardison Sousa

*/
```
