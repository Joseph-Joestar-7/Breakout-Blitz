
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

