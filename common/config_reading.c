#include <stdio.h>
#include <stdlib.h>
#include "config_reading.h"

#define SOCKET_NAME_MAX_LENGTH 128

const char * getSocketNameFromConfig(const char * configName) {
    FILE *configFile = fopen(configName, "r");
    if (configFile == NULL) {
        perror("failed opening config");
        exit(-1);
    }

    char *socketName = malloc(sizeof(char) * SOCKET_NAME_MAX_LENGTH);
    fgets(socketName, SOCKET_NAME_MAX_LENGTH, configFile);

    return socketName;
}
