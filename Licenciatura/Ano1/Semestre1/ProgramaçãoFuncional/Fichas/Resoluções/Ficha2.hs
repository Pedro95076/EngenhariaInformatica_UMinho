module Ficha2 where

{-
1:
a) o output é a soma de todos os valores da lista ao quadrado
funA [2,3,5,1] = 4+9+25+1 = 34
b) o output é uma lista com todos os números pares da listra introduzida
funB [8,5,12] = [8,12]
 
c) a função vai pegando no tail da lista recursivamente até ter 1 elemento ou 0, aí retorna lista vaiz
funC [1,2,3,4,5] = []
d)da funçao utiliza um acomulador que adicion a cabeça a uma lista, devolve o inverso da string inicial
-}
import Data.Char
-- 2
dobros :: [Float] -> [Float]
dobros [] = []
dobros (a:b) = 2*a:dobros b



dobros2 :: [Float] -> [Float]
dobros2 l = [ x * 2 | x <- l] -- lista em compreensao


numOcorre :: Char -> String -> Int
numOcorre x [] = 0 
numOcorre x (a:b)
    | x == a    = 1 + numOcorre x b
    | otherwise = numOcorre x b



positivos :: [Int] -> Bool
positivos [] = True
positivos (a:b)
    | mod a 2 == 0 = positivos b
    | otherwise    = False


soPos :: [Int] -> [Int]
soPos [] = []
soPos (a:b)
    | a <= 0 = soPos b
    | otherwise = a:soPos b 

somaNeg :: [Int] -> Int
somaNeg [] = 0
somaNeg (a:b)
    | a < 0 = a + somaNeg b
    | otherwise = somaNeg b

tresUlt :: [a] -> [a]
tresUlt (a:b)
    | length (a:b) == 3 = (a:b)
    | otherwise = tresUlt b

segundos :: [(a,b)] -> [b]
segundos [] = []
segundos ((a,b):c) = b:segundos c


nosPrimeiros :: (Eq a) => a -> [(a,b)] -> Bool
nosPrimeiros _ [] = False
nosPrimeiros x ((a,b):c)
    | x == a = True
    | otherwise = nosPrimeiros x c



sumTriplos :: (Num a, Num b, Num c) => [(a,b,c)] -> (a,b,c)
sumTriplos [] = (0,0,0)
sumTriplos [(a,b,c)] = (a,b,c)
sumTriplos ( (a,b,c) : h ) = (a+x1,b+x2,c+x3) where (x1,x2,x3) = (sumTriplos h)

sumTriplos2 :: (Num a, Num b, Num c) => [(a,b,c)] -> (a,b,c)
sumTriplos2 l = g (0,0,0) l 
g (a,b,c) [] = (a,b,c)
g (a,b,c) ((z1,z2,z3):t) = g (a+z1,b+z2,c+z3) t

-- 3
-- Nota:  "abc" = ['a','b','c']
soDigitos :: [Char] -> [Char]
soDigitos [] = []
soDigitos (a:b) = if elem (ord a) [48..57] then a:soDigitos b else soDigitos b


minusculas :: [Char] -> Int
minusculas [] = 0
minusculas (a:b) = if elem (ord a) [97..122] then 1 + minusculas b else minusculas b


nums :: String -> [Int]
nums [] = []
nums (a:b) = if elem (ord a) [48..57] then (digitToInt a):nums b else nums b

-- 4


-- (coeficiente, expoente) (2,3)-> 2x^3

type Polinomio = [Monomio]
type Monomio = (Float,Int)

conta :: Int -> Polinomio -> Int
conta n [] = 0
conta n ((a,b):t) = if b == n then 1 + conta n t else conta n t 

grau :: Polinomio -> Int
grau [] = 0
grau [(a,b)] = b
grau ((a,b):t) = max b (grau t) 

selgrau :: Int -> Polinomio -> Polinomio
selgrau _ [] = []
selgrau x ((a,b):t) | x == b = (a,b):selgrau x t
                    | otherwise = selgrau x t

deriv :: Polinomio -> Polinomio
deriv [] = []
deriv ((a,0):t) = deriv t
deriv ((a,b):t) = ( a * (fromIntegral b :: Float) ,b-1) : deriv t 

calcula :: Float -> Polinomio -> Float
calcula _ [] = 0
calcula x ((a,b):t) = a * (x^b) + calcula x t

simp :: Polinomio -> Polinomio
simp [] = []
simp ((a,b):t) = if a == 0 then simp t else (a,b) : simp t

mult :: Monomio -> Polinomio -> Polinomio
mult _ [] = [] 
mult (x,y) ((a,b):t) = (a*x,b+y):(mult (a,b) t)

-- h)

s :: Polinomio -> Float
s [] = 0
s ((a,b):t) = a + (s t)

retira :: Int -> Polinomio -> Polinomio
retira x [] = []
retira x ( (a,b) : c )
    | x == b    = retira x c 
    | otherwise = ((a) ,b):retira x c

normaliza :: Polinomio -> Polinomio
normaliza [] = []
normaliza ((a,b):t) = (s((a,b):(selgrau b t)),b):normaliza (retira b t)

--h2

normaliza2 :: Polinomio -> Polinomio
normaliza2 [] = []
normaliza2 (h:t) = (head (sumFst h t)) : (normaliza (tail (sumFst h t)))

sumFst :: Monomio -> Polinomio -> Polinomio
sumFst (a,b) [] = [(a,b)]
sumFst (a,b) ((c,d):ls) 
    | b == d = sumFst ((a + c),b) ls
    | otherwise = (sumFst (a,b) ls) ++ [(c,d)]


soma :: Polinomio -> Polinomio -> Polinomio
soma l [] = l
soma [] l = l
soma l l2 = normaliza (l++l2)


produto :: Polinomio -> Polinomio -> Polinomio
produto l [] = l
produto [] l = l 