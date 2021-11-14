# CMakeList.txt: проект CMake для calculator; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)             # Стандарт C++
set(CMAKE_CXX_STANDARD_REQUIRED ON)    # Обязательность установки указанного стандарта (если OFF (по умолчанию), то воспринимается как совет)

# Добавьте источник в исполняемый файл этого проекта.
add_executable (calculator "calculator.cpp" "calculator.h" "error.h" "operations/description_operator.h" "operations/operation.h" "token.h" "parser/parser.h" "scanner/scanner.h" "parser/parser.cpp" "scanner/scanner.cpp"  "eval/eval.h"  "calculation/calculation.h" "dllFunction/plugins_loader.h")

add_subdirectory(dllFunction)
# TODO: Добавьте тесты и целевые объекты, если это необходимо.
