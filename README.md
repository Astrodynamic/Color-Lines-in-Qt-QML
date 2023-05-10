# Color Lines in Qt/QML

Color Lines (Russian: "Цветные линии", abbreviated as "Lines") is a logical computer game developed by Oleg D'yomin, Gennady Denisov, and Igor Ivkin, and published by the Russian company Gamos in 1992.

![promo](img/promo.gif)

## Contents

- [Color Lines in Qt/QML](#color-lines-in-qtqml)
  - [Contents](#contents)
  - [Gameplay](#gameplay)
  - [Build Instructions](#build-instructions)
  - [Dependencies](#dependencies)
  - [Examples](#examples)
  - [License](#license)

## Gameplay

The game is played on a square field consisting of 9x9 cells and involves a series of moves. In each move, the computer randomly places three balls of different colors in random cells. Then the player makes a move by moving any ball to another free cell, provided that there is a non-diagonal path between the initial and final cells consisting of free cells. If, after the movement, five or more balls of the same color align in a line horizontally, vertically, or diagonally, those balls disappear, and the player is given the opportunity to make another ball move. If no line is formed after the movement, the turn ends, and a new one begins with the appearance of new balls. If a line is formed when new balls appear, it disappears, and the player earns points, but no additional ball movement is allowed. The game continues until the entire field is filled with balls and the player is unable to make a move.

The goal of the game is to achieve the highest score possible. The scoring system is designed in such a way that the player earns significantly more points for removing more than five balls in a single move. During the game, three colors of balls that will appear on the field in the next move are displayed on the screen.

## Build Instructions

To build and run the project, follow these steps:

1. Make sure you have CMake version 3.15 or higher installed.
2. Clone the repository.
3. Open a terminal and navigate to the project directory.
4. Run the following commands:

```shell
cmake -S . -B ./build
cmake --build ./build
```

These commands will generate the necessary build files and compile the project.

## Dependencies

The project requires the following dependencies:

- Qt6 (version 6.2 or higher) with the following components:
  - Quick
  - Sql

Make sure you have the dependencies installed before building the project.

## Examples

The project includes some example code to help you get started. You can find the examples in the `examples` directory.

## License

This project is licensed under the [MIT License](LICENSE).