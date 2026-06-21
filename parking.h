#ifndef PARKING_H // Include guard (Module 1): Prevents this file from being included multiple times, which would cause errors.
#define PARKING_H

#include <time.h> // We need this library to use 'time_t' and track when cars park.

// --- SYLLABUS: MODULE 5 (Enumerations) ---
// 'enum' is a user-defined type consisting of a set of named integer constants.
// We use it here to make our code more readable. FREE is automatically 0, OCCUPIED is 1.
typedef enum {
    FREE,
    OCCUPIED
} SlotStatus;

// --- SYLLABUS: MODULE 5 (Structures and typedef) ---
// A 'struct' groups related variables under one name.
// 'typedef' allows us to use 'Vehicle' as a type name, instead of writing 'struct Vehicle' every time.
typedef struct {
    char license_plate[20]; // SYLLABUS: MODULE 3 (Strings/Character Arrays). Stores the car's plate.
    time_t entry_time;      // Stores the exact second the car parked.
} Vehicle;

// Structure representing a single parking spot.
typedef struct {
    int slot_number;        // E.g., Slot 1, Slot 2...
    SlotStatus status;      // Uses the enum above. Is it FREE or OCCUPIED?
    Vehicle parked_vehicle; // SYLLABUS: MODULE 5 (Structures within Structures). 
                            // If occupied, this holds the car's details.
} ParkingSlot;

// --- SYLLABUS: MODULE 4 (Function Prototypes) ---
// These are declarations. They tell the compiler "These functions exist and look like this",
// but the actual code for them is in parking.c.

// Initializes the parking lot (sets all slots to FREE).
void initialize_lot(ParkingSlot *lot, int capacity);

// Parks a vehicle. Returns 1 if successful, 0 if lot is full.
int park_vehicle(ParkingSlot *lot, int capacity, const char *plate);

// Removes a vehicle by slot number and calculates the fee.
void remove_vehicle(ParkingSlot *lot, int capacity, int slot_num);

// Prints how many slots are full and empty.
void generate_statistics(const ParkingSlot *lot, int capacity);

// Saves the parking data to a file so it isn't lost when the program closes.
void save_data(const ParkingSlot *lot, int capacity);

// Loads the parking data from a file when the program starts.
int load_data(ParkingSlot *lot, int capacity);

#endif // PARKING_H
