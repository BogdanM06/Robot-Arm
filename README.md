# Robot Arm

## Overview

This project uses a 5-axis robotic arm to physically solve the Towers of Hanoi puzzle.

The robot arm was programmed in C to control five Dynamixel AX-12A servo motors. The program determines the required sequence of moves and coordinates the robot's movement to pick up, move, and place the disks between the three towers.

## Features

- Solves the Towers of Hanoi puzzle automatically
- Controls five Dynamixel AX-12A servo motors
- Coordinates multiple motors to perform compound movements
- Uses the robot's gripper to pick up and release disks
- Communicates with the motors using UART serial communication
- Executes the solution using the minimum number of moves

## Hardware

- 5 × Dynamixel AX-12A servo motors
- Robotic arm
- Three Towers of Hanoi blocks
- Disks used for the puzzle
- Controller with UART communication

### Motor Configuration

| Motor | Function |
|-------|----------|
| Motor 1 | Rotates the arm between towers |
| Motor 2 | Controls the first arm joint |
| Motor 3 | Controls the second arm joint |
| Motor 4 | Controls the vertical position |
| Motor 5 | Controls the gripper |

## Software

- C
- UART serial communication
- Dynamixel AX-12A motor control

## How It Works

The program first calculates the sequence of moves required to solve the Towers of Hanoi problem.

For each move, the robot:

1. Moves to the source tower.
2. Positions the arm above the disk.
3. Closes the gripper to pick up the disk.
4. Moves to the destination tower.
5. Positions the disk above the tower.
6. Opens the gripper to release the disk.
7. Returns to a suitable position before performing the next move.

The Towers of Hanoi solution follows the standard recursive algorithm, requiring:

`2^n - 1`

moves to solve a puzzle containing `n` disks.

## Control

The robotic arm is controlled by sending commands to the Dynamixel motors through UART communication.

Different motor positions are combined to create the movements required to:

- Reach each tower
- Pick up disks
- Move disks between towers
- Release disks accurately
