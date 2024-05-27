#include "server_definitions.h"

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
    if (!logsOutput.is_open())
    {
        std::cerr << "Error opening serverLogs.txt" << std::endl;
        exit(EXIT_FAILURE);
    }

    // set up the logs
    std::string newLogs(40, '=');
    logsOutput << std::endl
               << newLogs << std::endl;

    // initialise WSA
    if (!initialiseWsa(&wsaData, wVersioRequested, logsOutput))
        exit(EXIT_FAILURE);

    // set the initial hints for expected address details
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    if (!addrResolution(&result, &hints, NULL, logsOutput))
        exit(EXIT_FAILURE);

    // Create the listening socket
    SOCKET listenSocket;
    if (!createSocket(&listenSocket, result, logsOutput))
        exit(EXIT_FAILURE);

    // bind the socket
    if(!bindSocket(&listenSocket, result, logsOutput))
        exit(EXIT_FAILURE);

    exit(EXIT_SUCCESS);
}
