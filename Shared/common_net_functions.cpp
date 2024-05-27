#include "net_definitions.h"
#include "definitions.h"

// function to initialise the WSA
bool initialiseWsa(WSADATA *wsaData, WORD wVersionRequested, std::ofstream &logFile)
{
    error_logs logs;
    logs.option = START;
    logs.errorResult = NULL_INT;
    logs.errorString = NULL;

    int wsaError = WSAStartup(wVersionRequested, wsaData);

    if (wsaError != 0)
    {
        // set up the logs
        logs.operationStatus = FAILURE;
        logs.details = strdup("Winsock dll not found!");
    }
    else
    {
        // set up the logs
        logs.operationStatus = SUCCESS;
        logs.details = strdup("Winsock found! Status: ");
        logs.errorString = strdup((*wsaData).szSystemStatus);
    }

    writeLogs(logs, logFile);
    return logs.operationStatus;
}

// function to resolve the address and port of the server
bool addrResolution(struct addrinfo **result, struct addrinfo *hints, char *serverName, std::ofstream &logFile)
{
    error_logs logs;
    logs.errorString = NULL;
    logs.option = GET_ADDR_INFO_OPTION;
    int getAddrResult = getaddrinfo(serverName, TCP_PORT, hints, result);

    // get the addres
    if (getAddrResult)
    {
        // for when getting the address fails
        logs.operationStatus = FAILURE;
        logs.errorResult = getAddrResult;
        logs.details = strdup("getaddrinfo failed with error: ");

        WSACleanup();
    }
    else
    {
        // for when getting the address succeeds
        logs.operationStatus = SUCCESS;
        logs.errorResult = NULL_INT;
        logs.details = strdup("address and port resolved");
    }

    writeLogs(logs, logFile);
    return logs.operationStatus;
}

// function to create a socket
bool createSocket(SOCKET *socketToCreate, struct addrinfo *result, std::ofstream &logFile)
{
    *socketToCreate = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    error_logs logs;
    logs.errorString = NULL;
    logs.option = SOCKET_CREATE;

    // Check for socket creation success
    if (*socketToCreate == INVALID_SOCKET)
    {
        logs.details = strdup("Error creating socket: ");
        logs.errorResult = WSAGetLastError();
        logs.operationStatus = FAILURE;
    }
    else
    {
        logs.details = strdup("Socket created");
        logs.errorResult = NULL_INT;
        logs.operationStatus = SUCCESS;
    }

    writeLogs(logs, logFile);
    return logs.operationStatus;
}

// function to write logs for the program
void writeLogs(error_logs logs, std::ofstream &logFile)
{
    std::string divider = " | ";                                                 // divider for sections
    std::string operationMessage = logs.operationStatus ? "SUCCESS" : "FAILURE"; //

    char *timeLog = NULL;
    getCurrentTimeLog(timeLog);
    const char *optionString = getOption(logs.option);

    int optionWidth = 18;
    int opMessageWidth = 9;
    int detailWidth = 30;
    int errorResultWidth = 8;
    int errorStringWidth = 30;

    // check if time log is null
    if (timeLog != NULL)
    {
        logFile << timeLog << divider;
        if (TOGGLE_LOGS_DISPLAY)
            std::cout << timeLog << divider;
    }

    // check if option string is null
    if (optionString != NULL)
    {
        logFile << std::left << std::setw(optionWidth) << optionString << divider;
        if (TOGGLE_LOGS_DISPLAY)
            std::cout << std::left << std::setw(optionWidth) << optionString << divider;
    }

    // print the error message
    logFile << std::left << std::setw(opMessageWidth) << operationMessage << divider;
    std::cout << std::left << std::setw(opMessageWidth) << operationMessage << divider;

    // check if details is null
    if (logs.details != NULL)
    {
        logFile << std::left << std::setw(detailWidth) << logs.details << divider;
        if (TOGGLE_LOGS_DISPLAY)
            std::cout << std::left << std::setw(detailWidth) << logs.details << divider;
    }

    // check if error result is null_int
    if (logs.errorResult != NULL_INT)
    {
        logFile << std::right << std::setw(errorResultWidth) << logs.errorResult << divider;
        if (TOGGLE_LOGS_DISPLAY)
            std::cout << std::right << std::setw(errorResultWidth) << logs.errorResult << divider;
    }

    // check if error string is null
    if (logs.errorString != NULL)
    {
        logFile << std::left << std::setw(errorStringWidth) << logs.errorString << divider;
        if (TOGGLE_LOGS_DISPLAY)
            std::cout << std::left << std::setw(errorStringWidth) << logs.errorString << divider;
    }

    logFile << std::endl;
    std::cout << std::endl;
}

// function to get the current time
void getCurrentTimeLog(char *timeString)
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
const char *getOption(l_options option)
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
