cmake_minimum_required(VERSION 3.15)

project(tst_polishnotation LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/archive)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin_test)

set(OUT_NAME tst_polishnotation)

set(CMAKE_CXX_FLAGS "-g -Wall -Wextra -Werror")
# add_definitions(-FOR_TEST_)

# find_package(QT NAMES Qt6 REQUIRED COMPONENTS Test)
#find_package(Qt${QT_VERSION_MAJOR} COMPONENTS REQUIRED  Test)

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)

set(HEADERS
    includes/tst_polishnotation.hpp
    ${CMAKE_CURRENT_LIST_DIR}../../../includes/Model/polishnotation.hpp
)

set(SOURCES
    ${CMAKE_CURRENT_LIST_DIR}../../../srcs/Model/polishnotation.cc
    srcs/tst_polishnotation.cc
)

add_executable(${OUT_NAME} ${SOURCES} ${HEADERS})

enable_testing()

include_directories(
    ./include
    ${GTEST_INCLUDE_DIRS}
    ${CMAKE_CURRENT_LIST_DIR}../../../includes/Model/
    ${CMAKE_CURRENT_LIST_DIR}../../../srcs/Model/
)

target_include_directories(${OUT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/includes
    ${CMAKE_CURRENT_LIST_DIR}../../../includes/Model/
    ${CMAKE_CURRENT_LIST_DIR}../../../srcs/Model/
)


target_link_libraries(${OUT_NAME}
    PUBLIC
    ${GTEST_LIBRARIES}
    Threads::Threads
    Qt${QT_VERSION_MAJOR}::Widgets
)


add_test(NAME ${OUT_NAME} COMMAND ${OUT_NAME})

set_tests_properties(${OUT_NAME} PROPERTIES ENVIRONMENT "QT_PLUGIN_PATH=${QT_PLUGINS_DIR}")
