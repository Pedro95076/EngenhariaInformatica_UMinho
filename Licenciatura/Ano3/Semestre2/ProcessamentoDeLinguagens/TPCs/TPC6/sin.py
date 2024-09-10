# Imports
from lexico import lexer

simbol = ('Erro', '', 0, 0)

# Print do erro
def parserError(s):
    print("Erro sintatico: ", s)

############################################################################################################
# Reconhcer terminais
def rec_term(simb):
    global simbol
    if simbol.type == simb:
        simbol = lexer.token() # Proximo simbolo
    else:
        parserError(simb) # Terminal nao reconhecido

# Reconhecer elementos var | num
def rec_elem():
    global simbol
    if simbol.type == 'VAR' or simbol.type == 'NUM':
        print("Reconheci p8, valor=\'" +  str(simbol.value) + '\'')
        simbol = lexer.token() # Proximo simbolo
    else: 
        parserError("elem nao reconhecido")

# Reconhecer operações '+' | '-' | '*' | '/'
def rec_op():
    global simbol
    if (simbol.type == 'SUM' or simbol.type == 'DIV' or simbol.type == 'MUL' or simbol.type == 'SUB'):
        print("Reconheci p9, valor=\'" + str(simbol.value) + '\'')
        simbol = lexer.token() # Proximo simbolo
    else: 
        parserError("op nao reconhecido")

############################################################################################################
# Reconhcer expressão
def rec_expr(): # Op body
    if (simbol.type == 'SUM' or simbol.type == 'DIV' or simbol.type == 'MUL' or simbol.type == 'SUB'):
        rec_op()
        rec_body()
        print("Reconheci p6")
    else:
        print("Reconheci p7")

# Reconhecer corpo
def rec_body():
    global simbol
    
    # Reconhecer Expressao com parentesis '(' Content ')'
    if (simbol.type == 'LPAREN'):
        rec_term('LPAREN')
        rec_body()
        rec_term('RPAREN')
        print("Reconheci p4")
    else: # Elem expr
        rec_elem()
        rec_expr()
        print("Reconheci p5")

# Reconhecer start
def rec_start():
    global simbol

    # Verificar o token do incio da linha
    if (simbol.type == 'INPUT'): # ?Var
        rec_term('INPUT')
        rec_term('VAR')
        print("Reconheci p1")
    elif (simbol.type == 'PRINT'): # !Expr
        rec_term('PRINT')
        rec_body()
        print("Reconheci p2")
    elif (simbol.type == 'VAR'): # Var = Expr
        rec_term('VAR')
        rec_term('EQ')
        rec_body()
        print("Reconheci p3")
    else:
        parserError(simbol) # Inicio da linha nao reconhecido

# Iterar tudo
def parser(data):
    global simbol

    print("Parser start")

    # Obter o proximo token
    lexer.input(data)
    simbol = lexer.token()
    rec_start()

    print("Finish")

linha = input("Insert expression: ")
parser(linha)