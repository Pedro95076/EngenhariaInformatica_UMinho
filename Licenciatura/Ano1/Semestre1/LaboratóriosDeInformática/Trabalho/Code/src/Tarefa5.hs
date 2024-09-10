{- |

= Introdução
A tarefa 5 baseia-se na implementação da movimentação e comportamento dos jogadores
fantasmas. É, desta forma, necessária a implementação da movimentação dos fantasmas
na tarefa 2 e em cada instante, é necessário ter em consideração o estado de cada
fantasma. Deverão ser implementadas duas funções "chaseMode" e "scatterMode", nas quais
se recebe um estado do jogo e um identificador de fantasma de modo a devolver o
um (Move identificador orientacao), necessário na implementãção de uma jogada "Play".

= Objetivos
Para a concretização desta tarefa, pretende-se que o comportamento normal, no qual o
fantasma se encontra em modo /Alive/, seja perseguir o Pacman. Caso o fantasma esteja em
modo /Dead/, este deve fugir ao Pacman em modo Mega até que voltar a estar em modo /Alive/.
Adicionalmente, sempre que os fantasmas passem para o modo /Dead/, estes devem obter uma
orientação oposta à que tinha no momento anterior. Para isto, é necessária a implementação
da função "ghostPlay" que recebe um estado de jogo e devolve um conjunto de jogadas, uma
para cada fantasma, com a melhor alternativa de reação ao Pacman.

= Estratégia de Implementação
As estratégias utilizadas nesta tarefa, são as seguintes:

* __Fantasmas (/Alive/) em perseguição do Pacman__: quando um fantasma se deparar com um muro,
este irá determinar a posição do Pacman, sendo que o fantasma irá na direção mais próxima
do Pacman. Por exemplo: o fantasma encontra um muro na posição imediatamente acima da sua - 
se o Pacman se encontrar abaixo, o fantasma seguirá essa direção, utilizando esta estratégia
para as outras direções. Para além desta estratégia, colocou-se a hipótese do fantasma se
encontrar entre duas paredes, tendo sido contemplada esta opção no código abaixo. Neste caso,
o fantasma muda de direção antes de ficar encurralado.

* __Fantasmas (/Dead/) fogem do Pacman (Mega)__: quando o fantasma se depara com uma parede, este
move-se para a sua direita, circulando a área onde se encontra no sentido dos ponteiros de
relógico, tal como mencionado acima. Esta estratégia foi conseguida através da função "scatterMode" 
que sempre que muda a direção dos fantasmas como descrito.

= Conclusão
Em geral, conclui-se que esta tarefa foi implementada com sucesso e que os objetivos foram
todos cumpridos com excelência. Mais uma vez a qualidade do código poderia melhorar, mas o 
foco desta tarefa foi implementar duas estratégias que complicassem o jogo e, ao mesmo tempo,
que permitissem ao jogador Pacman criar uma estratégia para tentar prever os movimentos dos 
fantasmas e, desta forma, ganhar o jogo.

-}

module Tarefa5 where 

import Types
import Tarefa1
import Tarefa2
import Tarefa6


-- | __'chaseMode'__: This function gives movements to the ghosts so that they chase Pacman
chaseMode :: State 
          -> Int -- ^ The ID of the ghost that will be moved
          -> Play
chaseMode (State x@(y:ys) ((Pacman (PacState (id,(a,b),v,o,p,vi) t m k)):(Ghost (GhoState (id',(a',b'),v',o',p',vi') q)):z) l) i | id'== i && (a',b') == middleMaze x || (a'+1,b') == middleMaze x || (a',b'+1) == middleMaze x || (a'+1,b'+1) == middleMaze x || (a',b'-1) == middleMaze x || (a'-1,b'-1) == middleMaze x = (Move id' U)  -- This case is for the ghost to get out of the ghosts' house and doesn't stay inside
                                                                                                                                 | id'== i && ( (a' == div (length x) 2) || (a' == (div (length x) 2) - 1) ) && b' == (length y)-2 && positionsa (a',b'-1) x == Just Wall && a>= a' = (Move id' D)
                                                                                                                                 | id'== i && ( (a' == div (length x) 2) || (a' == (div (length x) 2) - 1) ) && b' == (length y)-2 && positionsa (a',b'-1) x == Just Wall && a < a' = (Move id' U)
                                                                                                                                 | id'== i && ( (a' == div (length x) 2) || (a' == (div (length x) 2) - 1) ) && b' == (length y)-2 = (Move id' L)
                                                                                                                                 | id'== i && ( (a' == div (length x) 2) || (a' == (div (length x) 2) - 1) ) && b' == 1 && positionsa (a',b'+1) x == Just Wall && a>= a' = (Move id' D)
                                                                                                                                 | id'== i && ( (a' == div (length x) 2) || (a' == (div (length x) 2) - 1) ) && b' == 1 && positionsa (a',b'+1) x == Just Wall && a < a' = (Move id' U)
                                                                                                                                 | id'== i && ( (a' == div (length x) 2) || (a' == (div (length x) 2) - 1) ) && b' == 1 = (Move id' R)
                                                                                                                                 | id'== i && (a+1) == a' = (Move id' U)
                                                                                                                                 | id'== i && (a-1) == a' = (Move id' D)
                                                                                                                                 | id'== i && (b+1) == b' = (Move id' L)
                                                                                                                                 | id'== i && (b-1) == b' = (Move id' R)
                                                                                                                                 | id'== i && o' == R && (positionsa (a',b'+2) x) == (Just Wall) && (positionsa (a'+1,b'+1) x) == (Just Wall) && a' <= a && b' <= b = (Move id' D) ---- These cases
                                                                                                                                 | id'== i && o' == D && (positionsa (a'+1,b'+1) x) == (Just Wall) && (positionsa (a'+2,b') x) == (Just Wall) && a' <= a && b' <= b = (Move id' R) -- are to
                                                                                                                                 | id'== i && o' == D && (positionsa (a'+2,b') x) == (Just Wall) && (positionsa (a'+1,b'-1) x) == (Just Wall) && a' <= a && b' >= b = (Move id' L) -- prevent
                                                                                                                                 | id'== i && o' == L && (positionsa (a',b'-2) x) == (Just Wall) && (positionsa (a'+1,b'-1) x) == (Just Wall) && a' <= a && b' >= b = (Move id' D) -- the ghost  ---\  exemple : Wall Ghost                                           
                                                                                                                                 | id'== i && o' == L && (positionsa (a',b'-2) x) == (Just Wall) && (positionsa (a'-1,b'-1) x) == (Just Wall) && a' >= a && b' >= b = (Move id' U) -- from being ---/                 Wall
                                                                                                                                 | id'== i && o' == U && (positionsa (a'-1,b'-1) x) == (Just Wall) && (positionsa (a'-2,b') x) == (Just Wall) && a' >= a && b' >= b = (Move id' L) -- "trapped"             pacman
                                                                                                                                 | id'== i && o' == U && (positionsa (a'-2,b') x) == (Just Wall) && (positionsa (a'-1,b'+1) x) == (Just Wall) && a' >= a && b' <= b = (Move id' R) -- between
                                                                                                                                 | id'== i && o' == R && (positionsa (a',b'+2) x) == (Just Wall) && (positionsa (a'-1,b'+1) x) == (Just Wall) && a' >= a && b' <= b = (Move id' U) ---- 2 walls
                                                                                                                                 | id'== i && o' == U && (positionsa (a'-1,b') x) == (Just Wall) && a>a' && abs (a-a') > 3 = (Move id' D)
                                                                                                                                 | id'== i && o' == U && (positionsa (a'-1,b') x) == (Just Wall) && b<b' = (Move id' L)
                                                                                                                                 | id'== i && o' == U && (positionsa (a'-1,b') x) == (Just Wall) && b'<b = (Move id' R)
                                                                                                                                 | id'== i && o' == U && (positionsa (a'-1,b') x) == (Just Wall) && b==b'= (Move id' R)
                                                                                                                                 | id'== i && o' == D && (positionsa (a'+1,b') x) == (Just Wall) && a<a' && abs (a-a') > 3 = (Move id' U)
                                                                                                                                 | id'== i && o' == D && (positionsa (a'+1,b') x) == (Just Wall) && b<b' = (Move id' L)
                                                                                                                                 | id'== i && o' == D && (positionsa (a'+1,b') x) == (Just Wall) && b'<b = (Move id' R)
                                                                                                                                 | id'== i && o' == D && (positionsa (a'+1,b') x) == (Just Wall) && b==b'= (Move id' L)
                                                                                                                                 | id'== i && o' == L && (positionsa (a',b'-1) x) == (Just Wall) && b>b' && abs (b-b') > 3 = (Move id' R)
                                                                                                                                 | id'== i && o' == L && (positionsa (a',b'-1) x) == (Just Wall) && a<a' = (Move id' U)
                                                                                                                                 | id'== i && o' == L && (positionsa (a',b'-1) x) == (Just Wall) && a'<a = (Move id' D)
                                                                                                                                 | id'== i && o' == L && (positionsa (a',b'-1) x) == (Just Wall) && a==a'= (Move id' U) 
                                                                                                                                 | id'== i && o' == R && (positionsa (a',b'+1) x) == (Just Wall) && b'>b && abs (b-b') > 3= (Move id' L)
                                                                                                                                 | id'== i && o' == R && (positionsa (a',b'+1) x) == (Just Wall) && a<a' = (Move id' U)
                                                                                                                                 | id'== i && o' == R && (positionsa (a',b'+1) x) == (Just Wall) && a'<a = (Move id' D)
                                                                                                                                 | id'== i && o' == R && (positionsa (a',b'+1) x) == (Just Wall) && a==a'= (Move id' D)
                                                                                                                                 | id'== i = (Move id' o')
                                                                                                                                 | otherwise = chaseMode (State x ((Pacman (PacState (id,(a,b),v,o,p,vi) t m k)):z) l) i

-- | __'scatterMode'__: This function gives movements to ghosts so that they can escape Pacman
scatterMode :: State 
               -> Int -- ^ The ID of the ghost that will be moved
               -> Play
scatterMode (State x ((Pacman (PacState (id,(a,b),v,o,p,vi) t m k)):(Ghost (GhoState (id',(a',b'),v',o',p',vi') q)):z) l) i | id'== i && o' == U && (positionsa (a'-1,b') x) == (Just Wall) = (Move id' R)
                                                                                                                            | id'== i && o' == D && (positionsa (a'+1,b') x) == (Just Wall) = (Move id' L)
                                                                                                                            | id'== i && o' == L && (positionsa (a',b'-1) x) == (Just Wall) = (Move id' U)
                                                                                                                            | id'== i && o' == R && (positionsa (a',b'+1) x) == (Just Wall) = (Move id' D)
                                                                                                                            | id'== i = (Move id' o')
                                                                                                                            | otherwise = scatterMode (State x ((Pacman (PacState (id,(a,b),v,o,p,vi) t m k)):z) l) i


-- | __'chaseMode'__: This function uses the function chaseMode to give a list of movements to go in the direction of Pacman, one for each Ghost
chaseMode' :: State 
           -> [Int] -- ^ list with the living ghosts' ids
           -> [Play]
chaseMode' state [] = []
chaseMode' state [h] = [(chaseMode state h)]
chaseMode' state (h:t) = (chaseMode state h):(chaseMode' state t) 

-- | __'scatterMode'__: This function uses the function scatterMode to give a list of movements to escape Pacman, one for each Ghost
scatterMode' :: State 
             -> [Int] -- ^ list with the dead ghosts' ids
             -> [Play]
scatterMode' state [] = []
scatterMode' state [h] = [(scatterMode state h)]
scatterMode' state (h:t) = (scatterMode state h):(scatterMode' state t) 

-- | __'separateAliveID'__: This function gives all the living ghosts IDs
separateAliveID :: [Player] -- ^ only ghosts
                -> [Int]
separateAliveID [] = []
separateAliveID ((Ghost (GhoState (id,(a,b),v,o,p,vi) q)):z) = if q==Alive then id : separateAliveID z else separateAliveID z

-- | __'separateDeadID'__: This function gives all dead ghosts' IDs
separateDeadID :: [Player] -- ^ only ghosts
                  -> [Int]
separateDeadID [] = []
separateDeadID ((Ghost (GhoState (id,(a,b),v,o,p,vi) q)):z) = if q==Dead then id : separateDeadID z else separateDeadID z


-- | __'ghostPlay'__: This function receives the game state and returns a set of moves, one from each ghost
ghostPlay :: State -> [Play]
ghostPlay (State x p l) = (chaseMode' (State x p' l) i1) ++ (scatterMode' (State x p' l) i2)
                        where p' = (onlyPacman p) ++ (onlyGhost p)
                              i1 = separateAliveID (onlyGhost p)
                              i2 = separateDeadID  (onlyGhost p)