module Ficha7 where

{-- 1 --}

data ExpInt = Const Int
            | Simetrico ExpInt
            | Mais ExpInt ExpInt
            | Menos ExpInt ExpInt
            | Mult ExpInt ExpInt

ex1 :: ExpInt
ex1 =  Mais (Const 3) (Mult  (Const 7) (Const 5))
ex2 :: ExpInt
ex2 =  Mais (Const 3) (Menos (Const 2) (Const 5))

-- (a) : Defina uma funcao calcula :: ExpInt -> Int que, dada uma destas expressoes calcula o seu valor.
calcula :: ExpInt -> Int
calcula (Const x) = x
calcula (Simetrico a) = (-1) * (calcula a)
calcula (Mais  a b)   = (calcula a) + (calcula b)
calcula (Menos a b)   = (calcula a) - (calcula b)
calcula (Mult  a b)   = (calcula a) * (calcula b)

-- (b) : Defina uma funcao infixa :: ExpInt -> String de forma a que infixa (Mais (Const 3) (Menos (Const 2) (Const 5))) dê como resultado "(3 + (2 - 5))".
infixa :: ExpInt -> String
infixa (Const x) = show x
infixa (Simetrico a) = "- (" ++ (infixa a) ++ ")"
infixa (Mais    a b) = "(" ++ (infixa a) ++ " + " ++ (infixa b) ++ ")"
infixa (Menos   a b) = "(" ++ (infixa a) ++ " - " ++ (infixa b) ++ ")"
infixa (Mult    a b) = "(" ++ (infixa a) ++ " * " ++ (infixa b) ++ ")"

-- (c) : Defina uma outra funcao de conversao para strings posfixa :: ExpInt -> String de forma a que quando aplicada a expressao acima dê como resultado "3 2 5 - +".
posfixa :: ExpInt -> String
posfixa (Const x) = show x
posfixa (Simetrico a) = (posfixa a) ++ " (*(-1))"
posfixa (Mais  a b) = (posfixa a) ++ " " ++ (posfixa b) ++ " +"
posfixa (Menos a b) = (posfixa a) ++ " " ++ (posfixa b) ++ " -"
posfixa (Mult  a b) = (posfixa a) ++ " " ++ (posfixa b) ++ " *"


{-- 2 --}
data RTree a = R a [RTree a]
           deriving Show

arv = R 5 [ R 4 [ R 3 [R 17 []], 
                  R 2 [], 
                  R 7 []],
            R 10 [], 
            R 1 [ R 8 [R 0 [],  
                       R 20 [],  
                       R 15 []], 
           
            R 12 [] ]]

-- (a) : soma :: Num a => RTree a -> a que soma os elementos da arvore.
soma :: Num a => RTree a -> a
soma (R x []) = x
soma (R x l)  = x + sum (map soma l)

-- (b) : altura :: RTree a -> Int que calcula a altura da arvore.
altura :: RTree a -> Int
altura (R x []) = 1
altura (R x l)  = 1 + maximum (map altura l)

-- (c) : prune :: Int -> RTree a -> RTree a que remove de uma arvore todos os elementos a partir de uma determinada profundidade.
prune :: Int -> RTree a -> RTree a
prune 1 (R x _) = R x []
prune k (R x l) = (R x (map (prune (k-1)) l))

-- (d) : mirror :: RTree a -> RTree a que gera a arvore simetrica.
mirror :: RTree a -> RTree a
mirror (R x []) = R x []
mirror (R x l)  = R x (map mirror (reverse l))

-- (e) : postorder :: RTree a -> [a] que corresponde a travessia postorder da arvore.
postorder :: RTree a -> [a]
postorder (R x l) = concat (map postorder l) ++ [x]


{-- 3 --}
data BTree a = Empty | Node a (BTree a) (BTree a)
    deriving(Show)
data LTree a = Tip a | Fork (LTree a) (LTree a)
    deriving(Show)

larv = Fork (Fork (Tip 7) (Tip 8) ) (Fork (Tip 4) (Fork (Tip 1) (Tip 6)))

-- (a) : ltSum :: Num a => LTree a -> a que soma as folhas de uma arvore.
lfSum :: Num a => LTree a -> a
lfSum (Tip x) = x
lfSum (Fork l r) = (lfSum l) + (lfSum r)

-- (b) : listaLT :: LTree a -> [a] que lista as folhas de uma arvore (da esquerda para a direita).
listaLT :: LTree a -> [a]
listaLT (Tip x) = [x]
listaLT (Fork l r) = (listaLT l) ++ (listaLT r)

-- (c) : ltHeight :: LTree a -> Int que calcula a altura de uma arvore.
ltHeight :: LTree a -> Int
ltHeight (Tip x) = 1
ltHeight (Fork l r) = 1 + (max (ltHeight l) (ltHeight r))


{-- 4 --}
data FTree a b = Leaf b | No a (FTree a b) (FTree a b)
    deriving(Show)


farv = No 1 (No 4 (No 5 (Leaf 'a') (Leaf 'b')) (Leaf 'c'))
            (No 7 (Leaf 'd') (Leaf 'e'))

splitFTree :: FTree a b -> (BTree a, LTree b)
splitFTree (Leaf x)   = (Empty, Tip x)
splitFTree (No x e d) = let (eb,el) = splitFTree e
                            (db,dl) = splitFTree d
                        in (Node x eb db, Fork el dl)














