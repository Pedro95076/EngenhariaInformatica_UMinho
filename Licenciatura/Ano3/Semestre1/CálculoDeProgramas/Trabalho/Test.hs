import Cp
import St
import Nat

import System.IO  
import Control.Monad

main = do
    let f1list = map (f 1 1 1) [0..20]
        g1list = map (fbl 1 1 1) [0..20]
        
        f2list = map (f 1 2 3) [0..20]
        g2list = map (fbl 1 2 3) [0..20]
        
        f3list = map (f (-2) 1 5) [0..20]
        g3list = map (fbl (-2) 1 5) [0..20]
    
    print (f1list)
    print (g1list)

    print (f2list)
    print (g2list)

    print (f3list)
    print (g3list)

f :: Int -> Int -> Int -> Int -> Int
f a b c 0 = 0
f a b c 1 = 1
f a b c 2 = 1
f a b c n = a * (f a b c (n - 1)) + b * (f a b c (n - 2)) + c * (f a b c (n-3))


--Solucao exercicio 1

g :: Int -> Int -> Int -> Int -> Int
g a b c 0 = 1
g a b c n = a * (g a b c (n-1)) + b * (h a b c (n-1)) + c * (i a b c (n-1))

h :: Int -> Int -> Int -> Int -> Int
h a b c 0 = 1
h a b c n = (g a b c (n-1)) 

i :: Int -> Int -> Int -> Int -> Int
i a b c 0 = 0
i a b c n = (h a b c (n-1)) 


fbl a b c = p2 . for (loop a b c) init where
    loop a b c ((g,h),i) = ((a*g+b*h+c*i,g),h)
    init = ((1,1),0)  
