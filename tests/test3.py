def testf(a):
	print("Testing f...")
	if a % 2 == 0:
		print("Your number is even!")
	else:
		print("Your number is odd!")
	
	print("Done testing f!")


a = int(input("Give me a number: "))

if __name__ == "__main__":
	print("Running through an if statement!")
	if a == 0:
		print("You typed 0!")
	else:
		testf(a)
	

