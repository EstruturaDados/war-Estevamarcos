#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TOTAL_MISSOES 5

/* ============================================================================
 STRUCT DO TERRITORIO
 ============================================================================
 */
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Prototipos das funcoes (Modularizacao estrita conforme o enunciado)
void cadastrarTerritorios(Territorio* mapa, int quantidade);
void exibirMapa(Territorio* mapa, int quantidade, char* corJogador);
void atacar(Territorio* atacante, Territorio* defensor);
void atribuirMissao(char* destino, char* missoes[], int totalMissoes);
int verificarMissao(char* missao, Territorio* mapa, int tamanho);
void liberarMemoria(Territorio* mapa, char* missao);
void limparBuffer();

/* ============================================================================
 FUNCAO PRINCIPAL
 ============================================================================
 */
int main() {
    int quantidade = 5; 
    int acao = -1;
    int idxAtacante, idxDefensor;
    Territorio* mapa = NULL;
    char* missaoJogador = NULL;

    // Vetor de strings com as descricoes das missoes estrategicas
    char* bancoDeMissoes[TOTAL_MISSOES] = {
        "Destruir o exercito Verde.",
        "Conquistar 3 territorios do mapa.",
        "Eliminar todas as tropas da cor vermelha.",
        "Acumular um total de 10 tropas.",
        "Destruir o exercito Amarelo."
    };

    srand(time(NULL));

    // REQUISITO: Alocacao dinamica utilizando malloc
    mapa = (Territorio*) malloc(quantidade * sizeof(Territorio));
    missaoJogador = (char*) malloc(100 * sizeof(char));
    
    if (mapa == NULL || missaoJogador == NULL) {
        printf("Erro fatal: Memoria insuficiente!\n");
        return 1;
    }

    // Fase de cadastro inicial de 5 territorios
    cadastrarTerritorios(mapa, quantidade);

    // REQUISITO: Sorteio da missao passada por referencia para atribuicao
    atribuirMissao(missaoJogador, bancoDeMissoes, TOTAL_MISSOES);

    // Guardamos a cor do jogador (por padrao do print, baseada na Europa - ID 2)
    char corJogador[10];
    strcpy(corJogador, mapa[1].cor); 

    // Loop principal baseado no Menu de Acoes dos prints
    while (1) {
        // Exibe o mapa, o cabeçalho da missao e o menu de acoes
        exibirMapa(mapa, quantidade, corJogador);
        printf("\nSua missao:\n%s\n\n", missaoJogador);

        printf("--- MENU DE ACOES ---\n");
        printf("1 - Atacar\n");
        printf("2 - Verificar Missao\n");
        printf("0 - Sair\n");
        printf("Escolha sua acao: ");
        scanf("%d", &acao);
        limparBuffer();

        // OPCAO 0: Sair do Jogo
        if (acao == 0) {
            break;
        }

        // OPCAO 1: Fase de Ataque
        if (acao == 1) {
            printf("\n--- FASE DE ATAQUE ---\n");
            printf("Escolha o territorio atacante (1 a %d): ", quantidade);
            scanf("%d", &idxAtacante);
            limparBuffer();

            printf("Escolha o territorio defensor (1 a %d): ", quantidade);
            scanf("%d", &idxDefensor);
            limparBuffer();

            idxAtacante--;
            idxDefensor--;

            // Validacoes de seguranca do sistema de ataque
            if (idxAtacante < 0 || idxAtacante >= quantidade || idxDefensor < 0 || idxDefensor >= quantidade) {
                printf("\n[ERRO] IDs invalidos!\n");
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

            // REQUISITO: Validar para que o jogador so ataque territorios inimigos
            if (strcmp(mapa[idxAtacante].cor, mapa[idxDefensor].cor) == 0) {
                printf("\n[ERRO] Voce nao pode atacar a si mesmo ou a sua propria cor!\n");
                printf("Pressione Enter para continuar...\n");
                getchar();
                continue;
            }

            // Executa o ataque via ponteiros
            atacar(&mapa[idxAtacante], &mapa[idxDefensor]);
        }
        // OPCAO 2: Verificar a condicao de vitoria de forma explicita
        else if (acao == 2) {
            printf("\n");
            if (verificarMissao(missaoJogador, mapa, quantidade)) {
                printf("PARABENS! Voce cumpriu sua missao estrategica e venceu o jogo!\n");
                break;
            } else {
                // Mensagem exata correspondente ao Print 3
                printf("Voce ainda nao cumpriu sua missao. Continue a lutar!\n");
            }
            printf("\nPressione Enter para continuar...");
            getchar();
        }
    }

    // REQUISITO E PRINT 5: Liberação de memoria e mensagens de encerramento exatas
    liberarMemoria(mapa, missaoJogador);
    mapa = NULL;
    missaoJogador = NULL;

    return 0;
}

/* ============================================================================
 FUNCAO: Cadastro dos Territórios
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
 FUNCAO: Exibicao do Mapa (Identico ao visual do Print 1)
 ============================================================================
 */
void exibirMapa(Territorio* mapa, int quantidade, char* corJogador) {
    int i;
    printf("\n==================== MAPA DO MUNDO ====================\n");
    
    // Formatação exata com espaçamento de colunas alinhadas por tabulação/largura
    for (i = 0; i < quantidade; i++) {
        printf("%d. %-15s (Exercito: %-10s , Tropas: %d)\n", 
               i + 1, 
               mapa[i].nome, 
               mapa[i].cor, 
               mapa[i].tropas);
    }
    printf("=======================================================\n\n");
    
    // Mostra o cabeçalho dinâmico da missão
    printf("--- SUA MISSAO (Exercito %s) ---\n", corJogador);
}

/* ============================================================================
 FUNCAO: Atribuicao de Missao
 ============================================================================
 */
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int indiceSorteado = rand() % totalMissoes;
    strcpy(destino, missoes[indiceSorteado]);
}

/* ============================================================================
 FUNCAO: Verificacao da Missao
 ============================================================================
 */
int verificarMissao(char* missao, Territorio* mapa, int tamanho) {
    int i;
    
    // Lógica para a missão do print: "Destruir o exercito Verde."
    if (strstr(missao, "Verde") != NULL) {
        for (i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "Verde") == 0) {
                return 0; // O exército verde ainda existe, missão não cumprida
            }
        }
        return 1; // Se não achou nenhum verde, missão cumprida!
    }
    
    // Lógica para: "Destruir o exercito Amarelo."
    if (strstr(missao, "Amarelo") != NULL) {
        for (i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "Amarelo") == 0) {
                return 0;
            }
        }
        return 1;
    }

    // Lógica padrão secundária (Conquistar pelo menos 4 territórios)
    int contagem = 0;
    for (i = 0; i < tamanho; i++) {
        if (strcmp(mapa[i].cor, mapa[1].cor) == 0) {
            contagem++;
        }
    }
    if (contagem >= 4) return 1;

    return 0;
}

/* ============================================================================
 FUNCAO: Simulacao de Ataque (Identico ao Print 2)
 ============================================================================
 */
void atacar(Territorio* atacante, Territorio* defensor) {
    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("\n--- RESULTADO DA BATALHA ---\n");
    // Formatação exata do Print 2: Ataque (Nome): X | Defesa (Nome): Y
    printf("Ataque (%s): %d | Defesa (%s): %d\n", atacante->nome, dadoAtacante, defensor->nome, dadoDefensor);

    // REQUISITO: Se o atacante vencer, domina e transfere metade das tropas
    if (dadoAtacante > dadoDefensor) {
        printf("VITORIA DO ATAQUE! O territorio %s foi dominado pelo Exercito %s!\n", defensor->nome, atacante->cor);
        
        strcpy(defensor->cor, atacante->cor);
        
        int metade = atacante->tropas / 2;
        if (metade == 0) metade = 1; 
        
        defensor->tropas = metade;
        atacante->tropas = atacante->tropas - metade;
    } 
    // Se a defesa vencer (Print 2)
    else {
        printf("VITORIA DA DEFESA! O atacante perdeu 1 tropa.\n");
        if (atacante->tropas > 1) {
            atacante->tropas--;
        }
    }

    printf("\nPressione Enter para continuar...");
    getchar(); 
    printf("\n");
}

/* ============================================================================
 FUNCAO: Liberação de Memória (Mensagens exatas do Print 5)
 ============================================================================
 */
void liberarMemoria(Territorio* mapa, char* missao) {
    free(mapa);
    free(missao);
    printf("Encerrando o jogo...\n");
    printf("Memoria liberada com sucesso.\n");
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}