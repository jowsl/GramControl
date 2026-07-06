cmake_minimum_required(VERSION 3.5)
project(GramControl VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

include_directories(includes)

# =========================================================================
# ALVO 1: O Aplicativo Gráfico (Interface Qt)
# =========================================================================
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

add_executable(GramControl ${PROJECT_SOURCES})
target_link_libraries(GramControl PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_compile_definitions(GramControl PRIVATE PROJECT_ROOT_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

# =========================================================================
# ALVO 2: A Bateria de Testes Unitários do Grupo (Terminal - Sem Qt)
# =========================================================================
set(TEST_SOURCES
    tests/unit/main.cpp
    tests/unit/test_login_reg.cpp
    tests/unit/test_login_reg.h
    src/GramControl.cpp
)

add_executable(TestesUnitarios ${TEST_SOURCES})
target_compile_definitions(TestesUnitarios PRIVATE PROJECT_ROOT_DIR="${CMAKE_CURRENT_SOURCE_DIR}")