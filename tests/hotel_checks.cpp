#include <cassert>
#include <sstream>
#define main coursework_main
#include "../src/hotel_management.cpp"
#undef main

int main() {
    int jan31[] = {31,1,2024}, feb1[] = {1,2,2024};
    int feb28[] = {28,2,2024}, mar1[] = {1,3,2024};
    int dec31[] = {31,12,2024}, jan1[] = {1,1,2025};
    assert(countNoOfDays(jan31, feb1) == 1);
    assert(countNoOfDays(feb28, mar1) == 2);
    assert(countNoOfDays(dec31, jan1) == 1);
    room sample; sample.room_number = 101; sample.beds = 3; sample.bedtype = king;
    sample.start[0]=1; sample.start[1]=1; sample.start[2]=2024;
    sample.end[0]=3; sample.end[1]=1; sample.end[2]=2024;
    assert(CALCULATE_BILL(sample) == 1200);
    assert(sample.beds == 3);
    assert(ADD_ROOM(sample));
    assert(!ADD_ROOM(sample));
    assert(SEARCH_INDEX(999) == -1);
    room invalid; invalid.room_number=102; invalid.beds=4;
    assert(!ADD_ROOM(invalid));
    room booking; booking.room_number=103; booking.beds=1;
    std::istringstream invalidDates("31 2 2024 2 3 2024");
    auto originalInput=std::cin.rdbuf(invalidDates.rdbuf());
    assert(!BOOKING(booking));
    assert(booking.bookingid == -1 && booking.start[0] == 0);
    std::istringstream validDates("28 2 2024 1 3 2024");
    std::cin.rdbuf(validDates.rdbuf());
    assert(BOOKING(booking));
    assert(CHECK_IN(booking));
    assert(CHECK_OUT(booking));
    std::cin.rdbuf(originalInput);
    assert(SAVE_INVENTORY());
    currentRoom=0; rooms[0]=room();
    LOAD_ROOM();
    assert(currentRoom==1 && rooms[0].room_number==101 && rooms[0].beds==3);
    std::cout << "\nHotel checks passed: calendar boundaries, leap year, billing, duplicate and invalid rooms, booking validation, check-in/out, persistence.\n";
}
