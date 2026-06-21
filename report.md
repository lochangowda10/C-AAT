# PROJECT REPORT

**Course:** C Programming (AAT)
**Project Title:** Smart Parking Management System
**Student Name:** Lochan Gowda

---

## 1. ABSTRACT
As urban infrastructure expands, the management of parking facilities becomes a critical bottleneck. Traditional manual tracking of parking slots is error-prone, inefficient, and lacks proper data persistence. This project presents the "Smart Parking Management System," a robust, console-based application developed entirely in the C programming language. The system aims to automate the allocation of parking spaces, track real-time occupancy, calculate time-based parking fees, and ensure data persistence across system reboots. By heavily utilizing core C concepts such as dynamic memory allocation, pointers, structures, and file I/O operations, this project serves as both a practical utility and a comprehensive demonstration of structured programming principles.

---

## 2. INTRODUCTION
### 2.1 Background
Shopping malls and commercial complexes experience high volumes of vehicular traffic. Managing this traffic requires a system that can quickly allocate available parking spots to incoming vehicles and accurately calculate fees upon exit. 

### 2.2 Problem Statement
"A shopping mall wants to automate parking allocation. Develop a C application that tracks parking slot availability, allocates spaces, and generates occupancy statistics."

### 2.3 Proposed Solution
The proposed solution is a modular C application that uses an array of structures to represent the parking lot. To ensure scalability, the size of this lot is not hardcoded; instead, the user dictates the capacity at runtime, and the system dynamically allocates the necessary memory. 

---

## 3. OBJECTIVES
1.  **Automate Space Allocation:** Automatically find and assign the lowest available parking slot to an incoming vehicle.
2.  **Time-Based Ticketing:** Record the exact entry time of a vehicle using the `<time.h>` library and calculate fees dynamically upon exit.
3.  **State Persistence:** Utilize Binary File I/O to save the state of the parking lot, ensuring recovery after a crash or shutdown.
4.  **Robust Input Handling:** Prevent application crashes caused by invalid user inputs (e.g., entering characters instead of integers).
5.  **Syllabus Integration:** Actively demonstrate all 5 modules of the C programming syllabus.

---

## 4. SYSTEM ARCHITECTURE
The system follows a modular architecture, splitting responsibilities across different files to adhere to the principle of separate compilation.

*   **`parking.h`**: The header file. Contains all data structure definitions (`struct`, `enum`) and function prototypes.
*   **`parking.c`**: The implementation file. Contains the business logic (finding a slot, calculating fees, file writing/reading).
*   **`main.c`**: The presentation layer. Contains the `main()` function, dynamic memory allocation, and the interactive menu loop.

---

## 5. THEORETICAL BACKGROUND (SYLLABUS MAPPING)
This project meticulously implements concepts from the C programming syllabus.

### 5.1 Module 1: Overview of C and Console I/O
The project uses `printf` and `scanf` for all user interactions. A custom function `clear_input_buffer()` is implemented to safely flush the standard input stream, protecting the `scanf` calls from buffer overflow and infinite loops caused by bad data.

### 5.2 Module 2: Statements
*   **Iteration Statements:** A continuous `while(1)` loop drives the main menu, keeping the program alive until the user explicitly chooses to exit. `for` loops are used extensively in `parking.c` to iterate over the parking slots.
*   **Selection Statements:** A `switch` statement handles the user's menu choice, providing a clean execution path for Park, Remove, Stats, and Exit operations. `if-else` blocks handle internal logic checks.

### 5.3 Module 3: Arrays, Strings, and Pointers
*   **Strings:** Vehicle license plates are stored as character arrays (`char license_plate[20]`). The `<string.h>` library's `strcpy` function is used to safely copy string data.
*   **Pointers:** Pointers are the backbone of this project. Instead of passing massive arrays by value (which duplicates memory), the dynamically allocated array is passed by reference (using a pointer) to all functions in `parking.c`.

### 5.4 Module 4: Functions and Dynamic Allocation
*   **Dynamic Allocation:** The `<stdlib.h>` library is used. `malloc(capacity * sizeof(ParkingSlot))` dynamically provisions memory from the heap based on user input. `free()` is strictly called before exit to prevent memory leaks.
*   **Modular Functions:** Code is broken into cohesive, single-purpose functions like `initialize_lot`, `park_vehicle`, and `remove_vehicle`.

### 5.5 Module 5: Structures, Enums, and Typedefs
*   **Structures:** Complex data types are modeled using `struct`. The system features nested structures, where a `Vehicle` struct is contained within a `ParkingSlot` struct.
*   **Enumerations:** `enum SlotStatus { FREE, OCCUPIED }` is used to increase code readability and enforce strict states.
*   **Typedef:** The `typedef` keyword aliases the structures, preventing the need to write `struct Vehicle` repeatedly.

---

## 6. DATA STRUCTURES
The core of the system relies on the following custom data types defined in `parking.h`:

```c
// Defines the state of a slot
typedef enum {
    FREE,
    OCCUPIED
} SlotStatus;

// Defines a Vehicle
typedef struct {
    char license_plate[20];
    time_t entry_time;
} Vehicle;

// Defines a single Parking Slot
typedef struct {
    int slot_number;
    SlotStatus status;
    Vehicle parked_vehicle;
} ParkingSlot;
```
The entire parking lot is an array of `ParkingSlot` elements, manipulated via a pointer (`ParkingSlot *lot`).

---

## 7. ALGORITHMS

### 7.1 Initialization & Loading Algorithm
1.  START
2.  Prompt user for `capacity`.
3.  Allocate memory: `lot = malloc(capacity * sizeof(ParkingSlot))`.
4.  If memory allocation fails, print error and EXIT.
5.  Attempt to open `parking_data.dat` in binary read mode (`rb`).
6.  If file exists, read data into `lot` array.
7.  If file does not exist, iterate from 0 to `capacity-1` setting `status = FREE`.
8.  END

### 7.2 Parking Allocation Algorithm
1.  START
2.  Receive `plate` string from user.
3.  Iterate `i` from 0 to `capacity - 1`.
4.  If `lot[i].status == FREE`:
    1.  Set `lot[i].status = OCCUPIED`.
    2.  Copy `plate` into `lot[i].parked_vehicle.license_plate`.
    3.  Set `lot[i].parked_vehicle.entry_time = current_time()`.
    4.  Print Success.
    5.  Return Success.
5.  If loop finishes, Print "Lot is Full".
6.  Return Failure.
7.  END

### 7.3 Vehicle Removal & Ticketing Algorithm
1.  START
2.  Receive `slot_number` from user.
3.  Validate: Is `slot_number` between 1 and `capacity`? If no, Print Error and Return.
4.  Calculate `index = slot_number - 1`.
5.  If `lot[index].status == OCCUPIED`:
    1.  Get `current_time`.
    2.  Calculate `seconds_parked = current_time - lot[index].parked_vehicle.entry_time`.
    3.  Calculate `fee = Base_Fee + (seconds_parked * Rate)`.
    4.  Print Receipt (Plate, Time, Fee).
    5.  Set `lot[index].status = FREE`.
6.  Else, Print "Slot already empty".
7.  END

---

## 8. EXPECTED I/O AND TESTING

### 8.1 Starting the Application
```text
=========================================
   Welcome to Smart Parking Management   
=========================================
Enter the total capacity of the parking lot: 50
=> Starting with a fresh, empty parking lot.
```

### 8.2 Parking a Vehicle
```text
--- Main Menu ---
1. Park a Vehicle
2. Remove a Vehicle
3. View Statistics
4. Exit
Enter your choice: 1
Enter License Plate: KA-01-AB-1234

=> Vehicle KA-01-AB-1234 parked successfully in Slot 1.
```

### 8.3 Generating Statistics
```text
Enter your choice: 3

--- Parking Lot Statistics ---
Total Capacity: 50
Slot 01: [OCCUPIED] - Plate: KA-01-AB-1234
Slot 02: [  FREE  ]
Slot 03: [  FREE  ]
...
------------------------------
Total Occupied: 1
Total Free:     49
------------------------------
```

### 8.4 Removing a Vehicle
```text
Enter your choice: 2
Enter Slot Number to remove vehicle from: 1

=> Vehicle KA-01-AB-1234 is leaving Slot 1.
=> Time parked: 120 units.
=> Total Fee: $245.00
```

---

## 9. ADVANTAGES AND LIMITATIONS

### 9.1 Advantages
*   **Highly Scalable:** The use of `malloc` ensures the program can handle a parking lot of 10 cars or 10,000 cars without recompilation.
*   **Resilient:** The implementation of Binary File I/O ensures that a sudden power loss does not result in the loss of billing data or current occupancy states.
*   **Modular:** The separation of concerns between `main.c` and `parking.c` makes the codebase easy to maintain, debug, and expand.

### 9.2 Limitations
*   **No Database:** While file I/O works for small scales, a real enterprise system would require a SQL database for concurrent access and querying.
*   **Single Vehicle Type:** The current struct design assumes all vehicles take up one slot and pay the same rate.

---

## 10. FUTURE ENHANCEMENTS
1.  **Vehicle Categories:** Expand the `Vehicle` struct to include a `type` enum (e.g., TWO_WHEELER, FOUR_WHEELER) and apply different pricing models.
2.  **VIP/Reserved Slots:** Add logic to reserve certain slots for specific license plates.
3.  **Search Functionality:** Implement a search algorithm to locate a car's slot based on its license plate using string matching (`strcmp`).

---

## 11. CONCLUSION
The Smart Parking Management System project successfully demonstrates the application of C programming concepts to solve a real-world infrastructure problem. By fulfilling all core requirements—tracking availability, allocating spaces, and generating statistics—the project achieves its primary goal. Furthermore, the inclusion of dynamic memory allocation and file-based state persistence elevates the application from a simple academic exercise to a robust, fault-tolerant software prototype.

---

## 12. APPENDIX: SOURCE CODE

### 12.1 `parking.h`
```c
#ifndef PARKING_H
#define PARKING_H

#include <time.h> 

typedef enum { FREE, OCCUPIED } SlotStatus;

typedef struct {
    char license_plate[20]; 
    time_t entry_time;      
} Vehicle;

typedef struct {
    int slot_number;        
    SlotStatus status;      
    Vehicle parked_vehicle; 
} ParkingSlot;

void initialize_lot(ParkingSlot *lot, int capacity);
int park_vehicle(ParkingSlot *lot, int capacity, const char *plate);
void remove_vehicle(ParkingSlot *lot, int capacity, int slot_num);
void generate_statistics(const ParkingSlot *lot, int capacity);
void save_data(const ParkingSlot *lot, int capacity);
int load_data(ParkingSlot *lot, int capacity);

#endif 
```

### 12.2 `parking.c`
```c
#include <stdio.h>   
#include <string.h>  
#include <time.h>    
#include "parking.h" 

void initialize_lot(ParkingSlot *lot, int capacity) {
    for (int i = 0; i < capacity; i++) {
        lot[i].slot_number = i + 1; 
        lot[i].status = FREE;       
    }
}

int park_vehicle(ParkingSlot *lot, int capacity, const char *plate) {
    for (int i = 0; i < capacity; i++) {
        if (lot[i].status == FREE) {
            lot[i].status = OCCUPIED; 
            strcpy(lot[i].parked_vehicle.license_plate, plate);
            lot[i].parked_vehicle.entry_time = time(NULL); 
            printf("\n=> Vehicle %s parked successfully in Slot %d.\n", plate, lot[i].slot_number);
            return 1; 
        }
    }
    printf("\n=> Sorry, the parking lot is completely FULL!\n");
    return 0; 
}

void remove_vehicle(ParkingSlot *lot, int capacity, int slot_num) {
    if (slot_num < 1 || slot_num > capacity) {
        printf("\n=> Invalid slot number!\n");
        return; 
    }

    int index = slot_num - 1;

    if (lot[index].status == OCCUPIED) {
        time_t exit_time = time(NULL); 
        double seconds_parked = difftime(exit_time, lot[index].parked_vehicle.entry_time);
        double fee = 5.0 + (seconds_parked * 2.0);

        printf("\n=> Vehicle %s is leaving Slot %d.\n", lot[index].parked_vehicle.license_plate, slot_num);
        printf("=> Time parked: %.0f units.\n", seconds_parked);
        printf("=> Total Fee: $%.2f\n", fee);

        lot[index].status = FREE;
    } else {
        printf("\n=> Slot %d is already empty!\n", slot_num);
    }
}

void generate_statistics(const ParkingSlot *lot, int capacity) {
    int occupied_count = 0;
    
    printf("\n--- Parking Lot Statistics ---\n");
    printf("Total Capacity: %d\n", capacity);

    for (int i = 0; i < capacity; i++) {
        if (lot[i].status == OCCUPIED) {
            occupied_count++;
            printf("Slot %02d: [OCCUPIED] - Plate: %s\n", lot[i].slot_number, lot[i].parked_vehicle.license_plate);
        } else {
            printf("Slot %02d: [  FREE  ]\n", lot[i].slot_number);
        }
    }
    
    printf("------------------------------\n");
    printf("Total Occupied: %d\n", occupied_count);
    printf("Total Free:     %d\n", capacity - occupied_count);
    printf("------------------------------\n");
}

void save_data(const ParkingSlot *lot, int capacity) {
    FILE *file = fopen("parking_data.dat", "wb");
    if (file == NULL) return;
    fwrite(lot, sizeof(ParkingSlot), capacity, file);
    fclose(file); 
}

int load_data(ParkingSlot *lot, int capacity) {
    FILE *file = fopen("parking_data.dat", "rb");
    if (file == NULL) return 0; 
    fread(lot, sizeof(ParkingSlot), capacity, file);
    fclose(file);
    return 1; 
}
```

### 12.3 `main.c`
```c
#include <stdio.h>
#include <stdlib.h> 
#include "parking.h"

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

int main() {
    int capacity;
    int choice;
    ParkingSlot *lot = NULL; 

    printf("=========================================\n");
    printf("   Welcome to Smart Parking Management   \n");
    printf("=========================================\n");

    printf("Enter the total capacity of the parking lot: ");
    while (scanf("%d", &capacity) != 1 || capacity <= 0) {
        printf("Invalid input. Please enter a positive number: ");
        clear_input_buffer(); 
    }
    clear_input_buffer(); 

    lot = (ParkingSlot *)malloc(capacity * sizeof(ParkingSlot));
    
    if (lot == NULL) {
        printf("CRITICAL ERROR: Memory allocation failed!\n");
        return 1; 
    }

    if (load_data(lot, capacity)) {
        printf("=> Previous parking data loaded successfully!\n");
    } else {
        printf("=> Starting with a fresh, empty parking lot.\n");
        initialize_lot(lot, capacity);
    }

    while (1) {
        printf("\n--- Main Menu ---\n");
        printf("1. Park a Vehicle\n");
        printf("2. Remove a Vehicle\n");
        printf("3. View Statistics\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("\n=> Invalid input! Please enter a number.\n");
            clear_input_buffer();
            continue; 
        }
        clear_input_buffer();

        switch (choice) {
            case 1: {
                char plate[20];
                printf("Enter License Plate: ");
                scanf("%19[^\n]", plate);
                clear_input_buffer();
                park_vehicle(lot, capacity, plate);
                save_data(lot, capacity); 
                break;
            }
            case 2: {
                int slot;
                printf("Enter Slot Number to remove vehicle from: ");
                if (scanf("%d", &slot) == 1) {
                    remove_vehicle(lot, capacity, slot);
                    save_data(lot, capacity); 
                } else {
                    printf("Invalid slot number format.\n");
                }
                clear_input_buffer();
                break;
            }
            case 3:
                generate_statistics(lot, capacity);
                break;
            case 4:
                printf("\n=> Saving data and shutting down. Goodbye!\n");
                free(lot); 
                return 0; 
            default:
                printf("\n=> Invalid choice! Please select 1-4.\n");
        }
    }

    return 0; 
}
```
