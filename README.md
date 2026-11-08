# Hotel Management System

**C++ · Console application · File persistence**

A first-year problem-solving course project for managing hotel room inventory and reservations. It demonstrates structs, enums, arrays, functions, file handling, and a menu-driven interface.

## Features

- Add and delete rooms in an inventory of up to 100 rooms
- Book rooms and record arrival and departure dates
- Check guests in and out
- Calculate bills from the stay length, bed count, and bed type
- Save and reload inventory through local text files
- Protect inventory actions with a simple demonstration password

## Build and run

Use a C++11-capable compiler or newer. For GCC:

```bash
g++ -std=c++11 -Wall -Wextra src/hotel_management.cpp -o hotel-management
./hotel-management
```

On Windows, run `hotel-management.exe`. Alternatively, create a Visual Studio C++ console project and add `src/hotel_management.cpp`.

## First run

1. Choose **Inventory Task** and enter the demonstration password `1234`.
2. Add a room with a unique positive room number, 1–3 beds, and a bed type.
3. Save the inventory, then return to **Hotel Reservations** to make a booking.
4. Enter dates as day, month, and full year. Departure must follow arrival.
5. Save the inventory again after reservation changes if you want to retain them.

The program creates `INVENTORY.txt`, `CUURENT.txt` (original spelling retained), and `PASSWORD.txt` in its working directory. Missing-file messages on an initial run are expected.

## Portfolio preparation

The publication copy fixes the month index in stay calculations, an assignment in the bed-count condition, invalid room lookup access, duplicate room numbers, invalid booking dates, and an unchecked loaded room count. A small platform wrapper allows the same source to use standard sleeping on non-Windows systems.

## Limitations

This is an educational console application. Passwords are stored as plain text, saving is manual, and general nonnumeric input recovery remains limited. Use sample data. The original executable and archive are omitted; build from the source.

## Validation

Compiled and checked with Visual C++ 2022. The checks cover calendar boundaries, leap years, billing, duplicate and invalid rooms, booking dates, check-in/check-out, and a save/load round trip. The check source is in `tests/hotel_checks.cpp`.

With CMake installed, run:

```bash
cmake -S . -B build
cmake --build build --config Debug
ctest --test-dir build -C Debug --output-on-failure
```

## Author and context

Ramy Slait · First-year problem-solving coursework. The supplied source is preserved in structure, with the focused corrections described above.
