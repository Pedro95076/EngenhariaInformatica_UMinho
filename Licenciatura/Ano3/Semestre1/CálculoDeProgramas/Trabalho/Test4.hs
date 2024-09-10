module Test4 where

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

import System.IO  
import Control.Monad

type Team = String
type Group = [Team]
type Match = (Team, Team)

main = do
    let gsm   = genGroupStageMatches groups --Teste criacao de jogos dos grupos
        gpw   = simulateGroupStage   gsm    --Teste simulacao fase de grupos
        gpw'  = simulateGroupStage'  gsm    --Teste simulacao fase de grupos com consolidate'
       
        
      
    print "Grupos:"
    print ""
    mapM_ print groups
    print ""
    print "Jogos de cada Grupo:"
    print ""
    mapM_ print gsm
    print ""
    print "Vencedores do Grupo:"
    print ""
    mapM_ print gpw
    print ""
    print ("Vencedores por Grupos com consolidate':")
    print ""
    mapM_ print gpw'
    print ""
    print ("Vencedor do Mundial:")
    print ""
    print (arrangement gpw)
    print ""
    print "Vencedores do Grupo Probabilistico:"
    print ""
    print pwinner
  
groups :: [Group]
groups = [["Qatar"    , "Ecuador"     , "Senegal"    , "Netherlands"   ],
          ["England"  , "Iran"        , "USA"        , "Wales"         ],
          ["Argentina", "Saudi Arabia", "Mexico"     , "Poland"        ],
          ["France"   , "Denmark"     , "Tunisia"    , "Australia"     ],
          ["Spain"    , "Germany"     , "Japan"      , "Costa Rica"    ],
          ["Belgium"  , "Canada"      , "Morocco"    , "Croatia"       ],
          ["Brazil"   , "Serbia"      , "Switzerland", "Cameroon"      ],
          ["Portugal" , "Ghana"       , "Uruguay"    , "Korea Republic"]]

rankings = [("Argentina",      4.8), ("Australia", 4.0), ("Belgium",    5.0), ("Brazil",       5.0),
            ("Cameroon",       4.0), ("Canada",    4.0), ("Costa Rica", 4.1), ("Croatia",      4.4),
            ("Denmark",        4.5), ("Ecuador",   4.0), ("England",    4.7), ("France",       4.8),
            ("Germany",        4.5), ("Ghana",     3.8), ("Iran",       4.2), ("Japan",        4.2),
            ("Korea Republic", 4.2), ("Mexico",    4.5), ("Morocco",    4.2), ("Netherlands",  4.6),
            ("Poland",         4.2), ("Portugal",  4.6), ("Qatar",      3.9), ("Saudi Arabia", 3.9),
            ("Senegal",        4.3), ("Serbia",    4.2), ("Spain",      4.7), ("Switzerland",  4.4),
            ("Tunisia",        4.1), ("USA",       4.4), ("Uruguay",    4.5), ("Wales",        4.3)]


------------------------------------------------------------------------------


--1)
simulateGroupStage' :: [[Match]] -> [[Team]]
simulateGroupStage' = map (groupWinners' gsCriteria)

groupWinners' criteria = best 2 . consolidate' . (>>=matchResult criteria)

consolidate' :: (Eq a, Num b) => [(a, b)] -> [(a, b)]
consolidate' = cataList cgene

cgene (Left ())=[]
cgene (Right (h,t))=map (id><sum) (collect' c)
                   where c = h:t

--get all tuples that start with same element and second elems are all in a list
collect' :: (Eq a, Num b) => [(a, b)] -> [(a, [b])]
collect' [] = []
collect' l@((x,y):xs) = (x,(map snd (filter (\(a,b) -> a==x) l))) : collect' (filter (\(a,b) -> a /= x) xs)

--2)
matchResult :: (Match -> Maybe Team) -> Match -> [(Team, Int)]
matchResult f (x,y) 
    | w == Nothing = [(x,1),(y,1)]
    | w == Just x  = [(x,3),(y,0)]
    | w == Just y  = [(x,0),(y,3)]
    where w = f (x,y)

--3)
pairup :: Eq b => [b] -> [(b, b)]
pairup [] = []
pairup [x] = []
pairup (x:xs) = (map (\a -> (x,a)) xs) ++ pairup xs

--4)
initKnockoutStage = anaLTree glt . arrangement

glt [a] = Left a
glt l = Right (halfList l)

halfList :: [a] -> ([a], [a]) 
halfList l =((take h l), (drop h l))
    where h = (length l ) `div` 2


--glt (Leaf a) = Left (Leaf a)
--glt (Fork (a,b)) = Right (Fork (a,b))


------------------------------------------------------------------------------


------------------------------------------------------------------------------

--pinitKnockoutStage= undefined
pinitKnockoutStage  d= return $ (initKnockoutStage d)

pgroupWinners :: (Match -> Dist (Maybe Team)) -> [Match] -> Dist [Team]
pgroupWinners pgsCriteria m = D (map (\(a,b) -> ((best 2 $ consolidate $ concat $ map (\(c,d) -> [c,d]) a),b)) x) 
                             where D x = sequenceA $ map (pmatchResult pgsCriteria) m

pmatchResult f (x,y) 
  | fst (di!!0) == Nothing = D[(emp,snd (di!!0)),(vx,snd (di!!1)),(vy,snd (di!!2))]
  | otherwise = D [(vx,snd (di!!0)),(vy,snd (di!!1))]
  where D di=f (x,y)
        emp=((x,1),(y,1))
        vx=((x,3),(y,0))
        vy=((x,0),(y,3))
------------------------------------------------------------------------------

winner :: Team
winner = wcup groups

wcup = knockoutStage . groupStage

knockoutStage = cataLTree (either id koCriteria)

groupStage :: [Group] -> LTree Team
groupStage = initKnockoutStage . simulateGroupStage . genGroupStageMatches

genGroupStageMatches :: [Group] -> [[Match]]
genGroupStageMatches = map generateMatches

simulateGroupStage :: [[Match]] -> [[Team]]
simulateGroupStage = map (groupWinners gsCriteria)

groupWinners criteria = best 2 . consolidate . (>>=matchResult criteria)

generateMatches = pairup

arrangement = (>>= swapTeams) . chunksOf 4 where
  swapTeams [[a1,a2],[b1,b2],[c1,c2],[d1,d2]] = [a1,b2,c1,d2,b1,a2,d1,c2]

rank x = 4 ** (pap rankings x - 3.8)

gsCriteria = s . split (id >< id) (rank >< rank) where
  s ((s1, s2), (r1, r2)) = let d = r1 - r2 in
                           if d > 0.5 then Just s1
                                      else if d < -0.5 then Just s2
                                                       else Nothing
koCriteria = s . split (id >< id) (rank >< rank) where
  s ((s1, s2), (r1, r2)) = let d = r1 - r2 in
                           if d == 0 then s1
                                     else if d > 0 then s1 else s2

pgsCriteria = s . split (id >< id) (rank >< rank) where
  s ((s1, s2), (r1, r2)) =
     if abs(r1-r2) > 0.5 then fmap Just (pkoCriteria(s1,s2)) else f (s1,s2)
  f = D . ((Nothing,0.5):) . map (Just><(/2)) . unD . pkoCriteria

pkoCriteria (e1, e2) = D [(e1, 1 - r2 / (r1 + r2)), (e2, 1 - r1 / (r1 + r2))] where
    r1 = rank e1
    r2 = rank e2

psimulateGroupStage = trim .  map (pgroupWinners pgsCriteria)
trim = top 5 . sequence . map (filterP.norm)  where
   filterP (D x) = D [(a,p) | (a,p) <- x, p > 0.0001 ]
   top n = vec2Dist . take n . reverse . presort snd . unD 
   vec2Dist x = D [ (a,n/t) | (a,n) <- x ] where t = sum(map snd x) 

pwinner :: Dist Team
pwinner = mbin f x >>= pknockoutStage where
   f(x,y) = initKnockoutStage(x++y)
   x = split (g . take 4) (g . drop 4) groups
   g = psimulateGroupStage . genGroupStageMatches

best n = map fst . take n . reverse . presort p2

consolidate :: (Num d, Eq d, Eq b) => [(b, d)] -> [(b, d)]
consolidate = map (id><sum) . collect

collect :: (Eq a, Eq b) => [(a, b)] -> [(a, [b])]
collect x = nub [ k |-> [ d' | (k',d') <- x , k'==k ] | (k,d) <- x ]

mmbin :: Monad m => ((a, b) -> m c) -> (m a, m b) -> m c
mmbin f (a,b) = do { x <- a ; y <- b ; f(x,y) }

mbin :: Monad m => ((a, b) -> c) -> (m a, m b) -> m c
mbin = mmbin . (return.)

(f `is` v) x = (f x) == v

rcons(x,a) = x++[a]

pwcup = pknockoutStage .! pgroupStage 

pknockoutStage = mcataLTree' (either return pkoCriteria)

pgroupStage = pinitKnockoutStage .! psimulateGroupStage . genGroupStageMatches

mcataLTree' g = k where
        k (Leaf a) = g1 a
        k (Fork(x,y)) = mmbin g2 (k x, k y)
        g1 = g . i1
        g2 = g . i2