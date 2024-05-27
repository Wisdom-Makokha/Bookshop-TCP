#include "definitions.h"
#include "net_definitions.h"

// function to print an entry
void printEntry(book_entry *entry)
{
    int serialPrecision = 6;   // precision size for serial
    int titlePrecision = 32;   // precision size for title
    int authorPrecision = 24;  // precision size for author
    int isbnPrecision = 15;    // precision size for isbn no
    int publishPrecision = 24; // precision size for publisher

    std::cout << std::setw(serialPrecision) << std::left << entry->serialNo;
    std::cout << std::setw(titlePrecision) << std::left << entry->title;
    std::cout << std::setw(authorPrecision) << std::left << entry->author;
    std::cout << std::setw(isbnPrecision) << std::left << entry->isbnNo;
    std::cout << std::setw(publishPrecision) << std::left << entry->publisher;
    std::cout << entry->dateOfPublication.day << "/"
              << entry->dateOfPublication.month << "/"
              << entry->dateOfPublication.year << std::endl;
}
