#include "statsd.h"

int ADDCALL statsd_openBatch(Statsd* statsd){
   return STATSD_SUCCESS;
}

int ADDCALL statsd_addToBatch(Statsd* statsd, StatsType type, const char* bucket, int value, double sampleRate){
   return STATSD_SUCCESS;
}

int ADDCALL statsd_sendBatch(Statsd* statsd){
   return STATSD_SUCCESS;
}


