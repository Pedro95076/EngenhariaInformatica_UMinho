module TestesTarefa3 where

import Tarefa1
import Tarefa3 
import Types

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-- compactMaze test with the smallest maze
testcompactMaze1 = compactMaze (generateMaze 15 10 111)
-- compactMaze test with a maze with a random maze
testcompactMaze2 = compactMaze (generateMaze 32 10 123)
-- compactMaze test with a maze with the same dimensions as before but with a different seed
testcompactMaze3 = compactMaze (generateMaze 32 10 111)
