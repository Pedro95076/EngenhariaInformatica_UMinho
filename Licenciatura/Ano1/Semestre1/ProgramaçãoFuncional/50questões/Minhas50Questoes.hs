module ExameQuestoes where

--Usado na p.30
--import Data.Char
-- Usado na 42
--import Data.Either

-- Questao 1
myenumFromTo :: Int -> Int -> [Int]
myenumFromTo x y | x == y = [x]
                 | x > y = x : (myenumFromTo (x-1) y)
                 | otherwise = x : (myenumFromTo (x+1) y)

-- Questao 2
myenumfromthento :: Int -> Int -> Int -> [Int]
myenumfromthento x y z | y < x || x > z = []
                       | x == y = [x]
                       | otherwise = x:myenumfromthento y (y+(y-x)) z

-- Questao 3
concatena :: [a] -> [a] -> [a]
concatena [] l = l
concatena (h:t) l = h:concatena t l

-- Questao 4
elementodalista :: [a] -> Int -> a
elementodalista (h:t) x | x==0 = h
                        | otherwise = elementodalista t (x-1)

-- Questao 5
myreverse :: [a] -> [a]
myreverse [] = []
myreverse (h:t) = myreverse t ++ [h]

-- Questao 6
mytake :: Int -> [a] -> [a]
mytake _ [] = []
mytake x (h:t) | x==0 = []
               | otherwise = h:mytake (x-1) t 

-- Questao 7
mydrop :: Int -> [a] -> [a]
mydrop 0 l = l
mydrop _ [] = []
mydrop x (h:t) = mydrop (x-1) t

-- Questao 8
myzip :: [a] -> [b] -> [(a,b)]
myzip (x:xs) (y:ys) = (x,y) : myzip xs ys
myzip _ _ = []

-- Questao 9
myelem :: Eq a => a -> [a] -> Bool
myelem x [] = False
myelem x (h:t) | x==h = True
               | otherwise = myelem x t

-- Questao 10
myreplica :: Int -> a -> [a]
myreplica x e | x==0 = []
              | otherwise = e:myreplica (x-1) e

-- Questao 11
myintersperse :: a -> [a] -> [a]
myintersperse _ [x] = [x]
myintersperse x (h:t) = h:x:myintersperse x t

-- Questao 12
mygroup :: Eq a => [a] -> [[a]]
mygroup [] = []
mygroup l  = mygroupaux l : mygroup (drop (length (mygroupaux l)) l)

mygroupaux :: Eq a => [a] -> [a]
mygroupaux [x] = [x]
mygroupaux (x:t) | x==head t = x:mygroupaux t
                 | otherwise = [x]

-- Questao 13
myconcat :: [[a]] -> [a]
myconcat [] = []
myconcat (h:t) = h ++ myconcat t

-- Questao 14
myinits :: [a]->[[a]]
myinits [] = [[]]
myinits l = myinits (init l) ++ [l]

-- Questao 15
mytails :: [a]->[[a]]
mytails [] = [[]]
mytails l = [l] ++ mytails (drop 1 l)

-- Questao 16
myisprefixof :: Eq a => [a] -> [a] -> Bool
myisprefixof [] _ = True
myisprefixof (x:xs) (y:ys) | x==y = myisprefixof xs ys
                           | otherwise = False 

-- Questao 17
myissuffixof :: Eq a => [a] -> [a] -> Bool
myissuffixof [] _ = True
myissuffixof l1 l2 | last l1 == last l2 = myissuffixof (init l1) (init l2)
                   | otherwise = False

-- Questao 18
myissubsequenceof :: Eq a => [a] -> [a] -> Bool
myissubsequenceof [] _ = True
myissubsequenceof _ [] = False
myissubsequenceof (x:xs) (y:ys) | x==y = myissubsequenceof xs ys
                                | otherwise = myissubsequenceof (x:xs) ys

-- Questao 19 :
{- Sem acumulador
myelemindices :: Eq a => a -> [a] -> [Int]
myelemindices _ [] = []
myelemindices x l | x == last l = myelemindices x (init l) ++ [((length l) - 1)]
                  | otherwise = myelemindices x (init l)
-}

-- Com acumulador
myelemindices :: Eq a => a -> [a] -> [Int]
myelemindices x l = myelemindicesAC x l 0
                  where myelemindicesAC x [] ac = []
                        myelemindicesAC x l ac | x == head l = ac : myelemindicesAC x (drop 1 l) (ac+1)
                                               | otherwise = myelemindicesAC x (drop 1 l) (ac+1)

-- Questao 20 :
{-
mynub :: Eq a => [a] -> [a]
mynub [] = []
mynub (h:t) | elem h t = mynub t
            | otherwise = h:mynub t
-}

mynub :: Eq a => [a] -> [a]
mynub l = g [] l
g l2 [] = l2
g l2 (a:b) | elem a l2 = g l2 b 
           | otherwise = g (l2++[a]) b                                                                                    

-- Questao 21
mydelete :: Eq a => a -> [a] -> [a]
mydelete x (h:t) | elem x (h:t) == False = (h:t) 
                 | x==h = t
                 | otherwise = h:mydelete x t

-- Questao 22 
myremove :: Eq a => [a] -> [a] -> [a]
myremove l [] = l
myremove [] _ = []
myremove (x:xs) (y:ys) | x==y = myremove xs ys
                       | otherwise = x : myremove xs (y:ys)

-- Questao 23
myunion :: Eq a => [a] -> [a] -> [a]
myunion l [] = l
myunion [] l = l
myunion l (h:t) | elem h l = myunion l t
                | otherwise = (myunion l t) ++ [h]

-- Questao 24
myintersect :: Eq a => [a] -> [a] -> [a]
myintersect l [] = l
myintersect [] l = []
myintersect (h:t) l | elem h l = h:(myintersect t l)
                    | otherwise = myintersect t l

-- Questao 25
myinsert :: Ord a => a -> [a] -> [a]
myinsert x [] = [x]
myinsert x (h:t) | x<=h = x:h:t
                 | otherwise = h:myinsert x t

-- Questao 26
myunwords :: [String] -> String
myunwords []    = ""
myunwords [x]   = x
myunwords (h:t) = h++" "++myunwords t

-- Questao 27
myunlines :: [String] -> String
myunlines []    = ""
myunlines (h:t) = h++"\n"++myunlines t

-- Questao 28
   -- Maneira que o Daniel fez
posicao' :: Ord a => [a] -> Int
posicao' [x] = 0
posicao' (h:t) | maximo (h:t) == h = 0
               | otherwise = posicao' t + 1

maximo :: Ord a => [a] -> a
maximo [x] = x
maximo (x:y:t) | x>y = maximo (x:t)
               | x<y = maximo (y:t)

-- Questao 29
temrepetidos :: Eq a => [a] -> Bool
temrepetidos [] = False
temrepetidos (h:t) | elem h t  = True
                   | otherwise = temrepetidos t

-- Questao 30 
{- Usando Data.Char
algarismos :: [Char] -> [Char]
algarismos [] = []
algarismos (h:t) | isDigit h = h:algarismos t
                 | otherwise = algarismos t
-}

algarismos :: [Char] -> [Char]
algarismos [] = []
algarismos (a:b) = if elem a ['0'..'9'] then a:algarismos b 
                   else algarismos b 

-- Questao 31 
posimpares :: [a] -> [a]
posimpares []      = []
posimpares [x]     = []
posimpares (x:y:t) = y:posimpares t

-- Questao 32
pospares :: [a] -> [a]
pospares []      = []
pospares [x]     = [x]
pospares (x:y:t) = x:pospares t

-- Questao 33
issorted :: Ord a => [a] -> Bool
issorted []  = True
issorted [x] = True
issorted (x:y:t) | x>y = False
                 | otherwise = issorted (y:t)

-- Questao 34
isort :: Ord a => [a] -> [a]
isort [] = []
isort (h:t) = insert h (isort t)

         -- No enunciado diz "assuma que existe definida a funcao "insert"
insert :: (Ord a) => a -> [a] -> [a]
insert x [] = [x]
insert x (y:ys) | x<=y = x:y:ys
                | otherwise = y : insert x ys

-- Questao 35
menor :: String -> String -> Bool
menor [] _ = True
menor _ [] = False
menor (x:xs) (y:ys) | x<y = True
                    | x>y = False
                    | otherwise = menor xs ys

-- Questao 36
elemmset :: Eq a => a -> [(a,Int)] -> Bool 
elemmset n [] = False
elemmset n ((x,y):t) | n==x = True
                     | otherwise = elemmset n t

-- Questao 37
lengthmset :: [(a,Int)] -> Int
lengthmset [] = 0
lengthmset ((x,y):t) = y + lengthmset t

-- Questao 38
convertemset :: [(a,Int)] -> [a]
convertemset [] = []
convertemset ((x,k):t) = cadapar (x,k) ++ convertemset t
                   where cadapar (x,0) = []
                         cadapar (x,k) = x : cadapar (x,k-1)

-- Questao 39
inseremset :: Eq a => a -> [(a,Int)] -> [(a,Int)]
inseremset k [] = [(k,1)]
inseremset k ((x,y):t) | k==x = ((x,y+1):t)
                       | otherwise = (x,y) : inseremset k t

-- Questao 40
removemset :: Eq a => a -> [(a,Int)] -> [(a,Int)]
removemset k [] = []
removemset k ((x,y):t) | k==x && y==1 = t
                       | k==x && y>1  = ((x,y-1):t)
                       | otherwise = (x,y) : removemset k t

-- Questao 41
constroimset :: Ord a => [a] -> [(a,Int)]
constroimset [] = [] 
constroimset l = (head l,h):(constroimset (drop h l))
      where h = length (g l)
            g [x] = [x]
            g (x:t) | x==head t = x:g t
                    | otherwise = [x]

-- Questao 42
{-   -- Minha maneira
mypartitioneithers :: [Either a b] -> ([a],[b])
mypartitioneithers l = (left l, right l)
                     where left (Left a:t) = a:left t
                           left (Right a:t) = left t
                           left [] = []
                           right (Right a:t) = a:right t
                           right (Left a:t) = right t
                           right [] = []
-}

   -- Maneira que a stora mostrou
mypartitioneithers' :: [Either a b] -> ([a],[b])
mypartitioneithers' [] = ([],[])
mypartitioneithers' ((Left x):t) = (x:l1,l2)
                 where (l1,l2) = mypartitioneithers' t
mypartitioneithers' ((Right x):t) = (l1,x:l2)
                 where (l1,l2) = mypartitioneithers' t

-- Questao 43
catmaybes :: [Maybe a] -> [a]
catmaybes [] = []
catmaybes (Just a:t)  = a:catmaybes t
catmaybes (Nothing:t) =   catmaybes t

-- Questao 44
data Movimento = Norte | Sul | Este | Oeste
              deriving Show

posicao:: (Int,Int)->[Movimento]->(Int,Int)
posicao (x,y) []        = (x,y)  
posicao (x,y) (Norte:t) = posicao (x,y+1) t
posicao (x,y) (Sul  :t) = posicao (x,y-1) t
posicao (x,y) (Este :t) = posicao (x+1,y) t
posicao (x,y) (Oeste:t) = posicao (x-1,y) t

-- Questao 45
--data Movimento = Norte | Sul | Este | Oeste
--               deriving Show

caminho :: (Int,Int) -> (Int,Int) -> [Movimento]
caminho (x,y) (a,b) | x==a && y==b = []
                    | x<a = [Este]  ++ caminho (x+1,y) (a,b)
                    | x>a = [Oeste] ++ caminho (x-1,y) (a,b)
                    | y<b = [Norte] ++ caminho (x,y+1) (a,b)
                    | y>b = [Sul]   ++ caminho (x,y-1) (a,b)

-- Questao 46
--data Movimento = Norte | Sul | Este | Oeste
--               deriving Show

vertical :: [Movimento] -> Bool
vertical [] = True
vertical (Norte:t) = vertical t
vertical (Sul:t)   = vertical t
vertical (_:t) = False

-- Questao 47
data Posicao = Pos Int Int
             deriving Show

maiscentral :: [Posicao] -> Posicao
maiscentral [x] = x
maiscentral (x:y:t) | dcentral x <= dcentral y = maiscentral (x:t)
                    | dcentral x >  dcentral y = maiscentral (y:t)
                where dcentral (Pos a b) = sqrt (fromIntegral(a^2 + b^2))

-- Questao 48
--data Posicao = Pos Int Int
--             deriving Show

vizinhos :: Posicao -> [Posicao] -> [Posicao]
vizinhos _ [] = []
vizinhos (Pos x y) ((Pos a b):t) | x==a+1 && y==b = (Pos a b):vizinhos (Pos x y) t 
                                 | x==a-1 && y==b = (Pos a b):vizinhos (Pos x y) t
                                 | x==a && y==b+1 = (Pos a b):vizinhos (Pos x y) t
                                 | x==a && y==b-1 = (Pos a b):vizinhos (Pos x y) t
                                 | otherwise      = vizinhos (Pos x y) t

-- Questao 49
--data Posicao = Pos Int Int
--             deriving Show

mesmaordenada :: [Posicao] -> Bool
mesmaordenada [x] = True
mesmaordenada ((Pos x y):(Pos a b):t) | y==b      = mesmaordenada ((Pos a b):t)
                                      | otherwise = False

-- Questao 50
data Semaforo = Verde | Amarelo | Vermelho
              deriving Show

interseccaook :: [Semaforo] -> Bool
interseccaook l = cor l <= 1
                where cor [Vermelho] = 0 
                      cor [Amarelo]  = 1
                      cor [Verde]    = 1
                      cor (Vermelho:t) = 0 + cor t 
                      cor (Amarelo:t)  = 1 + cor t
                      cor (Verde:t)    = 1 + cor t 