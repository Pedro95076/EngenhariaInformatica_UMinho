module Ficha4 where

{-
(a) [x | x <- [1..20], mod x 2 == 0, mod x 3 == 0]
retorna uma lista com todos os valores de x entre 1 e 20 que são divísveis por 2 E divisíveis por 3
(b) [x | x <- [y | y <- [1..20], mod y 2 == 0] , mod x 3 == 0]
retorna uma lista x que verifica dentro de uma lista de numeros pares de 0 a 20 , 
aqueles que são divisíveis por 3
(c) [(x,y) | x <- [0..20], y <- [0..20], x+y == 30]
retorna tuplos de valores x e y de valores entre 0 e 20 em que a sua soma é == 30
                   lista de impares até x              
(d) [ sum  [ y |  y <- [1..x] , odd y] | x <- [1..10]]
[1,1,4,4,9,9,16,16,25,25]
retorna a soma dos elementos impares de 1 a x para todo o x de 1 a 10
a) [1,2,4,8,16,32,64,128,256,512,1024]
   [2^x | x <- [1..10]]
b) [(1,5),(2,4),(3,3),(4,2),(5,1)]
   [(x,6-x) | x <- [1..5]]
c) [[1],[1,2],[1,2,3],[1,2,3,4],[1,2,3,4,5]]
   [take x [1..5] | x <- [1..5]]
   [ [1..x] | x <- [1..5]]
d) [[1],[1,1],[1,1,1],[1,1,1,1],[1,1,1,1,1]]
   [take x [1,1,1,1,1] | x <- [1,5]]
   [take x [1,1..] | x <- [1,5]]
   [replicate x 1 | x <- [1..5]]
e) [1 , 2, 6, 24, 120, 720]    
   [ product [1..x] | x <- [1..6] ]
-}

import Data.Char
import Data.List
digitAlpha :: String -> (String,String)
--digitAlpha =. (filter isDigit l,filter isAlpha l)
digitAlpha [] = ([],[])
digitAlpha (h:t)
    | isDigit h = (h:p ,q)
    | isAlpha h = (p, h:q)
    | otherwise = (p,q)
    where (p,q) = digitAlpha t

nzp :: [Int] -> (Int,Int,Int)
nzp [] = (0,0,0)
nzp (h:t)
    | h > 0 = (p,q,r+1)
    | h < 0 = (p+1,q,r)
    | otherwise = (p,q+1,r)
    where (p,q,r) = nzp t


div' :: Int -> Int -> Int
div' x y 
    | x < y = 0 
    | x >= y = 1 + div' (x-y) y

mod' :: Int -> Int -> Int 
mod' x y
    | x < y = x
    | x >= y = mod (x-y) y

divMod' :: Integral a => a -> a -> (a, a)
divMod' x y
    | x < y = (0,x)
    | x >= y = (1+ p ,q)
    where (p,q) = divMod'(x-y) y



fromDigits :: [Int] -> Int
fromDigits l = faux 0 l
faux x [] = x
faux x (h:t) = faux (x + h * 10 ^ (length t)) t

fromDigits2 l = foldr (\x a -> 10 * a + x) 0 l


fromDigits3 l = foldl (\a x -> 10 * a + x) 0 l



-- transforma um int de 0 a 9 em "0"..."9"
cint :: Int -> String
--cint x =. [chr(ord '0'+x)]--intToDigit x
cint = (:[]) . chr . (+48)
--cint2 :: Int -> [Char] ????????????????
cint2 = [ chr . (+48)]

--converte string to int

si :: String -> Int
si "" = 0
si (h:t) =(digitToInt h) * 10 ^ (length t) + si t

si3 :: String -> Int
si3 l = foldr (\x a -> a*10 + (digitToInt x) ) 0 l






maxSumInit :: (Num a, Ord a) => [a] -> a
--maxSumInit l =. maximum [sum m | m <- inits l]
maxSumInit l = maux  0 0 l
    where maux m s (x:xs) 
              | m < (s + x)  = maux (x+s) (s+x) xs
              | otherwise = maux m (s+x) xs


fib:: Integer -> Integer

fib 0 = 0
fib 1 = 1


--fib n = fib (n-1) + fib (n-2)

--fib 10 = fib 9 + fib 8 = fib 8 + fib 7 + fib 7+ fib 6 = fib 7+fib 6+fib 6+fib 5+fib 6+fib 5+fib 5+fib 4 

--1,1,2,3,5,8,13,21,34,55,89,144,233,377

fib n = fiaux n (0,1)

  where fiaux 0 (a,b) = a
        fiaux 1 (a,b) = b
        fiaux n (a,b) = fiaux (n-1) (b,b+a)

--f 10 (0,1) = f 9 (1,1) = f 8 (1,2) = f 7 (2,3) = f 6 (3,5) = f5 ( 5,8) = f4 (8,13) = f3 (13,21) = f 2 ( 21, 34) = f1 (34,55)= 55


seqFib = 0:1: [ a+b | (a,b) <- zip seqFib (tail seqFib)]




-- crivo de [2..n]
crivo [] = []
crivo (x:xs) = x : crivo [ n | n <- xs , mod n x /= 0 ]