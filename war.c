#include <stdio.h>
#include <string.h>

#define TOTAL_TERRITORIOS 5

/* ============================================================================
 REQUISITO: Criação da struct Territorio
 Define um tipo de dado composto para agrupar as características de um território.
 ============================================================================
 */
struct Territorio {
    char nome[30];      // Armazena o nome do território (até 29 caracteres + '\0')
    char cor[10];       // Armazena a cor do exército dominante (até 9 caracteres + '\0')
    int tropas;         // Quantidade de tropas presentes no território
};

// Protótipo da função auxiliar para limpar o buffer do teclado
void limparBuffer();

int main() {
    /* ============================================================================
     REQUISITO: Declaração de vetor de structs
     Cria um vetor (array) capaz de armazenar 5 estruturas do tipo Territorio.
     ============================================================================
     */
    struct Territorio territorios[TOTAL_TERRITORIOS];
    int i;

    printf("==================================================\n");
    printf("   SISTEMA DE CADASTRO DE TERRITÓRIOS (WAR GAME)  \n");
    printf("==================================================\n\n");

    /* ============================================================================
     REQUISITO: Cadastro dos territórios (Entrada de dados)
     Utiliza um laço 'for' para interagir com o usuário e preencher as structs.
     ============================================================================
     */
    for (i = 0; i < TOTAL_TERRITORIOS; i++) {
        printf("--- Cadastrando o %dº Território ---\n", i + 1);
        
        // Leitura do Nome (Usando %29s para evitar estouro de buffer e garantir segurança)
        printf("Digite o nome do território: ");
        scanf("%29s", territorios[i].nome);
        limparBuffer(); // Boa prática: limpa qualquer resíduo do buffer

        // Leitura da Cor
        printf("Digite a cor do exército: ");
        scanf("%9s", territorios[i].cor);
        limparBuffer();

        // Leitura da Quantidade de Tropas
        printf("Digite a quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);
        limparBuffer();

        printf("\n"); // Quebra de linha para melhorar a usabilidade visual
    }

    /* ============================================================================
     REQUISITO: Exibição dos dados (Desempenho e Saída)
     Percorre o vetor e exibe os dados imediatamente com formatação clara.
     ============================================================================
     */
    printf("==================================================\n");
    printf("         RELATÓRIO DE TERRITÓRIOS CADASTRADOS      \n");
    printf("==================================================\n");
    
    // Formatação em formato de tabela simples para excelente legibilidade
    printf("%-5s | %-20s | %-10s | %-6s\n", "ID", "NOME DO TERRITÓRIO", "COR", "TROPAS");
    printf("--------------------------------------------------\n");

    for (i = 0; i < TOTAL_TERRITORIOS; i++) {
        printf("%-5d | %-20s | %-10s | %-6d\n", 
               i + 1, 
               territorios[i].nome, 
               territorios[i].cor, 
               territorios[i].tropas);
    }
    
    printf("==================================================\n");

    return 0;
}

/* ============================================================================
 FUNÇÃO AUXILIAR: Manutenibilidade e Robustez
 Remove os caracteres restantes no buffer de entrada (como o '\n'), evitando
 que o scanf pule as próximas leituras de dados.
 ============================================================================
 */
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}