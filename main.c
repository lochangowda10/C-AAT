#include <stdio.h>
#include <stdlib.h> // Required for malloc and free (Module 4: Dynamic Allocation)
#include "parking.h"

// Clears the input buffer to prevent infinite loops on bad input
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

// SYLLABUS: MODULE 4 (main function and return statement)
int main() {
    int capacity;
    int choice;
    ParkingSlot *lot = NULL; // Pointer to hold our dynamically allocated array

    printf("=========================================\n");
    printf("   Welcome to Smart Parking Management   \n");
    printf("=========================================\n");

    // --- SYLLABUS: MODULE 4 (Dynamic Allocation) ---
    // Instead of hardcoding "ParkingSlot lot[100];", we ask the user how big the lot is.
    // This makes the program flexible!
    printf("Enter the total capacity of the parking lot: ");
    while (scanf("%d", &capacity) != 1 || capacity <= 0) {
        printf("Invalid input. Please enter a positive number: ");
        clear_input_buffer(); // Clear the bad characters from the input stream
    }
    clear_input_buffer(); // Clear the newline character left by scanf

    // malloc (Memory Allocation) asks the OS for a specific amount of bytes.
    // We need space for 'capacity' number of ParkingSlots.
    lot = (ParkingSlot *)malloc(capacity * sizeof(ParkingSlot));
    
    if (lot == NULL) {
        printf("CRITICAL ERROR: Memory allocation failed!\n");
        return 1; // Return non-zero to indicate an error to the Operating System
    }

    // Try to load existing data from file. If it fails (first run), initialize a new lot.
    if (load_data(lot, capacity)) {
        printf("=> Previous parking data loaded successfully!\n");
    } else {
        printf("=> Starting with a fresh, empty parking lot.\n");
        initialize_lot(lot, capacity);
    }

    // --- SYLLABUS: MODULE 2 (Iteration Statements - 'while' loop) ---
    // This loop keeps the program running until the user chooses to exit.
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
            continue; // Skip the rest of the loop and start over
        }
        clear_input_buffer();

        // --- SYLLABUS: MODULE 2 (Selection Statements - 'switch') ---
        switch (choice) {
            case 1: {
                char plate[20];
                printf("Enter License Plate: ");
                // Read a string with spaces using format specifier [^\n]
                scanf("%19[^\n]", plate);
                clear_input_buffer();
                park_vehicle(lot, capacity, plate);
                save_data(lot, capacity); // Save state after a change
                break;
            }
            case 2: {
                int slot;
                printf("Enter Slot Number to remove vehicle from: ");
                if (scanf("%d", &slot) == 1) {
                    remove_vehicle(lot, capacity, slot);
                    save_data(lot, capacity); // Save state after a change
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
                // --- SYLLABUS: MODULE 4 (Dynamic Allocation - free) ---
                // We must give the memory back to the Operating System when we are done!
                free(lot); 
                return 0; // Return 0 indicates the program ran successfully
            default:
                printf("\n=> Invalid choice! Please select 1-4.\n");
        }
    }

    return 0; // The code should never reach here because of the 'while(1)' loop
}
