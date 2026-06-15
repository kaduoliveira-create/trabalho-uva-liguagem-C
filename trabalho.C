/*
 ================================================================
  SISTEMA DE NOTAS E MÉDIAS DE ALUNOS
  Disciplina : Paradigmas de Linguagens de Programação
  Paradigma  : Estruturado
  Linguagem  : C
 ================================================================
*/


/* ============================================================
   BLOCO 1 — BIBLIOTECAS
   Ferramentas externas que o programa precisa importar.
   ============================================================
   stdio.h  → entrada e saída: printf, scanf, fgets, getchar
   string.h → manipulação de texto: strcpy, strcspn
   stdlib.h → utilitários gerais (boa prática incluir em C)
   ============================================================ */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/* ============================================================
   BLOCO 2 — CONSTANTES
   Valores fixos usados em todo o programa.
   Centralizar aqui facilita alterações futuras.
   ============================================================
   MAX_ALUNOS      → tamanho máximo do vetor de alunos (100)
   MAX_NOME        → caracteres máximos de um nome (com '\0')
   NUM_NOTAS       → quantas notas cada aluno possui (4)
   MEDIA_APROVACAO → nota mínima para ser aprovado (6.0)
   ============================================================ */
#define MAX_ALUNOS      100
#define MAX_NOME        80
#define NUM_NOTAS       4
#define MEDIA_APROVACAO 6.0f


/* ============================================================
   BLOCO 3 — ESTRUTURA DE DADOS
   Define o tipo "Aluno" que agrupa todos os dados de
   um único aluno em um só lugar.
   ============================================================
   nome[MAX_NOME]   → nome completo do aluno (texto)
   notas[NUM_NOTAS] → vetor com as 4 notas individuais
   media            → média calculada das 4 notas
   aprovado         → resultado: 1 = aprovado / 0 = reprovado
   ============================================================ */
typedef struct {
    char  nome[MAX_NOME];
    float notas[NUM_NOTAS];
    float media;
    int   aprovado;
} Aluno;


/* ============================================================
   BLOCO 4 — PROTÓTIPOS DAS FUNÇÕES
   Avisa ao compilador quais funções existem antes de
   ele encontrá-las no código.
   ============================================================
   Leitura e validação de dados:
     ler_alunos       → lê nome e notas do teclado
     limpar_buffer    → remove lixo do buffer de entrada

   Processamento:
     calcular_media   → calcula média de um aluno
     processar_alunos → aplica calcular_media em todos
     ordenar_por_media→ ordena do maior para o menor

   Exibição de resultados:
     exibir_listagem    → imprime tabela com todos os alunos
     exibir_estatisticas→ imprime resumo geral da turma

   Cálculos auxiliares:
     calcular_media_geral → média de toda a turma
     maior_nota           → maior nota encontrada
     menor_nota           → menor nota encontrada
   ============================================================ */
void   ler_alunos(Aluno alunos[], int *n);
void   limpar_buffer(void);
float  calcular_media(float notas[], int qtd);
void   processar_alunos(Aluno alunos[], int n);
void   ordenar_por_media(Aluno alunos[], int n);
void   exibir_listagem(const Aluno alunos[], int n);
void   exibir_estatisticas(const Aluno alunos[], int n);
float  calcular_media_geral(const Aluno alunos[], int n);
float  maior_nota(const Aluno alunos[], int n);
float  menor_nota(const Aluno alunos[], int n);


/* ============================================================
   BLOCO 5 — FUNÇÃO PRINCIPAL (main)
   Ponto de entrada do programa.
   Orquestra todas as etapas na ordem correta.
   ============================================================
   ENTRADA : nenhuma
   SAÍDA   : retorna 0 ao sistema (execução sem erros)
   ============================================================ */
int main(void) {

    /* Variáveis locais do main
       alunos[] → armazena todos os alunos do sistema
       n        → quantidade real de alunos carregados   */
    Aluno alunos[MAX_ALUNOS];
    int   n = 0;

    printf("==============================================\n");
    printf("   SISTEMA DE NOTAS E MÉDIAS DE ALUNOS\n");
    printf("==============================================\n\n");

    /* --------------------------------------------------
       ENTRADA DE DADOS
       Alunos e notas pré-carregados conforme o grupo.
       Para digitar pelo teclado, substitua este bloco
       pela chamada: ler_alunos(alunos, &n);
       -------------------------------------------------- */
    n = 4;

    strcpy(alunos[0].nome, "Thiaggo");
    alunos[0].notas[0] = 8.0f; alunos[0].notas[1] = 9.5f;
    alunos[0].notas[2] = 7.5f; alunos[0].notas[3] = 6.5f;

    strcpy(alunos[1].nome, "Ana");
    alunos[1].notas[0] = 5.0f; alunos[1].notas[1] = 4.5f;
    alunos[1].notas[2] = 6.0f; alunos[1].notas[3] = 4.0f;

    strcpy(alunos[2].nome, "Bruno");
    alunos[2].notas[0] = 5.0f; alunos[2].notas[1] = 4.5f;
    alunos[2].notas[2] = 6.0f; alunos[2].notas[3] = 4.0f;

    strcpy(alunos[3].nome, "Thalita");
    alunos[3].notas[0] = 8.0f; alunos[3].notas[1] = 9.5f;
    alunos[3].notas[2] = 7.5f; alunos[3].notas[3] = 6.5f;

    if (n == 0) {
        printf("Nenhum aluno cadastrado. Encerrando.\n");
        return 0;
    }

    /* --------------------------------------------------
       PROCESSAMENTO
       Calcula médias, define situação e ordena a lista.
       -------------------------------------------------- */
    processar_alunos(alunos, n);   /* passo 1: calcula média e aprovação */
    ordenar_por_media(alunos, n);  /* passo 2: ordena do maior ao menor  */

    /* --------------------------------------------------
       SAÍDA DE DADOS
       Exibe os resultados formatados no terminal.
       -------------------------------------------------- */
    exibir_listagem(alunos, n);      /* tabela individual dos alunos */
    exibir_estatisticas(alunos, n);  /* resumo geral da turma        */

    return 0;
}


/* ============================================================
   BLOCO 6 — FUNÇÕES DE ENTRADA
   Responsáveis por coletar dados do usuário com segurança.
   ============================================================ */

/*
 * limpar_buffer
 * -------------
 * ENTRADA : nenhuma
 * SAÍDA   : nenhuma
 * O QUE FAZ: descarta caracteres presos no buffer do teclado
 *            após um scanf, evitando leituras incorretas.
 */
void limpar_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/*
 * ler_alunos
 * ----------
 * ENTRADA : alunos[] → vetor a ser preenchido
 *           *n       → ponteiro que receberá a quantidade
 * SAÍDA   : nenhum retorno — preenche alunos[] e *n
 * O QUE FAZ: pergunta quantos alunos existem, depois
 *            coleta nome e 4 notas de cada um,
 *            rejeitando notas fora do intervalo 0–10.
 */
void ler_alunos(Aluno alunos[], int *n) {
    printf("Quantos alunos deseja cadastrar? ");
    scanf("%d", n);
    limpar_buffer();

    if (*n <= 0 || *n > MAX_ALUNOS) {
        printf("Número inválido. Permitido entre 1 e %d.\n", MAX_ALUNOS);
        *n = 0;
        return;
    }

    for (int i = 0; i < *n; i++) {
        printf("\n--- Aluno %d ---\n", i + 1);

        printf("  Nome: ");
        fgets(alunos[i].nome, MAX_NOME, stdin);
        alunos[i].nome[strcspn(alunos[i].nome, "\n")] = '\0'; /* remove '\n' */

        for (int j = 0; j < NUM_NOTAS; j++) {
            do {
                printf("  Nota %d (0,0 a 10,0): ", j + 1);
                scanf("%f", &alunos[i].notas[j]);
                limpar_buffer();

                if (alunos[i].notas[j] < 0.0f || alunos[i].notas[j] > 10.0f)
                    printf("  [ERRO] Nota fora do intervalo. Tente novamente.\n");

            } while (alunos[i].notas[j] < 0.0f || alunos[i].notas[j] > 10.0f);
        }
    }
}


/* ============================================================
   BLOCO 7 — FUNÇÕES DE PROCESSAMENTO
   Responsáveis por calcular e transformar os dados.
   ============================================================ */

/*
 * calcular_media
 * --------------
 * ENTRADA : notas[] → vetor de notas do aluno
 *           qtd     → quantidade de notas
 * SAÍDA   : float com a média aritmética
 * O QUE FAZ: soma todas as notas e divide pelo total.
 *            Função pura — não altera nenhuma variável externa.
 */
float calcular_media(float notas[], int qtd) {
    float soma = 0.0f;
    for (int i = 0; i < qtd; i++)
        soma += notas[i];
    return soma / (float)qtd;
}

/*
 * processar_alunos
 * ----------------
 * ENTRADA : alunos[] → vetor de alunos (leitura e escrita)
 *           n        → total de alunos
 * SAÍDA   : nenhum retorno — preenche media e aprovado
 * O QUE FAZ: para cada aluno, chama calcular_media e
 *            define aprovado (1) ou reprovado (0) conforme
 *            MEDIA_APROVACAO.
 */
void processar_alunos(Aluno alunos[], int n) {
    for (int i = 0; i < n; i++) {
        alunos[i].media    = calcular_media(alunos[i].notas, NUM_NOTAS);
        alunos[i].aprovado = (alunos[i].media >= MEDIA_APROVACAO) ? 1 : 0;
    }
}

/*
 * ordenar_por_media
 * -----------------
 * ENTRADA : alunos[] → vetor de alunos (leitura e escrita)
 *           n        → total de alunos
 * SAÍDA   : nenhum retorno — reorganiza alunos[] no lugar
 * O QUE FAZ: aplica Selection Sort em ordem DECRESCENTE.
 *            A cada passo encontra o maior elemento restante
 *            e o troca com a posição atual.
 */
void ordenar_por_media(Aluno alunos[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int maior_idx = i;

        for (int j = i + 1; j < n; j++)
            if (alunos[j].media > alunos[maior_idx].media)
                maior_idx = j;

        if (maior_idx != i) {
            Aluno tmp         = alunos[i];
            alunos[i]         = alunos[maior_idx];
            alunos[maior_idx] = tmp;
        }
    }
}


/* ============================================================
   BLOCO 8 — FUNÇÕES DE CÁLCULO AUXILIAR
   Calculam estatísticas gerais da turma.
   ============================================================ */

/*
 * calcular_media_geral
 * --------------------
 * ENTRADA : alunos[] → vetor somente leitura (const)
 *           n        → total de alunos
 * SAÍDA   : float com a média geral da turma
 * O QUE FAZ: soma as médias individuais e divide pelo
 *            número de alunos.
 */
float calcular_media_geral(const Aluno alunos[], int n) {
    float soma = 0.0f;
    for (int i = 0; i < n; i++)
        soma += alunos[i].media;
    return soma / (float)n;
}

/*
 * maior_nota
 * ----------
 * ENTRADA : alunos[] → vetor somente leitura (const)
 *           n        → total de alunos
 * SAÍDA   : float com a maior nota encontrada na turma
 * O QUE FAZ: varre todas as notas de todos os alunos
 *            e guarda o maior valor encontrado.
 */
float maior_nota(const Aluno alunos[], int n) {
    float max = alunos[0].notas[0];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < NUM_NOTAS; j++)
            if (alunos[i].notas[j] > max)
                max = alunos[i].notas[j];
    return max;
}

/*
 * menor_nota
 * ----------
 * ENTRADA : alunos[] → vetor somente leitura (const)
 *           n        → total de alunos
 * SAÍDA   : float com a menor nota encontrada na turma
 * O QUE FAZ: varre todas as notas de todos os alunos
 *            e guarda o menor valor encontrado.
 */
float menor_nota(const Aluno alunos[], int n) {
    float min = alunos[0].notas[0];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < NUM_NOTAS; j++)
            if (alunos[i].notas[j] < min)
                min = alunos[i].notas[j];
    return min;
}


/* ============================================================
   BLOCO 9 — FUNÇÕES DE SAÍDA
   Responsáveis por exibir os resultados no terminal.
   ============================================================ */

/*
 * exibir_listagem
 * ---------------
 * ENTRADA : alunos[] → vetor somente leitura (const)
 *           n        → total de alunos
 * SAÍDA   : nenhum retorno — imprime tabela no terminal
 * O QUE FAZ: percorre o vetor (já ordenado) e imprime
 *            posição, nome, as 4 notas, média e situação
 *            de cada aluno em colunas alinhadas.
 */
void exibir_listagem(const Aluno alunos[], int n) {
    printf("\n==============================================\n");
    printf("   LISTAGEM DE ALUNOS (ordenada por média)\n");
    printf("==============================================\n");
    printf("%-4s %-20s %6s %6s %6s %6s %7s %-12s\n",
           "Pos", "Nome", "N1", "N2", "N3", "N4", "Média", "Situação");
    printf("----------------------------------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        printf("%-4d %-20s %6.2f %6.2f %6.2f %6.2f %7.2f %-12s\n",
               i + 1,
               alunos[i].nome,
               alunos[i].notas[0], alunos[i].notas[1],
               alunos[i].notas[2], alunos[i].notas[3],
               alunos[i].media,
               alunos[i].aprovado ? "APROVADO" : "REPROVADO");
    }
    printf("----------------------------------------------------------------------\n");
}

/*
 * exibir_estatisticas
 * -------------------
 * ENTRADA : alunos[] → vetor somente leitura (const)
 *           n        → total de alunos
 * SAÍDA   : nenhum retorno — imprime resumo no terminal
 * O QUE FAZ: conta aprovados e reprovados, depois chama
 *            calcular_media_geral, maior_nota e menor_nota
 *            para exibir o resumo final da turma.
 */
void exibir_estatisticas(const Aluno alunos[], int n) {
    int aprovados  = 0;
    int reprovados = 0;

    for (int i = 0; i < n; i++) {
        if (alunos[i].aprovado) aprovados++;
        else                    reprovados++;
    }

    printf("\n==============================================\n");
    printf("         ESTATÍSTICAS DA TURMA\n");
    printf("==============================================\n");
    printf("  Total de alunos  : %d\n",   n);
    printf("  Aprovados        : %d\n",   aprovados);
    printf("  Reprovados       : %d\n",   reprovados);
    printf("  Média geral      : %.2f\n", calcular_media_geral(alunos, n));
    printf("  Maior nota       : %.2f\n", maior_nota(alunos, n));
    printf("  Menor nota       : %.2f\n", menor_nota(alunos, n));
    printf("==============================================\n");
}
