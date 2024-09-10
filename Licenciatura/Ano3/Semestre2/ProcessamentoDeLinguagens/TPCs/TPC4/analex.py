import re
import sys

tokens = [
    ('SELECT', r'(?i:\bSELECT\b)'),
    ('FROM', r'(?i:\bFROM\b)'),
    ('WHERE', r'(?i:\bWHERE\b)'),
    ('ID', r'\b[a-zA-Z_][a-zA-Z0-9_]*\b'),
    ('NUMERO', r'\b\d+\b'),
    ('OPERADOR', r'[=<>]'),
    ('VIRGULA', r','),
]

def analex (texto):
    res = {}
    unknown_characters = []

    while texto:
        texto = texto.lstrip()
        matched = False
        for token_name, pattern in tokens:
            match = re.match(pattern, texto)
            if match:
                token = (token_name, match.group())
                texto = texto[len(match.group()):]
                res[token] = res.get(token, 0) + 1
                matched = True
                break        
        if not matched:
            unknown_characters.append(texto[0])
            texto = texto[1:]
    
    return res, unknown_characters

def read_file(nome_ficheiro):
    with open(nome_ficheiro, 'r') as file:
        return file.read()

def main():
    contagem_tokens, unknown_characters = analex(read_file(sys.argv[1]))

    print("\nContagem de tokens:")
    for token, count in contagem_tokens.items():
        print(f"{token}: {count}")

    if unknown_characters:
        for char in unknown_characters:
            print(f"Caractere {char} desconhecido.")
main()
