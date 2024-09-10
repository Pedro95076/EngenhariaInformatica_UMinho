import ply.lex as lex

tokens = (
    'TAG', # pessoa
    'ATAG', # <
    'FTAG', # >
    'ATAGF', # </
    'CONTEUDO', # Maira / 32
)

#* Vamos falar de condições e estados (dependendo do estado, o tratamento será diferente):
# Por exemplo, Maria será conteúdo, mas pessoa será tag.
"""
states = (
    ('intag', 'exclusive'), # exclusive: só pode estar em um estado por vez
                            # inclusive: pode estar em dois estados ao mesmo tempo 
    # Estado inicial chama-se INITIAL   
)
"""
states = (
    ('intaga', 'exclusive'), # ex: <pessoa>
    ('intagf', 'exclusive'), # ex: </pessoa>
)

def t_ATAGF(t):
    r"</"
    t.lexer.begin('intagf') # Muda para o estado intag
    return t

def t_ATAG(t):
    r"<"
    t.lexer.begin('intaga') # Muda para o estado intag
    return t

def t_intaga_intagf_FTAG(t):
    r">"
    t.lexer.begin('INITIAL') # Muda para o estado INITIAL, saindo do intag
    return t

def t_intaga_TAG(t): # Só vai ser chamda de o estado estiver em intag
    r"\w+"
    t.lexer.tag.append(t.value)
    return t

def t_intagf_TAG(t): # Só vai ser chamda de o estado estiver em intag
    r"\w+"
    correct_tag = t.lexer.tag.pop()
    if t.value == correct_tag:
        return t
    raise ValueError(f"Tag de fechamento {t.value} não esperada")

def t_CONTEUDO(t):
    r"[^<]+" # Qualquer coisa que não seja <
    return t

def t_ANY_error(t): # ANY: Para ser utilizado em qualquer estado
    print(f"Caracter inválido: {t.value[0]}")
    t.lexer.skip(1)

t_ANY_ignore = " \n\t" # ANY: Para ser utilizado em qualquer estado

lexer = lex.lex()
lexer.tag = []

file = """
<pessoa>                                                                                                                                                                    ─╯
    <nome>Maria</nome>
    <idade>32</idade>
</pessoa>
"""

lexer.input(file)

while True:
    tok = lexer.token()
    if not tok:
        break
    print(tok)
    