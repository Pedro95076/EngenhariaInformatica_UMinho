module Test3 where

import Cp
import List hiding (fac)
import NEList (out)
import Exp
import Nat hiding (aux)
import LTree
import Rose hiding (g)
import Probability
import Data.List hiding (find)
import Data.List.Split hiding (split,chunksOf) 
import Svg hiding (for,wrap)
import Control.Concurrent 
import Cp2223data

import Control.Concurrent (threadDelay)

import System.IO  
import Control.Monad

type Square = (Point, Side)
type Side = Double
type Point = (Double,Double)
await = threadDelay 1000000

drawSq x = picd'' [Svg.scale 0.10 (0,0) (x >>=sq2svg)]
sq2svg (p,l) = (color "#67AB9F".polyg) [p,p .+(0,l),p .+(l,l),p .+(l,0)]

sierpinski :: (Square,Int) -> [Square]
sierpinski (((x,y),t),p)= hyloRose gr2l gsq (((x+t,y+t),t),p)

geneCarpets :: Int -> Either [Square] ([Square],Int)
geneCarpets 0 = Left (sierpinski (((0,0), 32),0))
geneCarpets p = Right (sierpinski (((0,0),32),p-1),p-1)

carpets :: Int -> [[Square]] 
carpets = anaList geneCarpets

genePresent :: Either () ([Square],IO [()]) -> IO [()]
genePresent g = case g of
  Left () -> return []
  Right (s,io) -> do x <- io
                     drawSq s
                     await 
                     return (():x)
                     
present :: [[Square]] -> IO [()]
present = cataList genePresent

constructSierp :: Int -> IO [()]
constructSierp = present . carpets

gr2l :: (a,[[a]]) -> [a]
gr2l (s, []) = [s]
gr2l (s,l) = s : concat l

gsq :: (Square, Int) -> (Square,[(Square, Int)])
gsq (s,0) = (s,[])
gsq (s,p) = (s, map (\x -> (x,p-1)) (carpet s))

carpet :: Square -> [Square]
carpet (p,l) =[(p .+(-2*l/3 ,   l/3),l/3),(p .+(-2*l/3 ,    4*l/3),l/3),
                (p .+(-2*l/3 ,-2*l/3),l/3),(p .+(  l/3  ,    4*l/3),l/3),
                (p .+(  l/3  , -2*l/3),l/3),(p .+( 4*l/3 ,    4*l/3),l/3),
                (p .+( 4*l/3 ,    l/3),l/3),(p .+( 4*l/3 ,   -2*l/3),l/3)]

rose2List :: Rose Square -> [Square]
rose2List = cataRose gr2l

sierp4 = drawSq (sierpinski (((0,0),32),3))

constructSierp5 = do drawSq (sierpinski (((0,0),32),0))
                     await
                     drawSq (sierpinski (((0,0),32),1))
                     await
                     drawSq (sierpinski (((0,0),32),2))
                     await
                     drawSq (sierpinski (((0,0),32),3))
                     await
                     drawSq (sierpinski (((0,0),32),4))
                     await
