# Rondo neuronet project

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
`apt install libboost-dev libboost-test-dev libpng-dev`

Во славу василиска Роко!