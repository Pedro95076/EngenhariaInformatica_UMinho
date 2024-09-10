module Ficha3 where

data Hora = H Int Int deriving (Show,Eq)
type Etapa = (Hora,Hora)
type Viagem = [Etapa]


-- hora valida
dv :: Hora -> Bool 
dv (H x y) = elem x [0..23] && elem y [0..59]
-- hora-> minutos
dhm :: Hora -> Int
dhm (H x y) = x * 60 + y
-- min-> horas

dmh :: Int -> Hora 
dmh x = H (div x 60) (mod x 60)

-- diferença de horas em minutos

ddh :: Hora -> Hora -> Int
ddh (H x y) (H x2 y2) = abs((x * 60 + y) - (x2 * 60 + y2))
--

drh :: (Int) -> (Int)
drh x = mod x 24 
--soma de minutos a horas
dah :: Hora -> Int -> Hora
dah (H x y) z 
    |(y + mod z 60) >= 60 = H (drh (x + div z 60 + 1)) ( y + mod z 60 - 60)
    | otherwise = H (drh (x + div z 60)) (y + mod z 60)


depois :: Hora -> Hora -> Bool
depois (H a b) (H c d) = dhm (H a b) > dhm (H c d)



etapav :: Etapa -> Bool
etapav (hp,hc) = dv hp && dv hc && depois hc hp

--chegadae partida de uma viagem
chepar :: Viagem -> Etapa
chepar l = ( fst (head l), snd (last l))

--tempototal
tp :: Viagem -> Hora
tp l =  
        let (H x2 y2) = snd (last l)
            (H x y)   = fst (head l) 
        in dmh (ddh (H x2 y2) (H x y)) 
--tempo espera

tpespe :: Viagem -> Hora
tpespe [] = H 0 0
--tpespe (h:ht:t) = tpespe ( dmh (  ddh (fst ht) (snd h)  ) ) t
--NAO FUNCIONA 
--terminar
temto :: Viagem -> Hora
temto [] = H 0 0
temto l = dmh(ddh (snd (last l)) (fst (head l)))
-- 2
data Figura = Circulo Ponto Double
            | Rectangulo Ponto Ponto
            | Triangulo Ponto Ponto Ponto
            deriving (Show,Eq)

type Poligonal = [Ponto]
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


---
t :: [Ponto]
t = [(Cartesiano 3 4 ),(Cartesiano (-4) 9 ),(Polar 3 pi),(Cartesiano 4 4 ),(Cartesiano 3 4 )]
---

--comprimento poligonal
clp :: Poligonal -> Double 
clp [] = 0 
clp [a] = 0
clp (h:ht:t) = distf h ht + clp (ht:t) 
    
--linha poligonal fechada
lpf :: Poligonal -> Bool
lpf [] = False
lpf (h:t)  = if elem h t then True--testa se tem pontos repetidos
             else lpf t 

--Poligonal = [Pontos], [Figura] 
triangula :: Poligonal -> [Figura]
triangula [] = []
triangula (p1:p2:p3:t) = if length (p1:p2:p3:t) <= 3 then [] 
                         else (Triangulo p1 p2 p3): triangula (p1:p3:t) 


--calcular area dos triangulos
d :: Poligonal -> Double--NAO FUNCIONA
d l = are1( triangula l)  

are1 :: [Figura] -> Double
are1 [] = 0
are1 (h:t) = cala h + are1 t

cala :: Figura -> Double
cala l = areat l 

areat :: Figura -> Double
areat (Triangulo (Cartesiano x y) (Cartesiano x2 y2) (Cartesiano x3 y3)) =
    let a = distf (Cartesiano x y) (Cartesiano x2 y2)
        b = distf (Cartesiano x2 y2) (Cartesiano x3 y3)
        c = distf (Cartesiano x3 y3) (Cartesiano x y)
        s = (a+b+c) / 2 -- semi-perimetro
    in sqrt (s * (s-a) * (s-b) * (s-c)) -- formula de Heron


mover :: Poligonal -> Ponto -> Poligonal

--3

data Contacto = Casa Integer
              | Trab Integer
              | Tlm Integer
              | Email String
              deriving Show 
type Nome = String
type Agenda = [(Nome, [Contacto] )]

--[("Manuel", [Casa 253123456, Email "a@gmail.com"])]
acrescEmail :: Nome -> String -> Agenda -> Agenda
acrescEmail n s [] = [(n,[Email s])]
acrescEmail n s ((a,b):t) = if n == a then ((a,(Email s):b):t) else (a,b):acrescEmail n s t 

verEmails :: Nome -> Agenda -> Maybe [String]
verEmails n [] = Nothing
verEmails n ((a,b):t)
    | n == a = Just (emails b) 
    | otherwise = verEmails n t 

emails :: [Contacto] -> [String]
emails [] = []
emails ((Email s):t) = s:emails t
emails (_:t) = emails t

consTelefs :: [Contacto] -> [Integer]
consTelefs [] = []
consTelefs((Casa s):t) = s:consTelefs t
consTelefs((Tlm  s):t) = s:consTelefs t
consTelefs((Trab s):t) = s:consTelefs t
consTelefs (_:t) = consTelefs t

c :: [Contacto] -> Maybe Integer--retira casa
c [] = Nothing
c (Casa a:t) = Just a 
c (_:t) = c t

casa :: Nome -> Agenda -> Maybe Integer
casa n [] = Nothing
casa n (a:b) = if n == (fst a) then c (snd a) else casa n b

-- 4
{-
type Dia = Int
type Mes = Int
type Ano = Int
type Nome = String
-}



--5 

data Movimento = Credito Float | Debito Float
    deriving Show
data Data = D Int Int Int
    deriving Show
data Extracto = Ext Float [(Data, String, Movimento)]
    deriving Show

{-
c2 :: Extracto
c2 = Ext 100 [(D 200 1 30),"blabla", Debito 100]
-}

extValor :: Extracto -> Float -> [Movimento]
extValor (Ext x l) z = aux x l


    where aux :: Float -> [(Data, String, Movimento)] -> [Movimento]
          aux f [] = [] 
          aux x ((_,_,Debito n):t) | n > x = Debito n : aux x t 
                                   | otherwise = aux x t 
          aux x ((_,_,Credito n):t) | n > x = Credito n : aux x t 
                                    | otherwise = aux x t 