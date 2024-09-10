module Main where

import Data.Time.Clock.POSIX
import Control.Monad.IO.Class
import Types
import FileUtils
import Tarefa1
import Tarefa2
import Tarefa3
import Tarefa4
import Tarefa5
import Tarefa6
import UI.NCurses

loadManager :: Manager
loadManager = ( Manager (q) 0 0 0 0 defaultDelayTime )

-- | __'updateControlledPlayer'__: this function allows the player to move Pacman with the keyboard
updateControlledPlayer :: Key -> Manager -> Manager
updateControlledPlayer k (Manager (State m pl l) pid step bf delt del) = case k of 
               KeyUpArrow -> (Manager (State m (changeOrientation pid pl U) l) pid step bf delt del)
               KeyDownArrow -> (Manager (State m (changeOrientation pid pl D) l) pid step bf delt del)
               KeyLeftArrow -> (Manager (State m (changeOrientation pid pl L) l) pid step bf delt del)
               KeyRightArrow -> (Manager (State m (changeOrientation pid pl R) l) pid step bf delt del)

-- | __'changeOrientation'__: auxiliary funtion to "updateControlledPlayer"
changeOrientation :: Int -> [Player] -> Orientation -> [Player]
changeOrientation _ [] _ = []
changeOrientation id ((Pacman (PacState (x,y,z,t,h,l) q c d )):xs) o 
        | id == x = ((Pacman (PacState (x,y,z,o,h,l) q c d )):xs)
        | otherwise = (Pacman (PacState (x,y,z,t,h,l) q c d )):(changeOrientation id xs o)
changeOrientation id ((Ghost (GhoState (x,y,z,t,h,l) q )):xs) o
        | id == x = ((Ghost (GhoState (x,y,z,o,h,l) q )):xs)
        | otherwise = (Ghost (GhoState (x,y,z,t,h,l) q )):(changeOrientation id xs o) 

updateScreen :: Window  -> ColorID -> Manager -> Curses ()
updateScreen w a man =
                  do
                    updateWindow w $ do
                      clear
                      setColor a
                      moveCursor 0 0 
                      drawString $ show (state man)
                    render
     
currentTime :: IO Integer
currentTime = fmap ( round . (* 1000) ) getPOSIXTime

updateTime :: Integer -> Manager -> Manager
updateTime now (Manager (State m (x:xs) n) pid step bf delt del) = (Manager (State m (x:xs) n) pid step bf (now-bf) del)

resetTimer :: Integer -> Manager -> Manager
resetTimer now (Manager (State m (x:xs) n) pid step bf delt del) = (Manager (State m (x:xs) n) pid step now 0 del)

nextFrame :: Integer -> Manager -> Manager
nextFrame now (Manager (State m (x:xs) n) pid step bf delt del) = resetTimer now (Manager (passTime step (State m (x:xs) n)) pid (step+1) bf delt del)


loop :: Window -> Manager -> Curses ()
loop w man@(Manager s pid step bf delt del ) = do 
  color_schema <- newColorID ColorBlue ColorWhite  10
  now <- liftIO  currentTime
  updateScreen w  color_schema man
  if ( delt > del )
    then loop w $ nextFrame now man
    else do
          ev <- getEvent w $ Just 0
          case ev of
                Nothing -> loop w (updateTime now man)
                Just (EventSpecialKey arrow ) -> loop w $ updateControlledPlayer arrow (updateTime now man)
                Just ev' ->
                  if (ev' == EventCharacter 'q')
                    then return ()
                    else loop w (updateTime now man)

main :: IO ()
main =
  runCurses $ do
    setEcho False
    setCursorMode CursorInvisible
    w <- defaultWindow
    loop w loadManager