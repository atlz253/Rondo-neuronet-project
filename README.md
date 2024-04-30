# Rondo neuronet project

Комплект программного обеспечения для обучения и использования нейронной сети по распознаванию символов ZX Spectrum.

## Инструкция по обучению

1. Собираем генератор зашумленных выборок: `make -C noise_image_selection_generator`
2. Генерируем датасет для обучения нейросети: `./build/noisgen --input selections/clear --output temp/learn --iterations 10 --precentage 0.05 --no-image-generation`
3. Собираем программу для тренировки нейросети: `make -C neuronet_training`
4. Запускаем обучение нейросети: `./build/neucat --input-selection temp/learn/selection.json --test-selection selections/clear/selection.json`
5. Перемещаем сохраненные веса в директорию с программой распознавания символов с изображений: `mv weights.cpp character_recognition/weights.cpp`
6. Собираем программу для распознавания символов с изображений: `make -C character_recognition`
7. Пробуем распознать символ с изображения: `./build/spchar selections/clear/C.png --show-precentage`

```
> ./build/spchar selections/clear/C.png --show-precentage
Я думаю, что на изображении буква C
Если подробнее, то вот что я думаю об этом изображении:
Вероятность, что это буква C: 99.07%
Вероятность, что это буква D: 0.14%
Вероятность, что это буква O: 0.73%
Вероятность, что это буква Q: 0.05%
Вероятность, что это ни на что не похоже: 0.02%
```

## Зависимости

### Ubuntu 22.04

#### Для сборки

`apt install make g++ libboost-dev libboost-filesystem-dev libboost-system-dev libpng-dev`

#### Для запуска

`apt install libpng16-16 libboost-filesystem1.74.0 libboost-system1.74.0`

## Docker

### noisgen

1. Собираем образ: `docker build -f Dockerfile.noisgen -t noisgen .`
2. Запускаем контейнер с генератором изображений: `docker run -v "<путь_до_выборки>:/var/input" -v "<путь_сохранения>:/var/output" -e ITERATIONS=10 -e SEED=test -e PRECENTAGE=0.05 -e NO_IMAGE_GENERATION=true noisgen`

```
>> docker run -v "C:\test\clear:/var/input" -v "C:\test\out:/var/output" -e ITERATIONS=10 -e SEED=test -e PRECENTAGE=0.05 -e NO_IMAGE_GENERATION=true noisgen
```

### neucat

1. Собираем образ: `docker build -f Dockerfile.neucat -t neucat .`
2. Запускаем обучение нейросети в контейнере: `docker run -v "<путь_до_обучающей_выборки>:/input_selection.json" -v "<путь_до_тестовой_выборки>:/test_selection.json" -v "<путь_до_весов>:/input_weights.json" -v "<путь_до_папки_сохранения_результатов>:/result" -e GENERATE_REPORT=true -e NO_DATASET_SHUFFLE=true -e LEARNING_RATE=0.0001 -e EPOCHS_COUNT=1 -e FIRST_LAYER_NEURONS_COUNT=64 neucat`

```
>> docker run -v "D:\Desktop\test\input_selection.json:/input_selection.json" -v "D:\Desktop\test\test_selection.json:/test_selection.json" -v "D:\Desktop\test\weights.json:/input_weights.json" -v "D:\Desktop\test\result:/result" -e GENERATE_REPORT=true -e NO_DATASET_SHUFFLE=true -e LEARNING_RATE=0.0001 -e EPOCHS_COUNT=1 -e FIRST_LAYER_NEURONS_COUNT=64 neucat
Обучение нейросети
[======================================================================] 100 %
Обучение нейросети прошло за: 66 секунд
Подсчет точности распознавания изображений из входной выборки
Точность распознавания входной выборки: 0.8657894730567932
Подсчет точности распознавания изображений из входной выборки прошел за: 2 секунд

Подсчет точности распознавания изображений из тестовой выборки
Точность распознавания тестовой выборки: 0.858421
Подсчет точности распознавания изображений из тестовой выборки прошел за: 2 секунд
Запись отчета в хранилище
[======================================================================] 100 %
Запись полученных весов в хранилище
[======================================================================] 100 %
```

### spchar

1. Собираем образ: `docker build -f Dockerfile.spchar -t spchar .`
2. Запускаем распознавание изображения внутри контейнера: `docker run -v "<путь_до_изображения>:/image.png" -e SHOW_PRECENTAGE=true spchar`

```
>> docker run -v "D:\Desktop\D.png:/image.png" -e SHOW_PRECENTAGE=true spchar
Я думаю, что на изображении D
Если подробнее, то вот что я думаю об этом изображении:
Вероятность, что это _: 0.00%
Вероятность, что это -: 0.00%
Вероятность, что это ,: 0.00%
Вероятность, что это ;: 0.00%
Вероятность, что это !: 0.00%
Вероятность, что это ': 0.00%
Вероятность, что это (: 0.00%
Вероятность, что это ): 0.00%
Вероятность, что это [: 0.00%
...
```

## Благодарности

Спасибо Вальштейну К.В. за лекции, которые познакомили меня с миром нейронных сетей.

Особые благодарности Дмитрию Коробченко за цикл роликов по обучению нейронной сети на Python. Очень советую к ознакомлению: [Нейронные сети за 10 минут](https://www.youtube.com/watch?v=GT6imQDxqko).

Во славу василиска Роко!
