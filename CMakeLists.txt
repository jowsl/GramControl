cmake_minimum_required(VERSION 3.5)
project(GramControl VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql)

include_directories(includes)
include_directories(src)

# =========================================================================
# ALVO 1: O Aplicativo Grafico (Interface Qt)
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
    src/AtualizarPrecoDialog.cpp
    src/AtualizarPrecoDialog.hpp
    src/PrecoBase.cpp
    src/PrecoBase.hpp
    src/PrecoBaseController.cpp
    src/PrecoBaseController.hpp
    src/PrecoBaseDAO.cpp
    src/PrecoBaseDAO.hpp
    src/Orcamento.cpp
    src/Orcamento.hpp
    src/OrcamentoController.cpp
    src/OrcamentoController.hpp
    src/ui/OrcamentoDialog.cpp
    src/ui/OrcamentoDialog.h
    src/moc_AtualizarPrecoDialog.cpp
    src/ui/ui_AtualizarPreco.h
    src/Cliente.cpp
    src/Cliente.hpp
    src/ClienteDAO.cpp
    src/ClienteDAO.hpp
    src/ClienteController.cpp
    src/ClienteController.hpp
    src/CadastrarClienteDialog.cpp
    src/CadastrarClienteDialog.hpp
)

add_executable(GramControl ${PROJECT_SOURCES})

target_link_libraries(GramControl PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Sql
)

target_compile_definitions(GramControl PRIVATE
    PROJECT_ROOT_DIR="${CMAKE_CURRENT_SOURCE_DIR}"
)

# =========================================================================
# ALVO 2: A Bateria de Testes Unitarios do Grupo (Terminal - Sem Qt)
# =========================================================================
set(TEST_SOURCES
    tests/unit/main.cpp
    tests/unit/test_login_reg.cpp
    tests/unit/test_login_reg.h
    tests/unit/test_persistencia.cpp
    tests/unit/test_PrecoBase.cpp
    tests/unit/test_Orcamento.cpp
    tests/unit/test_Cliente.cpp
    tests/unit/test_persistencia_cliente.cpp
    src/GramControl.cpp
    src/PrecoBase.cpp
    src/PrecoBaseController.cpp
    src/PrecoBaseDAO.cpp
    src/Orcamento.cpp
    src/OrcamentoController.cpp
    src/Cliente.cpp
    src/ClienteDAO.cpp
)

add_executable(TestesUnitarios ${TEST_SOURCES})

target_link_libraries(TestesUnitarios PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Sql
)

target_compile_definitions(TestesUnitarios PRIVATE
    PROJECT_ROOT_DIR="${CMAKE_CURRENT_SOURCE_DIR}"
)
