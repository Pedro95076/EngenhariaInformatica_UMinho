import ply.lex as lex
import re

tokens = (
    'CONTENT',
    'INLINECOMMENT',
    'COMMENT'
)

states = (
    ('incomment', 'exclusive'),
)

#* COMMENT
def t_ANY_entercomment(t):
    r"\/\*"
    t.lexer.commentlevel += 1
    t.lexer.begin('incomment')
    
def t_incomment_leave(t):
    r"\*\/"
    t.lexer.commentlevel -= 1
    if t.lexer.commentlevel == 0:
        t.lexer.begin('INITIAL')

def t_incomment_COMMENT(t):
    r".+?(?=\*\/|\/\*)"
    return t

#* INLINECOMMENT
def t_INLINECOMMENT(t):
    r"//[^\n]+"
    return t

#* CONTENT
def t_CONTENT(t):
    r".+(?=\/\/|\/\*|$)"
    return t

lexer = lex.lex(reflags=re.DOTALL)
lexer.commentlever = 0

lexer.input("""           
""")

content = ""

while tok := lexer.token():
    if tok.type == 'CONTENT':
        content += tok.value
        
