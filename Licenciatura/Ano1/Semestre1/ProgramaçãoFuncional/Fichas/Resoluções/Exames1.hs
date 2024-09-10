module Exames where

import Data.Char
import System.Random

-- Exercicio 1
-- (a)

elemIndices :: Eq a => a -> [a] -> [Int]
elemIndices x l = elemIndicesAC x l 0
               where elemIndicesAC x [] ac = []
                     elemIndicesAC x (h:t) ac | x == h = ac : (elemIndicesAC x t (ac + 1))
                                              | otherwise = elemIndicesAC x t (ac + 1)

isSubsequenceOf :: Eq a => [a] -> [a] -> Bool
isSubsequenceOf [] _ = True
isSubsequenceOf _ [] = False
isSubsequenceOf (x:xs) (y:ys) | x == y = isSubsequenceOf xs ys
                              | otherwise = isSubsequenceOf (x:xs) ys

-- Exercicio 2

data BTree a = Empty | Node a (BTree a) (BTree a)
exBT = Node 3 (Node 9 Empty Empty) (Node 2 Empty (Node 7 Empty Empty))

-- (a)
lookupAP :: Ord a => a -> BTree (a,b) -> Maybe b
lookupAP x Empty = Nothing
lookupAP x (Node (a,b) l r) | x == a = Just b
                            | x <  a = lookupAP x l
                            | x >  a = lookupAP x r

-- (b)
zipWithBT :: (a -> b -> c) -> BTree a -> BTree b -> BTree c
zipWithBT f (Node x1 l1 r1) (Node x2 l2 r2) = Node (f x1 x2) (zipWithBT f l1 l2) (zipWithBT f r1 r2) 
zipWithBT f _ _ = Empty

-- Exercicio 3
digitAlpha :: String -> (String,String)
digitAlpha (h:t) = digitAlphaAC (h:t) ("","")
                where digitAlphaAC [] (l,r) = (l,r)
                      digitAlphaAC (h:t) (l,r) | isDigit h = digitAlphaAC t (l ++ [h],r)
                                               | otherwise = digitAlphaAC t (l,r ++ [h])

-- Exercicio 4

data Seq a = Nil | Cons a (Seq a) | App (Seq a) (Seq a)

exSeq = App (Cons 1 Nil) (App (Cons 7 (Cons 5 Nil)) (Cons 3 Nil))
exSeq'= (App (App (Cons 7 (Cons 5 Nil)) (Cons 3 Nil)) (Cons 1 Nil))

-- (a)
firstSeq :: Seq a -> a
firstSeq (Cons a _) = a
firstSeq (App Nil r) = firstSeq r
firstSeq (App l r)  = firstSeq l 

-- (b)
dropSeq :: Int -> Seq a -> Seq a
dropSeq _ Nil = Nil
dropSeq x (Cons a r) = dropSeq (x-1) r
dropSeq x (App e d)  | x > (contaSeq e) = dropSeq (x - contaSeq e) d
                     | x == contaSeq e = d
                     | otherwise = (App (dropSeq x e) d)

contaSeq :: Seq a -> Int
contaSeq Nil = 0
contaSeq (Cons a l) = 1 + contaSeq l
contaSeq (App e d)  = contaSeq e + contaSeq d

-- (c)
instance Show a => Show (Seq a) where
     show a = "<<" ++ mostra a ++ ">>"

mostra :: Show a => Seq a -> String
mostra Nil = ""
mostra (Cons a Nil) = (show a)
mostra (Cons a l) = (show a) ++ "," ++ (mostra l) 
mostra (App l r) = mostra l ++ "," ++ mostra r

-- Exercicio 5

type Mat a = [[a]]

matriz = [[6,7,2], [1,5,9], [8,3,4]]

-- (a)
getElem :: Mat a -> IO a
getElem a = do x <- randomRIO (0,(length a)-1)
               y <- randomRIO (0,(length (head a))-1)
               return ((a!!x)!!y)

--magic :: Mat Int -> Bool

--linhaTeste :: Mat Int -> Bool
--linhaTeste [] = True
--linhaTeste (h:t) | sum h == sum (head t) = linhaTeste t
--                 | otherwise = False

--colunaTeste :: Mat Int -> Bool

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

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

triSup :: Num a => Mat a -> Bool 
triSup (h:t) = triSupAC t 1
           where triSupAC [] ac = True
                 triSupAC (h:t) ac | elem 0 (take ac h) == False = False
                                   | otherwise = triSupAC t (ac+1)




































































