def d(n):
    return n

def next(cur, n):
    return (cur+0.01)*(n+1)/n

pos = 0
i = 1
while d(i) > pos: 
    pos = next(pos,i)
    
print(i)
    