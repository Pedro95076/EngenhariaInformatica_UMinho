# TPC5: Máquina de Vending

## Autor:
- Pedro Marcelo Bogas Oliveira
- a95076

## Tarefas:
- Simular uma máquina de vending.
- Stock de produtos: uma lista de triplos, nome do produto, quantidade e preço.
- Persistir a lista de stock num ficheiro em JSON que é carregado no arranque do programa e é atualizado quando o programa termina.
- Usar a imaginação e criatividade e contemplar todos os cenários, por exemplo, produto inexistente ou stock vazio. 
- **(Extra)** Adicionar um comando para adicionar alguns produtos ao stock existente (produtos novos ou já existentes).

## Exemplos:
**Exemplo de stock:**
```
stock = [
 {"cod": "A23", "nome": "água 0.5L", "quant": 8, "preco": 0.7},
 ...
]
```

**Exemplos de comandos:**
```
maq: 2024-03-08, Stock carregado, Estado atualizado.
maq: Bom dia. Estou disponível para atender o seu pedido.
>> LISTAR
maq:
cod | nome | quantidade |  preço
---------------------------------
A23 água 0.5L 8 0.7
...
>> MOEDA 1e, 20c, 5c, 5c .
maq: Saldo = 1e30c
>> SELECIONAR A23
maq: Pode retirar o produto dispensado "água 0.5L"
maq: Saldo = 60c
>> SELECIONAR A23
maq: Saldo insufuciente para satisfazer o seu pedido
maq: Saldo = 60c; Pedido = 70c
>> ...
...
maq: Saldo = 74c
>> SAIR
maq: Pode retirar o troco: 1x 50c, 1x 20c e 2x 2c.
maq: Até à próxima
```
