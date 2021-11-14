# CMakeList.txt: проект CMake для calculator; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)             # Стандарт C++
set(CMAKE_CXX_STANDARD_REQUIRED ON)    # Обязательность установки указанного стандарта (если OFF (по умолчанию), то воспринимается как совет)

add_subdirectory("ln")
add_subdirectory("pow")
add_subdirectory("trigonometry")

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
