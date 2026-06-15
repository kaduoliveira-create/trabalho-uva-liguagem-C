/*
 * SISTEMA DE NOTAS E MÉDIAS DE ALUNOS
 * Disciplina: Paradigmas de Linguagens de Programação
 * Paradigma: Estruturado
 * Linguagem: C
 *
/* -------------------------------------------------------
 * BIBLIOTECAS UTILIZADAS
 * -------------------------------------------------------
 * stdio.h  → funções de entrada e saída (printf, scanf,
 *             fgets, getchar)
 * string.h → manipulação de strings (strcpy, strcspn)
 * stdlib.h → utilitários gerais (não usado diretamente
 *             aqui, mas boa prática incluir para projetos C)
 * ------------------------------------------------------- */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* -------------------------------------------------------
 * CONSTANTES
 * -------------------------------------------------------
 * MAX_ALUNOS     → limite máximo de alunos que o programa
 *                  suporta (tamanho do vetor)
 * MAX_NOME       → tamanho máximo em caracteres do nome
 *                  de um aluno (incluindo '\0' final)
 * NUM_NOTAS      → quantidade de notas por aluno
 * MEDIA_APROVACAO→ valor mínimo de média para aprovação
 * ------------------------------------------------------- */
#define MAX_ALUNOS      100
#define MAX_NOME        80
#define NUM_NOTAS       4
#define MEDIA_APROVACAO 6.0f

/* -------------------------------------------------------
 * ESTRUTURA: Aluno
 * -------------------------------------------------------
 * Agrupa todos os dados de um aluno em um único tipo.
 *
 * Campos:
 *   nome[MAX_NOME] → vetor de caracteres com o nome
 *   notas[NUM_NOTAS] → vetor com as notas individuais
 *   media          → média aritmética das notas (calculada)
 *   aprovado       → flag de situação: 1 = aprovado,
 *                    0 = reprovado
 * ------------------------------------------------------- */
typedef struct {
    char  nome[MAX_NOME];
    float notas[NUM_NOTAS];
    float media;
    int   aprovado;
} Aluno;

/* -------------------------------------------------------
 * PROTÓTIPOS DAS FUNÇÕES
 * -------------------------------------------------------
 * Declarados antes do main para que o compilador conheça
 * as assinaturas antes de encontrar as chamadas.
 *
 * ENTRADA → parâmetros que a função recebe
 * SAÍDA   → o que a função retorna ou modifica
 *
 * void ler_alunos(Aluno[], int*)
 *   ENTRADA: vetor de Aluno (para preencher), ponteiro
 *            para inteiro n (para definir quantos alunos)
 *   SAÍDA  : preenche o vetor e atualiza *n (sem retorno)
 *
 * float calcular_media(float[], int)
 *   ENTRADA: vetor de notas e quantidade de notas
 *   SAÍDA  : float com a média aritmética calculada
 *
 * void processar_alunos(Aluno[], int)
 *   ENTRADA: vetor de Aluno e total de alunos
 *   SAÍDA  : preenche media e aprovado de cada aluno
 *
 * void ordenar_por_media(Aluno[], int)
 *   ENTRADA: vetor de Aluno e total de alunos
 *   SAÍDA  : reorganiza o vetor em ordem decrescente
 *            de média (sem retorno)
 *
 * void exibir_listagem(const Aluno[], int)
 *   ENTRADA: vetor de Aluno (somente leitura) e total
 *   SAÍDA  : imprime tabela formatada no terminal
 *
 * float calcular_media_geral(const Aluno[], int)
 *   ENTRADA: vetor de Aluno (somente leitura) e total
 *   SAÍDA  : float com a média de todas as médias
 *
 * float maior_nota(const Aluno[], int)
 *   ENTRADA: vetor de Aluno (somente leitura) e total
 *   SAÍDA  : float com o maior valor de nota encontrado
 *
 * float menor_nota(const Aluno[], int)
 *   ENTRADA: vetor de Aluno (somente leitura) e total
 *   SAÍDA  : float com o menor valor de nota encontrado
 *
 * void exibir_estatisticas(const Aluno[], int)
 *   ENTRADA: vetor de Aluno (somente leitura) e total
 *   SAÍDA  : imprime resumo geral da turma no terminal
 *
 * void limpar_buffer(void)
 *   ENTRADA: nenhuma
 *   SAÍDA  : descarta caracteres residuais do stdin
 * ------------------------------------------------------- */
void   ler_alunos(Aluno alunos[], int *n);
float  calcular_media(float notas[], int qtd);
void   processar_alunos(Aluno alunos[], int n);
void   ordenar_por_media(Aluno alunos[], int n);
void   exibir_listagem(const Aluno alunos[], int n);
float  calcular_media_geral(const Aluno alunos[], int n);
float  maior_nota(const Aluno alunos[], int n);
float  menor_nota(const Aluno alunos[], int n);
void   exibir_estatisticas(const Aluno alunos[], int n);
void   limpar_buffer(void);

/* -------------------------------------------------------
 * FUNÇÃO: main
 * -------------------------------------------------------
 * Ponto de entrada do programa. Coordena o fluxo geral:
 * carrega dados → processa → ordena → exibe resultados.
 *
 * ENTRADA: nenhuma (void)
 * SAÍDA  : int — retorna 0 ao sistema operacional
 *          indicando encerramento sem erros
 * ------------------------------------------------------- */
int main(void) {
    /* alunos[] → vetor que armazena todos os alunos
       n        → quantidade real de alunos carregados  */
    Aluno alunos[MAX_ALUNOS];
    int   n = 0;

    printf("==============================================\n");
    printf("   SISTEMA DE NOTAS E MÉDIAS DE ALUNOS\n");
    printf("==============================================\n\n");

    /* -------------------------------------------------------
     * DADOS PRÉ-CARREGADOS
     * Cada aluno recebe: nome (string) e 4 notas (float).
     * Para usar entrada pelo teclado, substitua este bloco
     * pela chamada: ler_alunos(alunos, &n);
     * ------------------------------------------------------- */
    n = 4;

    /* Aluno 0 – Thiaggo: notas 8.0, 9.5, 7.5, 6.5 */
    strcpy(alunos[0].nome, "Thiaggo");
    alunos[0].notas[0] = 8.0f; alunos[0].notas[1] = 9.5f;
    alunos[0].notas[2] = 7.5f; alunos[0].notas[3] = 6.5f;

    /* Aluno 1 – Ana: notas 5.0, 4.5, 6.0, 4.0 */
    strcpy(alunos[1].nome, "Ana");
    alunos[1].notas[0] = 5.0f; alunos[1].notas[1] = 4.5f;
    alunos[1].notas[2] = 6.0f; alunos[1].notas[3] = 4.0f;

    /* Aluno 2 – Bruno: notas 5.0, 4.5, 6.0, 4.0 */
    strcpy(alunos[2].nome, "Bruno");
    alunos[2].notas[0] = 5.0f; alunos[2].notas[1] = 4.5f;
    alunos[2].notas[2] = 6.0f; alunos[2].notas[3] = 4.0f;

    /* Aluno 3 – Thalita: notas 8.0, 9.5, 7.5, 6.5 */
    strcpy(alunos[3].nome, "Thalita");
    alunos[3].notas[0] = 8.0f; alunos[3].notas[1] = 9.5f;
    alunos[3].notas[2] = 7.5f; alunos[3].notas[3] = 6.5f;

    /* Descomente para entrada interativa pelo teclado:
       ler_alunos(alunos, &n); */

    if (n == 0) {
        printf("Nenhum aluno cadastrado. Encerrando.\n");
        return 0;
    }

    /* Etapa 1 → calcula media e define aprovado/reprovado */
    processar_alunos(alunos, n);

    /* Etapa 2 → reordena o vetor por média (maior → menor) */
    ordenar_por_media(alunos, n);

    /* Etapa 3 → imprime a tabela com a listagem ordenada */
    exibir_listagem(alunos, n);

    /* Etapa 4 → imprime estatísticas gerais da turma */
    exibir_estatisticas(alunos, n);

    return 0;
}

/* ==========================================================
 *                   IMPLEMENTAÇÕES
 * ========================================================== */

/* -------------------------------------------------------
 * FUNÇÃO: limpar_buffer
 * -------------------------------------------------------
 * Descarta todos os caracteres ainda pendentes no buffer
 * de entrada (stdin) até encontrar '\n' ou fim de arquivo.
 * Necessária após scanf para evitar que fgets leia lixo.
 *
 * ENTRADA: nenhuma
 * SAÍDA  : nenhuma (void) — efeito colateral no stdin
 * ------------------------------------------------------- */
void limpar_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/* -------------------------------------------------------
 * FUNÇÃO: ler_alunos
 * -------------------------------------------------------
 * Solicita ao usuário a quantidade de alunos e coleta
 * nome e notas de cada um via teclado, com validação.
 *
 * ENTRADA:
 *   alunos[] → vetor de Aluno a ser preenchido
 *   *n       → ponteiro para inteiro; receberá a
 *              quantidade de alunos digitada
 * SAÍDA  : nenhum retorno — modifica alunos[] e *n
 *          diretamente (passagem por ponteiro/referência)
 * ------------------------------------------------------- */
void ler_alunos(Aluno alunos[], int *n) {
    printf("Quantos alunos deseja cadastrar? ");
    scanf("%d", n);          /* *n recebe o valor digitado */
    limpar_buffer();

    /* Valida se o número está dentro do intervalo permitido */
    if (*n <= 0 || *n > MAX_ALUNOS) {
        printf("Número inválido. Permitido entre 1 e %d.\n", MAX_ALUNOS);
        *n = 0;
        return;
    }

    for (int i = 0; i < *n; i++) {
        printf("\n--- Aluno %d ---\n", i + 1);

        printf("  Nome: ");
        fgets(alunos[i].nome, MAX_NOME, stdin);
        /* Remove o '\n' que fgets inclui no final da string */
        alunos[i].nome[strcspn(alunos[i].nome, "\n")] = '\0';

        /* Loop de leitura de notas com rejeição de valores inválidos */
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

/* -------------------------------------------------------
 * FUNÇÃO: calcular_media
 * -------------------------------------------------------
 * Soma todos os elementos do vetor de notas e divide
 * pela quantidade. Função pura: não altera nenhuma
 * variável externa, depende apenas dos parâmetros.
 *
 * ENTRADA:
 *   notas[] → vetor de float com as notas do aluno
 *   qtd     → int com a quantidade de notas no vetor
 * SAÍDA  : float — média aritmética calculada
 * ------------------------------------------------------- */
float calcular_media(float notas[], int qtd) {
    float soma = 0.0f;
    for (int i = 0; i < qtd; i++)
        soma += notas[i];        /* acumula a soma das notas */
    return soma / (float)qtd;   /* divide pelo total → média */
}

/* -------------------------------------------------------
 * FUNÇÃO: processar_alunos
 * -------------------------------------------------------
 * Percorre o vetor de alunos e, para cada um, chama
 * calcular_media e define o campo aprovado com base
 * em MEDIA_APROVACAO.
 *
 * ENTRADA:
 *   alunos[] → vetor de Aluno (leitura e escrita)
 *   n        → int com o total de alunos
 * SAÍDA  : nenhum retorno — preenche alunos[i].media
 *          e alunos[i].aprovado para cada i
 * ------------------------------------------------------- */
void processar_alunos(Aluno alunos[], int n) {
    for (int i = 0; i < n; i++) {
        /* Calcula e armazena a média individual */
        alunos[i].media = calcular_media(alunos[i].notas, NUM_NOTAS);

        /* Operador ternário: 1 se aprovado, 0 se reprovado */
        alunos[i].aprovado = (alunos[i].media >= MEDIA_APROVACAO) ? 1 : 0;
    }
}

/* -------------------------------------------------------
 * FUNÇÃO: ordenar_por_media
 * -------------------------------------------------------
 * Ordena o vetor de alunos em ordem DECRESCENTE de média
 * usando o algoritmo Selection Sort:
 *   - a cada iteração externa, encontra o maior elemento
 *     restante e o troca com a posição atual.
 *
 * ENTRADA:
 *   alunos[] → vetor de Aluno (leitura e escrita)
 *   n        → int com o total de alunos
 * SAÍDA  : nenhum retorno — reorganiza alunos[] in-place
 * ------------------------------------------------------- */
void ordenar_por_media(Aluno alunos[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int maior_idx = i;          /* assume posição i como maior */

        /* Busca o maior entre os elementos restantes */
        for (int j = i + 1; j < n; j++) {
            if (alunos[j].media > alunos[maior_idx].media)
                maior_idx = j;
        }

        /* Troca apenas se encontrou um maior */
        if (maior_idx != i) {
            Aluno tmp         = alunos[i];       /* cópia temporária */
            alunos[i]         = alunos[maior_idx];
            alunos[maior_idx] = tmp;
        }
    }
}

/* -------------------------------------------------------
 * FUNÇÃO: exibir_listagem
 * -------------------------------------------------------
 * Imprime no terminal uma tabela formatada com todos os
 * alunos na ordem em que estão no vetor (já ordenado).
 *
 * ENTRADA:
 *   alunos[] → vetor de Aluno somente leitura (const)
 *   n        → int com o total de alunos
 * SAÍDA  : nenhum retorno — produz saída no terminal
 * ------------------------------------------------------- */
void exibir_listagem(const Aluno alunos[], int n) {
    printf("\n==============================================\n");
    printf("   LISTAGEM DE ALUNOS (ordenada por média)\n");
    printf("==============================================\n");

    /* Cabeçalho da tabela com larguras fixas (%-Ns = alinhar à esquerda) */
    printf("%-4s %-20s %6s %6s %6s %6s %7s %-12s\n",
           "Pos", "Nome", "N1", "N2", "N3", "N4", "Média", "Situação");
    printf("----------------------------------------------------------------------\n");

    /* Uma linha por aluno com posição, nome, notas, média e situação */
    for (int i = 0; i < n; i++) {
        printf("%-4d %-20s %6.2f %6.2f %6.2f %6.2f %7.2f %-12s\n",
               i + 1,
               alunos[i].nome,
               alunos[i].notas[0],
               alunos[i].notas[1],
               alunos[i].notas[2],
               alunos[i].notas[3],
               alunos[i].media,
               alunos[i].aprovado ? "APROVADO" : "REPROVADO");
    }
    printf("----------------------------------------------------------------------\n");
}

/* -------------------------------------------------------
 * FUNÇÃO: calcular_media_geral
 * -------------------------------------------------------
 * Soma as médias individuais de todos os alunos e divide
 * pelo total, obtendo a média geral da turma.
 *
 * ENTRADA:
 *   alunos[] → vetor de Aluno somente leitura (const)
 *   n        → int com o total de alunos
 * SAÍDA  : float — média geral da turma
 * ------------------------------------------------------- */
float calcular_media_geral(const Aluno alunos[], int n) {
    float soma = 0.0f;
    for (int i = 0; i < n; i++)
        soma += alunos[i].media;   /* soma das médias individuais */
    return soma / (float)n;        /* divide pelo nº de alunos */
}

/* -------------------------------------------------------
 * FUNÇÃO: maior_nota
 * -------------------------------------------------------
 * Percorre TODAS as notas de TODOS os alunos e rastreia
 * o maior valor encontrado.
 *
 * ENTRADA:
 *   alunos[] → vetor de Aluno somente leitura (const)
 *   n        → int com o total de alunos
 * SAÍDA  : float — maior nota individual da turma
 * ------------------------------------------------------- */
float maior_nota(const Aluno alunos[], int n) {
    float max = alunos[0].notas[0];   /* inicializa com a 1ª nota */
    for (int i = 0; i < n; i++)
        for (int j = 0; j < NUM_NOTAS; j++)
            if (alunos[i].notas[j] > max)
                max = alunos[i].notas[j];  /* atualiza se for maior */
    return max;
}

/* -------------------------------------------------------
 * FUNÇÃO: menor_nota
 * -------------------------------------------------------
 * Percorre TODAS as notas de TODOS os alunos e rastreia
 * o menor valor encontrado.
 *
 * ENTRADA:
 *   alunos[] → vetor de Aluno somente leitura (const)
 *   n        → int com o total de alunos
 * SAÍDA  : float — menor nota individual da turma
 * ------------------------------------------------------- */
float menor_nota(const Aluno alunos[], int n) {
    float min = alunos[0].notas[0];   /* inicializa com a 1ª nota */
    for (int i = 0; i < n; i++)
        for (int j = 0; j < NUM_NOTAS; j++)
            if (alunos[i].notas[j] < min)
                min = alunos[i].notas[j];  /* atualiza se for menor */
    return min;
}

/* -------------------------------------------------------
 * FUNÇÃO: exibir_estatisticas
 * -------------------------------------------------------
 * Conta aprovados e reprovados e imprime o resumo geral
 * da turma chamando as funções de cálculo auxiliares.
 *
 * ENTRADA:
 *   alunos[] → vetor de Aluno somente leitura (const)
 *   n        → int com o total de alunos
 * SAÍDA  : nenhum retorno — produz saída no terminal
 * ------------------------------------------------------- */
void exibir_estatisticas(const Aluno alunos[], int n) {
    int aprovados  = 0;
    int reprovados = 0;

    /* Conta situação de cada aluno pelo campo aprovado */
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

