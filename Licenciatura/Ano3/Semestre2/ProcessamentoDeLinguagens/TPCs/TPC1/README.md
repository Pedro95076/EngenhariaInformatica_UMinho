# TPC1: Análise de um dataset

## Autor

**Nome:** Pedro Marcelo Bogas Oliveira

**id:** A95076

## Enunciado

O trabalho proposto requer o desenvolvimento de um programa em **Python** que seja capaz de processar um conjunto de dados apresentado em formato **CSV**, sem a utilização do módulo CSV, a fim de realizar uma série de análises específicas. As análises solicitadas incluem:

1. Geração de uma lista ordenada alfabeticamente das modalidades desportivas presentes no conjunto de dados.

2. Cálculo das percentagens de atletas aptos e inaptos para a prática desportiva, com base nas informações disponíveis no dataset.

3. Análise da distribuição dos atletas por escalão etário. Cada escalão corresponde a um intervalo de 5 anos, por exemplo, [30-34], [35-39], e assim por diante.

Para atingir esses objetivos, espera-se que o programa seja capaz de processar os dados do arquivo CSV diretamente, sem a utilização de bibliotecas ou módulos específicos para essa finalidade. O programa deve ser capaz de realizar as análises mencionadas de forma precisa e eficiente, fornecendo resultados claros e bem estruturados.

## Resumo

1. Começo por ler o ficheiro **.csv** a partir do **stdin**;
2. A verificação das modalidades presentes no ficheiro é realizada a partir de uma observação global das linhas do ficheiro, guardando numa lista as novas modalidades encontradas;
3. Para verificar a percentagem de atletas aptos e não aptos, foi verificada cada linha do ficheiro e, por cada True ou False na respetiva coluna, foi incrementado o valor nas variáveis usadas para guardar o número de atletas de cada categoria. No final foi calculada a percentagem.
4. Por fim, para a distribuição dos atletas pelas idades, criei uma array de **ints** e, ao percorrer os dados, divido a idade do mesmo por 5 e incremento 1 na posição equivalente ao resultado obtido na divisão. De seguida, calculo as percentagens para a distribuição.
