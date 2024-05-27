#include <WinSock2.h>
#include <windows.h>
#include <WS2tcpip.h>
#include <stdlib.h>
#include <time.h>

#define TOGGLE_LOGS_DISPLAY true
#define NULL_INT 4179789
#define TCP_PORT "5412"

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

//common net functions
bool initialiseWsa(WSADATA *wsaData, WORD wVersionRequested, std::ofstream &logFile);
bool addrResolution(struct addrinfo **result, struct addrinfo *hints, char *serverName, std::ofstream &logFile);
bool createSocket(SOCKET *socketToCreate, struct addrinfo* result, std::ofstream &logFile);

void writeLogs(error_logs logs, std::ofstream &logFile);
const char *getOption(l_options option);
