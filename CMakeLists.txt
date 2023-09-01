cmake_minimum_required(VERSION 3.5)

# project(SmartCalc VERSION 0.1 LANGUAGES CXX)
project(SmartCalc LANGUAGES CXX C)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_FLAGS "-g -Wall -Wextra -Werror")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(PROJECT_HEADERS
    includes/calculationsmartcalc.hpp
    includes/creditcalculator.hpp
    includes/View/dialoggraph.hpp
    includes/View/calculator.hpp
    code_c/s21_credit_calc.h
    code_c/s21_smart_calc.h
    code_c/s21_stack.h
)

set(PROJECT_SOURCES
    srcs/calculationsmartcalc.cc
    srcs/creditcalculator.cc
    srcs/View/dialoggraph.cc
    srcs/View/calculator.cc
    srcs/main.cc
    srcs/View/dialoggraph.ui
    srcs/View/calculator.ui
    code_c/s21_credit_calc.c
    code_c/s21_smart_calc.c
    code_c/s21_stack.c
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    message("\nGREATER_EQUAL 6\n")
    qt_add_executable(SmartCalc
        ${PROJECT_HEADERS}
        ${PROJECT_SOURCES}
    )
else()
    add_executable(SmartCalc
        ${PROJECT_SOURCES}
        ${PROJECT_HEADERS}
        )
endif()

# add_subdirectory(lib)
add_subdirectory(tests)

target_include_directories(SmartCalc
  PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/srcs
  ${CMAKE_CURRENT_LIST_DIR}/includes
  ${CMAKE_CURRENT_LIST_DIR}/View/
  ${CMAKE_CURRENT_LIST_DIR}/Model/
  ${CMAKE_CURRENT_LIST_DIR}/Controller/
    ${CMAKE_CURRENT_LIST_DIR}/code_c/
    ${CMAKE_CURRENT_LIST_DIR}/code_c/includes
    ${CMAKE_CURRENT_LIST_DIR}/code_c/srcs
)

target_link_libraries(SmartCalc PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
)
