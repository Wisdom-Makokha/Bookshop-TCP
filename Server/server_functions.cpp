#include "server_definitions.h"

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
            readFile >> catalog->serialNo; // serial no read
            readFile.ignore(1);            // skip the newline character on the first line

            readFile.getline(catalog->title, TITLE_LIMIT);                                                                                       // get the title
            readFile.getline(catalog->author, AUTHOR_LIMIT);                                                                                     // get the author
            readFile.getline(catalog->isbnNo, ISBN_LIMIT);                                                                                       // get the isbn no
            readFile.getline(catalog->publisher, PUB_LIMIT);                                                                                     // get the publisher
            readFile >> catalog->dateOfPublication.day >> slash >> catalog->dateOfPublication.month >> slash >> catalog->dateOfPublication.year; // get the date of publication

            printEntry(catalog);
            catalog++;               // move to the next entry
            *entries = *entries + 1; // increase entry
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

// function to bind a socket to a specific address
bool bindSocket(SOCKET *socketToBind, struct addrinfo *result, std::ofstream &logFile)
{
    error_logs logs;
    logs.option = BIND;
    logs.errorString = NULL;

    // check for socket binding status
    if ((bind(*socketToBind, result->ai_addr, (int)result->ai_addrlen)) == SOCKET_ERROR)
    {
        logs.operationStatus = FAILURE;
        logs.errorResult = WSAGetLastError();
        logs.details = strdup("Binding failed: ");
    }
    else
    {
        logs.operationStatus = SUCCESS;
        logs.errorResult = NULL_INT;
        logs.details = strdup("Binding is OK!");
    }

    writeLogs(logs, logFile);
    return logs.operationStatus;
}