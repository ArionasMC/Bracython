# Bracython
A C++ preprocessor for Python with curly braces written by a university student who had nothing better to do.

Compiled with TDM-GCC

# Installation 
1) Install Python
2) Download the whole project or the 'bin' folder and the 'bry.bat' file and put them in the same directory
3) Add to your "Path" Environmental Variable the path to the above directory

# Let's Play
Let's make a new Bracython file! We'll make the equivalent of the famous HelloWorld "hello.bry". Open it with your favourite editor (e.g. Notepad++).
Remember: Python with curly braces:
```
def hello() {
  print('Hello Python with curly braces!')
}

hello()
```

Now we have to run this file.
1) Open your command prompt
2) Go to the directory of your "hello.bry" file
3) Type "bry hello.bry" (You can use the bry command if you have completed the 3rd Installation step)
4) Bracython will convert your "bry" file to a "py" one and execute "py hello.py"

# Tests
You can find a "tests" folder in this project where there are a few "bry" files testing the limits of this project.
For example, you can use this kind of syntax:
```
def hello() { print('Hello') }
```
or this one:
```
def hello()
{
  print('Hello')
}
```

If you find a block of code that is not correctly converted to Python with Bracython, I'll be happy to see and try implement it!
