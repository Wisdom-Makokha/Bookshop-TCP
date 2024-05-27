#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include "..\Shared\definitions.h"
#include "..\Shared\net_definitions.h"

//server only functions
bool bindSocket(SOCKET *socketToBind, struct addrinfo *result, std::ofstream &logFile);
bool readFileContents(book_entry *catalog, int *entries);

