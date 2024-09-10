#define Max 10

struct staticStack {
	int sp; // tamanho da stack - sp = stack pointer
	int values [Max];
};
typedef struct staticStack *SStack;

struct dinStack {
	int size; // tamanho total / capacidade de memoória da struct
	int sp; // tamanho da stack em cada momento - sp = stack pointer
	int *values;
};
typedef struct dinStack *DStack;

void SinitStack (SStack s);
int  SisEmpty (SStack s);
int  Spush (SStack s, int x);
int  Spop (SStack s, int *x);
int  Stop (SStack s, int *x);
void ShowSStack (SStack s);

void DinitStack (DStack s);
int  DisEmpty (DStack s);
int  Dpush (DStack s, int x);
int  Dpop (DStack s, int *x);
int  Dtop (DStack s, int *x);
void ShowDStack (DStack s);
