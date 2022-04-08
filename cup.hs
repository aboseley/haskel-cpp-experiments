
cup flOz = \msg -> msg flOz

coffeeCup = cup 12

getOz aCup = aCup (\x -> x ) 

drink aCup ozDrank = cup ozAfter 
   where ozAvail = getOz aCup
         ozDiff = ozAvail - ozDrank
         ozAfter = if ozDiff > 0 
             then ozDiff
             else 0

isEmpty aCup = getOz aCup == 0

afterManySips = foldl drink coffeeCup [1,2,3,4]
