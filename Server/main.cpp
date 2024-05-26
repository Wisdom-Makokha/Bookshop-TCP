#include "server_definitions.h"

using std::getline;
std::ofstream logsOutput;

int main(void)
{
    // Initialise WSA variables
    WSADATA wsaData;
    WORD wVersioRequested = MAKEWORD(2, 2);

    // initialise variables to store address details
    struct addrinfo *result = NULL;
    struct addrinfo hints;

    int entries = 0;
    book_entry catalog[BOOK_LIMIT];

    // read the contents of read file to the catalog
    if (!readFileContents(catalog, &entries))
        exit(EXIT_FAILURE);

    logsOutput.open("serverLogs.txt", std::ios::app);
    if (logsOutput.is_open())
    {
        std::cerr << "Error opening serverLogs.txt" << std::endl;
        exit(EXIT_FAILURE);
    }

    // set up the logs
    std::string newLogs(40, '=');
    logsOutput << std::endl
               << newLogs << std::endl;

    //initialise WSA

    exit(EXIT_SUCCESS);
}

// function to read the contents of the readfile and put into server memory
bool readFileContents(book_entry *catalog, int *entries)
{
    std::ifstream readFile("Data/read_file.txt"); // open the file
    bool result;                                  // store the result
    char slash;                                   // store the slash for the date

    // check if the file is open
    if (readFile.is_open())
    {
        // read until the file ends
        while (!readFile.eof())
        {
            char newline;                  // newline character for when reading the next character after the serial no
            readFile >> catalog->serialNo; // serial no read
            readFile >> newline;           // remove the newline character

            readFile.getline(catalog->title, TITLE_LIMIT);                                                                                       // get the title
            readFile.getline(catalog->author, AUTHOR_LIMIT);                                                                                     // get the author
            readFile.getline(catalog->isbnNo, ISBN_LIMIT);                                                                                       // get the isbn no
            readFile.getline(catalog->publisher, PUB_LIMIT);                                                                                     // get the publisher
            readFile >> catalog->dateOfPublication.day >> slash >> catalog->dateOfPublication.month >> slash >> catalog->dateOfPublication.year; // get the date of publication

            printEntry(catalog);
            catalog++;               // move to the next entry
            *entries = *entries + 1; // increase entry

            // if (readFile.eof())
            //     break;
        }

        result = SUCCESS;
    }
    else
    {
        std::cerr << "Error opening readfile.txt for reading the catalog" << std::endl;
        result = FAILURE;
    }

    readFile.close();
    return result;
}

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

// function to write logs for the program
void writeLogs(error_logs logs, std::ofstream &logFile)
{
    std::string divider = " | "; //divider for sections
    std::string operationMessage = logs.operationStatus ? "SUCCESS" : "FAILURE"; // 

    char *timeLog = NULL;
    GetCurrentTime(timeLog);
    char *optionString = getOption(logs.option);
    
    int optionWidth = 18;
    int opMessageWidth = 9;
    int detailWidth = 30;
    int errorResultWidth = 8;
    int errorStringWidth = 30;

    //check if time log is null
    if(timeLog != NULL)
        logFile << timeLog << divider;
    
    //check if option string is null
    if(optionString != NULL)
        logFile << std::left << std::setw(optionWidth) << optionString << divider;

    // print the error message
    logFile << std::left << std::setw(opMessageWidth) << operationMessage << divider;
    
    // check if details is null
    if(logs.details != NULL)
        logFile << std::left << std::setw(detailWidth) << logs.details << divider;

    // check if error result is null_int
    if(logs.errorResult != NULL_INT)
        logFile << std::right << std::setw(errorResultWidth) << logs.errorResult << divider;

    // check if error string is null
    if(logs.errorString != NULL)
        logFile << std::left << std::setw(errorStringWidth) << logs.errorString << divider;

    logFile << std::endl;
}

// function to get the current time
void getTimeCurrentTimeLog(char *timeString)
{
    // initialise time struct
    time_t currentTime;

    currentTime = time(NULL);

    // check if current time is a negative time_t
    if (currentTime == ((time_t)-1))
    {
        std::cerr << "Failure to obtain the current time." << std::endl;
        timeString = NULL;
        return;
    }

    // convert current time into a string
    timeString = ctime(&currentTime);
    if (timeString == NULL)
    {
        std::cerr << "Failure to convert to current time." << std::endl;
        timeString = NULL;
        return;
    }

    // set the last character in timeString to \0
    int stringLength = strlen(timeString);
    timeString[stringLength - 1] = '\0';
}

// function to get the option message
char *getOption(l_options option)
{
    // pick message
    switch (option)
    {
    case CONNECT:
        return "connect";
    case SEND:
        return "send";
    case RECEIVE:
        return "receive";
    case SHUTDOWN:
        return "shutdown";
    case START:
        return "start";
    case BIND:
        return "bind";
    case LISTEN:
        return "listen";
    case ACCEPT:
        return "accept";
    case SOCKET_CREATE:
        return "socket create";
    case GET_ADDR_INFO_OPTION:
        return "get address info";
    case UNKNOWN:
    default:
        return "UNKOWN OPTION";
    }
}

// function to initialise the WSA
bool intialiseWsa(WSADATA *wsaData, WORD wVersionRequested, std::ofstream &logFile)
{
    error_logs logs;
    logs.option = START;
    logs.errorResult = NULL_INT;
    logs.errorString = NULL;

    int wsaError = WSAStartup(wVersionRequested, wsaData);

    if(wsaError != 0)
    {
        
    }
}