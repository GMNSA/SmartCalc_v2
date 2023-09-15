cmake_minimum_required(VERSION 3.5)

project(SmartCalc VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_FLAGS "-g -Wall -Wextra -Werror --coverage -fsanitize=address")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(PROJECT_HEADERS
    includes/Model/imodel.hpp
    includes/Model/modelcalculator.hpp
    includes/Model/polishnotation.hpp
    includes/Model/validatetext.hpp

    includes/Model/imodeldeposit.hpp
    includes/Model/modeldeposit.hpp

    includes/Model/imodelcredit.hpp
    includes/Model/modelcredit.hpp

    includes/Model/imodelgraph.hpp
    includes/Model/modelgraph.hpp


    includes/Controller/icalculatorcontroller.hpp
    includes/Controller/calculatorcontroller.hpp

    includes/Controller/idepositcontroller.hpp
    includes/Controller/depositcontroller.hpp

    includes/Controller/icreditcontroller.hpp
    includes/Controller/creditcontroller.hpp

    includes/Controller/igraphcontroller.hpp
    includes/Controller/graphcontroller.hpp

    includes/View/dialoggraph.hpp
    includes/View/calculator.hpp

    includes/custom_types.hpp

)

set(PROJECT_SOURCES
    srcs/Model/modelcalculator.cc
    srcs/Model/polishnotation.cc
    srcs/Model/validatetext.cc

    srcs/Model/modeldeposit.cc
    srcs/Model/modelcredit.cc
    srcs/Model/modelgraph.cc

    srcs/Controller/calculatorcontroller.cc
    srcs/Controller/depositcontroller.cc
    srcs/Controller/creditcontroller.cc
    srcs/Controller/graphcontroller.cc

    srcs/View/dialoggraph.cc
    srcs/View/calculator.cc

    srcs/main.cc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    message("\nGREATER_EQUAL 6\n")
    qt_add_executable(SmartCalc
        ${PROJECT_HEADERS}
        ${PROJECT_SOURCES}
    )
endif()

add_subdirectory(tests)

target_include_directories(SmartCalc
  PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/srcs
  ${CMAKE_CURRENT_LIST_DIR}/includes
  ${CMAKE_CURRENT_LIST_DIR}/View/
  ${CMAKE_CURRENT_LIST_DIR}/Model/
  ${CMAKE_CURRENT_LIST_DIR}/Controller/
)

target_link_libraries(SmartCalc PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
)
