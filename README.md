# TetrisGameSDL2

To get the project working : 
1) Make sure you've downloaded SDL2/SDL2_image and added libraries and include directories to the project.
2) Make sure SDL2.dll, SDL2_image.dll, zlib.dll, libpng16-16.dll is in the source file.

# Technical Issues :
1) A 3*3 matrix is used to represent a tetris block, in that way it's easier to get the location of the each square of the matrix after the rotation of the block because
of the fact that origin's location remains the same.

# If i have more time, I'll add : 
1) Add a function into the map class that checks whether a line is completed so it'll be deleted from the map.
2) Add an end menu.

# Screenshots :

![alt text](https://github.com/emreOytun/TetrisGameSDL2/blob/master/screenshots/ss1.png)
![alt text](https://github.com/emreOytun/TetrisGameSDL2/blob/master/screenshots/ss2.png)
![alt text](https://github.com/emreOytun/TetrisGameSDL2/blob/master/screenshots/ss3.png)
