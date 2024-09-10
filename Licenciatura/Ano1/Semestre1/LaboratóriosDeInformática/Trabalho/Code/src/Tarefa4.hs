
{- | 

= Introdução
A tarefa 4 baseia-se na implementação da reação à passagem do tempo e para além disso,
na implementação de movimentação dos jogadores numa interação. Desta forma, esta tarefa
é divida em duas partes:

* __Parte 1__: integra os tipos e as funções que advém da 1ª fase numam biblioteca
denominada NCurses

* __Parte 2__: utiliza o estado e informação vinda da primeira parte para avançar o jogo
numa iteração, fazendo, desta forma, a movimentação de todos os jogadores

= Objetivos
Os objetivos desta tarefa passam pelo cálculo do efeito da passagem de um instante de
tempo num determinado estado de jogo. Através de um /data/ Manager, no final desta
tarefa, pretende-se ser possível controlar a passagem do tempo definido para efetuar uma
nova jogada, que por si só, deve movimentar os jogadores, tendo em conta a sua velocidade
e o respetivo estado. Para este efeito, devem ser introduzidos na tarefa 2 comportamentos
afetos ao estado Mega, ao próprio Pacman (abrir e fechar a boca) e à velocidade dos
jogadores.

= Estratégia de Implementação
Numa primeira instância, foram introduzidas no ficheiro Main.hs algumas funções que 
permitissem a passagem do tempo a cada jogada, tal como, a "nextFrame", a "updateTime" e
a "resetTimer". Para além disso, foi concretizada uma funçãom "updateControlledPlayer" que
através das setas do teclado, permite mudar a direção do jogador Pacman.
Na segunda parte desta tarefa, foi implementada a função "passTime". Esta função permitiu
não só a implementação da função "ghostPlay" tarefa 5, como também o bot tarefa 6.
A estratégia utilizada para esta função passou pela utilização de uma função auxiliar que
cobrisse todos os casos obrigatórios nesta tarefa: a constante movimentação do Pacman na
direção em que se encontra (até ser pressionada uma Key numa direção diferente), as diferentes
velocidades dos jogadores (nomeadamente os fantasmas) e a implementação da tarefa 5, com a
atribuição de cada Play da lista originada na função "ghostPlay" ao respetivo fantasma.
A função em formato de comentário permite o funcionamento do bot num jogo Pacman.

= Conclusão
De uma forma geral, pode-se concluir que esta tarefa se apresentou como desafiadora e em certas
circunstâncias difícil de implementar. A prestação total desta tarefa poderia ser muito melhor
contudo, apesar de algumas imperfeições e pontos falhados (nomeadamente no estado Mega), foi 
possível ter uma melhor compreensão do que é a passagem do tempo num jogo. A estratégia utilizada 
poderá não ter sido a melhor, contudo e de uma forma geral, foi possível colocar o jogo a funcionar
de maneira razoável. Um dos pontos mais marcantes na realização desta tarefa foi que a mesma se
demonstrou ser desafiadora.

-}


module Tarefa4 where 

import Types
import Tarefa2
import Tarefa5
import Tarefa6

defaultDelayTime = 250 -- 250 ms


passTime :: Int -> State -> State
passTime step (State m pl l) = passTimeAux step (State m pl l) pl (ghostPlay (State m pl l))

passTimeAux :: Int -> State -> [Player] -> [Play] -> State
passTimeAux _ s [] _  = s
passTimeAux step s ((Pacman (PacState (x,y,z,t,h,l) q c d)):xs) n = passTimeAux step (play (Move x t) s) xs n
passTimeAux step s ((Ghost (GhoState (id',(a',b'),v',o',po,e) q)):xs) n 
                | v' == 0.5 && even step = passTimeAux step (play (assignPlay n id') s) xs n
                | v' == 2.0 = passTimeAux step (play (assignPlay n id') (play (assignPlay n id') s)) xs n
                | v' == 1.5 && (mod 3 step) == 0 = passTimeAux step (play (assignPlay n id') s) xs n
                | otherwise = passTimeAux step (play (assignPlay n id') s) xs n
                                                              where
                                                                assignPlay :: [Play] -> Int -> Play
                                                                assignPlay [x] _ = x
                                                                assignPlay ((Move id o):xs) x | x == id = Move id o
                                                                                              | otherwise = assignPlay xs x

{-

passTime :: Int -> State -> State
passTime step (State m ps l) = passTimeAux step (State m ps l) ps (ghostPlay (State m ps l)) (bot (getPacmanID ps) (State m ps l))

passTimeAux :: Int -> State -> [Player] -> [Play] -> Maybe Play -> State
passTimeAux _ s [] _ _ = s
passTimeAux step s ((Pacman (PacState (x,y,z,t,h,l) q c d)):xs) n m | d == Dying = s
                                                                    | m == Nothing = passTimeAux step (play (Move x t) s) xs n Nothing
passTimeAux step s ((Pacman (PacState (x,y,z,t,h,l) q c d)):xs) n (Just m) = passTimeAux step (play m s) xs n (Just m)
passTimeAux step s ((Ghost (GhoState (x,y,z,t,h,l) q)):xs) n m | z == 0.5 && even step = passTimeAux step (play (assignPlay n x) s) xs n m
                                                               | z == 2.0 = passTimeAux step (play (assignPlay n x) (play (assignPlay n x) s)) xs n m
                                                               | z == 1.5 && (mod 3 step) == 0 = passTimeAux step (play (assignPlay n x) s) xs n m
                                                               | otherwise = passTimeAux step (play (assignPlay n x) s) xs n m
                                                              where
                                                                assignPlay :: [Play] -> Int -> Play
                                                                assignPlay [x] _ = x
                                                                assignPlay ((Move id o):xs) x | x == id = Move id o
                                                                                              | otherwise = assignPlay xs x

getPacmanID :: [Player] -> Int
getPacmanID (Pacman(PacState (i,(x1,y1),v,o,p,l) t m q):xs) = i
getPacmanID (Ghost(GhoState (id,(x2,y2),vel,ori,pt,lv) q):xs) = getPacmanID xs

-}