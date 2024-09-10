module Ficha1 where

import Data.Char

perimetro :: Double -> Double
perimetro r = 2 * pi * r

dist ::(Double,Double) -> (Double,Double) -> Double
dist (x1,y1) (x2,y2) = sqrt( (x2-x1) ^ 2 + (y2-y1) ^ 2 )

primtUlt :: [a] -> (a,a)
primtUlt l = (head l, last l)

multiplo :: Int -> Int -> Bool
multiplo x y = (mod x y) == 0


trucaImpar :: [a] -> [a]
trucaImpar l = if ((mod (length l) 2) == 0)
               then l 
               else tail l


max2 :: Int -> Int -> Int
max2 x y = if (x>y) then x else y


max3 :: Int -> Int -> Int -> Int
max3 x y z = max2(max2 x y) z

--2.a--
nRaizes :: Float -> Float -> Float -> Int 
nRaizes a b c = if (b^2 - 4*a*c) == 0
                then 1
                else if (b^2 - 4*a*c) < 0
                     then 0
                     else 2

nRaizes2 :: Float -> Float -> Float -> Int 
nRaizes2 a b c
    | b^2 - 4*a*c == 0    = 1
    | b^2 - 4*a*c <  0    = 0
    | otherwise           = 2

-- 2.b
raizesc ::  Float -> Float -> Float -> [Float]
 
raizesc a b c | nRaizes a b c == 2 = [(-b + raiz)/2*a, (-b - raiz)/2*a]
              | nRaizes a b c == 1 = [(-b)/2*a] 
              | otherwise = []
  where 
      raiz = sqrt(b^2 - 4*a*c)

raizesc2 ::  Float -> Float -> Float -> [Float]
raizesc2 a b c = case (nRaizes a b c) of
                    1 -> [ (-b) / 2 * a ]
                    2 -> [ (-b + sqrt (b**2 - 4*a*c))/2*a ,(-b - sqrt(b^2 - 4*a*c))/2*a]
                    _ -> []

--3
type Hora = (Int,Int)

-- 3.a
th :: Hora -> Bool
th (x,y) = x <= 23 && y < 60 && x >=0 && y >=0
--elem ve se determinado item pertence a uma lista
th2 :: Hora -> Bool
th2 (x,y) = elem x [0..23] && elem y [0..59]

-- 3.b

hs :: Hora -> Hora -> Hora 
hs (x,y) (x2,y2) = if (x > x2 || (x == x2 && y > y2)) then (x,y) else (x2,y2)

hs2 :: Hora -> Hora -> Hora
hs2 (x,y) (x2,y2) = if (y + 60 * x > y2 + 60 * x2) 
                    then (x,y)
                    else (x2,y2)
                   
-- 3.c
chm :: Hora -> Int
chm (x,y) = x * 60 + y

-- 3.d
cmh :: Int -> Hora
cmh x = (div x 60, mod x 60)

-- 3.e
dh :: Hora -> Hora -> Int
dh (x,y) (x2,y2) = abs((x * 60 + y) - (x2 * 60 + y2))

-- 3.f

--reduzir a hora para 24 
rh :: (Int) -> (Int)
rh x = mod x 24 

ah :: Hora -> Int -> Hora 
ah (x,y) z = if (y + mod z 60) >= 60 
             then(rh (x + div z 60 + 1) , y + mod z 60 - 60)
             else (rh (x + div z 60) , y + mod z 60)

-- 4

data Hora2 = H Int Int deriving (Show,Eq)

dvh :: Hora2 -> Bool 
dvh (H x y) = elem x [0..23] && elem y [0..59]

dchm :: Hora2 -> Int
dchm (H x y) = x * 60 + y

dcmh :: Int -> Hora
dcmh x = (div x 60, mod x 60)

ddh :: Hora2 -> Hora2 -> Int
ddh (H x y) (H x2 y2) = abs((x * 60 + y) - (x2 * 60 + y2))

drh :: (Int) -> (Int)
drh x = mod x 24 

dah :: Hora2 -> Int -> Hora
dah (H x y) z = if (y + mod z 60) >= 60 
                then(drh (x + div z 60 + 1) , y + mod z 60 - 60)
                else (drh (x + div z 60) , y + mod z 60)

-- 5
data Semaforo = Verde | Amarelo | Vermelho deriving (Show,Eq)

next :: Semaforo -> Semaforo
next Verde = Amarelo
next Amarelo = Vermelho
next Vermelho = Verde

stop :: Semaforo -> Bool--obrigatorio parar
stop Verde = False
stop Amarelo = False
stop Vermelho = True

safe :: Semaforo -> Semaforo -> Bool
safe x y = (stop x) || (stop y) 

-- 6
data Ponto = Cartesiano Double Double | Polar Double Double deriving (Show,Eq)

posx :: Ponto -> Double
posx (Cartesiano x y ) = abs x 
posx (Polar x y) = abs((cos y) * x)

posy :: Ponto -> Double
posy (Cartesiano x y ) = abs y 
posy (Polar x y) = abs((sin y) * x)

raio :: Ponto -> Double
raio (Cartesiano x y ) = sqrt( (x)^2 + (y)^2 )

angulo :: Ponto -> Double
angulo (Polar x y) = y 
angulo (Cartesiano x y )
    | (x > 0 && y >0 ) || (x > 0 && y < 0) = atan (y/x) *180/pi
    | x < 0 && y > 0 = -atan (y/x) *180/pi + 90
    | x < 0 && y < 0 = -atan (y/x) *180/pi - 90
    | x == 0 = if y<0 then (-90) else 90 
    | y == 0 = if x>0 then 0 else 180
    | x == 0 && y == 0 = 0


distf :: Ponto -> Ponto -> Double


distf (Cartesiano x y ) (Cartesiano x2 y2 ) = sqrt( (x-x2)^2 + (y-y2)^2 )
distf (Cartesiano x y ) (Polar d a ) = sqrt( (x- (cos a) * d )^2 + (y- (sin a) * d)^2 )
distf (Polar d a ) (Cartesiano x y ) = distf (Cartesiano x y ) (Polar d a )
distf (Polar d a ) (Polar d2 a2 ) = sqrt( ((cos a) * d - (cos a2) * d2 )^2 + ((sin a) * d- (sin a2) * d2)^2 )

-- 7
data Figura = Circulo Ponto Double
            | Rectangulo Ponto Ponto
            | Triangulo Ponto Ponto Ponto
            deriving (Show,Eq)
poligono :: Figura -> Bool
poligono (Circulo _ r) = r > 0 
poligono (Rectangulo (Cartesiano x y) (Cartesiano x2 y2)) = (x /= x2) && (y /= y2 )
poligono (Triangulo (Cartesiano x y) (Cartesiano x2 y2) (Cartesiano x3 y3)) = x /= x2 && x2 /=x3 && x /= x3 && y /= y2 && y2 /=y3 && y /= y3

vertices :: Figura -> [Ponto]

vertices (Rectangulo (Cartesiano x y) (Cartesiano x2 y2)) =  [(Cartesiano x y),(Cartesiano x2 y2), (Cartesiano x y2),(Cartesiano x2 y)]
vertices (Triangulo (Cartesiano x y) (Cartesiano x2 y2) (Cartesiano x3 y3)) =  [(Cartesiano x y),(Cartesiano x2 y2), (Cartesiano x3 y3)]

area :: Figura -> Double
area (Triangulo (Cartesiano x y) (Cartesiano x2 y2) (Cartesiano x3 y3)) =
    let a = distf (Cartesiano x y) (Cartesiano x2 y2) 
        b = distf (Cartesiano x2 y2) (Cartesiano x3 y3)
        c = distf (Cartesiano x3 y3) (Cartesiano x y)
        s = (a+b+c) / 2 -- semi-perimetro
    in sqrt (s*(s-a)*(s-b)*(s-c)) -- formula de Heron

area (Rectangulo (Cartesiano x y) (Cartesiano x2 y2)) = abs(x-x2) * abs(y-y2)
area (Circulo _ r) = r^2 * pi

perimetrof :: Figura -> Double

perimetrof  (Circulo _ r) = r*2*pi
perimetrof  (Rectangulo (Cartesiano x y) (Cartesiano x2 y2)) = 2*(abs(x-x2)+abs(y-y2))
perimetrof  (Triangulo (Cartesiano x y) (Cartesiano x2 y2) (Cartesiano x3 y3 ) ) = (distf (Cartesiano x y) (Cartesiano x2 y2)) + (distf (Cartesiano x2 y2) (Cartesiano x3 y3) ) + (distf(Cartesiano x y) (Cartesiano x3 y3))

-- 8

myisLower :: Char -> Bool
myisLower x = elem (ord x) [97..122]

myisDigit :: Char -> Bool
myisDigit x = elem (ord x) [48..57]

myisAlpha :: Char -> Bool
myisAlpha x = myisLower x || elem (ord x) [65..90]

mytoUpper :: Char -> Char
mytoUpper x = chr ( (ord x) - 32)

myintToDigit :: Int -> Char
myintToDigit x = chr (x + 48) 

mydigitToInt :: Char -> Int
mydigitToInt x = ord (x)-48