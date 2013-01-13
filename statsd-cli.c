#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "statsd.h"

#define STRING_MATCH 0

static char* serverAddress = NULL;
static int port = STATSD_PORT;
static char* prefix = NULL;
static char* bucket = NULL;
static int type = STATSD_NONE;

static void usageAndExit(char* prog, FILE* where, int returnCode){
   fprintf(where, "%s usage:\n", prog);
   fprintf(where, "  -s --server : specify the server name or ip address\n");
   fprintf(where, "  -p --port : specify the port (default = 8125)\n");
   fprintf(where, "  -r --prefix : specify the bucket prefix\n");
   fprintf(where, "  -b --bucket : specify the bucket\n");
   fprintf(where, "  -t --type : specify the stat type\n");
   fprintf(where, "example:\n");
   fprintf(where, "  %s -s statsd.example.com -r some.statsd -b counts 25\n");
}

static int parseCommandLine(int argc, char* argv[]){
   for (int i = 0; i < argc; i++){
      if (strcmp(argv[i], "-s") == STRING_MATCH || strcmp(argv[i], "--server") == STRING_MATCH){

      }
      else if (strcmp(argv[i], "-p") == STRING_MATCH || strcmp(argv[i], "--port") == STRING_MATCH){

      }
      else if (strcmp(argv[i], "-r") == STRING_MATCH || strcmp(argv[i], "--prefix") == STRING_MATCH){

      }
      else if (strcmp(argv[i], "-b") == STRING_MATCH || strcmp(argv[i], "--bucket") == STRING_MATCH){

      }
      else if (strcmp(argv[i], "-t") == STRING_MATCH || strcmp(argv[i], "--type") == STRING_MATCH){

      }
      else {

      }
   }
}

int main(int argc, char* argv[]){
#if defined (_WIN32)
   //Initialize the windows socket library
   WSADATA wsaData = {0};

   if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0){
      return STATSD_SOCKET_INIT;
   }
#endif
   
   //Parse the command line

   //Set up the statsd object
   Statsd* stats = NULL;
   int ret = statsd_new(&stats, serverAddress, port, prefix, bucket);

   return EXIT_SUCCESS;
}
