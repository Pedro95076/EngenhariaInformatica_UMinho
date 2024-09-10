{- |

= Introdução
A tarefa 1 baseia-se na geração randomizada de labirintos válidos. Para que um
labirinto seja considerado válido, o mesmo tem de seguir as seguintes diretrizes:
* O labirinto tem de ser rodeado por peças Wall (exceto no túnel);

* A faixa mais central do labirinto tem de formar um túnel;

* Todos os corredores do labirinto têm o mesmo comprimento;

* A casa dos fantasmas está localizada no centro do labirinto.

= Objetivos
Os objetivos desta tarefa passam pela implementação de um mecanismo de geração de
labirintos, através da função "generateRandoms" que recebe o número de elementos a
gerar, uma semente e produz uma lista de valores pseudo-aleatórios (entre 0 e 99),
que posteriormente serão convertidos em peças do jogo. Esta função deve contemplar
outras que permitam a geração de labirintos válidos.

= Estratégia de Implementação
A estratégia utilizada nesta tarefa foi a realização de cada uma das directrizes dos
labirintos válidos. Começou-se por adicionar as paredes que rodeam o labirinto, sendo
que posteriormente, foram criados os túneis, através de cálculos que permitissem
encontrar o centro da altura do labirinto. Para além disso, gerou-se as possíveis
hipóteses para as casas dos fantasmas e através de funções que permitissem encontrar
os locais exatos da mesma no labirinto a implementassem nesse local. Numa primeira
instância, seriam colocados os corredores que não são alterados com a introdução da
casa dos fantasmas e depois corredores apenas com a casa dos fantasmas. Através
de outras funções recursivas colocou-se nestes últimos corredores (mais pequenos 
que os iniciais) as peças que faltavam de ambos os lados, extraídas do labirinto 
completo original.

= Conclusão
Desta forma, é possível concluir que esta tarefa foi concretizada com muito sucesso, 
considerando que foi possível de implementar uma estratégia geral de implementação da
casa dos fantasmas que permite introduzi-la no local correto em qualquer labirinto,
independentemente das suas dimensões. Assim, os objetivos foram cumpridos com excelência.

-}

module Tarefa1 where

import System.Random
import Types


-- | Sample of a maze
sampleMaze :: Maze
sampleMaze = [
                [Wall, Wall, Wall, Wall, Wall, Wall, Wall, Wall],
                [Empty, Food Little, Food Little, Food Big, Food Little, Food Big, Food Little, Empty],
                [Wall, Wall, Wall, Wall, Wall, Wall, Wall, Wall]
            ]

-- | __'generateMaze'__: this function generates the maze given a width, height and a seed
generateMaze :: Int -- ^ width of the maze
               -> Int  -- ^ height of the maze
               -> Int -- ^ seed for random generation
               -> Maze
generateMaze l a s = 
    let nr = (l-2) * (a-2) 
        random = geneRandoms nr s
        pieces = numbers2pieces random
        m = list2maze (l-2) pieces
        w = (twoWalls l : m) ++ [twoWalls l]
        t = tunnel a a w
        z = verticalWalls l t
        g = ghouseposition z l
        f = firstpositions l g z
        n = lastpositions l f z
    in n


-- | __'geneRandoms'__: this function generates a list of random numbers
geneRandoms :: Int -> Int -> [Int]
geneRandoms  n seed = let gen = mkStdGen seed 
                        in take n $ randomRs (0,99) gen


-- | __'convertPiece'__: this function assigns a piece to a specific group of numbers
convertPiece :: Int -- ^ 0 <= n <= 99
                -> Piece
convertPiece n | n == 3 = Food Big
               | n >= 0 && n < 70 = Food Little
               | n >= 70 && n<= 99 = Wall


-- | __'numbers2pieces'__: this function converts random numbers into pieces
numbers2pieces :: [Int] -> [Piece]
numbers2pieces [] = []
numbers2pieces (h:t) = convertPiece h : numbers2pieces t


-- | __'list2maze'__: this function creates the corridors by spliting the whole list of pieces
list2maze :: Int -> [Piece] -> Maze
list2maze w [] = [] 
list2maze w l = 
    let (c1, r) = splitAt w l
    in c1 : list2maze w r


-- | __'twoWalls'__: this function adds the top wall and the bottom wall
twoWalls :: Int -- ^ width of the maze
          -> [Piece] -- ^ all this pieces are walls
twoWalls 0 = []
twoWalls l = Wall : twoWalls (l-1)


-- | __'verticalWalls'__: this function adds the walls along the vertical sides of the maze
verticalWalls :: Int -- ^ width of the corridor
                -> Maze -> Maze
verticalWalls l [] = []
verticalWalls l ((x:y):t) | length (x:y) < l = (((Wall:x:y) ++ [Wall]) : verticalWalls l t)
                          | otherwise = ((x:y):verticalWalls l t)
                          

-- | __'tunnel'__: this function adds the tunnel(s) 
tunnel :: Int -- ^ the maze's height
           -> Int -- ^ the maze's middle
           -> Maze -> Maze
tunnel a b l | odd  a = tunnelOdd  a b l
             | even a = tunnelEven a b l


-- | __'tunnelEven'__: auxiliary function to 'tunnel' used if the height of the maze is an even number
tunnelEven :: Int -> Int -> Maze -> Maze
tunnelEven a b ((h:hs):t) | a == (b `div` 2) + 1 = (((Empty:h:hs) ++ [Empty]) : tunnelEven (a-1) b t)
                          | a == (b `div` 2)     = (((Empty:h:hs) ++ [Empty]) : t)
                          | otherwise            = (h:hs) : (tunnelEven (a-1) b t)


-- | __'tunnelOdd'__: auxiliary function to 'tunnel' used if the height of the maze is an odd number
tunnelOdd :: Int -> Int -> Maze -> Maze
tunnelOdd a b ((h:hs):t) | a == (b `div` 2) + 1 = (((Empty:h:hs) ++ [Empty]):t)
                         | otherwise = (h:hs) : (tunnelOdd (a-1) b t)


-- | __'ghosthouse'__: this function generates the ghost's house
ghosthouse :: Int -- ^ the maze's width
              -> Maze
ghosthouse l | even l = [ 
                          [Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty],
                          [Empty, Wall, Wall, Wall, Empty, Empty, Wall, Wall, Wall, Empty],
                          [Empty, Wall, Empty, Empty, Empty, Empty, Empty, Empty, Wall, Empty],
                          [Empty, Wall, Wall, Wall, Wall, Wall, Wall, Wall, Wall, Empty],
                          [Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty]
                        ]
           | otherwise = [ 
                              [Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty],
                              [Empty, Wall, Wall, Wall, Empty, Empty, Empty, Wall, Wall, Wall, Empty],
                              [Empty, Wall, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Wall, Empty],
                              [Empty, Wall, Wall, Wall, Wall, Wall, Wall, Wall, Wall, Wall, Empty],
                              [Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty]
                           ]


-- | __'ghousecor'__: this function takes the first x corridors that don't change with the insertion of the ghost house
ghousecor :: Maze -> Maze
ghousecor l = take ((div ((length l)-5) 2)) l


-- | __'ghousecor1'__: this function drops the last x corridors that don't change with the insertion of the ghost house
ghousecor1 :: Maze -> Maze
ghousecor1 l = drop ((div ((length l)+5) 2)) l


-- | __'ghouseposition'__: this function adds the results of the last two functions 'ghousecor' and 'ghousecor1' with the one that generates the ghost house 'ghosthouse'
ghouseposition :: Maze -> Int -- ^ the maze's width
                  -> Maze
ghouseposition n l = ghousecor n ++ ghosthouse l ++ ghousecor1 n


-- | __'firstpositions'__: this function takes the first pieces of an even corridor and adds them to the places where they are missing
firstpositions :: Int -- ^ width of the maze 
                  -> Maze -- ^ maze with the ghost house
                  -> Maze -- ^ inicial maze without the ghost house
                  -> Maze
firstpositions a [] [] = []
firstpositions a (x:xs) (h:hs) | (length x) < a = ((take ((div ((length h)-(length x)) 2)) h) ++ x ): (firstpositions a xs hs)
                               | otherwise = x:(firstpositions a xs hs)


-- | __'lastpositions'__: this function takes the last pieces of the corridor and adds them to the places where they are missing
lastpositions :: Int -- ^ the maze's width
                 -> Maze -- ^ maze with the ghost house
                 -> Maze -- ^ inicial maze without the ghost house
                 -> Maze
lastpositions a [] [] = []
lastpositions a (x:xs) (h:hs) | even a && (length x) < a = (x ++ drop (div ((length h)+10) 2) h): (lastpositions a xs hs)
                              | odd a && (length x) < a = (x ++ drop (div ((length h)+11) 2) h): (lastpositions a xs hs)
                              | otherwise = x:(lastpositions a xs hs)


-- | __'printMaze'__: this function is used to show the maze in it's game state in the terminal
printMaze :: Maze -> IO ()
printMaze l = do putStrLn (printMaze' (l))


-- | __'printMaze''__ : auxiliary function to 'printMaze' that converts a maze into a string
printMaze' :: Maze -> String
printMaze' [] = ""
printMaze' (x:xs) = printCorridor x ++ printMaze' xs  


-- | __'printCorridor'__: auxiliary function to 'printMaze'' that converts a corridor into a string
printCorridor :: Corridor -> String
printCorridor [] = "\n"
printCorridor (x:xs) = show x ++ printCorridor xs                              