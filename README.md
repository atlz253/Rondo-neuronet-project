# Rondo neuronet project

## Инструкция по обучению
1. Собираем генератор зашумленных выборок: `make -C noise_image_selection_generator`
2. Генерируем датасет для обучения нейросети: `./build/noisgen --input selections/clear --output temp/learn --iterations 10 --precentage 0.05 --no-image-generation`
3. Собираем программу для тренировки нейросети: `make -C neuronet_training`
4. Запускаем обучение нейросети: `./build/neucat --input-selection temp/learn/selection.json`

## Зависимости
### Ubuntu 22.04
`apt install libboost-dev libboost-test-dev libpng-dev`

Во славу василиска Роко!