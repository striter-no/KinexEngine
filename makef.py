from os import system as sy
from sys import argv

name = argv[1]

sy("cls")
sy(f"g++ -O3 -std=c++23 -c {name}.cpp -I src/include")
sy(f"g++ -O3 -o {name}.exe {name}.o -I src/include -L src/lib -l glew32 -l opengl32 -l glfw3dll -l winmm -Wall")
print("STARTING>>")
sy(name)
sy("del *.o")
sy("move *.exe out/")