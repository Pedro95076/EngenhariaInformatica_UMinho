{- |

= Introdução
A tarefa2 baseia-se na implementação de jogadas para os jogadores do tipo Pacman.

= Objetivos
O objetivo desta tarefa é a implementação de jogadas do jogador Pacman, sendo que
dada uma Play numa determinada direção, o estado do jogo deve ser atualizado e por
sua vez, este deve atualizar o efeito dessa jogada no labirinto atual. No que à
movimentação concerne, é necessário concretizar as jogadas nas diferentes direções,
os casos em que nada acontece, a soma de pontos (aquando encontro do Pacman com a
comida), e ainda o estado Mega do Pacman.

= Estratégia de Implementação
Para esta tarefa, foram implementadas funções que permitissem determinar o tipo de
peça que se encontra imediatamente após o Pacman, numa determinada direção. Desta
forma, foi possível cobrir todos os casos referidos acima que englobassem o encontro
com algum tipo de peça ou jogador. Para além desta, foram implementadas funções que
mudassem as peças que se encontravam anteriormente nas coordenadas do Pacman, numa
jogada imediatamente anterior, para peças Empty. Posteriormente, e de uma forma geral,
foi executada uma função "move" que cobrisse todos os movimentos e encontros, para além
de soma de pontos e perda de vidas, em todas as direções. Para a concretização do estado
Mega, foi realizada uma função para este efeito (auxiliar às funções auxiliares da "move")
bem como outras auxiliares a esta, que permitissem cobrir todas as exigências deste
estado (encontro com fantasma morto, este volta para o meio do labirinto - local onde
se encontra a casa dos fantasmas, entre outros)

= Conclusão
É possível concluir, assim, que esta tarefa foi implementada com sucesso, considerando
que todos os casos incluídos no enunciado foram contemplados na função principal "play",
tendo sido os objetivos para esta tarefa concluídos com sucesso.

-}


module Tarefa2 where

import Tarefa1
import Types
import Data.Maybe
import FileUtils

-- | 'state': example of a maze with a predetermined state
state' :: State
state' = loadMaze "../maps/1.txt"


-- | __'positionsa'__: this function returns a Piece placed in the given coordinates
positionsa :: Coords -> Maze -> Maybe Piece
positionsa (a,b) [] = Nothing
positionsa (a,b) ((x:xs):y) | a /= 0 = positionsa (a-1,b) y
                            | a == 0 = positionsb (x:xs) b


-- | __'positionsb'__: auxiliary function to 'positionsa' that finds the right coordinate in a Corridor
positionsb :: Corridor -> Int -> Maybe Piece
positionsb [] b = Nothing
positionsb (x:xs) b | b==0 = Just x
                    | otherwise = positionsb xs (b-1)


-- | __'changeToEmpty'__: this funcion changes whatever piece placed in certain coordinates to the Piece Empty
changeToEmpty ::  Coords -> Maze -> Maze
changeToEmpty (a,b) ((x:xs):y) | positionsa (a,b) ((x:xs):y) == Just Empty = ((x:xs):y)
                               | otherwise = changeToEmptyA (a,b) ((x:xs):y)


-- | __'changetoEmptyA'__: auxiliary function to 'changetoEmpty' that finds the correspondent piece in a maze
changeToEmptyA :: Coords -> Maze -> Maze
changeToEmptyA (a,b) ((x:xs):y) | a /= 0 = (x:xs) : changeToEmptyA (a-1,b) y
                                | a == 0 = changeToEmptyB b (x:xs) : y

-- | __'changeToEmptyB'__: auxiliary function to 'changeToEmptyA' that finds the correspondent piece in a maze
changeToEmptyB :: Int -> Corridor -> Corridor
changeToEmptyB b (x:xs) | b /= 0 = x : changeToEmptyB (b-1) xs
                        | b == 0 = Empty : xs  

-- | __'Game Players'__: made to test the game
pl = [player1,player2,player3]
player1 = (Pacman (PacState (0,(3,1),1,L,0,2) 0 Open Normal))
player2 = (Ghost (GhoState (1,(1,1),1,D,0,1) Alive)) 
player3 = (Ghost (GhoState (2,(2,2),1,R,0,1) Alive))
q = (State y pl 1)
x = (generateMaze 15 15 238)
maze' (State m p l) = m
y = maze' (loadMaze "../maps/1.txt") 


-- | __'play'__: main function that given a play (movement of the player Pacman) and a state returns another state with the changes incorporated
play :: Play -> State -> State
play (Move id o) (State m (x:xs) l) | getPlayerID x == id = move o (State m (x:xs) l)
                                    | otherwise = play (Move id o) (State m (xs ++ [x]) l)


-- | __'move'__: auxiliary function to 'play' that manages the Pacman's movements
move :: Orientation -> State -> State
move o (State m ((Pacman (PacState (id',(a,b),v,o',p,vi) t m' p')):xs) l) | p'== Dying = (State m ((Pacman (PacState (id',(a,b),v,o',p,vi) t m' p')):xs) l)
                                                                          | o /= o' = (State m ((Pacman (PacState (id',(a,b),v,o,p,vi) t (mouthPacman m') p')):xs) l) -- when Pacman's orientation is different from the one given in the play
                                                                          | o == o' && o == R = (State (moveMR (a,b) m) (moveR m ((Pacman (PacState (id',(a,b),v,o',p,vi) t (mouthPacman m') p')):xs)) l) -- when Pacman's orientation is the same as the play (goes to the next piece on the Right)
                                                                          | o == o' && o == L = (State (moveML (a,b) m) (moveL m ((Pacman (PacState (id',(a,b),v,o',p,vi) t (mouthPacman m') p')):xs)) l) -- when Pacman's orientation is the same as the play (goes to the next piece on the Left)
                                                                          | o == o' && o == U = (State (moveMU (a,b) m) (moveU m ((Pacman (PacState (id',(a,b),v,o',p,vi) t (mouthPacman m') p')):xs)) l) -- when Pacman's orientation is the same as the play (goes to the next piece Upwards)
                                                                          | o == o' && o == D = (State (moveMD (a,b) m) (moveD m ((Pacman (PacState (id',(a,b),v,o',p,vi) t (mouthPacman m') p')):xs)) l) -- when Pacman's orientation is the same as the play (goes to the next piece Downwards)
                                                                          | otherwise = (State m ((Pacman (PacState (id',(a,b),v,o',p,vi) t m' p')):xs) l)
move o (State m ((Ghost (GhoState (id',(a,b),v,o',p,vi) q)):xs) l)        | o /= o' = (State m ((Ghost (GhoState (id',(a,b),v,o,p,vi) q)):xs) l)
                                                                          | o == o' && o == R = (State m (moveR m ((Ghost (GhoState (id',(a,b),v,o',p,vi) q)):xs)) l)
                                                                          | o == o' && o == L = (State m (moveL m ((Ghost (GhoState (id',(a,b),v,o',p,vi) q)):xs)) l)
                                                                          | o == o' && o == U = (State m (moveU m ((Ghost (GhoState (id',(a,b),v,o',p,vi) q)):xs)) l)
                                                                          | o == o' && o == D = (State m (moveD m ((Ghost (GhoState (id',(a,b),v,o',p,vi) q)):xs)) l)
                                                                          | otherwise = (State m ((Ghost (GhoState (id',(a,b),v,o',p,vi) q)):xs) l)

-- | __'moveMR'__: auxiliary function to 'move' that updates the maze when there are movements made to the right
moveMR :: Coords -> Maze -> Maze
moveMR (a,b) ((x:xs):y) | positionsa (a,b+1) ((x:xs):y) == Just Wall = ((x:xs):y) -- when Pacman moves to the right and encounters a wall (maze stays the same)
                        | b == (length (x:xs))-1 = ((x:xs):y)
                        | otherwise = changeToEmpty (a,b) ((x:xs):y) -- when Pacman moves to the left in other situations (last piece changes to empty

-- | __'moveR'__: auxiliary function to 'move' that moves the player to the right and contains all of his plays
moveR :: Maze -> [Player] -> [Player]
moveR ((x:xs):y) ((Pacman (PacState (id',(a,b),v,o',p,vi) t m' p')):z) | confrontation (Pacman (PacState (id',(a,b+1),v,o',p,vi) t m' p')) (onlyGhost z) == True = (pacmanVSghost ((x:xs):y) [(Pacman (PacState (id',(a,b+1),v,o',p,vi) t m' p')),onlyOneGhost (Pacman (PacState (id',(a,b+1),v,o',p,vi) t m' p')) (onlyGhost z)]) ++ (otherPlayers (Pacman (PacState (id',(a,b+1),v,o',p,vi) t m' p')) (onlyOneGhost (Pacman (PacState (id',(a,b+1),v,o',p,vi) t m' p')) (onlyGhost z)) ((Pacman (PacState (id',(a,b+1),v,o',p,vi) t m' p')):z)) -- when Pacman encounters a Ghost
                                                                       | positionsa (a,b+1) ((x:xs):y) == Just Wall = ((Pacman (PacState (id',(a,b),v,o',p,vi) t m' p')):z) -- when Pacman encounters a Wall (same state)
                                                                       | positionsa (a,b+1) ((x:xs):y) == Just (Food Little) = ((Pacman (PacState (id',(a,b+1),v,o',(p+1),vi) t m' p')):z) -- when Pacman encounters a 'Food Little' Piece(plus one point)
                                                                       | positionsa (a,b+1) ((x:xs):y) == Just (Food Big) = megaPacmanState ((Pacman (PacState (id',(a,b+1),v,o',p,vi) t m' Mega)):z) -- when Pacman encounters a 'Food Big' Piece(Mega State)
                                                                       | b == (length (x:xs))-1 = ((Pacman (PacState (id',(a,0),v,o',p,vi) t m' p')):z) -- when Pacman encounters a tunnel
                                                                       | otherwise = ((Pacman (PacState (id',(a,b+1),v,o',p,vi) t m' p')):z) -- other situations (same state)
moveR ((x:xs):y) ((Ghost (GhoState (id',(a,b),v,o',p,vi) q)):z)        | positionsa (a,b+1) ((x:xs):y) == Just Wall = ((Ghost (GhoState (id',(a,b),v,o',p,vi) q)):z)
                                                                       | b == (length (x:xs))-1 = ((Ghost (GhoState (id',(a,0),v,o',p,vi) q)):z)
                                                                       | otherwise = ((Ghost (GhoState (id',(a,b+1),v,o',p,vi) q)):z)


-- | __'moveML'__: auxiliary function to 'move' that updates the maze when there are movements to the left
moveML :: Coords -> Maze -> Maze
moveML (a,b) ((x:xs):y) | positionsa (a,b-1) ((x:xs):y) == Just Wall = ((x:xs):y) -- when Pacman moves to the left and encounters a wall (maze stays the same)
                        | b == 0 = ((x:xs):y)
                        | otherwise = changeToEmpty (a,b) ((x:xs):y) -- when Pacman moves to the left in other situations (last piece changes to empty)

-- | __'moveL'__: auxiliary funtion to 'move' that moves the player to the left and contains all of his plays
moveL :: Maze -> [Player] -> [Player]
moveL ((x:xs):y) ((Pacman (PacState (id',(a,b),v,o',p,vi) t m' p')):z) | confrontation (Pacman (PacState (id',(a,b-1),v,o',p,vi) t m' p')) (onlyGhost z) == True = (pacmanVSghost ((x:xs):y) [(Pacman (PacState (id',(a,b-1),v,o',p,vi) t m' p')),onlyOneGhost (Pacman (PacState (id',(a,b-1),v,o',p,vi) t m' p')) (onlyGhost z)]) ++ (otherPlayers (Pacman (PacState (id',(a,b-1),v,o',p,vi) t m' p')) (onlyOneGhost (Pacman (PacState (id',(a,b-1),v,o',p,vi) t m' p')) (onlyGhost z)) ((Pacman (PacState (id',(a,b-1),v,o',p,vi) t m' p')):z)) -- when Pacman encounters a Ghost
                                                                       | positionsa (a,b-1) ((x:xs):y) == Just Wall = ((Pacman (PacState (id',(a,b),v,o',p,vi) t m' p')):z) -- when Pacman encounters a Wall (same state)
                                                                       | positionsa (a,b-1) ((x:xs):y) == Just (Food Little) = ((Pacman (PacState (id',(a,b-1),v,o',(p+1),vi) t m' p')):z)  -- when Pacman encounters a 'Food Little' Piece(plus one point)
                                                                       | positionsa (a,b-1) ((x:xs):y) == Just (Food Big) = megaPacmanState ((Pacman (PacState (id',(a,b-1),v,o',p,vi) t m' Mega)):z) -- when Pacman encounters a 'Food Big' Piece(Mega State)
                                                                       | b == 0 = ((Pacman (PacState (id',(a,(length (x:xs))-1),v,o',p,vi) t m' p')):z) -- when Pacman encounters a tunnel
                                                                       | otherwise = ((Pacman (PacState (id',(a,b-1),v,o',p,vi) t m' p')):z) -- other situations (same state)
moveL ((x:xs):y) ((Ghost (GhoState (id',(a,b),v,o',p,vi) q)):z)        | positionsa (a,b-1) ((x:xs):y) == Just Wall = ((Ghost (GhoState (id',(a,b),v,o',p,vi) q)):z)
                                                                       | b == 0 = ((Ghost (GhoState (id',(a,(length (x:xs))-1),v,o',p,vi) q)):z)
                                                                       | otherwise = ((Ghost (GhoState (id',(a,b-1),v,o',p,vi) q)):z)


-- | __'moveMU'__: auxiliary function to 'move' that updates the maze when movements upwards are made
moveMU :: Coords -> Maze -> Maze
moveMU (a,b) ((x:xs):y) | positionsa (a-1,b) ((x:xs):y) == Just Wall = ((x:xs):y) -- when Pacman moves upwards and encounters a wall (maze stays the same)
                        | otherwise = changeToEmpty (a,b) ((x:xs):y) -- when Pacman moves upwards in other situations (last piece changes to empty

-- | __'moveU'__: auxiliary function to 'move' that moves the player upwards and contains all of his plays
moveU :: Maze -> [Player] -> [Player]
moveU m ((Pacman (PacState (id',(a,b),v,o',p,vi) t m' p')):z) | confrontation (Pacman (PacState (id',(a-1,b),v,o',p,vi) t m' p')) (onlyGhost z) == True = (pacmanVSghost m [(Pacman (PacState (id',(a-1,b),v,o',p,vi) t m' p')),onlyOneGhost (Pacman (PacState (id',(a-1,b),v,o',p,vi) t m' p')) (onlyGhost z)]) ++ (otherPlayers (Pacman (PacState (id',(a-1,b),v,o',p,vi) t m' p')) (onlyOneGhost (Pacman (PacState (id',(a-1,b),v,o',p,vi) t m' p')) (onlyGhost z)) ((Pacman (PacState (id',(a-1,b),v,o',p,vi) t m' p')):z)) -- when Pacman encounters a Ghost
                                                              | positionsa (a-1,b) m == Just Wall = ((Pacman (PacState (id',(a,b),v,o',p,vi) t m' p')):z) -- when Pacman encounters a Wall (same state)
                                                              | positionsa (a-1,b) m == Just (Food Little) = ((Pacman (PacState (id',(a-1,b),v,o',(p+1),vi) t m' p')):z) -- when Pacman encounters a 'Food Little' Piece(plus one point)
                                                              | positionsa (a-1,b) m == Just (Food Big) = megaPacmanState ((Pacman (PacState (id',(a-1,b),v,o',p,vi) t m' Mega)):z) -- when Pacman encounters a 'Food Big' Piece(Mega State)
                                                              | otherwise = ((Pacman (PacState (id',(a-1,b),v,o',p,vi) t m' p')):z) -- other situations (same state)
moveU m ((Ghost (GhoState (id',(a,b),v,o',p,vi) q)):z)        | positionsa (a-1,b) m == Just Wall = ((Ghost (GhoState (id',(a,b),v,o',p,vi) q)):z) 
                                                              | otherwise = ((Ghost (GhoState (id',(a-1,b),v,o',p,vi) q)):z)


-- | __'moveMD'__: auxiliary funtion to 'move' that updates the maze when movements downwards are made
moveMD :: Coords -> Maze -> Maze
moveMD (a,b) ((x:xs):y) | positionsa (a+1,b) ((x:xs):y) == Just Wall = ((x:xs):y) -- when Pacman moves downwards and encounters a wall (maze stays the same)
                        | otherwise = changeToEmpty (a,b) ((x:xs):y) -- when Pacman moves downwards in other situations (last piece changes to empty

-- | __'moveD'__: auxiliary funtion to 'move' that moves the player downwards and contains all of his plays
moveD :: Maze -> [Player] -> [Player]
moveD m ((Pacman (PacState (id',(a,b),v,o',p,vi) t m' p')):z) | confrontation (Pacman (PacState (id',(a+1,b),v,o',p,vi) t m' p')) (onlyGhost z) == True = (pacmanVSghost m [(Pacman (PacState (id',(a+1,b),v,o',p,vi) t m' p')),onlyOneGhost (Pacman (PacState (id',(a+1,b),v,o',p,vi) t m' p')) (onlyGhost z)]) ++ (otherPlayers (Pacman (PacState (id',(a+1,b),v,o',p,vi) t m' p')) (onlyOneGhost (Pacman (PacState (id',(a+1,b),v,o',p,vi) t m' p')) (onlyGhost z)) ((Pacman (PacState (id',(a+1,b),v,o',p,vi) t m' p')):z)) -- when Pacman encounters a Ghost
                                                              | positionsa (a+1,b) m == Just Wall = ((Pacman (PacState (id',(a,b),v,o',p,vi) t m' p')):z) -- when Pacman encounters a Wall (same state)
                                                              | positionsa (a+1,b) m == Just (Food Little) = ((Pacman (PacState (id',(a+1,b),v,o',(p+1),vi) t m' p')):z) -- when Pacman encounters a 'Food Little' Piece(plus one point)
                                                              | positionsa (a+1,b) m == Just (Food Big) = megaPacmanState ((Pacman (PacState (id',(a+1,b),v,o',p,vi) t m' Mega)):z) -- when Pacman encounters a 'Food Big' Piece(Mega State)
                                                              | otherwise = ((Pacman (PacState (id',(a+1,b),v,o',p,vi) t m' p')):z) -- other situations (same state)
moveD m ((Ghost (GhoState (id',(a,b),v,o',p,vi) q)):z)        | positionsa (a+1,b) m == Just Wall = ((Ghost (GhoState (id',(a,b),v,o',p,vi) q)):z) 
                                                              | otherwise = ((Ghost (GhoState (id',(a+1,b),v,o',p,vi) q)):z)

-- | __'megaPacmanState'__: this function regulates the Pacman's Mega mode
megaPacmanState :: [Player] -> [Player]
megaPacmanState [] = []
megaPacmanState (i@(Pacman (PacState (id,(a,b),v,o,p,vi) t m' p')):xs) | p' == Mega && t>0.25 = megaPacmanState ((Pacman (PacState (id,(a,b),v,o,p,vi) (t-0.25) m' Mega)):xs)
                                                                       | p' == Mega = ((Pacman (PacState (id,(a,b),v,o,p,vi) 0 m' Normal)):megaGhostState i xs)
                                                                       | otherwise = ((Pacman (PacState (id,(a,b),v,o,p,vi) 0 m' p')):xs)

-- | __'megaGhostState'__: auxiliary funtion to "megaPacmanState" that regulates the Ghosts when Pacman is in the Mega mode
megaGhostState :: Player -> [Player] -> [Player]
megaGhostState _ [] = []
megaGhostState i@(Pacman (PacState (id,(a,b),v,o,p,vi) t m' p')) ((Ghost (GhoState (id',(a',b'),v',o',po,e) q)):xs) 
                          | p' == Mega = (Ghost (GhoState (id',(a',b'),(v'*0.5),o',po,e) Dead)):megaGhostState i xs
                          | otherwise = (Ghost (GhoState (id',(a',b'),v',o',po,e) Alive)):megaGhostState i xs


-- | __'confrontation'__: this function returns True if there is a ghost in the same position as Pacman
confrontation :: Player -> [Player] -> Bool
confrontation (Pacman (PacState (id,(a,b),v,o,p,vi) t m' p')) [] = False
confrontation (Pacman (PacState (id,(a,b),v,o,p,vi) t m' p')) ((Ghost (GhoState (id',(a',b'),v',o',po,e) q)):xs) | a == a' && b == b' = True
                                                                                                                 | otherwise = confrontation (Pacman (PacState (id,(a,b),v,o,p,vi) t m' p')) xs


-- | __'onlyGhost'__: this function only returns a list with all the ghosts players
onlyGhost :: [Player] -> [Player]
onlyGhost [] = []
onlyGhost ((Pacman (PacState (id',(a,b),v,o',p,vi) t m' p')):xs) = onlyGhost xs
onlyGhost ((Ghost  (GhoState (id',(a,b),v,o',o,vi) q)):xs)       = ((Ghost  (GhoState (id',(a,b),v,o',o,vi) q)) : onlyGhost xs)

-- | __'onlyPacman'__: this function only returns a list with all the Pacman players
onlyPacman :: [Player] -> [Player]
onlyPacman [] = []
onlyPacman ((Pacman (PacState (id',(a,b),v,o',p,vi) t m' p')):xs) = (Pacman (PacState (id',(a,b),v,o',p,vi) t m' p')) : onlyPacman xs
onlyPacman ((Ghost  (GhoState (id',(a,b),v,o',o,vi) q)):xs)       = onlyPacman xs

-- | __'onlyOneGhost'__: this function returns a ghost with specific coordinates (same as Pacman)
onlyOneGhost :: Player -> [Player] -> Player
onlyOneGhost a (h:t) | getPlayerCoords h == getPlayerCoords a = h
                     | otherwise = onlyOneGhost a t


-- | __'middleMaze'__: this function returns the middle of the maze (inside the house of ghosts)
middleMaze :: Maze -> Coords
middleMaze (h:t) | odd y == True = ((div y 2),(div x 2))
                 | even y == True = ((div y 2)-1,(div x 2))
                      where 
                        x = length h
                        y = length (h:t)


-- | __'pacmanVSghost'__: this function deals with the confrontation between the pacman and the ghost
pacmanVSghost :: Maze -> [Player] -> [Player]
pacmanVSghost m [(Pacman (PacState (id,(a,b),v,o,p,vi) t m' p')),(Ghost (GhoState (id',(a',b'),v',o',po,e) q))] | q == Alive && (vi-1) >  0 = [(Pacman (PacState (id,(a,b),v,o,p,vi-1) t m' p')),(Ghost (GhoState (id',(a',b'),v',o',po,e) q))] -- when Pacman encounters an Alive Ghost and has more than one live (loses one live)
                                                                                                                | q == Alive && (vi-1) == 0 = [(Pacman (PacState (id,(a,b),v,o,p,vi-1) t m' Dying)),(Ghost (GhoState (id',(a',b'),v',o',po,e) q))] -- when Pacman encounters an Alive Ghost and has one live (His state changes to Dying)
                                                                                                                | q == Dead = [(Pacman (PacState (id,(a,b),v,o,p+10,vi) t m' p')),(Ghost (GhoState (id',(middleMaze m),v',o',po,e) Alive))] -- when Pacman encounters a Dead Ghost (plus ten points and ghost returns to the middle of the maze)


-- | __'otherPlayers'__: this function returns a list without the players that are in the same coordinates (Pacman and Ghost)
otherPlayers :: Player -> Player -> [Player] -> [Player]
otherPlayers a b [] = []
otherPlayers a b (h:t) | h == a || h == b = otherPlayers a b t
                       | otherwise = h : otherPlayers a b t

-- | __'mouthPacman'__ : This function switches the Pacman's mouth between open and closed
mouthPacman :: Mouth -> Mouth
mouthPacman Open   = Closed
mouthPacman Closed = Open