# Battle Simulator

The Battle Simulator is a simple C program that simulates a battle between two sides. Each side consists of a group of soldiers, and engagements occur between these soldiers. Each soldier has a specified level of health and strength.

## How it Works

The program reads commands from a file named `commands.txt` and processes them. The commands include adding soldiers, conducting battles, calling for reinforcements, and executing critical strikes.

## Commands

- **A [side] [soldier_data]:** Adds soldiers to a specific side. `[side]` can be 1 or 2, and `[soldier_data]` contains the health and strength levels of each soldier. Each soldier's data is separated by semicolons.
  Example: `A 1 80,70;50,60;`

- **F:** Advances the battle. During a battle, a clash occurs between the soldiers of both sides.

- **R [side]:** Calls for a random reinforcement to a specific side. `[side]` can be 1 or 2.
  Example: `R 2`

- **C:** Executes a critical strike. The critical strike eliminates a random soldier from the targeted side.

## Sample Command File (`commands.txt`)

```
A 1 80,70;50,60;
A 2 90,80;70,50;
F
R 1
F
C
F
```

This file initially adds soldiers to both sides, then initiates the battle, adds reinforcements to one side, executes a critical strike, and finally concludes the battle.

## Customization

You can customize the simulation by editing the `commands.txt` file to change the sequence of events or adjust the initial setup of soldiers and their attributes.

## Contributors

- https://github.com/burak-albayrak

Feel free to contribute to this project by forking it and submitting pull requests!
