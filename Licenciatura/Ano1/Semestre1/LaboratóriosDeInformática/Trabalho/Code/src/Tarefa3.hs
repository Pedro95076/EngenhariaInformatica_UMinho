{- |

= Introdução
A tarefa 3 baseia-se na compressão máximo de um labirinto do jogo, ou seja, baseia-se
na simplificação máxima dos labirintos formados, de modo a que ocupassem o mínimo de
espaço possível, sem perder qualquer tipo de informação nele presente.
 
= Objetivos
O objetivo principal desta tarefa é atingir a compressão máxima, através da conversão 
de um labirinto para um conjunto de tuplos cujo primeiro valor é um inteiro e o segundo
uma peça. Para além disso, o somatório de todos os números inteiros deve ser igual à largura 
do labirinto e o comprimento da lista de instruções deve ser igual à altura do labirinto.

= Estratégia de Implementação
O processo de compactação de um labirinto, pode-se dividir em duas fases:

* __Compactação do labirinto horizontalmente__: nesta primeira fase, o processo começa pela
compactação de um corredor do labirito, sendo que, segundo as instruções acima, um corredor do
tipo [Wall,Wall,Wall,Empty,Food Big,Food Big,Wall] comprimido seria convertido a uma
instrução do tipo Instruct [(3,Wall),(1,Empty),(2,Food Big),(1,Wall)]. Desta forma, a soma
dos números inteiros seria igual à sua largura (7 == 3+1+2+1). Cada corredor é reduzido a um
dado deste tipo.

* __Compactação das Instruções Verticalmente__: na segunda fase, as instruções obtidas
anteriormente são compactadas verticalmente, ou seja, são identificados os corredores com peças
e posições iguais, de forma a que corredores iguais apenas consituam uma instrução, com o índice
de um elemento da lista de instruções. Nos labirintos com apenas dois corredores iguais (parede
de cima e de baixo), o último corredor será representado por Repeat 0 (repetição do corredor 0)

= Conclusão
Em suma, a concretização desta tarefa, no nosso ponto de vista, demonstrou-se bem sucedida,
considerando que foi possível atingir os objetivos propostos para esta tarefa. Importa,
ainda, referir que apesar da qualidade do código não ser a melhor, permitiu uma melhor
compressão da estratégia de compressão de labirintos.

-}

module Tarefa3 where

import Tarefa1
import Types


-- | __'compactMaze'__: main function that compresses the maze (with horizontal and vertical patterns)
compactMaze :: Maze -> Instructions
compactMaze m = reverse (aux (reverse (compactMazeHorizontal m)))
              where aux :: Instructions -> Instructions
                    aux [] = []
                    aux [x] = [x]
                    aux (h:t) = auxAC (h:t) 0 : aux t
                                where auxAC :: Instructions -> Int -> Instruction
                                      auxAC (h:t) k | elem h t == False = h
                                                    | h == last t = Repeat k
                                                    | otherwise = auxAC (init (h:t)) (k+1)


-- | __'compactMazeHorizontal'__: auxiliary function to 'compacMaze' that compresses the maze with horizontal patterns
compactMazeHorizontal :: Maze -> Instructions
compactMazeHorizontal [] = []
compactMazeHorizontal (h:t) = compactCorridor h : compactMazeHorizontal t


-- | 'compactCorridor': auxiliary function to 'compactMazeHorizontal' that compresses the corridors
compactCorridor :: Corridor -> Instruction
compactCorridor c = Instruct (aux c)
                  where aux :: Corridor -> [(Int,Piece)]
                        aux [] = []
                        aux c = (k,head c) : aux (drop k c)
                                          where k = length (g c)
                                                g [x] = [x]
                                                g (x:xs) | x==head xs = x:g xs
                                                         | otherwise = [x]