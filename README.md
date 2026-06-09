Tic Tac Toe — SFML Arcade Edition:

A modern, arcade-style Tic Tac Toe game built using C++ and SFML 3.
This project evolved from a simple console game into a fully interactive GUI application with game states, animations, and polished UI designs.

-> Features:

- Interactive GUI built with SFML
- Main Menu (Start Screen)
- Player vs Player gameplay
- Turn-based logic (X and O)
- Win detection (rows, columns, diagonals)
- Draw detection system
- Restart functionality (Press R)
- Mouse-based input system
- Hover highlight effect on grid cells
- Winning line highlight (arcade neon style)
- Clean UI with centered layout
- Subtle developer signature on screen
- Game States

The game follows a structured state system:

MENU → Start screen
PLAYING → Active gameplay
GAMEOVER → Win/Draw screen

🛠️ Tech Stack:
C++
SFML 3 (Graphics, Window, System)
MinGW-w64 (GCC 14.2.0)

📁 Project Structure: (Main Files)
TicTacToe Game Project/
 1-TicTacToe.cpp
  2-arial.ttf (or custom font)
   3-orbitron.ttf (optional UI font)
    4-sfml libraries (linked via system path)

▶️ How to Run:
1. Compile
g++ TicTacToe.cpp -IC:\SFML\include -LC:\SFML\lib -lsfml-graphics -lsfml-window -lsfml-system -o TicTacToe
2. Run
.\TicTacToe.exe
That's it!

🎮 Controls:
Action	Input
Place X/O	Left Mouse Click
Restart Game	R Key
Start Game	Mouse Click on Menu

🎨 UI Highlights:
Neon-style win line effect
Clean grid layout
Centered menu design
Soft hover highlight on cells
Minimal but readable typography
Subtle developer watermark

-> Developer:
Built by Muhammad Ali (@ali4xk)
Software Engineering Student | Game & Software Development Enthusiast

Future Improvements (Ideas)
AI opponent (Minimax algorithm)
Sound effects (click / win / draw)
Animated transitions between states
Main menu buttons (Play / Exit)
Mobile or web version (future port)

📌 Note:

This project was built as a learning experience to understand:

Game loops
Event handling
UI rendering with SFML
State-based architecture
Basic game design principles
