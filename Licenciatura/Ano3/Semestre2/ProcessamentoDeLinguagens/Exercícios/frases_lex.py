import ply.lex as lex

tokens = (
    'PALAVRA',
    'VIRGULA',
    'PONTOFINAL',
    'PONTOEXCL',
    'PONTOINTR',
    'RETICENCIAS'
)

# Tokens definidos como expressões regulares
t_PALAVRA = r'\w+'
t_VIRGULA = r','
t_PONTOFINAL = r'\.'
t_PONTOEXCL = r'!'
t_PONTOINTR = r'\?'
t_RETICENCIAS = r'\.\.\.'

# Ignorar espaços e tabs
t_ignore = ' \n\t'

# Tratamento de erros
def t_error(t):
    print("Caracter ilegal: ", t.value[0])
    t.lexer.skip(1)
    
# Exemplo
lexer = lex.lex()
lexer.input("O rato roeu a roupa do rei de roma.")
while token := lexer.token():
    print(token)

#* Output:
# LexToken(PALAVRA,'O',1,0)
# LexToken(PALAVRA,'rato',1,2)
# LexToken(PALAVRA,'roeu',1,7)
# LexToken(PALAVRA,'a',1,12)
# LexToken(PALAVRA,'roupa',1,14)
# LexToken(PALAVRA,'do',1,20)
# LexToken(PALAVRA,'rei',1,23)
# LexToken(PALAVRA,'de',1,27)
# LexToken(PALAVRA,'roma',1,30)
# LexToken(PONTOFINAL,'.',1,34)
