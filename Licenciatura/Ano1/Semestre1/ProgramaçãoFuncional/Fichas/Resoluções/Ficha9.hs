module Ficha9 where

import System.Random


-- exemplos
lanca2dados :: IO (Int,Int)
lanca2dados = do x <- randomRIO (1,6)
                 y <- randomRIO (1,6)
                 return (x,y)

ranRList :: Int -> (Int,Int) -> IO [Int]
-- ranRlist n (a,b) gera uma lista com n n°s de "a" a "b"
ranRList 0 (_,_) = return []
ranRList n (a,b) = do h <- randomRIO (a,b)
                      t <- ranRList (n-1) (a,b)
                      return (h:t)

sequence' :: [IO a]    -- lista de acoes 
             -> IO [a] -- 1 acao
-- Ja existe !
sequence' [] = return []
sequence' (h:t) = do x  <- h
                     xs <- sequence' t
                     return (x:xs)

-- logo podemos fazer a ranRList desta maneira :
ranRList' :: Int -> (Int,Int) -> IO [Int]
ranRList' n (a,b) = sequence (replicate n (randomRIO (a,b)))

-- Exercicio do Bingo
bingo :: IO ()
bingo = bingoN 99 []

bingoN :: Int -> [Int] -> IO ()
bingoN 0 l = return ()
bingoN n l = do getLine
                x <- randomRIO (1,99)
                if (elem x l) then bingoN n l
                              else do putStrLn (show x)
                                      bingoN (n-1) (x:l)


















