# 🎯 CLI Guess the Number

![Language](https://img.shields.io/badge/Language-C-blue.svg)
![Build](https://img.shields.io/badge/Build-Make-orange.svg)
![Environment](https://img.shields.io/badge/Environment-Linux%20%2F%20CLI-lightgrey.svg)

A modular, command-line "Guess the Number" game written entirely in C. 

Unlike a simple single-file script, this project is built with a focus on **modular software architecture**. It separates game logic from the main execution loop, utilizes custom header files with include guards, and manages state using enumerations—all tied together with a custom `Makefile` for streamlined compilation.

## ✨ Features

* **Modular Architecture:** Logic is cleanly separated across `main.c`, `random.c`, and `random.h`.
* **Input Tracking:** Records and displays your previous guesses each round.
* **Repetition Prevention:** Automatically detects if you've already guessed a specific number and warns you without costing a round.
* **Automated Build System:** Fully managed via a Makefile that handles object file generation in a dedicated `obj/` directory.

## 📂 Project Structure

```text
.
├── Makefile       # Automated build instructions
├── main.c         # Main execution loop and UI
├── random.c       # Core logic and RNG functions
└── random.h       # Function prototypes and Enums
```

## Game preview
```
--- Round 1 ---
Number guessed:  
Enter your guess: 75
	TOO LOW!

--- Round 2 ---
Number guessed: 75 95
Enter your guess: 95    
	TOO HIGH!

--- Round 3 ---
Number guessed: 75 95
Enter your guess: 93

	--- YOU WIN! ---
The correct number was: 93
```
