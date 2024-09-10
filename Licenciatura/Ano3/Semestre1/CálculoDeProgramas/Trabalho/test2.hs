module Test2 where

import Cp
import List hiding (fac)
import NEList (out)
import Exp
import Nat hiding (aux)
import LTree
import Rose hiding (g)
import Probability
import Data.List hiding (find)
import Svg hiding (for,wrap)
import Control.Concurrent
import Cp2223data

import System.IO  
import Control.Monad

tax :: [String] -> Exp String String
tax = anaExp gene

espacos :: String ->Int
espacos [] = 0
espacos (a:t) | a == ' ' = 1 + espacos(t) 
              | otherwise = 0

gene [a] = i1 ( a)
gene (a:t) = i2 ( a,(getLevels l))
    where l = map (drop 4) t

getLevels :: [String] -> [[String]]
getLevels [] = []
getLevels (h:t) = ([h]++(takeWhile (\x -> espacos x >= 4) t)) : getLevels (dropWhile (\x -> espacos x >= 4) t)

post :: Exp String String -> [String]
post (Var a) = [a]
post (Term a l) = [a]++(map (\x -> a++"|"++x) down)
    where down = concat $ map post l

--gene :: [String] -> Either String (String,[String])
--gene [a] = i1 a
--gene (a:t) = i2 (a,[])

--removeEspacoAux :: String -> Int ->String
--removeEspacoAux a 4 = a 
--removeEspacoAux (x:t) n | x == ' ' = removeEspacoAux t (n+1)
--                        | otherwise = (x:t)
--
--addLast :: [[String]]-> String ->[[String]]
--addLast (x:xs) b | xs == [] =  [x ++ [b]]
--                 | otherwise = addLast xs b
--
---- caso tenha 4 espaços no inicio vai ser uma sub-cabeça então eu crio uma nova sub-string para essa sub-cabeça, caso não seja subcabeça adiciona à ultima sublista de [[String]]
--auxGene :: [String] ->[[String]] ->[[String]] 
--auxGene (b:t) c | espacos b == 4 = auxGene t (c ++ [[(removeEspacoAux b 1)]])
--                | otherwise =  auxGene t (addLast c ( removeEspacoAux b 1))
--auxGene [] c = c             
--
--gene2:: [String] -> [[String]]
--gene2 (a:t) = auxGene t [[]]
--gene2 [] = [[]]
--
--gene = undefined
--
--
--parseExp :: [String] -> Exp String String
--parseExp (a:t) = Term a (parseCCS2 1 t)
--
--parseExp :: Int -> [String] -> [Exp String String] 
--parseExp _ [] = []
--parseExp i (a:t) | espacos a == i*4 && length t >=1 && espacos (head t) == ((i+1)*4) = Term a (parseCCS2 (i+1) t) : parseCCS2 i (x i t) 
--                  | espacos a == i*4 =Var a  : parseCCS2 i t
--                  | otherwise = [] 
--
--to_string :: CCS -> [String]
--to_string (Level i a []) = (a,[])
--to_string (Level i a l) = (a,map to_string l)
--
--data CCS = Level Int String [CCS] deriving (Show,Eq)
--
--parseCCS :: [String] -> CCS
--parseCCS (a:t) = Level 0 a (parseCCS2 1 t)
--
--parseCCS2 :: Int -> [String] -> [CCS]
--parseCCS2 _ [] = []
--parseCCS2 i (a:t) | espacos a == i*4 && length t >=1 && espacos (head t) == ((i+1)*4) = Level i a (parseCCS2 (i+1) t) : parseCCS2 i (x i t) 
--                  | espacos a == i*4 = Level i a [] : parseCCS2 i t
--                  | otherwise = [] 
--
--x :: Int -> [String] -> [String]
--x i [] = []
--x i (a:t) | espacos a == i*4 = (a:t)
--          | otherwise = x i t
--
--aux:: [((Int,String), (Int,String))] -> [(String,String)]
--aux [] = []
--aux ((a,b):t) 
--            | fst(a) == (fst(b) + 1) = ((snd(a),snd(b)) : (aux t))
--            | otherwise = aux t
--
--
--aux1::[(String,String)] -> [[String]]
--aux1 a = aux2 a [[]]
--
--aux2::[(String,String)] -> [[String]] ->[[String]]
--aux2 [(a,b)] _ = [[a,b]]
--aux2 ((a,b):t) ((h:j))
--            | a == last(h) = aux2 t ((h++[a]):j) 
--            | otherwise = aux2 t  ((h:j)++[[a]])
--aux2 [] _ = []

