# ZX Spectrum character recognition (spchar)

## Пример работы

```
> ./build/spchar selections/clear/C.png --show-precentage
Я думаю, что на изображении буква C
Если подробнее, то вот что я думаю об этом изображении
Вероятность, что это буква C: 99.07%
Вероятность, что это буква D: 0.14%
Вероятность, что это буква O: 0.73%
Вероятность, что это буква Q: 0.05%
Вероятность, что это ни на что не похоже: 0.02%
```

## Параметры

| Параметр          | Входные данные | Значение по-умолчанию | Описание                              |
| ----------------- | -------------- | --------------------- | ------------------------------------- |
| --show-precentage | bool           | false                 | Показать процент распознавания образа |

## Сборка .deb пакета

```
>> make build_deb
mkdir -p ../build
g++ main.cpp ../common/image/image.cpp weights.cpp -l png -o ../build/spchar
mkdir -p package/usr/bin
cp ../build/spchar package/usr/bin/spchar
mkdir -p ../packages
dpkg-deb --build ./package ../packages/spchar.deb
dpkg-deb: building package 'spchar' in '../packages/spchar.deb'.

>> sudo dpkg -i ../packages/spchar.deb
Selecting previously unselected package spchar.
(Reading database ... 205917 files and directories currently installed.)
Preparing to unpack ../packages/spchar.deb ...
Unpacking spchar (1.0) ...
Setting up spchar (1.0) ...

>> spchar ../selections/clear/O.png
Я думаю, что на изображении O
```
