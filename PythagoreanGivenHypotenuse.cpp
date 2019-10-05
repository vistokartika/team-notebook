// initialize c has all factors only primes 1 mod 4

c := Input()
ListOfPairs := []
For k in FactorsOf(c):
    s := c / k
    For n := 0 to Sqrt(s/2):
        mSquare = s - n^2
        m := Floor(Sqrt(mSquare))
        If m * m = mSquare:
            a = m^2 - n^2
            b = 2nm
            ListOfPairs.Push( (ka, kb) )
            ListOfPairs.Push( (kb, ka) )
Return ListOfPairs.RemoveDuplicates()
