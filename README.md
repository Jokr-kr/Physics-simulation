# Physics-Simulation

A self-made physics engine and simulation project.

## Project Goals
The purpose of this project is to learn:
- Lower-level programming
- Advanced C++
- Basics of engine creation
- Higher-level math applied to physics simulations

## Design Philosophy
To deepen understanding, this project avoids using most external libraries, including many built-in C++ libraries. The exceptions are:
- <chrono> for timing, as creating a custom timing solution from scratch would require kernel-level programming, which is too complex and time-consuming. <chrono> also ensures cross-platform compatibility.
- <thread> for managing frame rate control in a cross-platform way without platform-specific dependencies.

## Features
- Basic collision detection and resolution for different object types (e.g., circles, squares)
- Adjustable simulation timestep to control simulation speed
- Real-time physics calculations without relying on external physics libraries

## Installation & Usage
Instructions to build and run the simulation will be provided here at a later date.



#nonserious inclusions "be-low"

## Things i have learned during the making of this project:
- "#ifndef/#define/#endif is the conventional way to ensure a file is compiled only once. #pragma once is an alternative but isn't universally supported."
- C++ access levels (public, private, protected) are declared within the class. making classes not inherently private or public, but can have both private and public variables and functions.
- Constructors can have default values inlined. (ExampleConstructor(float foo = 0.0f) : bar(foo) {})
- Operators can be overloaded. did so in vector2D
- Learned about bitwise shifts with << and >> went down a deep rabbithole learning about bits, bitmanipulation and in the end some hexadecimal.
- During bit-rabbithole. learned division takes more cycles to calculate than multiplication in the cpu, keep in mind for possible optimisations later.
- First time coming across constexpr which does calculations at compiletime, making them easier during runtime.
- constexpr can potentially increase compiletime significantly.
- Learned that .hpp files work like interfaces by declaring methods for a .cpp file to implement. However, unlike typical interfaces, .hpp files can also define methods directly, especially for minor ones.
- Conventional cpp way to implement what a hpp class has declared, is to use "ClassName::method(){}
- chat gpt is a good tool to help with typos and grammar in README-files.

### general notes:
- project was started approximatley: 2024-10-07 12:00:00 (timeformat *sigh*) 
- added to github aproximately: 2024-10-25 13:00:00.

