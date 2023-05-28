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


function run100ClientsTest() {
  clientsPid=();
  debugLog "Starting 100 clients"
  for i in {1..100} ; do
      ./os_unix_brownian_client "$CONFIG_FILENAME" < "$CLIENT_RANDOM_NUMBERS_FILENAME" > /dev/null &
      clientsPid+=($!);
  done


  debugLog "Waiting until every client stop"
  wait ${clientsPid[@]}

  debugLog "Checking is server state equals zero"
  result=$(echo "0" | ./os_unix_brownian_client "$CONFIG_FILENAME");

  echo "$result"
  echo "$result" >> results.txt
  echo ""
  echo "" >> results.txt
}


function runNClientsWithDifferentSleepTime() {
  n=$1;

  for t in {200..1000..200} ; do
    clientsPid=();
    debugLog "Starting $n clients"
    for i in {1..$n} ; do
      ./os_unix_brownian_client "$CONFIG_FILENAME" -t "$t" < "$CLIENT_RANDOM_NUMBERS_FILENAME" > "/tmp/os-unix-logs-client-${i}" &
      clientsPid+=($!);
    done

    wait ${clientsPid[@]};

    serverStartedAt=$( head -n1 "$SERVER_LOGS_FILENAME" | awk -F '|' '{ print $1 }' );
    serverClosedAt=$( tail -n1 "$SERVER_LOGS_FILENAME" | awk -F '|' '{ print $1 }' );
    serverWorkedSeconds=$(( $(date -d "$serverClosedAt" "+%s") - $(date -d "$serverStartedAt" "+%s") ));

    slowestClient=0;
    for logFile in /tmp/os-unix-logs-client-* ; do
      clientStartedAt=$( head -n1 "$logFile" | awk -F '|' '{ print $1 }' );
      clientClosedAt=$( tail -n1 "$logFile" | awk -F '|' '{ print $1 }' );
      clientWorked=$(( $(date -d "$clientClosedAt" "+%s") - $(date -d "$clientStartedAt" "+%s") ));

      if [ $clientWorked -gt $slowestClient ]; then
          slowestClient=$clientWorked;
      fi
    done

    effectiveness=$(( serverWorkedSeconds - slowestClient ))
    successLog "Effectiveness with $t milliseconds to sleep: $effectiveness"
    echo "Effectiveness with $t milliseconds to sleep: $effectiveness" >> results.txt
  done
}


debugLog "Building app"
make
echo ""


debugLog "Deleting ${SERVER_LOGS_FILENAME} if exists"
rm "$SERVER_LOGS_FILENAME" 2> /dev/null

debugLog "Deleting results.txt if exists"
rm results.txt 2> /dev/null

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


debugLog "Shuf lines in ${CLIENT_RANDOM_NUMBERS_FILENAME}"
shuf "$CLIENT_RANDOM_NUMBERS_FILENAME" > /dev/null

debugLog "Got `wc -l ${CLIENT_RANDOM_NUMBERS_FILENAME}` lines"

debugLog "Adding socket name to config"
echo "$SOCKET_NAME" > "$CONFIG_FILENAME"

debugLog "Starting server"
./os_unix_brownian_server_bot "$CONFIG_FILENAME" > "$SERVER_LOGS_FILENAME" &
successLog "Started server"


debugLog "First time starting test script"
echo "First time starting test script " >> results.txt
run100ClientsTest



debugLog "Second time starting test script"
echo "Second time starting test script " >> results.txt
run100ClientsTest

debugLog "Checking memory usage"
echo "Checking memory usage" >> results.txt
grep "new connection socket" "$SERVER_LOGS_FILENAME" | sed -n '1p;$p'
grep "new connection socket" "$SERVER_LOGS_FILENAME" | sed -n '1p;$p' >> results.txt
echo ""
echo "" >> results.txt



for i in {1..100..10} ; do
  successLog "Running effectiveness test for $i clients"
  echo "Running effectiveness test for $i clients" >> results.txt

  pkill os_unix_brownian_server_bot
  rm "$SERVER_LOGS_FILENAME" 2> /dev/null
  debugLog "Starting server"
  ./os_unix_brownian_server_bot "$CONFIG_FILENAME" > "$SERVER_LOGS_FILENAME" &
  successLog "Started server"

  runNClientsWithDifferentSleepTime $i

  echo "" >> results.txt
done


debugLog "Clean up"
rm "$SERVER_LOGS_FILENAME" 2> /dev/null
rm "$CLIENT_RANDOM_NUMBERS_FILENAME" 2>/dev/null
rm "$CONFIG_FILENAME" 2> /dev/null
rm "$SOCKET_NAME" 2> /dev/null

rm -f /tmp/os-unix-logs-client-* 2>/dev/null

pkill os_unix_

successLog "Clean up succeed"
