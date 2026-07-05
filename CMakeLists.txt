cmake_minimum_required(VERSION 3.5)
project(GramControl VERSION 0.1 LANGUAGES CXX)

# Liga o pré-processador MOC automaticamente
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Busca as bibliotecas de interface gráfica do Qt
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# Avisa o compilador onde achar o seu json.hpp
include_directories(includes)

# Lista apenas os arquivos do SEU escopo da Sprint 1
set(PROJECT_SOURCES
    src/main.cpp
    src/GramControl.cpp
    src/GramControl.h
    src/User.h
    src/ui/LoginWindow.cpp
    src/ui/LoginWindow.h
    src/ui/AdminWindow.cpp
    src/ui/AdminWindow.h
)

# Cria o executável
add_executable(GramControl ${PROJECT_SOURCES})

# Linka com o Qt Widgets
target_link_libraries(GramControl PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Passa o caminho absoluto da pasta do seu projeto direto para o código C++
target_compile_definitions(GramControl PRIVATE PROJECT_ROOT_DIR="${CMAKE_CURRENT_SOURCE_DIR}")