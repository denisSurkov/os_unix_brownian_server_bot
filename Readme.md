# Server working with poll

Задача 4 из [задачника](https://eykuklin.github.io/OS-UNIX/).

Однопоточный сервер. Принимает числа, складывает с общим числом и отправляет ответ.
Для работы с несколькими клиентами используется `poll`.

```txt
usage: ./os_unix_brownian_server_bot /path/to/config/
usage: ./os_unix_brownian_client /path/to/config/ -t time_to_sleep
```

## Как запустить "тесты":
0. `cmake .` - создает `Makefile`. В репозитории уже лежит необходимый `Makefile`, так требует формат выполнения задач.
1. `chmod +x runme.sh`
2. `./runme.sh`


Сурков Денис Дмитриевич, МЕН-300801 (ФТ-301), 2023.
