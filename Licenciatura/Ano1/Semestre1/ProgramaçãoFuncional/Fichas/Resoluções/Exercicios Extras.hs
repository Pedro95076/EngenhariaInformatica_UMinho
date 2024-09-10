module ExerciciosExtras where


data BTree a = Empty | Node a (BTree a) (BTree a)
   deriving (Show)

{-

              1
            /   \
           2     3
          / \   / \
         4   5 6   7

         2       3
        / \     / \
       4   5   6   7

         3     4   5
        / \  
       6   7 

       4  5  6  7
       5  6  7
       6  7
       7

-}

-- Travessia por niveis

bt1 = Node 1 (Node 2 (Node 4 Empty Empty) (Node 5 Empty Empty))
             (Node 3 (Node 6 Empty Empty) (Node 7 Empty Empty))

niveisBT ::  BTree a -> [a]
niveisBT tree = travN [tree]

travN :: [BTree a] -> [a]
travN [] = []
travN (Empty:t) = travN t
travN ((Node x e d):t) = x : travN (t++[e,d])

------------------------------------------------------------------------------------------------------------------------------------------------------------------

data RTree a = R a [RTree a]
   deriving (Show)

rt1 = R 5 [ R 4 [ R 3 [R 17 []], R 2 [], R 7 []],
            R 10 [],
            R 1 [ R 8 [ R 0 [], R 20 [], R 15 [], R 39 [] ],
                  R 12 [] ]
          ]

niveisRT ::  RTree a -> [a]
niveisRT (R x l) = x : auxRT l

auxRT :: [RTree a] -> [a]
auxRT [] = []
auxRT ((R x l):t) = x : auxRT (t++l)

------------------------------------------------------------------------------------------------------------------------------------------------------------------

data LTree a = Tip a | Fork (LTree a) (LTree a)
   deriving (Show)

{-

              .
            /   \
           8     .
                / \
               2   5

-}

lt1 = Fork (Tip 8) (Fork (Tip 2) (Tip 5))

travessia :: LTree a -> [(a,Int)]
travessia (Tip x) = [(x,1)]
travessia (Fork e d) = map (\(x,n)->(x,n+1)) (travessia e ++ travessia d)

-- a funçao build, inversa desta, talque que build (travessia a) == a

build :: [(a,Int)] -> LTree a
build l = fst (auxLT 1 l)

auxLT :: Int -> [(a,Int)] -> (LTree a , [(a,Int)])
auxLT n ((a,x):t)
        | n == x = (Tip a , t)
        | n <  x = (Fork e d , t'')
           where (e,t')  = auxLT (n+1) ((a,x):t)
                 (d,t'') = auxLT (n+1) t'

------------------------------------------------------------------------------------------------------------------------------------------------------------------

-- Teste 2019

--Considere o seguinte tipo de dados para representar uma sequencia em que os elementos podem ser acrecentados
--a esquerda (Cons) ou por concatenacao de duas sequencias (App).

data Seq a = Nil | Cons a (Seq a) | App (Seq a) (Seq a)

--(b) Defina a funcao dropSeq :: Int -> Seq a -> Seq a, tal que dropSeq n s elimina os n primeiros elementos 
--    da sequencia s. A funcao deve manter a estrutura da sequencia.
--    Por exemplo : dropSeq 2 (App (App (Cons 7 (Cons 5 Nil)) (Cons 3 Nil)) (Cons 1 Nil)) == App (Cons 3 Nil) (Cons 1 Nil)

ex2 = (App (App (Cons 7 (Cons 5 Nil)) (Cons 3 Nil)) (Cons 1 Nil))

dropSeq :: Int -> Seq a -> Seq a
dropSeq n s | n<=0 = s
dropSeq n Nil = Nil
dropSeq n (Cons x s) = dropSeq (n-1) s
dropSeq n (App s1 s2) | lengthSeq s1 == n = s2
                      | (lengthSeq s1) < n = dropSeq (n-(lengthSeq s1)) s2
                      | (lengthSeq s1) > n = App (dropSeq n s1) s2dr

lengthSeq :: Seq a -> Int
lengthSeq s = length (toList s)

--(c) Declare (Seq a) como instancia da classe Show de forma a obter o seguinte comportamento no interpretador :
ex1 = App (Cons 1 Nil) (App (Cons 7 (Cons 5 Nil)) (Cons 3 Nil))
-- = <<1,7,5,3>>

toList :: Seq a -> [a]
toList Nil = []
toList (Cons x s) = x : (toList s)
toList (App s1 s2) = (toList s1) ++ (toList s2)


instance Show a => Show (Seq a) where -- tambem temos de ter maneira de converter os elementos tipo a para string, logo tambem lhe temos de definir o show
     show s = showSeq (toList s)
         where showSeq l = "<<" ++ (aux l)
               aux [] = ">>"
               aux [x] = (show x) ++ ">>"
               aux (x:xs) = (show x) ++ "," ++ (aux xs)

------------------------------------------------------------------------------------------------------------------------------------------------------------------

-- Exame 2017

--O problema das N rainhas consiste em colocar N rainhas num tabuleiro de xadrez com N linhas e N colunas, 
--de tal forma que nenhuma rainha esta ameacada por outra. Note que uma rainha ameaca todas as posicoes que 
--estao na mesma linha, na mesma coluna ou nas mesmas diagonais. Uma forma de representar estas solucoes é 
--usando listas de strings. O exemplo representa uma solucao para este problema quando N é 4.

type Tabuleiro = [String]
exemplo :: Tabuleiro 
exemplo = [ "..R.", 
            "R...",
            "...R", 
            ".R.." ]

--(a) Defina a funcao posicoes :: Tabuleiro -> [(Int,Int)] que determina as posicoes (coluna e linha) onde 
--    se encontram as rainhas num tabuleiro, de tal forma que posicoes exemplo == [(2,0),(0,1),(3,2),(1,3)].

posicoes :: Tabuleiro -> [(Int,Int)]
posicoes l = aux (0,0) l
        where aux :: (Int,Int) -> Tabuleiro -> [(Int,Int)]
              aux (x,y) (('.':t):ls) = aux (x+1,y) (t:ls)
              aux (x,y) (('R':t):ls) = (x,y) : aux (x+1,y) (t:ls)
              aux (x,y) ("":ls) = aux (0,y+1) ls
              aux _ [] = []












