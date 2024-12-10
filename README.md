# Solar System Simulation

This project creates a simple solar system simulation using OpenGL. The simulation includes a sun, a planet, a moon, and a dynamically moving meteor. A star field is also included in the background for visual enhancement.

## Features

- **Sun and Planet Movements**: The sun rotates on its axis, while the planet revolves around the sun and rotates on its axis.
- **Moon Movements**: The moon orbits the planet.
- **Meteor**: A meteor moves dynamically and triggers an explosion effect upon collision with a planet.
- **Stars**: Randomly placed stars decorate the scene.

## Requirements

To run this project, the following software and libraries are required:

- **C++ Compiler**: A C++ compiler such as `g++` or Visual Studio.
- **OpenGL**: OpenGL libraries along with GLUT.

### Required Packages for Linux:
```bash
sudo apt-get install freeglut3 freeglut3-dev
sudo apt-get install libglew-dev
```
### For Windows:
You need to download and configure GLUT libraries suitable for your system.

## Compilation and Execution
### Linux:
- Open the terminal and navigate to the project directory.
- Compile and run the project using the following commands:
```bash
g++ solar_system.cpp -o solar_system -lGL -lGLU -lglut
./solar_system
```
### Windows:
- Open the project file in an IDE such as Visual Studio.
- Link the required GLUT and OpenGL libraries.
- Build and run the project.

### Controls
- **Keyboard Keys**:
  - `x`, `X`, `y`, `Y`, `z`, `Z`: Rotate the solar system around different axes.
  - `4`, `6`, `8`, `2`: Move the camera along the x and y axes.
  - `7`, `9`: Move the camera along the z axis.
  - `ESC`: Exit the program.

### File Structure
- **solar_system.cpp**: The source code for the solar system simulation.
- **README.md**: This file.

### Output
When running the simulation, you will see a dynamic solar system in space with a sun, a planet, a moon, and a meteor. The meteor creates an explosion effect upon collision.

![image](https://github.com/user-attachments/assets/7633f0e3-0cc4-46ef-80ee-bd19f3500765)
