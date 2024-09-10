/**
 * @file parser.h Ficheiro que contém as funções referentes ao parser.
 */
#include <stdlib.h>

/**
 * @brief Tipo Enum que enumera os tipos de variáveis possíveis
 */
typedef enum {
    LONG   = 1,    /**< Define o tipo LONG */
    DOUBLE = 2,    /**< Define o tipo DOUBLE */
    CHAR   = 4,    /**< Define o tipo CHAR */
    STRING = 8,    /**< Define o tipo STRING */
    ARRAY  = 16,   /**< Define o tipo ARRAY */
    BLOCO  = 32,   /**< Define o tipo BLOCO */
} TIPO;

/**
 * @brief Estrutura de Dados que define o tipo DADOS
 */
typedef struct {
    TIPO    tipo;           /**< Define o tipo da estrutura de dados */
    union {
        long   vl;          /**< Contém o valor da variável caso esta seja do tipo long */
        double vd;          /**< Contém o valor da variável caso esta seja do tipo double */
        char   vc;          /**< Contém o valor da variável caso esta seja do tipo char */
        char  *vs;          /**< Contém o valor da variável caso esta seja do tipo string */
        struct stack *va;   /**< Contém o valor da variável caso esta seja do tipo array */
        struct stack *vb;   /**< Contém o valor da variável caso esta seja do tipo bloco */
    } data;                 /**< Union que contém todos os tipos possíveis */
} DADOS;

/**
 * @brief Estrutura de Dados que define a Stack
 */
typedef struct stack{
    DADOS *comp;   /**< Define o tipo de dados presente na stack */
    int count;     /**< Variável que conta o número de elementos da stack */
    int size;      /**< Variável que guarda o tamanho da stack */
} STACK;

void parser(char *line, STACK *stack, STACK *stackPointer[]);
STACK *novaStack();
void parserArrBlo(char *token, STACK *stackPointer[], int *flag, int *bloco, STACK *addressBloco);
void criarArray(STACK *stackPointer[],  int *flag);
void iniciarStack(STACK *stack);
void criarBloco(STACK *stackPointer[],  int *flag, STACK *addressBloco);
void blocoOperations(char *token, STACK *stackPointer[], int *flag, int *bloco, STACK *addressBloco);
void decideOperations(char *token, STACK *stackPointer[], int *flag, int *bloco, STACK *addressBloco);
int parserOperations(char *token, STACK *stackPointer[], int *flag);
void arrayOperations(char *token, STACK *stackPointer[], int *flag);
void criarString(char *token, STACK *stackPointer[], int *flag);
void atribuicao(DADOS *variaveis);
void PRINT_STACK(STACK *stack);
void PRINT_DADOS (DADOS P);
void PRINT_BLOCO(STACK *stack);
long POPL(STACK *stack);
double POPD(STACK *stack);
char POPC(STACK *stack);
char *POPS(STACK *stack);
DADOS POP(STACK *stack);
DADOS TOP(STACK *stack);
void PUSHL(STACK *stack, long x);
void PUSHD(STACK *stack, double x);
void PUSHC(STACK *stack, char x);
void PUSHS(STACK *stack, char *x);
void PUSHA(STACK *stack, STACK *array);
void PUSHB(STACK *stack, STACK *bloco);
void PUSH(STACK *stack, DADOS P);
int somaTiposTop(STACK *stack);
int areNumbers(STACK *stack);
void realocarM (STACK *stack);
int soma(STACK *stack);
int concatenarStrings(STACK *stack);
int concatena2Strings(STACK *stack);
int concatenaCharString(STACK *stack);
int subtracao(STACK *stack);
int multiplicacao(STACK *stack);
int replicateString(STACK *stack);
int divisao(STACK *stackPointer[], int *flag);
int incrementar(STACK *stack);
int decrementar(STACK *stack);
int restoDivInt(STACK *stack);
int exponenciacao(STACK *stack);
int searchSubstring(STACK *stack);
int and(STACK *stack);
int or(STACK *stack);
int xor(STACK *stack);
int not(STACK *stack);
int conjuncao(STACK *stack);
int disjuncao(STACK *stack);
int duplicar(STACK *stack);
int lastOut(STACK *stack);
int switchTwo(STACK *stack);
int rotateThree(STACK *stack);
int copyN(STACK *stack);
int convInteiro(STACK *stack);
int convDouble(STACK *stack);
int convCaracter(STACK *stack);
int lerLinha(STACK *stack);
int lerTudo(STACK *stack);
int igual(STACK *stack);
int indexStrings(STACK *stack);
void range(STACK *stackPointer[], int *flag);
int nao(STACK *stack);
int menorDe2(STACK *stack);
int maiorDe2(STACK *stack);
int ifThenElse(STACK *stack);
int variableTeste (char *token);
int twoPointsTeste (char *token);
void variableOut (STACK *stackPointer[], char *token, DADOS variaveis[26], int *flag, int *bloco, STACK *addressBloco);
void variableIn (STACK *stackPointer[], char *token, DADOS variaveis[26], int *flag);
int menor(STACK *stack);
int menorChar(STACK *stack);
int firstChars(STACK *stack);
int maior(STACK *stack);
int maiorChar(STACK *stack);
int lastChars(STACK *stack);
int aritmeticas(char *token, STACK *stackPointer[], int *flag);
int logicas(char *token, STACK *stack);
int opStack(char *token, STACK *stack);
int convertions(char *token, STACK *stack);
int comparison(char *token, STACK *stack);
void stringOperations(char *token, STACK *stackPointer[], int *flag);
void aritArrayOperations (char *token, STACK *stackPointer[], int *flag);
void elemArrayOperations (char *token, STACK *stackPointer[], int *flag);
void arrayToStack(STACK *stack, STACK *array);
void size(STACK *stack, STACK *array);
void indexArray(STACK *stack, STACK *array);
void replicate(STACK *stackPointer[], int *flag);
void removeFirst(STACK *stackPointer[], int *flag);
void removeLast(STACK *stackPointer[], int *flag);
void firstElements(STACK *stackPointer[], int *flag);
void lastElements(STACK *stackPointer[], int *flag);
void concatenarArrays(STACK *stackPointer[], int *flag);
void concatenaArrNum(STACK *stackPointer[], int *flag);
void concatenaResto(STACK *stackPointer[], int *flag);
void concatenaNumArr (STACK *array, STACK *stackPointer[], int *flag, DADOS P);
void concatenaArrArr (STACK *array, STACK *stackPointer[], int *flag, DADOS P);
int stringSize(STACK *stack);
void executaBloco(STACK *stackPointer[], int *flag, int *bloco, STACK *adressBloco);
void aplicaBloco(STACK *stackPointer[], int *flag, STACK *addressBloco);
void foldBloco(STACK *stackPointer[], int *flag);
void filtraBloco(STACK *stackPointer[], int *flag);
void ordenaBloco(STACK *stackPointer[], int *flag);
void selSort (long v[], int n, DADOS s[]);
void swapL (long v[], int i, int j);
void swapD (DADOS v[], int i, int j);
void spaces(STACK *stackPointer[], int *flag);
void newline(STACK *stackPointer[], int *flag);
int divideString(STACK *stackPointer[], int *flag);
