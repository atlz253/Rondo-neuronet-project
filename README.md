# Rondo neuronet project

## Инструкция по обучению
1. Собираем генератор зашумленных выборок: `make -C noise_image_selection_generator`
2. Генерируем датасет для обучения нейросети: `./build/noisgen --input selections/clear --output selections/learn --iterations 1000 --precentage 0.05 --no-image-generation`

## Зависимости
### Ubuntu 22.04
`apt install libboost-dev libboost-test-dev libpng-dev`

Во славу василиска Роко!