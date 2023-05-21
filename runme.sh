#!/bin/bash

CONFIG_FILENAME="/tmp/os-unix-brownian-bot.config"
SOCKET_NAME="/tmp/os-unix.socket"
CLIENT_RANDOM_NUMBERS_FILENAME="/tmp/os-unix-clients.numbers"
SERVER_LOGS_FILENAME="/tmp/os-unix-brownian-bot.log"
RANDOM_MAX=10
RANDOM_HALF=5

function debugLog() {
    echo -e "\e[93m[~]\e[0m\t$1\n"
}

function successLog() {
  echo -e "\e[32m[+]\e[0m\t$1\n"

}

function failedLog() {
    echo -e "\e[31m[!]\e[0m\t$1\n"
}


debugLog "Building app"
make
echo ""


debugLog "Deleting ${SERVER_LOGS_FILENAME} if exists"
rm "$SERVER_LOGS_FILENAME" 2> /dev/null

debugLog "Removing common file for clients if exists"
rm "$CLIENT_RANDOM_NUMBERS_FILENAME" 2>/dev/null

debugLog "Creating common file with 1000 numbers for clients";
totalSum=0
for i in {1..999} ; do
  number=$((($RANDOM % $RANDOM_MAX) - $RANDOM_HALF));
  totalSum=$(($totalSum + $number));
  echo "$number" >> "$CLIENT_RANDOM_NUMBERS_FILENAME"
done

if [ $totalSum -lt 0 ]; then
  totalSum=$((-1 * $totalSum));
  echo "$totalSum" >> "$CLIENT_RANDOM_NUMBERS_FILENAME"
else
  echo "-$totalSum" >> "$CLIENT_RANDOM_NUMBERS_FILENAME"
fi


debugLog "Shuffing lines in ${CLIENT_RANDOM_NUMBERS_FILENAME}"
shuf "$CLIENT_RANDOM_NUMBERS_FILENAME"

debugLog "Got `wc -l ${CLIENT_RANDOM_NUMBERS_FILENAME}` lines"

debugLog "Adding socket name to config"
echo "$SOCKET_NAME" > "$CONFIG_FILENAME"

debugLog "Starting server"
./os_unix_brownian_server_bot "$CONFIG_FILENAME" > "$SERVER_LOGS_FILENAME" &
successLog "Started server"


debugLog "Starting 100 clients"
for i in {1..100} ; do
    ./os_unix_brownian_client "$CONFIG_FILENAME" < "$CLIENT_RANDOM_NUMBERS_FILENAME" &
done

#debugLog "Clean up"
#rm "$SERVER_LOGS_FILENAME" 2> /dev/null
#rm "$CLIENT_RANDOM_NUMBERS_FILENAME" 2>/dev/null
#successLog "Clean up succeed"
