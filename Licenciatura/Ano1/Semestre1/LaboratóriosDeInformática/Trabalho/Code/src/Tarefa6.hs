{- |

= Introdução
A tarefa 6 consiste na criação de um robô, ou seja, de um jogador Pacman capaz de 
jogar automaticament e sem /input/ humano. 

= Objetivos
Os objetivos desta tarefa passam pela implementação de um robô que consiga tomar
decisões utilizando o /Play/ definido. A função principal desta tarefa /bot/ recebe
um identificador de jogador e um estado de jogo e retorna uma /Play/ do tipo /Maybe/.

= Estratégia de Implementação
Nesta tarefa foram implementadas duas ações do bot, sendo elas:

* __Pacman em modo Mega persegue os fantasmas__: nesta ação, o Pacman determina as
coordenadas do fantasma mais próximo e vai em direção a ele. Se a distância horizontal
entre os dois for menor do que a distância vertical, ele move-se para a esquerda ou
para a direita, consoante a direção do fantasma. No caso contrário, o Pacman move-se 
para cima ou para baixo, consoante a direção em que o fantasma se encontre. Para além
disso, se o Pacman se encontrar perto de um túnel e um dos fantasmas estiver perto do
outro túnel, o primeiro irá se deslocar em direção ao segundo. Importa ainda referir
que se o Pacman encontrar uma parede, ele irá se desviar do mesmo.

* __Pacman em modo Normal foge dos fantasmas__: nesta ação, quando o Pacman se encontra em 
perigo, ou seja, perto de um dos fantasmas (3 peças vertical ou horizontalmente), o 
Pacman irá mudar para a direção oposta do fantasma.

* __Pacman em modo Normal em direção à comida__: nesta ação, o Pacman vai determinar as
coordenadas da comida mais próxima, e irá na sua direção, usando a mesma estratégia 
utilizada na ação "Pacman em modo Mega persegue o fantasma" descrita acima.

= Conclusão
Em conclusão, apesar de existirem muitas outras estratégias na implementação de um
bot para este jogo, foi possível introduzir algumas que se apresentam como essenciais
para uma maior fluidez do jogo. Desta forma, os objetivos desta tarefa foram atingidos
com sucesso.

-}

module Tarefa6 where 

import Types
import Tarefa1
import Tarefa2
import FileUtils

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

-- | __'bot'__: main bot function
bot :: Int -> State -> Maybe Play
bot id (State m (x:xs) l) = control plID ghostList m
                    where plID = chooseByID id (State m (x:xs) l)
                          ghostList = onlyGhost (x:xs)

-- | __'control'__: this function controls the Pacman's movements in 3 different situations
control :: Player        -- ^ Pacman
           -> [Player]   -- ^ list of all ghosts
           -> Maze       -- ^ maze used to have the coords of foods and walls (when needed)
           -> Maybe Play
control (Pacman (PacState (id,(x,y),v,o,p,vi) t' m' p')) l m | dead /= [] = goToCoords m (Pacman (PacState (id,(x,y),v,o,p,vi) t' m' p')) k -- If the Pacman is in mega mode, he goes towards the nearest ghost
                                                             | alive /= [] && (abs (x-a) <= 5 && y==b) || (abs (y-b) <= 5 && x==a) || (sqrt (fromIntegral ((x-a)^2 + (y-b)^2))) < 5 = escapePacman m (Pacman (PacState (id,(x,y),v,o,p,vi) t' m' p')) (a,b) -- If the Pacman is not in mega mode and there us a ghost near him (distance 3) he runs away from him
                                                             | otherwise = goToCoords m (Pacman (PacState (id,(x,y),v,o,p,vi) t' m' p')) k' -- If the Pacman is not in mega mode and if Pacman doesn't have a ghost very close to him, he will move towards the nearest food
                                                           where alive = aliveGhosts l
                                                                 dead  = deadGhosts  l
                                                                 (a,b) = nearestCoords' (x,y) (coordsGhost alive)
                                                                 k     = nearestCoords' (x,y) (coordsGhost dead)
                                                                 k'    = nearestCoords  (x,y) (coordsFood  m)

aliveGhosts :: [Player] -> [Player]
aliveGhosts [] = []             
aliveGhosts ((Ghost (GhoState (id,(a,b),v,o,p,vi) q)):z) | q == Alive = (Ghost (GhoState (id,(a,b),v,o,p,vi) q)) : aliveGhosts z
                                                         | otherwise = aliveGhosts z

deadGhosts :: [Player] -> [Player]
deadGhosts [] = []             
deadGhosts ((Ghost (GhoState (id,(a,b),v,o,p,vi) q)):z) | q == Dead = (Ghost (GhoState (id,(a,b),v,o,p,vi) q)) : deadGhosts z
                                                        | otherwise = deadGhosts z

-- | __'chooseByID'__: this function returns the player with the ID and State given
chooseByID :: Int -> State -> Player
chooseByID id (State m (x:xs) l) = if getPlayerID x == id then x else chooseByID id (State m xs l)

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

-- | __'coordsFoodCorridor'__: this function gives the food coordinates of a corridor 
coordsFoodCorridor :: Corridor -> Coords -> [Coords]
coordsFoodCorridor (x:xs) (a,b) = acu (x:xs) (a,b)
                               where acu [] (_,_) = []
                                     acu (x:xs) (a,b) = if x == Food Big || x == Food Little then (a,b) : acu xs (a,b+1) else acu xs (a,b+1)

-- | __'coordsFood'__: this function returns the food coordinates of a maze
coordsFood :: Maze -> [Coords]
coordsFood (h:t) = acu (h:t) (0,0)
                where acu [] (x,y) = []
                      acu ([]:c) (x,y) = acu c (x+1,0)
                      acu ((p:ps):c) (x,y) | (p == Food Big) || (p == Food Little) = (x,y) : acu (ps:c) (x,y+1)
                                           | otherwise = acu ((ps):c) (x,y+1)

-- | __'coordsGhost'__: this function gives the coordinates of the ghosts
coordsGhost :: [Player] -- ^ list only with ghosts
            -> [Coords]
coordsGhost [] = []
coordsGhost ((Ghost (GhoState (id,(a,b),v,o,p,vi) q)):z) = (a,b):coordsGhost z

-- | __'nearestCoords'__: this function takes a list of coordinates and gives the closest coordinates to the one given
nearestCoords :: Coords -> [Coords] -> Coords
nearestCoords x l = nearestCoords' x (coordsList x l)
nearestCoords' :: Coords -> [Coords] -> Coords
nearestCoords' x [] = x
nearestCoords' x [a] = a
nearestCoords' x ((l,r):b:c) | x == (l,r) = nearestCoords' x (b:c)
                             | (x == (l+1,r+1)) || (x == (l+1,r-1)) || (x == (l-1,r-1)) || (x == (l-1,r+1)) = nearestCoords' x (b:c)
                             | distance x (l,r) <= distance x b = nearestCoords' x ((l,r):c)
                             | otherwise = nearestCoords' x (b:c)
                           where distance  (x',y') (a',b') = sqrt (fromIntegral ((x'-a')^2 + (y'-b')^2))
coordsList :: Coords -> [Coords] -> [Coords]
coordsList x (h:t) | elem x (h:t) == False = (h:t)
                   | x == h = t
                   | otherwise = h : coordsList x t

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

-- | __'goToCoords'__: this function returns a play for the player to go in the direction of the given coord
goToCoords :: Maze       -- ^ maze used to find if a certain position is a wall or not
           -> Player     -- ^ Player making the move
           -> Coords     -- ^ coords that we want where the Pacman goes
           -> Maybe Play
goToCoords (h:t) (Pacman (PacState (id,(x,y),v,o,p,vi) t' m' p')) (a,b) | even (length (h:t)) && (x == (div (length (h:t)) 2) || x == (div (length (h:t)) 2) - 1) && y < (div (length h) 2) && b > (div (length h) 2) = corridor (h:t) (Pacman (PacState (id,(x,y),v,o,p,vi) t' m' p')) (a,b)
                                                                        | even (length (h:t)) && (x == (div (length (h:t)) 2) || x == (div (length (h:t)) 2) - 1) && y > (div (length h) 2) && b < (div (length h) 2) = corridor (h:t) (Pacman (PacState (id,(x,y),v,o,p,vi) t' m' p')) (a,b)
                                                                        | odd  (length (h:t)) &&  x == (div (length (h:t)) 2) && y < (div (length h) 2) && b > (div (length h) 2) = corridor (h:t) (Pacman (PacState (id,(x,y),v,o,p,vi) t' m' p')) (a,b)
                                                                        | odd  (length (h:t)) &&  x == (div (length (h:t)) 2) && y > (div (length h) 2) && b < (div (length h) 2) = corridor (h:t) (Pacman (PacState (id,(x,y),v,o,p,vi) t' m' p')) (a,b)
                                                                        | a<x  &&  b==y = up    (h:t) (Pacman (PacState (id,(x,y),v,o,p,vi) t' m' p')) (a,b)
                                                                        | a>x  &&  b==y = down  (h:t) (Pacman (PacState (id,(x,y),v,o,p,vi) t' m' p')) (a,b)
                                                                        | a==x &&  b<y  = left  (h:t) (Pacman (PacState (id,(x,y),v,o,p,vi) t' m' p')) (a,b)
                                                                        | a==x &&  b>y  = right (h:t) (Pacman (PacState (id,(x,y),v,o,p,vi) t' m' p')) (a,b)
                                                                        | a<x  &&  b>y  = topRightCorner    (h:t) (Pacman (PacState (id,(x,y),v,o,p,vi) t' m' p')) (a,b)
                                                                        | a<x  &&  b<y  = topLeftCorner     (h:t) (Pacman (PacState (id,(x,y),v,o,p,vi) t' m' p')) (a,b)
                                                                        | a>x  &&  b>y  = bottomRightCorner (h:t) (Pacman (PacState (id,(x,y),v,o,p,vi) t' m' p')) (a,b)
                                                                        | a>x  &&  b<y  = bottomLeftCorner  (h:t) (Pacman (PacState (id,(x,y),v,o,p,vi) t' m' p')) (a,b)
                                                                        | a==x &&  b==y = Nothing
                                                                        | otherwise = Nothing

-- | __'topRightCorner'__: auxiliary function to 'goToCoords' that covers the situations refering to the top right corner of Pacman
topRightCorner :: Maze -> Player -> Coords -> Maybe Play
topRightCorner m (Pacman (PacState (id,(x,y),v,o,p,vi) t m' p')) (a,b) | o == D && (positionsa (x+2,y) m) == (Just Wall) && (positionsa (x+1,y-1) m) == (Just Wall) = Just (Move id L) -- These 2 cases are to prevent the Pacman
                                                                       | o == L && (positionsa (x,y-2) m) == (Just Wall) && (positionsa (x+1,y-1) m) == (Just Wall) = Just (Move id D) -- from being "trapped" between 2 walls
                                                                       | abs (x-a) <= abs (y-b) && (positionsa (x-1,y) m) == Just Wall = Just (Move id R)
                                                                       | abs (x-a) <= abs (y-b) && o == U = Nothing 
                                                                       | abs (x-a) <= abs (y-b) && o /= U = Just (Move id U)
                                                                       | abs (x-a) >  abs (y-b) && (positionsa (x,y+1) m) == Just Wall = Just (Move id U)
                                                                       | abs (x-a) >  abs (y-b) && o == R = Nothing
                                                                       | abs (x-a) >  abs (y-b) && o /= R = Just (Move id R)

-- | __'topLeftCorner'__: auxiliary function to 'goToCoords' that covers the situations refering to the top left corner of Pacman
topLeftCorner :: Maze -> Player -> Coords -> Maybe Play
topLeftCorner m (Pacman (PacState (id,(x,y),v,o,p,vi) t m' p')) (a,b) | o == R && (positionsa (x,y+2) m) == (Just Wall) && (positionsa (x+1,y+1) m) == (Just Wall) = Just (Move id D) -- These 2 cases are to prevent the Pacman
                                                                      | o == D && (positionsa (x+1,y+1) m) == (Just Wall) && (positionsa (x+2,y) m) == (Just Wall) = Just (Move id R) -- from being "trapped" between 2 walls
                                                                      | abs (x-a) <= abs (y-b) && (positionsa (x-1,y) m) == Just Wall = Just (Move id L)
                                                                      | abs (x-a) <= abs (y-b) && o == U = Nothing 
                                                                      | abs (x-a) <= abs (y-b) && o /= U = Just (Move id U)
                                                                      | abs (x-a) >  abs (y-b) && (positionsa (x,y-1) m) == Just Wall = Just (Move id U)
                                                                      | abs (x-a) >  abs (y-b) && o == L = Nothing
                                                                      | abs (x-a) >  abs (y-b) && o /= L = Just (Move id L)

-- | __'bottomRightCorner'__: auxiliary function to 'goToCoords' that covers the situations refering to the bottom right corner of Pacman
bottomRightCorner :: Maze -> Player -> Coords -> Maybe Play
bottomRightCorner m (Pacman (PacState (id,(x,y),v,o,p,vi) t m' p')) (a,b) | (x,y) == middleMaze m || (x+1,y) == middleMaze m || (x,y+1) == middleMaze m || (x+1,y+1) == middleMaze m || (x,y-1) == middleMaze m || (x-1,y-1) == middleMaze m = Just (Move id U)
                                                                          | o == L && (positionsa (x,y-2) m) == (Just Wall) && (positionsa (x-1,y-1) m) == (Just Wall) = Just (Move id U) -- These 2 cases are to prevent the Pacman
                                                                          | o == U && (positionsa (x-1,y-1) m) == (Just Wall) && (positionsa (x-2,b) m) == (Just Wall) = Just (Move id L) -- from being "trapped" between 2 walls
                                                                          | abs (x-a) <= abs (y-b) && (positionsa (x+1,y) m) == Just Wall = Just (Move id R)
                                                                          | abs (x-a) <= abs (y-b) && o == D = Nothing 
                                                                          | abs (x-a) <= abs (y-b) && o /= D = Just (Move id D)
                                                                          | abs (x-a) >  abs (y-b) && (positionsa (x,y+1) m) == Just Wall = Just (Move id D)
                                                                          | abs (x-a) >  abs (y-b) && o == R = Nothing
                                                                          | abs (x-a) >  abs (y-b) && o /= R = Just (Move id R)

-- | __'bottomLeftCorner'__: auxiliary function to 'goToCoords' that covers the situations refering to the bottom left corner of Pacman
bottomLeftCorner :: Maze -> Player -> Coords -> Maybe Play
bottomLeftCorner m (Pacman (PacState (id,(x,y),v,o,p,vi) t m' p')) (a,b) | (x,y) == middleMaze m || (x+1,y) == middleMaze m || (x,y+1) == middleMaze m || (x+1,y+1) == middleMaze m || (x,y-1) == middleMaze m || (x-1,y-1) == middleMaze m = Just (Move id U)
                                                                         | o == U && (positionsa (x-2,b) m) == (Just Wall) && (positionsa (x-1,y+1) m) == (Just Wall) = Just (Move id R) -- These 2 cases are to prevent the Pacman
                                                                         | o == R && (positionsa (x,y+2) m) == (Just Wall) && (positionsa (x-1,y+1) m) == (Just Wall) = Just (Move id U) -- from being "trapped" between 2 walls
                                                                         | abs (x-a) <= abs (y-b) && (positionsa (x+1,y) m) == Just Wall = Just (Move id L)
                                                                         | abs (x-a) <= abs (y-b) && o == D = Nothing 
                                                                         | abs (x-a) <= abs (y-b) && o /= D = Just (Move id D)
                                                                         | abs (x-a) >  abs (y-b) && (positionsa (x,y-1) m) == Just Wall = Just (Move id D)
                                                                         | abs (x-a) >  abs (y-b) && o == L = Nothing
                                                                         | abs (x-a) >  abs (y-b) && o /= L = Just (Move id L)

-- | __'up'__: auxiliary function to 'goToCoords' that covers the situations when the food or ghosts are above Pacman
up  :: Maze -> Player -> Coords -> Maybe Play
up m (Pacman (PacState (id,(x,y),v,o,p,vi) t m' p')) (a,b) | (positionsa (x-1,y) m) == Just Wall && (positionsa (x,y+1) m) == Just Wall = Just (Move id L) 
                                                           | (positionsa (x-1,y) m) == Just Wall = Just (Move id R)
                                                           | o == U = Nothing
                                                           | o /= U = Just (Move id U)

-- | __'down'__: auxiliary function to 'goToCoords' that covers the situations when the food or ghosts are under Pacman
down :: Maze -> Player -> Coords -> Maybe Play
down m (Pacman (PacState (id,(x,y),v,o,p,vi) t m' p')) (a,b) | (x,y) == middleMaze m || (x+1,y) == middleMaze m || (x,y+1) == middleMaze m || (x+1,y+1) == middleMaze m || (x,y-1) == middleMaze m || (x-1,y-1) == middleMaze m = Just (Move id U)
                                                             | (positionsa (x+1,y) m) == Just Wall && (positionsa (x,y-1) m) == Just Wall = Just (Move id R)
                                                             | (positionsa (x+1,y) m) == Just Wall = Just (Move id L)
                                                             | o == D = Nothing
                                                             | o /= D = Just (Move id D)

-- | __'right'__: auxiliary function to 'goToCoords' that covers the situations when the food or ghosts are at Pacman's right
right :: Maze -> Player -> Coords -> Maybe Play
right m (Pacman (PacState (id,(x,y),v,o,p,vi) t m' p')) (a,b) | (positionsa (x,y+1) m) == Just Wall && (positionsa (x+1,y) m) == Just Wall = Just (Move id U)
                                                              | (positionsa (x,y+1) m) == Just Wall = Just (Move id D)
                                                              | o == R = Nothing
                                                              | o /= R = Just (Move id R)

-- | __'left'__: auxiliary function to 'goToCoords' that covers the situations when the food or ghosts are at Pacman's left
left :: Maze -> Player -> Coords -> Maybe Play
left m (Pacman (PacState (id,(x,y),v,o,p,vi) t m' p')) (a,b) | (positionsa (x,y-1) m) == Just Wall && (positionsa (x-1,y) m) == Just Wall = Just (Move id D)
                                                             | (positionsa (x,y-1) m) == Just Wall = Just (Move id U)
                                                             | o == L = Nothing
                                                             | o /= L = Just (Move id L)

-- | __'corridor'__: auxiliary function to 'goToCoords' that puts Pacman in the tunnel if he needs it
corridor :: Maze -> Player -> Coords -> Maybe Play
corridor (h:t) (Pacman (PacState (id,(x,y),v,o,p,vi) t' m' p')) (a,b) | y < div (length h) 2 && b > div (length h) 2 && (positionsa (x,y-1) (h:t)) == Just Wall && a<=x = Just (Move id U)  ---- Go through
                                                                      | y < div (length h) 2 && b > div (length h) 2 && (positionsa (x,y-1) (h:t)) == Just Wall && a>x  = Just (Move id D)  -- the tunnel
                                                                      | y < div (length h) 2 && b > div (length h) 2 && o == L = Nothing                                                    -- on the
                                                                      | y < div (length h) 2 && b > div (length h) 2 && o /= L = Just (Move id L)                                           -- left
                                                                      | y > div (length h) 2 && b < div (length h) 2 && (positionsa (x,y+1) (h:t)) == Just Wall && a<=x = Just (Move id U)  ---- Go through
                                                                      | y > div (length h) 2 && b < div (length h) 2 && (positionsa (x,y+1) (h:t)) == Just Wall && a>x  = Just (Move id D)  -- the tunnel
                                                                      | y < div (length h) 2 && b > div (length h) 2 && o == R = Nothing                                                    -- on the
                                                                      | y > div (length h) 2 && b < div (length h) 2 && o /= R = Just (Move id R)                                           -- right
                                                                      | otherwise = Nothing

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

-- | __'escapePacma'__: this function gives pacman's plays when he needs to escape from the ghosts
escapePacman :: Maze      -- ^ maze used to find if a certain position is a wall or not
            -> Player     -- ^ the pacman if there is a ghost in front of him, in general, he turns to the other side
            -> Coords     -- ^ coords of the nearest ghost
            -> Maybe Play                                                                                                                                                                                                    ----------
escapePacman m (Pacman (PacState (id,(x,y),v,o,p,vi) t' m' p')) (a,b) | (x,y) == middleMaze m || (x+1,y) == middleMaze m || (x,y+1) == middleMaze m || (x+1,y+1) == middleMaze m || (x,y-1) == middleMaze m || (x-1,y-1) == middleMaze m = Just (Move id U) 
                                                                      | x == div (length m) 2 && ( (y == k - 1) || (y == k - 2) || (y == k - 3) ) = Just (Move id R)
                                                                      | x == div (length m) 2 && ( (y == 0) || (y == 1) || (y == 2) ) = Just (Move id L)
                                                                      | x == a && y < b && positionsa (x,y-1) m == Just Wall && positionsa (x-1,y) m == Just Wall = Just (Move id D)
                                                                      | x == a && y < b && positionsa (x,y-1) m == Just Wall = Just (Move id U)
                                                                      | x == a && y < b && o == L = Nothing
                                                                      | x == a && y < b && o /= L = Just (Move id L)
                                                                      | x == a && y >  b && positionsa (x,y+1) m == Just Wall && positionsa (x+1,y) m == Just Wall = Just (Move id U)
                                                                      | x == a && y >  b && positionsa (x,y+1) m == Just Wall = Just (Move id D)
                                                                      | x == a && y >  b && o == R = Nothing
                                                                      | x == a && y >  b && o /= R = Just (Move id R)
                                                                      | y == b && x < a && positionsa (x-1,y) m == Just Wall && positionsa (x,y+1) m == Just Wall = Just (Move id L)
                                                                      | y == b && x < a && positionsa (x-1,y) m == Just Wall = Just (Move id R)
                                                                      | y == b && x < a && o == U = Nothing
                                                                      | y == b && x < a && o /= U = Just (Move id U)
                                                                      | y == b && x >  a && positionsa (x+1,y) m == Just Wall && positionsa (x,y-1) m == Just Wall = Just (Move id R)
                                                                      | y == b && x >  a && positionsa (x+1,y) m == Just Wall = Just (Move id L)
                                                                      | y == b && x >  a && o == D = Nothing
                                                                      | y == b && x >  a && o /= D = Just (Move id D)
                                                                      | abs (x-a) > abs (y-b) && y >=b && positionsa (x,y+1) m == Just Wall && positionsa (x+1,y) m == Just Wall = Just (Move id U)
                                                                      | abs (x-a) > abs (y-b) && y >=b && positionsa (x,y+1) m == Just Wall = Just (Move id D)
                                                                      | abs (x-a) > abs (y-b) && y >=b && o == R = Nothing
                                                                      | abs (x-a) > abs (y-b) && y >=b && o /= R = Just (Move id R)
                                                                      | abs (x-a) > abs (y-b) && y <=b && positionsa (x,y-1) m == Just Wall && positionsa (x+1,y) m == Just Wall = Just (Move id U)
                                                                      | abs (x-a) > abs (y-b) && y <=b && positionsa (x,y-1) m == Just Wall = Just (Move id D)
                                                                      | abs (x-a) > abs (y-b) && y <=b && o == L = Nothing
                                                                      | abs (x-a) > abs (y-b) && y <=b && o /= L = Just (Move id L)
                                                                      | abs (x-a) < abs (y-b) && x > a && positionsa (x+1,y) m == Just Wall && positionsa (x,y+1) m == Just Wall = Just (Move id L)
                                                                      | abs (x-a) < abs (y-b) && x > a && positionsa (x+1,y) m == Just Wall = Just (Move id R)
                                                                      | abs (x-a) < abs (y-b) && x > a && o == D = Nothing
                                                                      | abs (x-a) < abs (y-b) && x > a && o /= D = Just (Move id D)
                                                                      | abs (x-a) < abs (y-b) && x < a && positionsa (x-1,y) m == Just Wall && positionsa (x,y-1) m == Just Wall = Just (Move id R)
                                                                      | abs (x-a) < abs (y-b) && x < a && positionsa (x-1,y) m == Just Wall = Just (Move id L)
                                                                      | abs (x-a) < abs (y-b) && x < a && o == U = Nothing
                                                                      | abs (x-a) < abs (y-b) && x < a && o /= U = Just (Move id U)
                                                                      | otherwise = Nothing
                                                                   where k  = k' m
                                                                         k' :: Maze -> Int
                                                                         k' (h:t) = length h


---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

-- Data to test

estado :: State
estado = (State labirintoMaze jogadores 1)

jogadores :: [Player]
jogadores = [jogadorPacman,fantasma]

jogadorPacman :: Player
jogadorPacman = (Pacman (PacState (0,(7,4),1,U,0,1) 0 Open Mega))
fantasma :: Player
fantasma = (Ghost (GhoState (2,(1,3),1,R,0,1) Alive))

labirintoMaze :: Maze
labirintoMaze = labirintoteste labirintoState
labirintoteste :: State -> Maze
labirintoteste (State m pl 1) = m
labirintoState :: State
labirintoState = loadMaze "../maps/TesteTarefa6WallFoods.txt"

teste :: Maybe Play
teste = bot (getPlayerID jogadorPacman) estado

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------