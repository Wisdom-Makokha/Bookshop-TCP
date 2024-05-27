#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using std::getline;

#define SERIAL_LIMIT 8
#define TITLE_LIMIT 256
#define AUTHOR_LIMIT 256
#define PUB_LIMIT 128
#define ISBN_LIMIT 12
#define BOOK_LIMIT 64
#define NULL_ENTRY (book_entry *)0
#define SUCCESS true
#define FAILURE false

// date struct
struct date
{
    int day;
    int month;
    int year;
};

// book entry struct
typedef struct entry
{
    int serialNo;
    char title[TITLE_LIMIT];
    char author[AUTHOR_LIMIT];
    char isbnNo[ISBN_LIMIT];
    char publisher[PUB_LIMIT];
    struct date dateOfPublication;
} book_entry;

// common functions
void printEntry(book_entry *entry);
void getCurrentTimeLog(char *timeString);

