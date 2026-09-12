# Plumbing Inventory

Allows creation and manipulation of an inventory, for plumbers.

Personal project. Create or modify an inventory (.txt file).
Inventory format: measurement, piece, count
Modifications available:
1. Print Inventory
2. add to count
3. subtract from count
4. append new entry
5. remove entry
6. sort inventory (sorted by measurement size)
7. get count from inventory
8. set count in inventory
NOTE: Requires c++17, multiple files required to compile due to header (command listed below)

## Prerequisites
Unix Terminal or other C++ compiler required.

## Installation

Get your development environment running by executing these steps:

```bash
Open Terminal.
On Mac: cmd + space to open spotlight and type terminal, press enter to open.
On Windows: windows key + R, type wt and enter.
```

## Usage

How to execute program:

```bash
Once terminal is open...
Navigate to where folder is stored using the "cd" command, ex) "cd Plumbing\ Inventory".
Once in the folder Plumbing Inventory, compile using "g++ inventory.cpp operations.cpp -std=c++17" and any other flags you'd like.
Run the file using the command "./a.out" to create an executable.
Options will be listed, enter option, enter required information, then choose whether or not to continue.
Tips:
Enter name of .txt file only, not .txt extension. Ex) "sample", NOT "sample.txt"
Open .txt file with "open" command in terminal. Ex) "open sample.txt"
```

## AI
AI was used for format of implementing and iterating maps.
AI was also used to format the setup and manipulation fstream reader and writer.

## Program is free use
