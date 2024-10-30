
# Breakout Blitz

Welcome to Breakout Blitz – a classic Breakout-style arcade game where the player controls a paddle to bounce a ball and break all bricks on the screen. Built with C++ and SFML, this game includes enhanced gameplay mechanics like brick lifespans and changing colors, making it both fun and challenging.

## Features

- **Brick Lifespan Mechanic**: Bricks require multiple hits to be destroyed, with their color changing as their lifespan decreases.
  - **Blue**: 3 hits remaining
  - **Pink**: 2 hits remaining
  - **Yellow**: 1 hit remaining
  - **Destroyed**: 0 hits remaining
- **Smooth Paddle and Ball Movement**: Responsive controls for paddle movement and smooth ball physics.
- **Score Tracking**: Displays the player’s score based on bricks destroyed.
- **Pause and Control Options**: Toggle between playing and pausing, with on-screen controls for user-friendly gameplay.

## Game Controls
- A / D: Move paddle left/right
- ESC: Pause/Resume the game
- Q: Quit the game

## Code Structure
This project is designed using the Entity Component System (ECS) pattern, making it modular, reusable, and efficient for handling game objects.

- Game.cpp and Game.hpp: Core game logic, including entity spawning, movement, collision, and rendering.
- EntityManager.cpp and EntityManager.hpp: Manages all game entities such as bricks, paddle, and ball.
- Components/: Contains various components (e.g., CTransform, CShape, CCollision) that define entity properties and behaviors. This setup allows for scalable and reusable entity definitions.

## Setup Instructions

### Prerequisites
- **SFML**: This project requires the Simple and Fast Multimedia Library (SFML) for rendering and handling multimedia. Download SFML from [here](https://www.sfml-dev.org/download.php).
- **C++ Compiler**: Ensure you have a compatible C++ compiler, such as GCC (for Linux/macOS) or MSVC (for Windows).
- **Visual Studio** (for Windows): Recommended IDE for Windows users to easily handle SFML linking.

### 1. Clone the Repository
Clone the project to your local machine using Git:

```bash
git clone https://github.com/Joseph-Joestar-7/Breakout-Blitz.git
cd Breakout-Blitz
```

### 2. Building on Windows
1. **Open the Solution File**: Open the `Breakout Blitz.sln` file in Visual Studio.
2. **Configure SFML**:
   - Add the SFML include directory (likely `include/SFML`) in **Project Properties > C/C++ > General > Additional Include Directories**.
   - Link the SFML libraries from the `lib` directory in **Project Properties > Linker > General > Additional Library Directories**.
3. **Build the Solution**:
   - Set the build configuration to **Debug**.
   - Go to **Build > Build Solution** to compile the game.
4. **Run the Game**:
   - After a successful build, navigate to the output directory (`x64/Debug`) and run the generated `BreakoutBlitz.exe` file.

### 3. Building on macOS
1. **Install SFML**:
   - Use Homebrew to install SFML by running: 
     ```bash
     brew install sfml
     ```

2. **Compile the Game**:
   - Navigate to the project's root directory and compile the source files using `g++` with SFML libraries. Run:
     ```bash
     g++ -std=c++17 src/*.cpp -o BreakoutBlitz -lsfml-graphics -lsfml-window -lsfml-system
     ```

3. **Run the Game**:
   - After compilation, run the game with:
     ```bash
     ./BreakoutBlitz
     ```

### 4. Building on Linux
1. **Install SFML**:
   - Use your package manager to install SFML. For Ubuntu/Debian, run:
     ```bash
     sudo apt update
     sudo apt install libsfml-dev
     ```

2. **Compile the Game**:
   - Compile the source files using `g++` with SFML libraries by running:
     ```bash
     g++ -std=c++17 src/*.cpp -o BreakoutBlitz -lsfml-graphics -lsfml-window -lsfml-system
     ```

3. **Run the Game**:
   - After a successful compilation, run the game with:
     ```bash
     ./BreakoutBlitz
     ```

