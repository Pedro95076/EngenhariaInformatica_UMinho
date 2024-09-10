######################## Imports ########################
import sys
import ply.lex as lex

######################## LEX ########################
# List of TOKENS
tokens = (
   'INPUT',  # ?
   'PRINT',  # !
   'EQ',     # =
   'MUL',    # *
   'DIV',    # /
   'SUM',    # +
   'SUB',    # -
   'LPAREN', # (
   'RPAREN', # )
   'NUM',    # 897132
   'VAR',    # a
)

t_INPUT = r'\?'
t_PRINT = r'!'
t_EQ = r'='
t_MUL = r'\*'
t_DIV = r'/'
t_SUM = r'\+'
t_SUB = r'-'
t_LPAREN = r'\('
t_RPAREN = r'\)'
t_NUM = r'[1-9]+'
t_VAR = r'[a-zA-Z]+'

#----------------------------------------- Functions -----------------------------------------
t_ignore = ' \t\r\n' # Ready for windows 10

def t_error(t):
    print("Caracter nao reconhecido:'%s'" % t.value[0])
    t.lexer.skip(1)

def t_eof(t):
    r'$'
    t.value = None

# Build the lexer
lexer = lex.lex()
