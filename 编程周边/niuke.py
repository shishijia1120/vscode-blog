ratings = ['c','c','d','d','c','e','b','a','c']
data = input()
print(data)
ratings.append(data)
l1 = ['a','b','c','d','e']
s ={}
for a in l1:
    s[a]=ratings.count(a)
      
print(s)