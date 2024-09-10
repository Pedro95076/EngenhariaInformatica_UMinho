module Ficha6 where

data BTree a = Empty
             | Node a (BTree a) (BTree a)
          deriving Show

exBT = Node 3 (Node 9 Empty Empty) (Node 2 Empty (Node 7 Empty Empty))
--      (3)
--      / \
--    (9) (2)
--          \
--          (7)


{-- 1 --}

-- (a) : altura :: BTree a -> Int que calcula a altura da arvore.
altura :: BTree a -> Int
altura Empty = 0
altura (Node x l r) = 1 + max (altura l) (altura r)

-- (b) : contaNodos :: BTree a -> Int que calcula o nu ́mero de nodos da arvore.
contaNodos :: BTree a -> Int
contaNodos Empty = 0
contaNodos (Node x l r) = 1 + (contaNodos l) + (contaNodos r)

-- (c) : folhas :: BTree a -> Int, que calcula o numero de folhas (i.e., nodos sem descendentes) da arvore.
folhas :: BTree a -> Int
folhas Empty = 0
-- No intance for (Eq (BTree a))
-- folhas (Node x l r) = if l == Empty && r == Empty then 1 + (folhas l) + (folhas r) else (folhas l) + (folhas r) 
folhas (Node x Empty Empty) = 1
folhas (Node x l r) = (folhas l) + (folhas r)

-- (d) : prune :: Int -> BTree a -> BTree a, que remove de uma arvore todos os elementos a partir de uma determinada profundidade.
prune :: Int -> BTree a -> BTree a
prune 0 _ = Empty
prune k Empty = Empty
prune k (Node x l r) = (Node x (prune (k-1) l) (prune (k-1) r))

-- (e) : path :: [Bool] -> BTree a -> [a], que dado um caminho (False corresponde a esquerda e True a direita) e uma arvore, da a lista com a informacao dos nodos por onde esse caminho passa.
path :: [Bool] -> BTree a -> [a]
path [] (Node x _ _) = [x]
path _ Empty = []
path (h:t) (Node x l r) = if h then x:(path t r) else x:(path t l)

-- (f) : mirror :: BTree a -> BTree a, que da a arvore simetrica.
mirror :: BTree a -> BTree a
mirror Empty = Empty
mirror (Node x l r) = Node x (mirror r) (mirror l)

-- (g) : zipWithBT :: (a -> b -> c) -> BTree a -> BTree b -> BTree c, que generaliza a funcao zipWith para arvores binarias.
zipWithBT' :: (a -> b -> c) -> BTree a -> BTree b -> BTree c
zipWithBT' f (Node x l r) (Node x' l' r') = (Node (f x x') (zipWithBT' f l l') (zipWithBT' f r r'))
zipWithBT' _ _ _ = Empty

-- (f) : unzipBT :: BTree (a,b,c) -> (BTree a,BTree b,BTree c), que generaliza a funcao unzip (neste caso de triplos) para arvores binarias.
unzipBT' :: BTree (a,b,c) -> (BTree a,BTree b,BTree c)
unzipBT' (Node (a,b,c) l r) = ( Node a l1 r1 , Node b l2 r2 , Node c l3 r3 )
                         where (l1,l2,l3) = unzipBT' l
                               (r1,r2,r3) = unzipBT' r
unzipBT' _ = (Empty,Empty,Empty)

exBT3 = (Node (1,2,3) (Node (10,20,30) Empty Empty) (Node (100,200,300) Empty Empty))


{-- 2 --}

exBT2 = (Node 6 (Node 4 Empty Empty) (Node 8 (Node 7 Empty Empty) (Node 9 Empty Empty)))
--      (6)
--      / \
--    (4) (8)
--        / \
--      (7) (9)

-- (a) : Defina uma funcao minimo :: Ord a => BTree a -> a que calcula o menor elemento de uma arvore binaria de procura nao vazia.
minimo :: Ord a => BTree a -> a
minimo (Node x Empty _) = x
--minimo' (Node x _ Empty) = x
minimo (Node x l r) = minimo l

-- (b) : Defina uma funcao semMinimo :: Ord a => BTree a -> BTree a que remove o menor elemento de uma arvore binaria de procura nao vazia.
semMinimo :: Ord a => BTree a -> BTree a
semMinimo (Node x Empty _) = Empty
semMinimo (Node x l r) = Node x (semMinimo l) r

-- (c) : Defina uma funcao minSmin :: Ord a => BTree a -> (a,BTree a), que calcula, com uma unica travessia da arvore o resultado das duas funcoes anteriores.
minSmin :: Ord a => BTree a -> (a,BTree a)
minSmin (Node x Empty _) = (x,Empty)
minSmin (Node x l r) = (k,Node x l1 r)
                    where (k,l1) = minSmin l

-- (d) : Defina uma funcao remove :: Ord a => a -> BTree a -> BTree a que remove um elemento de uma arvore binaria de procura, usando a funcao anterior.
remove :: Ord a => a -> BTree a -> BTree a
remove k Empty = Empty
remove k (Node x l r) | k == k2 = r2
                      | k == x = Node k1 l r1
                      | k < x  = (Node x (remove k l) r)
                      | k > x  = (Node x l (remove k r))
                   where (k1,r1) = minSmin r
                         (k2,r2) = minSmin (Node x l r)











































