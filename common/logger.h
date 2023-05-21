#ifndef OS_UNIX_LOGGER
#define OS_UNIX_LOGGER
#include "stdio.h"

extern FILE * logfile;

void initLog(FILE * stream);

void writeLog(const char * format, ...);

void closeLog();

#endif //OS_UNIX_LOGGER
