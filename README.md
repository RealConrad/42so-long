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
- [Troubleshooting](#troubleshooting)
- [Credits](#credits)
- [License](#license)

<div align="center">
 <img width="764" alt="Screenshot 2023-08-09 at 15 38 38" src="https://github.com/RealConrad/42so-long/assets/79513076/7c14333d-69e2-4f16-ba79-45ef90ca502c">
</div>
<br />

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
    - The map must end with `.ber`. \

Here is an example of a vaild map:
```
1111111111111
1C010T000T0C1
1000011111001
1P0011ET00001
1111111111111
```

## Installation
### Installing Dependencies
Ensure you have *cmake* and *glfw* installed. You can check via: `cmake --version`. If there is a version number, you good to go.
**<h4>For macOS:</h4>**
  - Install brew if you don't have it:  
```bash
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```
  - Install cmake
 ```bash
brew install cmake
brew install glfw
```
**<h4>For Lunix (Debian, Ubuntu etc.):</h4>** 
```bash
sudo apt update
sudo apt install -y cmake
sudo apt install libglfw3-dev
```

### Setting Up The Game
1. Clone the repository
```bash
git clone https://github.com/RealConrad/42so-long.git
```
2. Enter the directory and build everything
> NOTE: this project has git sub-modules of [MLX42](https://github.com/codam-coding-college/MLX42.git) and [42c-library](https://github.com/RealConrad/42c-library.git). Running `make` will clone these repositories.
```bash
cd 42so-long
make
```
3. Start the game
> Replace the second argument with the map file path: `./so_long <map-file-path>`
```bash
./so_long ./maps/valid/level3.ber
```

## Troubleshooting
If you encounter any problems, don't hesitate to open a new <a href="https://github.com/RealConrad/42so-long/issues"> Issue </a> and I will get back to you ASAP.
1. Incorrect brew folder:
   ```
   ld: warning: directory not found for option '-L/Users/<user>/.brew/opt/glfw/lib/'
   ```
   Type `which brew` in a terminal, and change the the BREW variable in the Makefile
    ```
     BREW = <your-brew-directory>
    ```
   Also change the Makefile variable (`MLX_FLAGS`) to where your glfw is installed.
     ```
     -L"/Users/$(USER)/$(BREW)/opt/glfw/lib/"
     ```

## Credits
<h4>1. Game Assets</h4>
I DO NOT take any credit for the artwork/assets used in this game. All credit goes to <a href="https://0x72.itch.io/dungeontileset-ii">Robert (0x72)</a>.

<h4>2. Game Engine/Library</h4>
You can find more information about the MLX42 library <a href="https://github.com/codam-coding-college/MLX42/tree/master">here</a>.

## License
[MIT](https://choosealicense.com/licenses/mit/)
