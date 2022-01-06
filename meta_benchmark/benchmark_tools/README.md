# ImgPrcBenchmark benchmark tools

Проект содержит набор утилит для написания бенчмарков и верификации.

## Представление изображений
В качестве внутреннего представления изображений используется представление библиотеки MinImg.
Поэтому для того, чтобы полноценно воспользоваться инструментами из данного проекта, сперва 
необходимо определить класс ```LibrarySuite```, с помощью которого происходит преобразование 
заголовков библиотеки.
```C++
class LibrarySuite {
public:
  /**
   * Creates new library image header from MinImg image.
   * The image data must not be copied.
   */
  std::unique_ptr<LibImg> HeaderConvert(const MinImg& image) {
    // Your code goes here
  }

  /**
   * Creates new MinImg header of image.
   * The image data must not be copied.
   */
  std::unique_ptr<MinImg> HeaderConvert(const LibImg& image) {
    // Your code goes here
  }
};
```

## Генераторы изображений
`generators.h`

* Рандомные изображения
* Измененные в размере изображения

## Генерирование размеров изображений
`custom_arguments.h`

* В виде сетки размеров `(w_i, h_j)` по геометрической прогрессии
* В виде последовательности размеров `(w_i, h_i)` по геометрической прогрессии

## Сравнение изображений
`checkers.h`

* Поэлементное сравнение двух изображений с заданной eps

## Запуск бенчмарков
`benchmark.h`

В проекте операции разбиты на несколько групп:
* Бинарные операции:
    * Без параметра: `(FirstImage, SecondImage) -> OutputImage`
    * С параметром: `(FirstImage, SecondImage, Param) -> OutputImage`
* Унарные операции:
    * Без параметра: `Image -> OutputImage`
    * С параметром: `(Image, Param) -> OutputImage`
