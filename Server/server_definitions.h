#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

#include <WinSock2.h>
#include <windows.h>
#include <WS2tcpip.h>
#include <stdlib.h>
#include <time.h>

#define TITLE_LIMIT 256
#define AUTHOR_LIMIT 256
#define PUB_LIMIT 128
#define ISBN_LIMIT 12
#define BOOK_LIMIT 64
#define NULL_ENTRY (book_entry *)0
#define SUCCESS true
#define FAILURE false
#define TOGGLE_LOGS_DISPLAY true
#define NULL_INT 4179789

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

// options for error logs
typedef enum level_options
{
    CONNECT,
    SEND,
    RECEIVE,
    SHUTDOWN,
    START,
    BIND,
    LISTEN,
    ACCEPT,
    SOCKET_CREATE,
    GET_ADDR_INFO_OPTION,
    UNKNOWN
} l_options;

// logs struct
typedef struct log_struct
{
    l_options option;
    bool operationStatus;
    char *details;
    int errorResult;
    char *errorString;
} error_logs;

bool readFileContents(book_entry *catalog, int *entries);
void printEntry(book_entry *entry);
void getTimeCurrentTimeLog(char *timeString);
char *getOption(l_options option);
void writeLogs(error_logs logs, std::ofstream &logFile);