# Server working with poll

Задача 4 из [задачника](https://eykuklin.github.io/OS-UNIX/).

Однопоточный сервер. Принимает числа, складывает с общим числом и отправляет ответ.
Для работы с несколькими клиентами используется `poll`.

```text
usage: ./os_unix_brownian_server_bot /path/to/config/
usage: ./os_unix_brownian_client /path/to/config/ -t time_to_sleep
```

## Как запустить "тесты":
0. `cmake .` - создает `Makefile`. В репозитории уже лежит необходимый `Makefile`, так требует формат выполнения задач.
1. `chmod +x runme.sh`
2. `./runme.sh`


## Мой вывод results.txt
```text
First time starting test script 
Sun May 28 15:56:45 2023	|	client start sending data
Sun May 28 15:56:45 2023	|	recv 1 bytes, 0
Sun May 28 15:56:45 2023	|	client send all data

Second time starting test script 
Sun May 28 15:56:46 2023	|	client start sending data
Sun May 28 15:56:46 2023	|	recv 1 bytes, 0
Sun May 28 15:56:46 2023	|	client send all data

Checking memory usage
Sun May 28 15:56:44 2023	|	new connection socket 5, sbrk 0x558a82f74000
Sun May 28 15:56:46 2023	|	new connection socket 206, sbrk 0x558a82f74000

Running effectiveness test for 1 clients
Effectiveness with 200 milliseconds to sleep: 0
Effectiveness with 400 milliseconds to sleep: 0
Effectiveness with 600 milliseconds to sleep: 1
Effectiveness with 800 milliseconds to sleep: 2
Effectiveness with 1000 milliseconds to sleep: 2

Running effectiveness test for 11 clients
Effectiveness with 200 milliseconds to sleep: 0
Effectiveness with 400 milliseconds to sleep: 0
Effectiveness with 600 milliseconds to sleep: 1
Effectiveness with 800 milliseconds to sleep: 1
Effectiveness with 1000 milliseconds to sleep: 2

Running effectiveness test for 21 clients
Effectiveness with 200 milliseconds to sleep: 0
Effectiveness with 400 milliseconds to sleep: 0
Effectiveness with 600 milliseconds to sleep: 1
Effectiveness with 800 milliseconds to sleep: 2
Effectiveness with 1000 milliseconds to sleep: 3

Running effectiveness test for 31 clients
Effectiveness with 200 milliseconds to sleep: -1
Effectiveness with 400 milliseconds to sleep: -1
Effectiveness with 600 milliseconds to sleep: 0
Effectiveness with 800 milliseconds to sleep: 1
Effectiveness with 1000 milliseconds to sleep: 2

Running effectiveness test for 41 clients
Effectiveness with 200 milliseconds to sleep: -1
Effectiveness with 400 milliseconds to sleep: -1
Effectiveness with 600 milliseconds to sleep: 0
Effectiveness with 800 milliseconds to sleep: 1
Effectiveness with 1000 milliseconds to sleep: 2

Running effectiveness test for 51 clients
Effectiveness with 200 milliseconds to sleep: -1
Effectiveness with 400 milliseconds to sleep: 0
Effectiveness with 600 milliseconds to sleep: 0
Effectiveness with 800 milliseconds to sleep: 1
Effectiveness with 1000 milliseconds to sleep: 2

Running effectiveness test for 61 clients
Effectiveness with 200 milliseconds to sleep: -1
Effectiveness with 400 milliseconds to sleep: 0
Effectiveness with 600 milliseconds to sleep: 0
Effectiveness with 800 milliseconds to sleep: 1
Effectiveness with 1000 milliseconds to sleep: 2

Running effectiveness test for 71 clients
Effectiveness with 200 milliseconds to sleep: 0
Effectiveness with 400 milliseconds to sleep: 0
Effectiveness with 600 milliseconds to sleep: 1
Effectiveness with 800 milliseconds to sleep: 1
Effectiveness with 1000 milliseconds to sleep: 2

Running effectiveness test for 81 clients
Effectiveness with 200 milliseconds to sleep: -2
Effectiveness with 400 milliseconds to sleep: -2
Effectiveness with 600 milliseconds to sleep: -1
Effectiveness with 800 milliseconds to sleep: 0
Effectiveness with 1000 milliseconds to sleep: 1

Running effectiveness test for 91 clients
Effectiveness with 200 milliseconds to sleep: -2
Effectiveness with 400 milliseconds to sleep: -1
Effectiveness with 600 milliseconds to sleep: -1
Effectiveness with 800 milliseconds to sleep: 0
Effectiveness with 1000 milliseconds to sleep: 1


```


Сурков Денис Дмитриевич, МЕН-300801 (ФТ-301), 2023.
