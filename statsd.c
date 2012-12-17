#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

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
static int winInit();

//Implement the private functions
#if defined(_WIN32)
static WSADATA wsaData = {0};

static int winInit(Statsd* statsd){
   if (WSAStartup(MAKEWORD(2,2) &wsaData) != 0){
      return STATSD_SOCKET_INIT;
   }

   return STATSD_SUCCESS;
}
#else
static int winInit(){
   return STATSD_SUCCESS;
}
#endif

//Implement the public functions
int ADDCALL statsd_new(Statsd** stats, const char* serverAddress, int port, const char* bucket){
   int ret = 0;
   
   Statsd* newStats = (Statsd*)malloc(sizeof(Statsd));
   if (!newStats){
      return STATSD_MALLOC;
   }

   memset(newStats, 0, sizeof(Statsd));

   *stats = newStats;
   
   //Initialize the winsocks for Windows computers, on unix systems
   //This does nothing.
   ret = winInit();
   if (ret != STATSD_SUCCESS){
      newStats->lastReturn = ret;
      return ret;
   }

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
   if (inet_ntop(AF_INET, &newStats->destination.sin_addr, newStats->ipAddress, sizeof(newStats->ipAddress)) == NULL){
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

int ADDCALL statsd_init(Statsd* statsd, const char* server, int port, const char* bucket){
   return STATSD_SUCCESS;
}

int ADDCALL statsd_increment(Statsd* statsd){
   return STATSD_SUCCESS;
}

int ADDCALL statsd_decrement(Statsd* statsd){
   return STATSD_SUCCESS;
}

int ADDCALL statsd_count(Statsd* statsd, int count, double sampleRate){
   return STATSD_SUCCESS;
}

int ADDCALL statsd_gauge(Statsd* statsd, int value, double sampleRate){
   return STATSD_SUCCESS;
}

int ADDCALL statsd_set(Statsd* statsd, int value, double sampleRate){
   return STATSD_SUCCESS;
}

int ADDCALL statsd_timing(Statsd* statsd, int timing, double sampleRate){
   return STATSD_SUCCESS;
}

int ADDCALL statsd_openBatch(Statsd* statsd){
   return STATSD_SUCCESS;
}

int ADDCALL statsd_addToBatch(Statsd* statsd, StatsType type, int value){
   return STATSD_SUCCESS;
}

int ADDCALL statsd_sendBatch(Statsd* statsd){
   return STATSD_SUCCESS;
}


