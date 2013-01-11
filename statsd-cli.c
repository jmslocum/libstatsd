#include <stdio.h>
#include <stdlib.h>
#include "statsd.h"

int main(int argc, char* argv[]){
#if defined (_WIN32)
   //Initialize the windows socket library
   WSADATA wsaData = {0};

   if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0){
      return STATSD_SOCKET_INIT;
   }
#endif
   
   Statsd* stats = NULL;

   return EXIT_SUCCESS;
}
