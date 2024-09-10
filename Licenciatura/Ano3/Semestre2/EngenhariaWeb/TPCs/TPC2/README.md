# TPC2:

## Autor:
- A95076
- Pedro Marcelo Bogas Oliveira

## Resumo:

Neste trabalho, partindo de informacoes de cidades obtidas atraves de dados JSON fornecidos, foi produzido um servidor em nodejs, capaz de mostrar um indice de cada cidade, bem como as suas paginas individuais.

Nestas, para alem da informacao de base de cada cidade, mostra-se tambem todas as ligacoes que esta tem para as outras cidades, bem como a distancia.

Todas as paginas e o indice foram gerados atraves de scripts em python.

Gerar paginas:
```bash
python3 make_index.py
python3 make_pages.py
```

Correr servidor (porta 7777):
```bash
node server.js
```
