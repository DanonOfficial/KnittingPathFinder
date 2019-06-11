cmake_minimum_required(VERSION 3.13)
project(KnittingPathFinder)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)
set(CMAKE_AUTOMOC ON)

add_executable(KnittingPathFinder src/main.cpp include/PathFinder.hpp src/PathFinder.cpp include/RenderArea.hpp src/RenderArea.cpp include/MainWidget.hpp src/MainWidget.cpp)

target_link_libraries(${PROJECT_NAME} Qt5::Core)
target_link_libraries(${PROJECT_NAME} Qt5::Gui)
target_link_libraries(${PROJECT_NAME} Qt5::Widgets)
