/* All indices starts from 1.		  
   dir(p,q,r) returns +ve number if p-q-r segments are clockwise,
     -ve number if they are anti clockwise and 0 if collinear.
     it can be defined as (q.y-p.y)(r.x-p.x) - (q.x-p.x)(r.y-p.y)
*/     
GetAllAntiPodalPairs(p[1..n])
  //Obtain upper and lower parts of polygon
  p’ = Sort p lexicographically (i.e. first by x then by y)
  U, L = create new stacks of points
  for k = 1 to n
    while U.size > 1 and dir(U[U.size-1], U[U.size], p’[k]) <= 0
      U.pop()
    while L.size > 1 and dir(L(L.size-1], L[L.size], p’[k]) >= 0
      L.pop()
    U.append(p’[k])
    L.append(p’[k])
	
  //Now we have U and L, apply rotating calipers
  i = 1
  j = L.size
  while i < U.size or j > 1
    yield U[i], L[j]
	
    //if i or j made it all the way through
    //advance other size
    if i = U.size
      j = j - 1
    else if j = 1
      i = i + 1
    else if (U[i+1].y - U[i].y) * (L[j].x - L[j-1].x)
         > (U[i+1].x - U[i].x) * (L[j].y - L[j-1].y)
      i = i + 1
    else
      j = j - 1