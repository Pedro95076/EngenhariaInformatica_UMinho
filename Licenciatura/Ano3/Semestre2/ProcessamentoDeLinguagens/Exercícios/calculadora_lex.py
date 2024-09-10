import ply.lex as lex

tokens = (
    'NUMBER',
    'PLUS',
    'MINUS',
    'TIMES',
    'DIVIDE',
    'LPAR',
    'RPAR'
)

# Tokens definidos como expressões regulares
t_PLUS = r'\+'
t_MINUS = r'-'
t_TIMES = r'\*'
t_DIVIDE = r'/'
t_LPAR = r'\('
t_RPAR = r'\)'

# Definindo o token NUMBER como uma função
# As funções são chamadas por ordem de definição e primeiro que os tokens definidos como expressões regulares
# A primeira função que der match é a que é usada
def t_NUMBER (t):
    r'\d+'
    t.value = int(t.value) # Pois o t.value é uma string
    return t

# Ignorar caracteres de nova linha
def t_newline(t):
    r'\n+'
    t.lexer.lineno += len(t.value)

# Ignorar espaços e tabs
t_ignore = ' \t'

# Tratamento de erros
def t_error(t):
    print("Caracter ilegal: ", t.value[0])
    t.lexer.skip(1)
    
    
# Construindo o lexer  
lexer = lex.lex()
# Testando o lexer 
lexer.input("4 * (2 + 3)")

# Imprimindo os tokens
while token := lexer.token():
    print(token)

#* Output:
# LexToken(NUMBER,4,1,0)
# LexToken(TIMES,'*',1,2)
# LexToken(LPAR,'(',1,4)
# LexToken(NUMBER,2,1,5)
# LexToken(PLUS,'+',1,7)
# LexToken(NUMBER,3,1,9)
# LexToken(RPAR,')',1,10)