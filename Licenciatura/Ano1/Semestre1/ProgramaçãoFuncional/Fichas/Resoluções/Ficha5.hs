module Ficha5 where

--import Data.List


myfoldr :: ( b -> a -> a )-> a -> [b] -> a
myfoldr f a [] = a
myfoldr f a (h:t) = f h (myfoldr f a t)  

myfoldl :: (a -> b -> a) -> a -> [b] -> a 
myfoldl f a [] = a
myfoldl f a (h:t) = myfoldl f (f a h) t  


mysum l = myfoldr (\x a -> x + a) 0 l
mylength l = foldr(\x a-> a + 1 ) 0 l
--mylength l = foldr(\x -> (+) 1 ) 0 l

mymap f l= foldr(\x a-> (f x): a) [] l
myreverse l = foldl (\a x -> x:a) [] l 

myfilter :: (a -> Bool) -> [a] -> [a]
myfilter c l = [x | x <- l, c x ]
--myfilter c l = foldr (\x a -> if c x then x else a) a l  

{-
sum l = foldr (+) 0 l
and l = foldr (&&) True l
or  l = foldr (||) False l 
-}



-- a
myany :: (a -> Bool) -> [a] -> Bool
myany c [] = False
myany c (h:t) = c h || myany c t

myany2 c l = foldr (\x a -> a || c x) (False) l 


-- b 
myzipWith :: (a -> b -> c) -> [a] -> [b] -> [c]
myzipWith f (h:t) (h2:t2) = (f h h2): myzipWith f t t2 
myzipWith _ _ _  = [] -- !


myzipWith2 :: (a -> b -> c) -> [a] -> [b] -> [c]
myzipWith2 f l l2 = [f x y | (x, y) <- zip l l2]


myzipWith3 :: (a -> b -> c) -> [a] -> [b] -> [c]
myzipWith3 f l l2 = foldr (\x a->(f (fst x) (snd x)):a) [] (zip l l2) 


-- tava a tentar fazer o mesmo mas com um foldl e sem usar ++ mas soue stupido:        
myzipWith4 f l l2 = foldl (\a x -> (flip (:)) a (f (fst x) (snd x))     ) [] (zip l l2) 



-- c

--takeWhile odd [1,3,4,5,6,6] == [1,3]
mytakeWhile :: ( a -> Bool ) -> [a] -> [a]
mytakeWhile c [] = []
mytakeWhile c (h:t) = if c h then h:mytakeWhile c t 
                      else [] 


--FIXME
--mytakeWhile2 :: ( a -> Bool ) -> [a] -> [a]
--mytakeWhile2 c l = foldl (\a x -> if c x then x:a else  ) [] l

--mytakeWhile c l = [x | x <- l, c x]
 

-- d
mydropWhile :: (a -> Bool) -> [a] -> [a]
mydropWhile c [] = [] 
mydropWhile c (h:t) = if c h then mydropWhile c t 
                      else []


mydropWhile2 :: (a -> Bool) -> [a] -> [a]
--FIXME dropwhile a acomeçar por tras?
mydropWhile2 c l = foldr (\x a-> if c x then [] else x:a ) [] l 

-- e   
--span =(takeWhile, dropWhile)
--span c l = (mytakeWhile c l, mydropWhile c l)--existe trabalho redundante

myspan :: (a -> Bool) -> [a] -> ([a],[a])
myspan c [] = ([],[])
myspan c l@(h:t) = if c h then (h:p,q)
                 else ([],l)
    where (p,q) = myspan c t
          
 
-- f


mydeleteBy :: (a -> a -> Bool) -> a -> [a] -> [a]
mydeleteBy c x [] = [] 
mydeleteBy c x (y:ys) = if c x y then ys 
                        else y: mydeleteBy c x ys

--mydeleteBy2 c x l 

-- g

--sortOn fst [(3,1),(1,2),(2,5)] == [(1,2),(2,5),(3,1)]

mysortOn :: Ord b => (a -> b) -> [a] -> [a]
mysortOn f [] = []
mysortOn f (h:t) = inserte f h  (mysortOn f t)


inserte :: Ord b => (a -> b) -> a -> [a] -> [a]
inserte f x [] = [] 
inserte f x (y:ys) = if f x <= f y then x:y:ys
                     else y: (inserte f x ys)



-- 2

type Polinomio = [Monomio]
type Monomio = (Float,Int)
p1 :: Polinomio
p1 = [(2,3),(3,4),(5,3),(4,5)]

selgrau :: Int-> Polinomio -> Polinomio
selgrau x pol = filter (\(c,e) -> e == x) pol

conta :: Int -> Polinomio -> Int
conta n [] = 0 
--conta n pol = length (selgrau n pol)  
--conta n (h:t) = if n == snd h then 1 + conta n t
--                else conta n t
conta n pol = foldr (\(c,e) a -> if e == n then 1+a else a) 0 pol



--so temos expoentes positivos poe h? 
-- (4,0)

grau :: Polinomio -> Int
--grau [] = 0 
--grau ((c,e):t) = max (e) (grau t) 

grau pol = foldr (\(c,e) a -> max e a) 0 pol

deriv :: Polinomio -> Polinomio
deriv pol = map (\(c,e) -> (c* fromIntegral e, e-1)) pol

calcula :: Float -> Polinomio -> Float
calcula x pol = foldr (\(c,e) r -> c*x^e + r) 0 pol 
--calcula x pol = sum (map (\(c,e) -> c*x^e ) pol )

simp :: Polinomio -> Polinomio
simp pol = [(c,e) | (c,e) <- pol, c/= 0]


mult :: Monomio -> Polinomio -> Polinomio
mult (c,e) pol = map (\(c2,e2)->(c*c2, e+e2)) pol
--mult (c,e) pol = foldr (\(c2,e2) r->(c*c2, e+e2):r) [] pol

produto :: Polinomio -> Polinomio -> Polinomio
--produto pol pol2 =. [ mult x pol | x <- pol2]
produto pol pol2 = foldr (\m a -> (mult m pol)++a) [] pol2


-- 3 
type Mat a = [[a]] 

m :: Matriz
m = [[1,2,3],
     [0,4,5],
     [0,0,6]]

m2 = [[1,2,3],
      [0,4,5],
      [0,3,0]]
dimOK :: Mat a -> Bool
dimOK [] = False
dimOK [a] = True
dimOK (h:h1:t) = (length h == length h1) && dimOK (h1:t)

dimOK2 :: Mat a -> Bool
dimOK2 [] = False
dimOK2 m = aux (map length m)
    where aux (0:_) = False
          aux (x:xs) = filter(/=x) xs == []

dimMat :: Mat a -> (Int,Int)
dimMat l = (length m, length (head m) )

addMat :: Num a => Mat a -> Mat a -> Mat a
addMat [] [] = []
addMat (h:t) (h2:t2) = zipWith (+) h h2 : addMat t t2
-------------
--aula jbb

type Matriz = [Linha]
type Linha = [Int]

somaM :: Matriz -> Matriz -> Matriz
--somaM m1 m2 =. zipWith (somalinhas) m1 m2 
somaM m1 m2 = zipWith (zipWith (+)) m1 m2

--somalinhas :: Linha -> Linha -> Linha
--somalinhas l1 l2 = zipWith (+) l1 l2 
--somalinhas = zipWith (+)

-------------
transpose :: Mat a -> Mat a
transpose ([]:_) = []
transpose m = (map head m): transpose (map tail m)

multMat :: Num a => Mat a -> Mat a -> Mat a
multMat (h:t) m2 = linha h m2: multMat t (m2)
multMat [] m = []

linha :: Num a => [a] -> Mat a -> [a]
linha h ([]:_) =[] 
linha h m2 = sum (zipWith (*) h (map head m2)):linha h (map tail m2) 



--zipWMat :: (a -> b -> c) -> Mat a -> Mat b -> Mat c
--zipWMat f (h:t) (h2:t2) = zipWMat (f) h h2: zipWMat (f) t t2
--zipWMat _ _ _ = []



{-
--testa se uma matriz é triangular superior
triSup :: Num a => Mat a -> Bool
triSup m@(mh:mt) = all (==True) [tri ta c m | c <- [0..ta]]
    where ta = length mh 
tri ta c m = if ta == 0 then True
             else (triaux ta c (m!!c)) && tri ta (c+1) m 
         
-- testa se uma linha é de uma m t superior
triaux :: Num a => Int -> Int-> [a] -> Bool
triaux ta c l = if contan l == (ta-c) then True 
                      else False 
--conta numero de 0 seguidos
contan :: [a] -> Int 
contan (h:t) = if h == 0 then 1+contan t else 0
-}