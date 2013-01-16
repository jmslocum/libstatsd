#ifndef LIB_STATS_D_H
#define LIB_STATS_D_H

#define ADDAPI
#define ADDCALL

#if defined (_WIN32)
   //Windows Specific includes
   #include <winsock2.h>
   #include <ws2tcpip.h>

   //Undefine the macros, and redefine them to perform
   //windows specific tasks
   #undef ADDAPI
   #undef ADDCALL

   #ifdef ADD_EXPORTS
      #define ADDAPI __declspec(dllexport)
   #else
      #define ADDAPI __declspec(dllimport)
   #endif

   #define ADDCALL __cdecl

#elif defined (__linux__) || defined (__unix__)
   //Unix specific includes
   #include <sys/socket.h>
   #include <arpa/inet.h>

#endif //end of windows/unix/linux OS stuff

#define STATSD_PORT 8125
#ifndef BATCH_MAX_SIZE
#define BATCH_MAX_SIZE 512
#endif

typedef struct _statsd_t {
   const char* serverAddress;
   char ipAddress[128];
   const char* nameSpace;
   const char* bucket;
   int port;
   int socketFd;
   struct sockaddr_in destination;

   char batch[BATCH_MAX_SIZE];
   int batchIndex;

   int messagesSent;
   int lastReturn;
   int lastErrno;
} Statsd;

typedef enum {
   STATSD_NONE = 0,
   STATSD_COUNT,
   STATSD_GAUGE,
   STATSD_SET,
   STATSD_TIMING,
   STATSD_BATCH
} StatsType;

typedef enum {
   STATSD_SUCCESS = 0,
   STATSD_BAD_BUCKET,
   STATSD_SOCKET,
   STATSD_SOCKET_INIT,
   STATSD_NTOP,
   STATSD_MALLOC,
   STATSD_BAD_SERVER_ADDRESS,
   STATSD_UDP_SEND,
   STATSD_BATCH_IN_PROGRESS,
   STATSD_NO_BATCH,
   STATSD_BATCH_FULL,
   STATSD_BAD_STATS_TYPE
} StatsError;

#ifdef __cplusplus
extern "C" {
#endif

ADDAPI int ADDCALL statsd_new(Statsd **stats, const char* serverAddress, int port, const char* nameSpace, const char* bucket);
ADDAPI void ADDCALL statsd_release(Statsd* statsd);
ADDAPI int ADDCALL statsd_init(Statsd* statsd, const char* server, int port, const char* nameSpace, const char* bucket);
ADDAPI int ADDCALL statsd_increment(Statsd* statsd, const char* bucket);
ADDAPI int ADDCALL statsd_decrement(Statsd* statsd, const char* bucket);
ADDAPI int ADDCALL statsd_count(Statsd* statsd, const char* bucket, int count, double sampleRate);
ADDAPI int ADDCALL statsd_gauge(Statsd* statsd, const char* bucket, int value, double sampleRate);
ADDAPI int ADDCALL statsd_set(Statsd* statsd, const char* bucket, int value, double sampleRate);
ADDAPI int ADDCALL statsd_timing(Statsd* statsd, const char* bucket, int timing, double sampleRate);
ADDAPI int ADDCALL statsd_resetBatch(Statsd* statsd);
ADDAPI int ADDCALL statsd_addToBatch(Statsd* statsd, StatsType type, const char* bucket, int value, double sampleRate);
ADDAPI int ADDCALL statsd_sendBatch(Statsd* statsd);

#ifdef __cplusplus
}
#endif

#endif //LIB_STATS_D_H
