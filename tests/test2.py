number = input("Give me a number: ")
number = int(number)

if number == 0:
	print("Your number is 0!")
elif number > 0:
	if number > 10:
		print("Your number is greater than 10!")
	elif number == 10:
		print("Your number is 10!")
	
	else:
		print("Your number is smaller than 10!")
	
	print("Your number is positive!")
else:
	print("Your number is negative!")

