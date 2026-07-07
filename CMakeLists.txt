cmake_minimum_required(VERSION 3.5)
project(GramControl VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql)

set(PROJETC_SOURCES
    src/main.cpp
    src/Cliente.cpp
    src/Cliente.hpp
    src/ClienteDAO.cpp
    src/ClienteDAO.hpp
    src/ClienteController.hpp
    src/ClienteController.cpp
    src/CadastrarClienteDialog.cpp
    src/CadastrarClienteDialog.hpp
)

add_executable(GramControl ${PROJETC_SOURCES})
target_link_libraries(GramControl PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Sql)

add_executable(TestesPersistencia
    tests/unit/test_persistencia_cliente.cpp
    src/Cliente.cpp
    src/ClienteDAO.cpp
)
target_link_libraries(TestesPersistencia PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Sql)

add_executable(TestesUnitarios
    tests/unit/test_Cliente.cpp
    src/Cliente.cpp
)
target_link_libraries(TestesUnitarios PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
