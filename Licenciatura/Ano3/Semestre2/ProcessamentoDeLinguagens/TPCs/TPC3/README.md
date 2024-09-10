# TPC2: Somador ON/OFF

## Autor:
- A95076
- Pedro Marcelo Bogas Oliveira

## Resumo

Neste trabalho foi proposta a criação de um programa que soma todas as sequências de dígitos encontradas num texto, quando um contador estava ligado. 
- Quando se encontrasse a string "On" (em qualquer combinação de maiúsculas ou minúsculas), o contado era desativado.
- Sempre que se encontrasse a string "Off" (em qualquer combinação de maiúsculas ou minúsculas), o contador era desligado. 
- Sempre que se encontrasse o caractér "=", o resultado da soma era colocado no stdout
- Sempre que se encontrasse um número esse número era somado ao total

O script [**somador_on_off**](somador_on_off.py) em python, lê as linhas de um ficheiro passado como arguemento. Utiliza a expressão regular `([Oo][Nn]|[Oo][Ff][Ff]|=|[-+]?\d+)` e a função findall, obtém-se uma lista com as expressões referidas acima, por ordem de ocorrência. Depois basta aplicar, para cada elemento da lista, a operação correspondente.
