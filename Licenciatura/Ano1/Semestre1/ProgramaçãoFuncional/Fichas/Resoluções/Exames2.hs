module Exames1718 where

-- 30 de Janeiro de 2018

-- Exercicio 1
p1 :: [a] -> Int -> a
p1 (h:t) 0 = h
p1 (h:t) x = p1 t (x-1)

-- Exercicio 2

data Movimento = Norte | Sul | Este | Oeste deriving Show

posicao :: (Int,Int) -> [Movimento] -> (Int,Int)
posicao (x,y) [] = (x,y)
posicao (x,y) (Norte:t) = posicao (x,y+1) t
posicao (x,y) (Sul:t)   = posicao (x,y-1) t
posicao (x,y) (Oeste:t) = posicao (x-1,y) t
posicao (x,y) (Este:t)  = posicao (x+1,y) t

-- Exercicio 3
any' :: (a -> Bool) -> [a] -> Bool 
any' f [] = False
any' f (h:t) | f h == True = True
             | otherwise = any' f t 

-- Exercicio 4
type Mat a = [[a]] 

ex1 = [[1,2,3], [0,4,5], [0,0,6]]

triSup :: (Num a,Eq a) => Mat a -> Bool 
triSup (h:t) = triSupAC t 1
           where triSupAC [] ac = True
                 triSupAC (h:t) ac | elem 0 (take ac h) == False = False
                                   | otherwise = triSupAC t (ac+1)

-- Exercicio 5
movimenta :: IO (Int,Int)
movimenta = movimenta' (0,0)

movimenta' :: (Int,Int) -> IO (Int,Int)
movimenta' (x,y) = do k <- getChar
                      case k of
                          'n' -> movimenta' (x,y+1)
                          's' -> movimenta' (x,y-1)
                          'o' -> movimenta' (x-1,y)
                          'e' -> movimenta' (x+1,y)
                          otherwise -> return (x,y)

-- Exercicio 6

data Imagem = Quadrado Int
            | Mover (Int,Int) Imagem
            | Juntar [Imagem]

ex2 :: Imagem
ex2 = Mover (5,5) (Juntar [Mover (0,1) (Quadrado 5),Quadrado 4,Mover (4,3) (Quadrado 2)])
ex3 = Juntar [Mover (5,5) (Quadrado 4), Mover (5,6) (Quadrado 5), Mover (9,8) (Quadrado 2)]

-- (a)
vazia :: Imagem -> Bool
vazia (Quadrado x) = False
vazia (Mover (x,y) i) = vazia i
vazia (Juntar l) | null l = True
                 | elem False (map vazia l) = False
                 | otherwise = True

-- (b)
maior :: Imagem -> Maybe Int
maior i = if null (maiorAC i []) then Nothing else Just (maximum  (maiorAC i []))
       where maiorAC (Quadrado x) ac = ac ++ [x]
             maiorAC (Mover (x,y) i) ac = maiorAC i ac
             maiorAC (Juntar []) ac = ac
             maiorAC (Juntar (h:t)) ac = (maiorAC h ac) ++ (maiorAC (Juntar t) ac) 

-- (c)

instance Eq Imagem where
    i1 == i2 = iguais (pos i1) (pos i2)

iguais :: [(Int,(Int,Int))] -> [(Int,(Int,Int))] -> Bool
iguais [] l = True
iguais (h:t) l | elem h l = iguais t l
               | otherwise = False

pos :: Imagem -> [(Int,(Int,Int))]
pos i = posAC i (0,0) []

posAC :: Imagem -> (Int,Int) -> [(Int,(Int,Int))] -> [(Int,(Int,Int))]
posAC (Quadrado k) (x,y) ac = ac ++ [(k,(x,y))]
posAC (Mover (a,b) i) (x,y) ac = posAC i (x+a,y+b) ac
posAC (Juntar []) (x,y) ac = []
posAC (Juntar (h:t)) (x,y) ac  = (posAC h (x,y) ac) ++ (posAC (Juntar t) (x,y) ac)










































