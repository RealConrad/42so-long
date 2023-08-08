<div align="center">
  <h1>
    📗 So Long
  </h1>
  <p>
    <b><i>A simple 2D game.</i></b>
  </p>
  <p>
    Developed using&nbsp&nbsp
    <a href="https://skillicons.dev">
      <img src="https://skillicons.dev/icons?i=c,vscode,git" />
    </a>
  </p>
</div>

<br />

## Table Of Content
- [Features](#features)
- [Game Mechanics](#game-mechanics)
- [Graphics Management](#graphics-management)
- [Map Design](#map-design)
- [Installation](#installation)
- [Tools](#tools)
- [Credits](#credits)

## Features
- **2D Gameplay:** Embark on a journey in the world of 'So Long' where the player's objective is to collect all the items scattered throughout the map and then find the exit to escape. Beware of traps and enemies!
- **Sprite Animation:** All sprites in the game are animated.
- **Game Over Screen:** Whether you win or lose, there will be a game-over screen with a message displayed.
- **Player Dialogue:** The player has some random dialogue that gets displayed to the screen every now and then. 
- **Map Customization:** Create your own custom maps. Learn more [here](#map-design).
- **Error Handling:** The game is equipped to handle any map misconfigurations, unexpected exits or malloc fails. 
- **Documentaiton:** All functions are documented using doxygen comments to facilitate the understanding of the underlying logic.

## Game Mechanics
- **Movement:** Move with W, A, S, and D keys.
- **Movement count:** Displays the total number of moves the player has done on screen.
- **Enviroment:** The map may contain 1 enemy, multiple mimics and traps.

## Graphics Management
- The game opens in a new window.
- Fluid window operations like minimizing, transitioning to another window, etc.
- Quick exit the game by pressing **ESC** or the close button. 

## Map Design
- The game supports the current map elements:
  - `1` for walls.
  - `0` for empty space (ground).
  - `D` for enemy patrol.
  - `P` for starting player position.
  - `M` for mimic enemy.
  - `C` for collectable.
  - `E` for exit.
  - `T` for trap.
- For the map to be "valid". The following have to be true:
    - There must be 1 player (`P`).
    - There must be atleast 1 collectable (`C`).
    - There must be 1 exit (`E`).
    - The map must be rectangular.
    - The map must be surrounded by walls.
    - The map must be solvable (e.g. The player (`P`) cannot be surrounded by walls).
    - The map must end with `.ber`.
