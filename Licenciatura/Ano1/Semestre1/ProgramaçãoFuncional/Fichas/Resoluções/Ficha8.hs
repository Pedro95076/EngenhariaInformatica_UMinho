module Ficha8 where

{-- 1 --}
data Frac = F Integer Integer

-- (a) : Defina a funcao normaliza :: Frac -> Frac, que dada uma fraccao calcula uma fraccao equivalente, irredutıvel, e com o denominador positivo. Por exemplo, normaliza (F (-33) (-51)) deve retornar F 11 17 e normaliza (F 50 (-5)) deve retornar F (-10) 1. Sugere-se que comece por definir primeiro a funcao mdc :: Integer -> Integer -> Integer que calcula o maximo divisor comum entre dois numeros, baseada na seguinte propriedade (atribuida a Euclides) : mdc x y == mdc (x+y) y == mdc x (y+x)

f = F (-33) (-51)
f2 = F 50 (-5)

mdc :: Integer -> Integer -> Integer
mdc a b
    | a > b = mdc (a-b) b
    | a < b = mdc a (b-a)
    | a==b = b

normaliza :: Frac -> Frac
normaliza (F n d) = F (k * (div n' m )) (div d' m)
    where k = signum n * signum d
          m = mdc n' d'
          n' = abs n
          d' = abs d

-- (b) : Defina Frac como instancia da classe Eq.
{-
class Eq a where
  (==) :: a -> a -> Bool
  (/=) :: a -> a -> Bool
  {-# MINIMAL (==) | (/=) #-}
-}

instance Eq Frac where
  (F a b) == (F c d) = a*d == c*b

-- (c) : Defina Frac como instancia da classe Ord.
{-
class Eq a => Ord a where
  compare :: a -> a -> Ordering
  (<) :: a -> a -> Bool
  (<=) :: a -> a -> Bool
  (>) :: a -> a -> Bool
  (>=) :: a -> a -> Bool
  max :: a -> a -> a
  min :: a -> a -> a
  {-# MINIMAL compare | (<=) #-}
-}

instance Ord Frac where
  f1 <= f2 = div a b <= div c d
          where (F a b) = normaliza f1
                (F c d) = normaliza f2

-- (d) : Defina Frac como instancia da classe Show, de forma a que cada fraccao seja apresentada por (numerador/denominador).
{-
class Show a where
  showsPrec :: Int -> a -> ShowS
  show :: a -> String
  showList :: [a] -> ShowS
  {-# MINIMAL showsPrec | show #-}
-}

instance Show Frac where
  --show :: Frac -> String
  show (F a b) = "(" ++ show a ++ "/" ++ show b ++ ")"

-- (e) : Defina Frac como instancia da classe Num. Relembre que a classe Num tem a seguinte definicao
{-
class Num a where
  (+) :: a -> a -> a
  (-) :: a -> a -> a
  (*) :: a -> a -> a
  negate :: a -> a
  abs :: a -> a
  signum :: a -> a
  fromInteger :: Integer -> a
  {-# MINIMAL (+), (*), abs, signum, fromInteger, (negate | (-)) #-}
-}

instance Num Frac where
  (F n1 d1) + (F n2 d2) = F (n1*d2 + n2*d1) (d1*d2)
  (F n1 d1) - (F n2 d2) = F (n1*d2 - n2*d1) (d1*d2)
  (F n1 d1) * (F n2 d2) = F (n1*n2) (d1*d2)
  abs (F n d) = F (abs n) (abs d)
  signum (F n d) = F (signum (n*d)) 1
  fromInteger x = F x 1

-- (f) : Defina uma funcao que, dada uma fracao f e uma lista de fracoes l, selecciona de l os elementos que sao maiores do que o dobro de f.

sd :: Frac -> [Frac] -> [Frac]
sd f l = filter (> 2*f) l


{-- 2 --}

data Exp a = Const a
             | Simetrico (Exp a)
             | Mais (Exp a) (Exp a)
             | Menos (Exp a) (Exp a)
             | Mult (Exp a) (Exp a)

ex1 =  Mais (Const 3) (Mult  (Const 7) (Const 5))
ex2 =  Mais (Const 3) (Menos (Const 2) (Const 5))

-- (a) : Declare Exp a como uma instancia de Show.
infixa :: Show a => Exp a -> String
infixa (Const x) = show x
infixa (Simetrico a) = "- (" ++ (infixa a) ++ ")"
infixa (Mais    a b) = "(" ++ (infixa a) ++ " + " ++ (infixa b) ++ ")"
infixa (Menos   a b) = "(" ++ (infixa a) ++ " - " ++ (infixa b) ++ ")"
infixa (Mult    a b) = "(" ++ (infixa a) ++ " * " ++ (infixa b) ++ ")"

instance Show a => Show (Exp a) where
  show = infixa 


-- (b) : Declare Exp a como uma instancia de Eq.

calcula :: Num a => Exp a -> a
calcula (Const x) = x
calcula (Simetrico e) = - (calcula e)
calcula (Mais e1 e2) = (calcula e1) + (calcula e2)
calcula (Menos e1 e2) = (calcula e1) - (calcula e2)
calcula (Mult e1 e2) =(calcula e1) * (calcula e2) 

{-
instance (Eq a,Num a) => Eq (Exp a) where
    a == b = calcula a == calcula b


-- (c) : Declare Exp a como instancia da classe Num.
instance Num (Exp a) where  
    (+) = Mais
    (*) = Mult
    (-) = Menos
    signum e = Const (signum (calcula e))
    abs e = | calcula e >= 0 = e
            | otherwise = Simetrico e 
    fromInteger n = Const (fromInteger n)
-}



















