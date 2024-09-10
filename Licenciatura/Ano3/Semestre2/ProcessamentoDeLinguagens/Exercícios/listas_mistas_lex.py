import ply.lex as lex

tokens = (
    'APR',
    'FPR',
    'VIRGULA',
    'INTEIRO',
    'FLOAT',
    'BOOL',
    'PALAVRA'
)

frase = "[ 1,5, palavra, False ,3.14,  0, fim]"

t_APR = r'\['
t_FPR = r'\]'
t_VIRGULA = r','

def t_FLOAT(t):
    r'\d+\.\d+'
    t.value = float(t.value)
    return t

def t_INTEIRO(t):
    r'\d+'
    t.value = int(t.value)
    return t

def t_BOOL(t):
    r'(True|False)'
    t.value = bool(t.value)
    return t

def t_PALAVRA(t):
    r'\w+'
    t.value = str(t.value)
    return t

t_ignore = ' \n\t'

def t_error(t):
    print("Caracter ilegal: ", t.value[0])
    t.lexer.skip(1)
    
lexer = lex.lex()
lexer.input(frase)

while token := lexer.token():
    print(token)

#* Output:
'''
LexToken(APR,'[',1,0)
LexToken(INTEIRO,1,1,2)
LexToken(VIRGULA,',',1,3)
LexToken(INTEIRO,5,1,4)
LexToken(VIRGULA,',',1,5)
LexToken(PALAVRA,'palavra',1,7)
LexToken(VIRGULA,',',1,14)
LexToken(BOOL,True,1,16)
LexToken(VIRGULA,',',1,22)
LexToken(FLOAT,3.14,1,23)
LexToken(VIRGULA,',',1,27)
LexToken(INTEIRO,0,1,30)
LexToken(VIRGULA,',',1,31)
LexToken(PALAVRA,'fim',1,33)
LexToken(FPR,']',1,36)
'''