module TestesTarefa1 where

import Tarefa1
import Types
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-- Test of the function "convertPiece"
convertPiece' :: Bool
convertPiece'  = testconvertPiece [3,0,50,70,80,99] -- This must be true

testconvertPiece :: [Int] -> Bool
testconvertPiece [] = True
testconvertPiece (x:xs) | x == 3             = if (convertPiece x == Food Big)    then testconvertPiece xs else False
                        | x >= 0  && x <  70 = if (convertPiece x == Food Little) then testconvertPiece xs else False
                        | x >= 70 && x <= 99 = if (convertPiece x == Wall )       then testconvertPiece xs else False
                        | otherwise = False
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-- Test of the function "numbers2pieces"
numbers2pieces' :: [Piece]
numbers2pieces' = numbers2pieces [3,0,50,80,99] -- This has to give “[o,.,.,#,#,#]
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-- Test of the function "list2maze"
     -- Data used in the test
random' = geneRandoms (4*4) 33   -- [19,85,45,69,44,90,3,3,13,68,64,53,22,71,36,22]
pieces' = numbers2pieces random' -- [. ,# ,. ,. ,. ,# ,o,o,. ,. ,. ,. ,. ,# ,. ,. ]

list2maze' :: Maze
list2maze' = list2maze 4 pieces' -- This has to give [[.,#,.,.],[.,#,o,o],[.,.,.,.],[.,#,.,.]]

     -- This function generates the maze without the top, bottom and vertical walls
mazeList2maze :: Int -> Int -> Int -> IO ()
mazeList2maze l a s = 
    let nr = (l-2) * (a-2) 
        random = geneRandoms nr s
        pieces = numbers2pieces random
        m = list2maze (l-2) pieces
        m'= printMaze m
    in m'
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-- Test of the function "twoWalls"
twoWalls' :: [Piece]
twoWalls' = twoWalls 4 -- [This has to give : [#,#,#,#] 

     -- For example : "testwoWalls" 4 has to give "(True,[#,#,#,#])" 
testtwoWalls :: Int -> (Bool,[Piece])
                        -- First element of the pair is True because all the pieces are Walls
                              -- Second element of the pair show what the function "twoWalls" should give
testtwoWalls x = (alwaysWalls (twoWalls x),twoWalls x)
               where alwaysWalls :: [Piece] -> Bool                        
                     alwaysWalls [] = True                                  
                     alwaysWalls (x:xs) | x == Wall = alwaysWalls xs
                                        | otherwise = False

     -- This function generates the maze only with the top and bottom walls without the vertical walls
mazeTwoWalls :: Int -> Int -> Int -> IO () 
mazeTwoWalls l a s = 
    let nr = (l-2) * (a-2) 
        random = geneRandoms nr s
        pieces = numbers2pieces random
        m = list2maze (l-2) pieces
        w = (twoWalls l : m) ++ [twoWalls l]
        w'= printMaze w
    in w'
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-- Test of the function "tunnel"
     -- Data used in the test
mazeEven :: Maze
mazeEven = [[Wall,Wall,Wall,Wall,Wall,Wall]
           ,[Wall,Food Little,Food Little,Food Little]
           ,[Wall,Food Little,Food Little,Wall]
           ,[Food Little,Food Little,Food Little,Food Little]
           ,[Food Little,Food Little,Wall,Wall]
           ,[Wall,Wall,Wall,Wall,Wall,Wall]]
             -- Width = 6 // Height 6
mazeOdd  :: Maze
mazeOdd  = [[Wall,Wall,Wall,Wall,Wall]
           ,[Wall,Food Little,Food Little]
           ,[Food Little,Wall,Food Little]
           ,[Food Little,Wall,Food Little]
           ,[Wall,Wall,Wall,Wall,Wall]] 
            -- Width 5 = // Height 5

tunnelEven' :: Maze
tunnelEven' = tunnelEven 6 6 (mazeEven) -- This has to give : [[#,#,#,#,#,#],[#,.,.,.],[Empty,#,.,.,#,Empty],[Empty,.,.,.,.,Empty],[.,.,#,#],[#,#,#,#,#,#]]
tunnelOdd' :: Maze
tunnelOdd'  = tunnelOdd  5 5 (mazeOdd)  -- This has to give : [[#,#,#,#,#],[#,.,.],[Empty,.,#,.,Empty],[.,#,.],[#,#,#,#,#]]

     -- This fuction test if the function Tunnel uses the right function between "tunnelEven" and "tunnelOdd"
testTunnel :: Int -> Int -> Maze -> Bool
testTunnel a b l | even b && tunnel a b l == tunnelEven' = True -- testTunnel 6 6 mazeEven should give True
                 | odd  b && tunnel a b l == tunnelOdd'  = True -- TestTunnel 5 5 mazeOdd slould give False
                 | otherwise = False

     -- This function generates the maze only with the top and bottom walls, with the empty space for the tunnel but without the vertical walls
mazeTunnel :: Int -> Int -> Int -> Maze
mazeTunnel l a s = 
    let nr = (l-2) * (a-2) 
        random = geneRandoms nr s
        pieces = numbers2pieces random
        m = list2maze (l-2) pieces
        w = (twoWalls l : m) ++ [twoWalls l]
        t = tunnel a a w
    in t
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-- Test of the function "verticalWalls"
     -- Data used in the test (example of a maze without vertical walls)
mazeWithoutVM :: Maze
mazeWithoutVM = [[Wall,Wall,Wall,Wall,Wall]
                ,[Wall,Food Little,Food Little]
                ,[Empty,Food Little,Wall,Food Little,Empty]
                ,[Food Little,Wall,Food Little]
                ,[Wall,Wall,Wall,Wall,Wall]] 

mazeWithVM :: Maze
mazeWithVM = [[Wall,Wall,Wall,Wall,Wall]
             ,[Wall,Wall,Food Little,Food Little,Wall]
             ,[Empty,Food Little,Wall,Food Little,Empty]
             ,[Wall,Food Little,Wall,Food Little,Wall]
             ,[Wall,Wall,Wall,Wall,Wall]] 

     -- This function tests if the function "verticalWalls" applied to a maze without walls if it places the walls correctly
testVerticalWalls :: Bool
testVerticalWalls = if (verticalWalls 5 mazeWithoutVM) == (mazeWithVM) then True else False

-- This function generates the maze with the top and bottom walls, with the empty space for the tunnel and with the vertical walls
mazeVerticalWalls :: Int -> Int -> Int -> IO ()
mazeVerticalWalls l a s = 
    let nr = (l-2) * (a-2) 
        random = geneRandoms nr s
        pieces = numbers2pieces random
        m = list2maze (l-2) pieces
        w = (twoWalls l : m) ++ [twoWalls l]
        t = tunnel a a w
        z = verticalWalls l t
        z'= printMaze z
    in z'
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-- Test of the function "ghousposition" and their aux functions
     -- Maze used to test the functions "ghouscor","ghousecor1" and "ghouseposition"
mazeExOdd :: Maze
mazeExOdd = [[Wall,Food Little,Food Little,Wall]
            ,[Wall,Food Little,Wall,Wall]
            ,[Wall,Food Little,Food Little,Wall]
            ,[Empty,Food Little,Wall,Empty]
            ,[Wall,Food Little,Wall,Wall]
            ,[Wall,Food Little,Food Little,Wall]
            ,[Wall,Food Big,Food Big,Wall]]
mazeExEven :: Maze
mazeExEven = [[Wall,Food Little,Food Little,Wall]
            ,[Wall,Food Little,Wall,Wall]
            ,[Wall,Food Little,Food Little,Wall]
            ,[Empty,Food Little,Wall,Empty]
            ,[Empty,Food Little,Wall,Empty]
            ,[Wall,Food Little,Wall,Wall]
            ,[Wall,Food Little,Food Little,Wall]
            ,[Wall,Food Big,Food Big,Wall]]

     -- This function tests if the function "ghousecor" takes the correct corridor(s)
testGhousecor :: Bool
testGhousecor = if ghousecor mazeExOdd  == [[Wall,Food Little,Food Little,Wall]]
                && ghousecor mazeExEven == [[Wall,Food Little,Food Little,Wall]]
                then True else False
     -- This function tests if the function "ghousecor1" takes the correct corridor(s)
testGhousecor1 :: Bool
testGhousecor1 = if ghousecor1 mazeExOdd  == [[Wall,Food Big,Food Big,Wall]]
                 && ghousecor1 mazeExEven == [[Wall,Food Little,Food Little,Wall],[Wall,Food Big,Food Big,Wall]]
                 then True else False

     -- This function test if the function "ghosthouse" picks the correct maze between the even and the odd
testGhosthouse :: Int -> Bool
testGhosthouse l | even l && even (g (ghosthouse l)) = True
                 | odd  l && odd  (g (ghosthouse l)) = True
                 | otherwise = False
                     where g :: Maze -> Int
                           g (h:t) = length h

     -- This function test if the functions "ghousecor","ghousecor1" and "ghosthouse" work correctly together
testGhouseposition :: Bool                             
testGhouseposition = if ghouseposition (mazeExOdd)  1 == [[Wall,Food Little,Food Little,Wall]] 
                                                         ++
                                                         [[Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty]
                                                         ,[Empty,Wall,Wall,Wall,Empty,Empty,Empty,Wall,Wall,Wall,Empty]
                                                         ,[Empty,Wall,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Wall,Empty]
                                                         ,[Empty,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Empty]
                                                         ,[Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty]] 
                                                         ++
                                                         [[Wall,Food Big,Food Big,Wall]]
                     && ghouseposition (mazeExEven) 2 == [[Wall,Food Little,Food Little,Wall]] 
                                                         ++
                                                         [[Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty]
                                                         ,[Empty,Wall,Wall,Wall,Empty,Empty,Wall,Wall,Wall,Empty]
                                                         ,[Empty,Wall,Empty,Empty,Empty,Empty,Empty,Empty,Wall,Empty]
                                                         ,[Empty,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Empty]
                                                         ,[Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty]] 
                                                         ++
                                                         [[Wall,Food Little,Food Little,Wall],[Wall,Food Big,Food Big,Wall]]
                     then True else False

     -- This function generates the maze with the ghost house in the middle of the maze height
mazeGhouseposition :: Int -> Int -> Int -> IO ()
mazeGhouseposition l a s = 
    let nr = (l-2) * (a-2) 
        random = geneRandoms nr s
        pieces = numbers2pieces random
        m = list2maze (l-2) pieces
        w = (twoWalls l : m) ++ [twoWalls l]
        t = tunnel a a w
        z = verticalWalls l t
        g = ghouseposition z l
        g'= printMaze g
    in g'
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-- Test of the function "firstpositions"
     -- Examples of mazes used for testing
mazeWithoutGH :: Maze
mazeWithoutGH = [[Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall]
                ,[Wall,Wall,Food Little,Food Little,Wall,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Wall,Wall]
                ,[Wall,Food Little,Food Little,Food Little,Wall,Wall,Wall,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Wall]
                ,[Empty,Wall,Food Little,Wall,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Empty]
                ,[Wall,Food Little,Food Little,Food Little,Food Little,Food Little,Wall,Food Little,Food Little,Wall,Food Little,Wall,Food Little,Food Little,Wall]
                ,[Wall,Food Little,Food Little,Food Little,Food Little,Food Little,Wall,Food Little,Food Little,Food Little,Food Little,Wall,Wall,Wall,Wall]
                ,[Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall]]

mazeWithGH :: Maze
mazeWithGH = [[Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall]
             ,[Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty]
             ,[Empty,Wall,Wall,Wall,Empty,Empty,Empty,Wall,Wall,Wall,Empty]
             ,[Empty,Wall,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Wall,Empty]
             ,[Empty,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Empty]
             ,[Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty]
             ,[Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall]]

maze1positions :: Maze
maze1positions = [[Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall]
                 ,[Wall,Wall,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty]
                 ,[Wall,Food Little,Empty,Wall,Wall,Wall,Empty,Empty,Empty,Wall,Wall,Wall,Empty]
                 ,[Empty,Wall,Empty,Wall,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Wall,Empty]
                 ,[Wall,Food Little,Empty,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Empty]
                 ,[Wall,Food Little,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty]
                 ,[Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall]]

     -- This function tests if the function "firstpositions" works correctly
testfirstpositions :: Bool
testfirstpositions = if firstpositions 15 mazeWithGH mazeWithoutGH == maze1positions then True else False

     -- This function generates the maze with the ghost house and the pieces that are to the left of the house
mazeFirstpositions :: Int -> Int -> Int -> IO ()
mazeFirstpositions l a s = 
    let nr = (l-2) * (a-2) 
        random = geneRandoms nr s
        pieces = numbers2pieces random
        m = list2maze (l-2) pieces
        w = (twoWalls l : m) ++ [twoWalls l]
        t = tunnel a a w
        z = verticalWalls l t
        g = ghouseposition z l
        f = firstpositions l g z
        f'= printMaze f
    in f'
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-- Test of the function "lastpositions"
     -- Examples of mazes used for testing
mazeWithoutGH' :: Maze
mazeWithoutGH' = [[Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall]
                ,[Wall,Wall,Food Little,Food Little,Wall,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Wall,Wall]
                ,[Wall,Food Little,Food Little,Food Little,Wall,Wall,Wall,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Wall]
                ,[Empty,Wall,Food Little,Wall,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Empty]
                ,[Wall,Food Little,Food Little,Food Little,Food Little,Food Little,Wall,Food Little,Food Little,Wall,Food Little,Wall,Food Little,Food Little,Wall]
                ,[Wall,Food Little,Food Little,Food Little,Food Little,Food Little,Wall,Food Little,Food Little,Food Little,Food Little,Wall,Wall,Wall,Wall]
                ,[Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall]]

mazeWith1positions :: Maze
mazeWith1positions = [[Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall]
                     ,[Wall,Wall,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty]
                     ,[Wall,Food Little,Empty,Wall,Wall,Wall,Empty,Empty,Empty,Wall,Wall,Wall,Empty]
                     ,[Empty,Wall,Empty,Wall,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Wall,Empty]
                     ,[Wall,Food Little,Empty,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Empty]
                     ,[Wall,Food Little,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty]
                     ,[Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall]]

mazeComplete :: Maze
mazeComplete = [[Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall]
               ,[Wall,Wall,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Wall,Wall]
               ,[Wall,Food Little,Empty,Wall,Wall,Wall,Empty,Empty,Empty,Wall,Wall,Wall,Empty,Food Little,Wall]
               ,[Empty,Wall,Empty,Wall,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Wall,Empty,Food Little,Empty]
               ,[Wall,Food Little,Empty,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Empty,Food Little,Wall]
               ,[Wall,Food Little,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Wall,Wall]
               ,[Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall]]

     -- This function tests if the function "lastpositions" works correctly
testlastpositions :: Bool
testlastpositions = if lastpositions 15 mazeWith1positions mazeWithoutGH' == mazeComplete then True else False

     -- This function generates the maze with the ghost house and the pieces that are to the left and to the right of the house
mazeLastpositions :: Int -> Int -> Int -> IO ()
mazeLastpositions l a s = 
    let nr = (l-2) * (a-2) 
        random = geneRandoms nr s
        pieces = numbers2pieces random
        m = list2maze (l-2) pieces
        w = (twoWalls l : m) ++ [twoWalls l]
        t = tunnel a a w
        z = verticalWalls l t
        g = ghouseposition z l
        f = firstpositions l g z
        n = lastpositions l f z
        n'= printMaze n
    in n'
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-- Examples of generated mazes
mazeExample1 :: IO () -- Example of the smallest maze
mazeExample1 = printMaze (generateMaze 15 10 453)
mazeExample2 :: IO () -- Example of an even width and even height maze
mazeExample2 = printMaze (generateMaze 18 14 453)
mazeExample3 :: IO () -- Example of an even width and odd height maze
mazeExample3 = printMaze (generateMaze 18 15 453)
mazeExample4 :: IO () -- Example of an odd width and even height maze
mazeExample4 = printMaze (generateMaze 17 14 453)
mazeExample5 :: IO () -- Example of an odd width and odd height maze
mazeExample5 = printMaze (generateMaze 17 15 453)                