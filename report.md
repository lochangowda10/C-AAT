# Project Report: Smart Parking Management System

## 1. Introduction
The Smart Parking Management System is a C-based console application designed to automate the parking allocation process for a shopping mall. As modern infrastructure scales, managing parking manually becomes inefficient. This application addresses that problem by tracking slot availability, dynamically allocating spaces to incoming vehicles, generating occupancy statistics, and calculating time-based parking fees.

## 2. Objectives
1. **Automate Allocation**: Replace manual tracking with a robust software system.
2. **Dynamic Scaling**: Allow the system to be configured for any size parking lot using dynamic memory allocation.
3. **Data Persistence**: Ensure parking data is not lost during system reboots or power failures by persisting data to a file.
4. **Demonstrate Proficiency**: Apply core concepts of the C programming language, specifically focusing on structs, pointers, dynamic allocation, and modular design.

## 3. Algorithm and Flowchart (Description)
**Main Flow**:
1. Initialize the system. Ask the user for the total parking capacity.
2. Dynamically allocate memory for the parking lot array.
3. Attempt to load existing data from `parking_data.dat`. If it fails, initialize all slots to `FREE`.
4. Enter an infinite loop displaying the Main Menu (Park, Remove, View Stats, Exit).
5. On Exit, free the allocated memory and terminate.

**Park Vehicle Flow**:
1. Accept license plate.
2. Iterate through the parking lot array.
3. If a slot is `FREE`, mark it `OCCUPIED`, save the plate, record the current system time, print success, and break.
4. If the loop finishes without finding a `FREE` slot, print "Lot is Full".

**Remove Vehicle Flow**:
1. Accept slot number.
2. Validate slot number. If valid, check if the slot is `OCCUPIED`.
3. If `OCCUPIED`, fetch current time. Calculate the difference between current time and entry time.
4. Calculate fee based on the time difference.
5. Mark the slot as `FREE`.

## 4. Implementation Details (Syllabus Concepts)

### 4.1 Modules 1 & 2: Control Flow and I/O
The system heavily utilizes formatted console I/O (`printf`, `scanf`). To ensure the program does not crash on invalid input (e.g., typing letters when a menu number is expected), a custom `clear_input_buffer()` function is implemented using a `while` loop to consume extraneous characters. The main menu is driven by a `switch` statement enclosed within a `while(1)` iteration.

### 4.2 Module 3: Arrays, Strings, and Pointers
The license plate of a vehicle is stored as a Character Array (String) of size 20. When allocating a spot, the standard library function `strcpy` is used. Furthermore, the core data structure of the entire application is an array of structures, manipulated entirely via Pointers passed between functions.

### 4.3 Module 4: Functions and Dynamic Allocation
Instead of a monolithic design, the code is separated into logical functions (`initialize_lot`, `park_vehicle`, etc.). 
Most importantly, the application does not rely on a hardcoded maximum capacity. It uses `malloc` to request exactly enough memory from the operating system based on the user's input at runtime. When the application exits, `free` is called to prevent memory leaks.

### 4.4 Module 5: Advanced Data Structures
The data model is built using `struct` and `typedef`. 
- An `enum` named `SlotStatus` restricts the state of a slot to strictly `FREE` or `OCCUPIED`.
- A `Vehicle` struct holds the string plate and the `time_t` entry time.
- A `ParkingSlot` struct contains an integer ID, the `SlotStatus`, and nests the `Vehicle` struct inside it. This nested structure perfectly models the real-world relationship between a parking spot and the car inside it.

## 5. Conclusion
The Smart Parking Management System successfully meets all requirements of the problem statement. By utilizing advanced C programming paradigms such as dynamic memory allocation and file I/O, the application is not only functional as an academic project but also robust enough to model a real-world software utility.
