import math

def solve(a, b, c):
	if a == 0:
		if b == 0:
			print("Error!")
		else:
			print(-c/b)
		
	else:
		d=math.sqrt(pow(b,2) - 4*a*c)
		if d >= 0:
			print((-b+d)/2*a)
			print((-b-d)/2*a)
		else:
			print("Meeeh I'm bored")
		
	


print("Give a, b, c to solve quadratic equation: ax^2 + bx + c = 0")
a = int(input("a = "))
b = int(input("b = "))
c = int(input("c = "))

solve(a, b, c)

