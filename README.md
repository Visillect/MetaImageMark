# ImgPrcBenchmark

Проект предоставляет набор инструментов для проведения бенчмарков и обработки полученных данных.

## Цель

Проект предназначен для удобного и быстрого количественного сравнения производительности реализаций различных операций
обработки изображений.

## Подключение к проекту devsubsystem

Создайте папку `prj.benchmark` в `devsubsystem`, склонируйте в эту папку репозиторий. Добавьте в конец файла
`devsubsystem/CmakeLists.txt` строчку `add_subdirectory(prj.benchmark)`.

## Инструменты

* [Готовые решения](benchmarks/README.md)
* [Генерация отчетов](data_processing/README.md)
* [Написание бенчмарков](benchmark_tools/README.md)
* [Примеры использования](demo/README.md)

## Готовые решения

Для некоторых библиотек и операций уже определены готовые наборы бенчмарков.

## Генерация отчетов

Генератор отчетов принимает на вход данные google/benchmark в формате json.

## Написание бенчмарков

В [benchmark_tools](benchmark_tools/README.md) содержатся инструменты для проведения бенчмарков. В первую очередь они
предназначены для сравнения различных библиотек, но также могут быть использованы и для бенчмарка отдельной библиотеки,
скомпилированной с различными параметрами.

## Примеры использования

В [demo](demo/README.md) описаны примеры использования инструментов для проведения бенчмарков и построения отчетов.

## Уменьшение шумов

Подробная информация о факторах, влияющих на шумы,
описана [тут](https://github.com/JuliaCI/BenchmarkTools.jl/blob/master/docs/src/linuxtips.md).

### Processor shielding

```bash
$ sudo apt-get install cpuset
$ sudo cset shield --cpu=0,1 --kthread=on
$ sudo cset shield --exec -- mybench --params
$ sudo cset shield --reset
```

### CPU frequency scaling

```bash
$ sudo cpupower frequency-set --governor performance
$ ./mybench
$ sudo cpupower frequency-set --governor powersave
```
