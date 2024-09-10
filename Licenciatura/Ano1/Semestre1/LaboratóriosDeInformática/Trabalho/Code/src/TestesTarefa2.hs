module TestesTarefa2 where

import Tarefa2
import Tarefa1
import Types

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

{---- Simple movement tests ----}
     -- Data
players1 = [pl1]
pl1 = (Pacman (PacState (0,(2,9),1,R,0,1) 0 Open Normal))
maze1 = generateMaze 14 14 643
baseState1 = (State maze1 players1 1)

-- Movement tests
testMoveR = play (Move 0 R) baseState1
testMoveL = play (Move 0 L) testChangeOrientationL
testMoveU = play (Move 0 U) testChangeOrientationU
testMoveD = play (Move 0 D) testChangeOrientationD
-- Orientation change tests
testChangeOrientationR = play (Move 0 R) testChangeOrientationL 
testChangeOrientationL = play (Move 0 L) baseState1
testChangeOrientationU = play (Move 0 U) baseState1
testChangeOrientationD = play (Move 0 D) baseState1
-- Test of collision into a wall
beforeCollisionWall = testMoveL
afterCollisionWall  = play (Move 0 L) testMoveL

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

{---- Eating tests ----}
     -- Data
players2 = [pl2, gh2,gh2']
players2'= [pl2',gh2,gh2']
players2x= [pl2x,gh2,gh2']
pl2 = (Pacman (PacState (0,(11,3),1,L,0,1) 0 Open Normal))
pl2'= (Pacman (PacState (0,(10,3),1,R,0,1) 0 Open Normal))
pl2x= (Pacman (PacState (0,(10,2),1,R,0,1) 0 Open Normal))
gh2 = (Ghost (GhoState (1,(2,1),1,R,0,1) Alive))
gh2'= (Ghost (GhoState (2,(2,2),1,R,0,1) Alive))
maze2 = generateMaze 14 14 643
baseState2  = (State maze2 players2  1)
baseState2' = (State maze2 players2' 1)
baseState2x = (State maze2 players2x 1)

-- Eat little food
testLittleFood = play (Move 0 L) baseState2
-- Eat two food littles
testLittleFood2 = play (Move 0 L) testLittleFood
-- Eat big food
testBigFood = play (Move 0 R) x
            where x = play (Move 0 R) baseState2'
-- Eat two different foods
testTwoDiffFood = play (Move 0 R) x
                where x = play (Move 0 R) baseState2x

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

{---- Test the tunnel ----}
     -- Data
player3l = [pl3l]
player3r = [pl3r]
pl3l = (Pacman (PacState (0,(7,0),1,L,0,1) 0 Open Normal))
pl3r = (Pacman (PacState (0,(7,14),1,R,0,1) 0 Open Normal))
maze3 = generateMaze 15 15 357
baseState3l = (State maze3 player3l 1)
baseState3r = (State maze3 player3r 1)

-- Go through the tunnel (on the left)
testGoTunnelL = play (Move 0 L) baseState3l
-- Go through the tunnel (on the right)
testGoTunnelR = play (Move 0 R) baseState3r
-- Go through the tunnel and back
testGoBackTunnel = play (Move 0 R) x
                 where x = play (Move 0 R) y
                       y = play (Move 0 L) baseState3l

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

{--- Test the collision with ghosts ----}
     -- Data
player4a = [pl4a,gh4a,gh4d]
player4d = [pl4d,gh4a,gh4d]
pl4a = (Pacman (PacState (0,(4,7),1,L,0,2) 0 Open Normal))
pl4d = (Pacman (PacState (0,(4,7),1,L,0,1) 0 Open Normal))
gh4a = (Ghost (GhoState (1,(4,6),1,R,0,0) Alive))
gh4d = (Ghost (GhoState (2,(4,8),1,R,0,0) Dead ))
maze4 = generateMaze 15 15 357
baseState3a = (State maze4 player4a 1)
baseState3d = (State maze4 player4d 1)

-- Hit a living ghost, lose a life and stay alive
testLoseLife = play (Move 0 L) baseState3a
-- Hit a living ghost, lose a life and die
testDie = play (Move 0 L) baseState3d
-- Hit a dead ghost (right score and the ghost goes to the ghost house)
testDeadGhost = play (Move 0 R) x
              where x = play (Move 0 R) baseState3a