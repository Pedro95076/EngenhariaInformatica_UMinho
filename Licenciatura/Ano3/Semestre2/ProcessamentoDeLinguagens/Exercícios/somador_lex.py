import ply.lex as lex
import re

tokens = (
    'ON',
    'OFF',
    'NUMBER',
    'EQUALS'
)

states = (
    #*INITIAL
    ('counton', 'inclusive'), # expandem com as regras do estado inicial
    ('countoff', 'inclusive')  # expandem com as regras do estado inicial  
)

#* ON 
def t_ON(t):
    # r"[Oo][Nn]""
    # r"(?i:on)"
    # Ou com o: lexer = lex.lex(reflags=re.I)
    r"on"
    t.lexer.begin('counton')
    return t

#* OFF
def t_OFF(t):
    r"of"
    t.lexer.begin('countoff')
    return t

#* EQUALS
def t_EQUALS(t):
    r"="
    print("Soma: " + str(t.lexer.soma))
    return t

#* NUMBER
def t_counton_NUMBER(t):
    r"-?\d+"
    t.lexer.soma += int(t.value)
    return t

def t_countoff_NUMBER(t):
    r"-?\d+"
    return t

def t_qualqueroutracoisa(t):
    r".+?"
    pass

t_ignore = " \n"

def t_error(t):
    #print("Caracter ilegal: ", t.value[0])
    t.lexer.skip(1)

lexer = lex.lex(reflags=re.I)
lexer.begin('counton')
lexer.soma = 0 

lexer.input("on 1 2 off 3 6 on 7 =")
for tok in lexer:
    pass