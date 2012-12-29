#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#if defined (_WIN32)
   #include <winsock2.h>
   #include <ws2tcpip.h>
#endif

#if defined (__unix__) || defined (__linux__)
   #include <unistd.h>
   #include <sys/types.h>
   #include <sys/socket.h>
   #include <arpa/inet.h>
   #include <netinet/in.h>
   #include <netdb.h>
#endif

#include "statsd.h"

//Define the private functions
static const char *networkToPresentation(int af, const void *src, char *dst, size_t size);

#if defined(_WIN32)
static const char *networkToPresentation(int af, const void *src, char *dst, size_t size){
   return InetNtop(af, src, dst, size);
}
#else
static const char *networkToPresentation(int af, const void *src, char *dst, size_t size){
   return inet_ntop(af, src, dst, size);
}
#endif

//Implement the public functions

/**
   This is allocate the memory for a statsd object from the heap
   initialize it with the givin values and return the newly constructed
   object ready for use. 

   @param[out] stats - This is where the statsd object will be placed.
   @param[in] serverAddress - The hostname, or ip address of the statsd server
   @param[in] port - The port number to use for statsd packets
   @param[in] bucket - The unique bucket name to use for reporting stats

   @return STATSD_SUCCESS on success, or an error if something went wrong
   @see StatsError
*/
int ADDCALL statsd_new(Statsd** stats, const char* serverAddress, int port, const char* bucket){
   Statsd* newStats = (Statsd*)malloc(sizeof(Statsd));
   if (!newStats){
      return STATSD_MALLOC;
   }

   memset(newStats, 0, sizeof(Statsd));

   *stats = newStats;
   
   //Do a DNS lookup (or IP address conversion) for the serverAddress
   struct addrinfo hints, *result = NULL;
   memset(&hints, 0, sizeof(hints));

   //Set the hints to narrow downs the DNS entry we want
   hints.ai_family = AF_INET;

   int addrinfoStatus = getaddrinfo(serverAddress, NULL, &hints, &result);
   if (addrinfoStatus != 0){
      newStats->lastReturn = STATSD_BAD_SERVER_ADDRESS;
      return STATSD_BAD_SERVER_ADDRESS;
   }

   //Copy the result into the UDP destination socket structure
   memcpy(&newStats->destination, result->ai_addr, sizeof(struct sockaddr_in));
   newStats->destination.sin_port = htons((short)port);

   newStats->serverAddress = serverAddress;
   newStats->port = port;
   newStats->bucket = bucket;

   //Free the result now that we have copied the data out of it.
   freeaddrinfo(result);

   //Store the IP address in readable form
   if (networkToPresentation(AF_INET, &newStats->destination.sin_addr, newStats->ipAddress, sizeof(newStats->ipAddress)) == NULL){
      newStats->lastReturn = STATSD_NTOP;
      return STATSD_NTOP;
   }

   //Open up the socket file descriptor
   newStats->socketFd = socket(AF_INET, SOCK_DGRAM, 0);
   if (newStats->socketFd == -1){
      newStats->lastReturn = STATSD_SOCKET;
      return STATSD_SOCKET;
   }

   return STATSD_SUCCESS;
}

/**
   Free a statsd object created through a call to statsd_new()

   @param[in] statsd - The statsd object created by a call to
      statsd_new(). 
*/
void ADDCALL statsd_release(Statsd* statsd){
   if (statsd->batch){
      while(statsd->batch){
         StatsdBatch* next = statsd->batch->next;
         free(statsd->batch);
         statsd->batch = next;
      }
   }

   free(statsd);
}

/**
   This will initialize (or reinitialize) a statsd object that 
   has already been created by a call to statsd_new() or has been
   allocated statically on the stack. 

   @param[in,out] statsd - A previously allocated statsd object
   @param[in] server - The hostname or ip address of the server
   @param[in] port - The port number that the packets will be sent to
   @param[in] bucket - The bucket name that will be used for the stats

   @return SCTE_SUCCESS on success, or an error otherwise
   @see StatsError
*/
int ADDCALL statsd_init(Statsd* statsd, const char* server, int port, const char* bucket){
   memset(statsd, 0, sizeof(Statsd));

   //Do a DNS lookup (or IP address conversion) for the serverAddress
   struct addrinfo hints, *result = NULL;
   memset(&hints, 0, sizeof(hints));

   //Set the hints to narrow downs the DNS entry we want
   hints.ai_family = AF_INET;

   int addrinfoStatus = getaddrinfo(server, NULL, &hints, &result);
   if (addrinfoStatus != 0){
      statsd->lastReturn = STATSD_BAD_SERVER_ADDRESS;
      return STATSD_BAD_SERVER_ADDRESS;
   }

   //Copy the result into the UDP destination socket structure
   memcpy(&statsd->destination, result->ai_addr, sizeof(struct sockaddr_in));
   statsd->destination.sin_port = htons((short)port);

   statsd->serverAddress = server;
   statsd->port = port;
   statsd->bucket = bucket;

   //Free the result now that we have copied the data out of it.
   freeaddrinfo(result);

   //Store the IP address in readable form
   if (networkToPresentation(AF_INET, &statsd->destination.sin_addr, statsd->ipAddress, sizeof(statsd->ipAddress)) == NULL){
      statsd->lastReturn = STATSD_NTOP;
      return STATSD_NTOP;
   }

   //Open up the socket file descriptor
   statsd->socketFd = socket(AF_INET, SOCK_DGRAM, 0);
   if (statsd->socketFd == -1){
      statsd->lastReturn = STATSD_SOCKET;
      return STATSD_SOCKET;
   }

   return STATSD_SUCCESS;
}

/**

*/
int ADDCALL statsd_increment(Statsd* statsd){
   return STATSD_SUCCESS;
}

/**

*/
int ADDCALL statsd_decrement(Statsd* statsd){
   return STATSD_SUCCESS;
}

/**

*/
int ADDCALL statsd_count(Statsd* statsd, int count, double sampleRate){
   return STATSD_SUCCESS;
}

/**

*/
int ADDCALL statsd_gauge(Statsd* statsd, int value, double sampleRate){
   return STATSD_SUCCESS;
}

/**

*/
int ADDCALL statsd_set(Statsd* statsd, int value, double sampleRate){
   return STATSD_SUCCESS;
}

/**

*/
int ADDCALL statsd_timing(Statsd* statsd, int timing, double sampleRate){
   return STATSD_SUCCESS;
}

