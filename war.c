#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* ============================================================================
 STRUCT DO TERRITÓRIO
 ============================================================================
 */
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Protótipos das funções
void cadastrarTerritorios(Territorio* mapa, int quantidade);
void exibirMapa(Territorio* mapa, int quantidade);
void atacar(Territorio* atacante, Territorio* defensor);
void liberarMemoria(Territorio* mapa);
void limparBuffer();

/* ============================================================================
 FUNÇÃO PRINCIPAL
 ============================================================================
 */
int main() {
    int quantidade = 5; 
    int idxAtacante, idxDefensor;
    Territorio* mapa = NULL; 

    srand(time(NULL));

    // Alocação dinâmica obrigatória pelo desafio
    mapa = (Territorio*) malloc(quantidade * sizeof(Territorio));
    
    if (mapa == NULL) {
        printf("Erro fatal: Memoria insuficiente!\n");
        return 1;
    }

    // Cadastro inicial dos 5 territórios
    cadastrarTerritorios(mapa, quantidade);

    // Loop da Fase de Ataque
    while (1) {
        exibirMapa(mapa, quantidade);
        
        printf("\n--- FASE DE ATAQUE ---\n");
        printf("Escolha o territorio atacante (1 a %d, ou 0 para sair): ", quantidade);
        scanf("%d", &idxAtacante);
        limparBuffer();

        // Se digitar 0, sai do loop imediatamente para encerrar
        if (idxAtacante == 0) {
            break;
        }

        printf("Escolha o territorio defensor (1 a %d): ", quantidade);
        scanf("%d", &idxDefensor);
        limparBuffer();

        idxAtacante--;
        idxDefensor--;

        // Validações de segurança
        if (idxAtacante < 0 || idxAtacante >= quantidade || idxDefensor < 0 || idxDefensor >= quantidade) {
            printf("\n[ERRO] IDs invalidos! Escolha territorios existentes.\n");
            printf("Pressione Enter para continuar...\n");
            getchar();
            continue;
        }

        if (idxAtacante == idxDefensor) {
            printf("\n[ERRO] Um territorio nao pode atacar a si mesmo!\n");
            printf("Pressione Enter para continuar...\n");
            getchar();
            continue;
        }

        if (strcmp(mapa[idxAtacante].cor, mapa[idxDefensor].cor) == 0) {
            printf("\n[ERRO] Ataque recusado! Mesma cor de exercito.\n");
            printf("Pressione Enter para continuar...\n");
            getchar();
            continue;
        }

        // Executa o combate
        atacar(&mapa[idxAtacante], &mapa[idxDefensor]);
    }

    // REQUISITO E TEXTO ATUALIZADOS: Liberação e mensagem exata do print final
    liberarMemoria(mapa);
    mapa = NULL; 

    return 0;
}

/* ============================================================================
 FUNÇÃO: Cadastro dos Territórios
 ============================================================================
 */
void cadastrarTerritorios(Territorio* mapa, int quantidade) {
    int i;
    for (i = 0; i < quantidade; i++) {
        printf("--- Cadastrando Territorio %d ---\n", i + 1);
        
        printf("Nome do Territorio: ");
        scanf("%29s", mapa[i].nome);
        limparBuffer();

        printf("Cor do Exercito: ");
        scanf("%9s", mapa[i].cor);
        limparBuffer();

        printf("Numero de Tropas: ");
        scanf("%d", &mapa[i].tropas);
        limparBuffer();
        printf("\n");
    }
}

/* ============================================================================
 FUNÇÃO: Exibição do Mapa 
 ============================================================================
 */
void exibirMapa(Territorio* mapa, int quantidade) {
    int i;
    printf("\n=========================================\n");
    printf("   MAPA DO MUNDO - ESTADO ATUAL\n");
    printf("=========================================\n\n");
    
    for (i = 0; i < quantidade; i++) {
        printf("%d. %s (Exercito %s, Tropas: %d)\n", 
               i + 1, 
               mapa[i].nome, 
               mapa[i].cor, 
               mapa[i].tropas);
    }
}

/* ============================================================================
 FUNÇÃO: Simulação de Ataque 
 ============================================================================
 */
void atacar(Territorio* atacante, Territorio* defensor) {
    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("\n--- RESULTADO DA BATALHA ---\n");
    printf("O atacante %s rolou um dado e tirou: %d\n", atacante->nome, dadoAtacante);
    printf("O defensor %s rolou um dado e tirou: %d\n", defensor->nome, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("VITORIA DO ATAQUE! O defensor perdeu 1 tropa.\n");
        if (defensor->tropas > 0) {
            defensor->tropas--;
        }
        
        if (defensor->tropas == 0) {
            printf("CONQUISTA! O territorio %s foi dominado pelo Exercito %s!\n", defensor->nome, atacante->cor);
            strcpy(defensor->cor, atacante->cor);
            defensor->tropas = 1; 
            if (atacante->tropas > 1) {
                atacante->tropas--;
            }
        }
    } 
    else {
        printf("VITORIA DA DEFESA! O atacante perdeu 1 tropa.\n");
        if (atacante->tropas > 1) {
            atacante->tropas--;
        }
    }

    printf("\nPressione Enter para continuar para o proximo turno...");
    getchar(); 
    printf("\n");
}

/* ============================================================================
 FUNÇÃO: Liberação de Memória com o texto exato do encerramento
 ============================================================================
 */
void liberarMemoria(Territorio* mapa) {
    free(mapa);
    // Texto exato extraído da sua captura de tela:
    printf("\nJogo encerrado e memoria liberada. Ate a proxima!\n");
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}