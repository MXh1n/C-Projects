# Pong: Real-Time Physics in C

A high-performance, fully featured clone of the classic arcade game Pong, written entirely in C using the Raylib framework. This project focuses on manual memory management, real-time multimedia processing (audio/graphics), and vector-based 2D physics.

make run<img width="849" height="530" alt="gameplay" src="https://github.com/user-attachments/assets/167b4604-0990-44bb-b1fe-2ada353af319" />

## Features

* **Dynamic Angular Reflection:** The ball's bounce angle is dynamically calculated based on the exact point of impact on the paddle, rewarding skilled shots (similar to the original Atari hardware logic).
* **Progressive Difficulty:** Implements a scalar acceleration modifier; the ball's velocity increases sequentially after every successful volley.
* **Normalized Vector Movement:** Ensures consistent ball speeds across all diagonal trajectories using precise vector normalization.
* **Audio Streaming & State:** Utilizes Raylib's audio device to stream background MP3 tracks while independently triggering instantaneous `.wav` / `.mp3` sound effects for collisions and scoring.
* **Game State Machine:** Smooth transitions between active gameplay, score events, reset prompts, and a definitive "Game Over" win screen.

## Tech Stack

* **Language:** C (C99)
* **Multimedia Library:** [Raylib](https://www.raylib.com/)
* **Compiler:** GCC (v13.3.0)
* **Build System:** Make

## Controls

* **Player 1 (Left):** `W` (Up) / `S` (Down)
* **Player 2 (Right):** `UP ARROW` (Up) / `DOWN ARROW` (Down)
* **Game Prompts:** `SPACE` (Start / Continue / Reset)

## Compiler Options Explained

To successfully link the game engine with your system hardware, the following flags are used:
* `-lraylib`: Links the core Raylib library.
* `-lGL`: Links OpenGL for hardware-accelerated graphics.
* `-lm`: Links the math library (required for `sqrt` and `pow` in physics).
* `-lpthread`: Enables multi-threading support (required for the background audio stream).
* `-ldl -lrt -lX11`: Standard Linux system libraries for window management and timing.

## Installation and Build

1. **Clone the repository:**
   bash
```
   git clone [https://github.com/MXh1n/C-Projects.git](https://github.com/MXh1n/C-Projects.git)
   cd C-Projects/pong
```
Compile and Run:
    The project includes a Makefile configured for Linux. You can compile and execute immediately with:

 Bash



Manual Compilation:
    If you do not have make installed, use the following GCC command:
    Bash
    
    
    gcc pong.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o pong
    ./pong
    
Folder Structure
    
    
    pong.c: Core application logic, rendering, physics, and state management.

    /audio/: Contains all multimedia assets (.mp3 and .wav).
    
