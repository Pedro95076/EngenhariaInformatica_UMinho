######################## Imports ########################
import json
import sys
from datetime import date
import ply.lex as lex

######################## STOCK JSON ########################
file = open("stock.json","r")  # Read and write
stockData = json.load(file)    # Load json from file

######################## MAQUINA START ########################
print("SISTEMA: Expressões com varias linhas aceites!")
print("SISTEMA: Colocar ponto final ao finalizar a expressão toda!")
print("")
print("maq: " + str(date.today()) + ", Stock carregado, Estado atualizado.")
print("maq: Bom dia. Estou disponível para atender o seu pedido.")

######################## LEX ########################
# List of TOKENS
tokens = (
   'OP',
   'EURO',
   'CENT',
   'COMMA',
   'STOP',
   'ERROR'
)

#------------ Regex ------------
# Current moneyF
global money
global moneySum  # Sum all money until a STOP appears
global currentOp # Current operation
global opRead    # Has an operation been read?
global product   # Id of product to buy

money = 0
moneySum = 0
currentOp = ""
opRead = False
product = ""

#----------------------------------------- Auxiliary Functions -----------------------------------------
# Function that resets all temporary values and sends a message to the client
def resetAndPrint(msg):
    print(msg)
    resetAllTempValues()

# Function that resets all temporary values (The read values from the expression are ignored and have no effect)
def resetAllTempValues():
    global moneySum, currentOp, opRead
    
    moneySum = 0      # Reset temporary quantity
    currentOp = ""    # Reset current operation
    opRead = False    # Reset operation verifier
    product = ""      # Reset any given selected products

# Returns a string that represents the value in euros and cents (1020 -> 10e20c)
def moneyToStr(money):
    cents = 0
    euros = 0
    finalStr = ""

    # Get euros from value
    if money >= 100:
        euros = int(money/100)
        cents = int(money%100)
        
        if(cents != 0): # Has cents and euros 
            finalStr = str(euros) + "e" + str(cents) + "c"
        else: # No cents
            finalStr = str(euros) + "e"
    else: # No euros
        cents = money
        finalStr = str(cents) + "c"
    
    return finalStr

# Function that prints all values in the json file
def printStock():
    print("""maq:\ncod | nome | quantidade |  preço\n---------------------------------""")

    # Print values from the stock
    for value in stockData['stock']:
        print(f"{value['cod']} {value['nome']} {value['quant']} {value['preco']}")

# Selects a product and buys it
def selectProduct():
    global product, money
    
    if(product != ""): 
        for value in stockData['stock']:
            if value['cod'] == product:
                if (value['preco']*100 <= money):
                    money -= value['preco']*100
                    remove_product_by_id(product)
                    print(f"maq: Pode retirar o produto dispensado \"{value['nome']}\"")
                    resetAndPrint(f"maq: Saldo = {moneyToStr(money)}")

    ## Error treatment ##
                else: 
                    resetAndPrint("maq: Saldo insufuciente para satisfazer o seu pedido")
                    print(f"maq: Saldo = {moneyToStr(money)}; Pedido = {value['preco']}")
            else: resetAndPrint("ERRO: Produto não foi encontrado! (Nenhuma ação realizada)")
    else: resetAndPrint("ERRO: Nenhum produto selecionado!")
        
# Remove product by code
def remove_product_by_id(cod):
    global stockData
    for i, product in enumerate(stockData['stock']):
        if product['cod'] == cod:
            del stockData['stock'][i]
            return True  # Removed
    return False # Not removed

#----------------------------------------- Functions -----------------------------------------
t_ignore = ' \t\r\n,' # Ready for windows 10

# Operation function
def t_OP(t):
    r'LISTAR|MOEDA|SELECIONAR|SAIR'
    global opRead, currentOp
    
    # Verify if theres only one operation
    if(opRead == False):
        opRead = True
        currentOp = t.value
    else:
        resetAndPrint("ERRO: Demasiadas operações! (Expressão rejeitada)") # Reset all temporary values

# Euro money function
def t_EURO(t):
    r'(\d+)[e|E]'
    global moneySum, opRead
    
    # Sum money if 'MOEDA' was read
    if(opRead == True):
        if(currentOp == "MOEDA"):
            value_str = t.value          # Get the euro value
            value = int(value_str[:-1])  # Remove the 'c' at the end
            
            if(value != 0):
                moneySum += value * 100  # Transform into euro
            else: resetAndPrint("ERRO: 0 euros não é permitido! (Expressão rejeitada)")   
        else: resetAndPrint("ERRO: Operação incorreta, utilizar \'MOEDA\' antes de inserir moedas! (Expressão rejeitada)")
    else: resetAndPrint("ERRO: Inserir operação \'MOEDA\' antes de inserir moedas! (Expressão rejeitada)")

# Cent money function
def t_CENT(t):
    r'(\d+)[c|C]'
    global moneySum, opRead
        
    # Sum money if 'MOEDA' was read
    if(opRead == True):
        if(currentOp == "MOEDA"):
            value_str = t.value          # Get the cents value
            value = int(value_str[:-1])  # Remove the 'c' at the end
            
            if(value != 0):
                moneySum += value # Add the cents
            else: resetAndPrint("ERRO: 0 centimos não é permitido! (Expressão rejeitada)")    
        else: resetAndPrint("ERRO: Operação incorreta, utilizar \'MOEDA\' antes de inserir moedas! (Expressão rejeitada)")
    else: resetAndPrint("ERRO: Inserir operação \'MOEDA\' antes de inserir moedas! (Expressão rejeitada)")

def t_VAR(t):
    r'[a-zA-Z]+\d+'
    global product

    product = t.value

# The end of any expression in the vending machine. Execute the expression.
def t_STOP(t):
    r'\.'
    global moneySum, money, currentOp, opRead

    # Vali operation read!
    if(opRead == True):
        # MOEDA Operation
        if(currentOp == "MOEDA"):
            if(moneySum != 0):
                # Reset all variables 
                money += moneySum # Sum current temporary quantity
                resetAndPrint("maq: Saldo = " + moneyToStr(money))
            else: resetAndPrint("ERRO: Sem nenhuma quantia a somar! (Expressão rejeitada)") 
        # LISTAR Operation
        if(currentOp == "LISTAR"):
            printStock()
            resetAllTempValues()
        # SELECIONAR Operation
        if(currentOp == "SELECIONAR"):
            selectProduct()
        # SAIR Operation
        if(currentOp == "SAIR"):
            file.close()
            fileW = open("stock.json","w")
            json.dump(stockData, fileW, indent=4, ensure_ascii=False)
            print("maq: Até à próxima")
            sys.exit()
    else: resetAndPrint("ERRO: Nenhuma operação reconhecida (Expressão rejeitada)") 

def t_error(t):
    print("Caracter nao reconhecido:'%s'" % t.value[0])
    t.lexer.skip(1)

# Build the lexer
lexer = lex.lex()

######################## LER INPUT ########################
for line in sys.stdin:
    # Give the lexer some input
    lexer.input(line)

    # Print the test
    for tok in lexer:
        print(tok)
        print(tok.type, tok.value, tok.lineno, tok.lexpos)
        
