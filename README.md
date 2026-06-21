<div align="center">

# 🚗 Smart Parking Management System

[![C Language](https://img.shields.io/badge/Language-C-blue.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux%20%7C%20macOS-lightgrey.svg)]()
[![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)]()

*A lightweight, robust console application to automate parking lot management, allocations, and billing.*

</div>

## 📌 Overview
The Smart Parking Management System replaces manual parking tracking with a fast, automated C program. It handles dynamic lot capacities, persistent data storage, and automated fee calculation based on parking duration.

## ✨ Features
*   **Dynamic Scaling**: Allocate parking lots of any size at runtime using dynamic memory (`malloc`).
*   **Smart Ticketing**: Automatically calculates parking fees based on time spent.
*   **Data Persistence**: System state is saved to a binary file (`parking_data.dat`), preventing data loss.
*   **Modular Architecture**: Clean, scalable code split across headers and implementation files.

## 🚀 Quick Start

### Prerequisites
*   A C compiler (e.g., `gcc`, `clang`, or MSVC)

### Compilation
Open your terminal and run:
```bash
gcc main.c parking.c -o parking
```

### Execution
*   **Windows**: `.\parking.exe`
*   **Mac/Linux**: `./parking`

## 📖 Usage Guide
1.  **Initialize**: On first launch, specify the maximum capacity of your parking lot.
2.  **Park**: Select option 1, enter a license plate, and the system automatically assigns the nearest open slot.
3.  **Leave**: Select option 2, enter the slot number. The system calculates the time parked and generates a bill.
4.  **Monitor**: Select option 3 to view a visual layout of occupied vs. free slots.

---
*Developed as part of the C Programming AAT Project.*
