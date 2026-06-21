#include <stdio.h>   // Standard I/O library for printf, scanf
#include <string.h>  // String library for strcpy (copying strings)
#include <time.h>    // Time library for tracking parking duration
#include "parking.h" // We include our own header file (Separate Compilation - Module 1)

// --- SYLLABUS: MODULE 4 (Functions and passing arguments) ---
// This function takes a pointer to our array of ParkingSlots and the total capacity.
void initialize_lot(ParkingSlot *lot, int capacity) {
    // SYLLABUS: MODULE 2 (Iteration Statements - 'for' loop)
    // We loop through every slot from 0 up to capacity-1.
    for (int i = 0; i < capacity; i++) {
        lot[i].slot_number = i + 1; // Humans count from 1, arrays count from 0
        lot[i].status = FREE;       // Set every slot to the FREE enum state
    }
}

// Parks a vehicle. Returns 1 on success, 0 if full.
int park_vehicle(ParkingSlot *lot, int capacity, const char *plate) {
    for (int i = 0; i < capacity; i++) {
        // SYLLABUS: MODULE 2 (Selection Statements - 'if')
        if (lot[i].status == FREE) {
            // Found a free slot!
            lot[i].status = OCCUPIED; // Mark as occupied
            
            // SYLLABUS: MODULE 3 (Strings)
            // We cannot do lot[i].parked_vehicle.license_plate = plate;
            // In C, strings are arrays, so we must use strcpy (string copy).
            strcpy(lot[i].parked_vehicle.license_plate, plate);
            
            // Record the current time. 'time(NULL)' returns seconds since Jan 1, 1970.
            lot[i].parked_vehicle.entry_time = time(NULL); 
            
            printf("\n=> Vehicle %s parked successfully in Slot %d.\n", plate, lot[i].slot_number);
            return 1; // Success
        }
    }
    // If the loop finishes and we never hit 'return 1', the lot is full.
    printf("\n=> Sorry, the parking lot is completely FULL!\n");
    return 0; // Failure
}

// Removes a vehicle and calculates a basic fee based on time spent.
void remove_vehicle(ParkingSlot *lot, int capacity, int slot_num) {
    // Input validation: ensure the slot exists
    if (slot_num < 1 || slot_num > capacity) {
        printf("\n=> Invalid slot number!\n");
        return; // Exit the function early
    }

    // Convert human slot number (1 to N) to array index (0 to N-1)
    int index = slot_num - 1;

    // Check if the slot is actually occupied before trying to remove a car
    if (lot[index].status == OCCUPIED) {
        time_t exit_time = time(NULL); // Get current time
        // Calculate the difference in seconds
        double seconds_parked = difftime(exit_time, lot[index].parked_vehicle.entry_time);
        
        // Let's pretend 1 second = 1 minute for the sake of a quick demonstration.
        // Fee calculation: Base fee $5 + $2 for every minute (second) parked.
        double fee = 5.0 + (seconds_parked * 2.0);

        printf("\n=> Vehicle %s is leaving Slot %d.\n", lot[index].parked_vehicle.license_plate, slot_num);
        printf("=> Time parked: %.0f units.\n", seconds_parked);
        printf("=> Total Fee: $%.2f\n", fee);

        // Reset the slot status to FREE
        lot[index].status = FREE;
    } else {
        printf("\n=> Slot %d is already empty!\n", slot_num);
    }
}

// Prints a summary of the parking lot
void generate_statistics(const ParkingSlot *lot, int capacity) {
    int occupied_count = 0;
    
    printf("\n--- Parking Lot Statistics ---\n");
    printf("Total Capacity: %d\n", capacity);

    for (int i = 0; i < capacity; i++) {
        if (lot[i].status == OCCUPIED) {
            occupied_count++;
            // Print details of occupied slots
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

// --- PROFESSIONAL FEATURE: File Persistence ---
// Saves the 'lot' array to a binary file named 'parking_data.dat'
void save_data(const ParkingSlot *lot, int capacity) {
    // Open file for writing in binary mode ("wb")
    FILE *file = fopen("parking_data.dat", "wb");
    if (file == NULL) {
        printf("Error: Could not save data to file.\n");
        return;
    }
    
    // Write the entire array of structs directly to the file in one go
    fwrite(lot, sizeof(ParkingSlot), capacity, file);
    fclose(file); // Always close files when done
}

// Loads the 'lot' array from the binary file.
int load_data(ParkingSlot *lot, int capacity) {
    // Open file for reading in binary mode ("rb")
    FILE *file = fopen("parking_data.dat", "rb");
    if (file == NULL) {
        // File doesn't exist yet (first time running), this is fine.
        return 0; 
    }
    
    // Read the data back into the array
    fread(lot, sizeof(ParkingSlot), capacity, file);
    fclose(file);
    return 1; // Success
}
