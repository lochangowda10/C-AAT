# Smart Parking Management System

This is a professional-grade C console application developed to automate parking allocation for a shopping mall. It tracks slot availability, allocates spaces, generates occupancy statistics, and calculates parking fees based on time.

## Features
- **Dynamic Capacity**: You choose how big the parking lot is when you start the program.
- **Ticketing & Billing**: Calculates a fee based on the time a vehicle spends in the lot.
- **Data Persistence**: Saves the state of the parking lot to `parking_data.dat` so you don't lose data when you close the app.
- **Robust Input Handling**: Protects against crashes when the user types text instead of numbers.

## Syllabus Concepts Demonstrated
This project serves as a comprehensive demonstration of core C concepts:
- **Module 1 & 2**: Control flow, iteration (`while`, `for`), selection (`switch`, `if`), and formatted I/O.
- **Module 3**: Arrays and String manipulation (`strcpy`).
- **Module 4**: Modular functions, standard libraries (`<time.h>`), and **Dynamic Memory Allocation** (`malloc`, `free`).
- **Module 5**: Advanced data structures (`struct`), nested structures, `typedef`, `enum`, and passing structure pointers.

## How to Compile and Run

You will need a C compiler (like GCC) installed on your system. 

1. Open your terminal or command prompt.
2. Navigate to the directory containing these files.
3. Compile the code using this command:
   ```bash
   gcc main.c parking.c -o parking
   ```
4. Run the executable:
   - On Windows: `parking.exe`
   - On Mac/Linux: `./parking`

## Usage
Upon starting, enter the desired capacity of the parking lot. The system will then present a menu:
1. **Park a Vehicle**: Enter a license plate to park. The system assigns the first available slot.
2. **Remove a Vehicle**: Enter a slot number to remove a vehicle. The system will display the time parked and the fee.
3. **View Statistics**: See a visual representation of all free and occupied slots.
4. **Exit**: Saves the current state and safely shuts down.
