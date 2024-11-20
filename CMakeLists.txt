cmake_minimum_required(VERSION 3.28)
project(PlateRecognizeSystem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

include_directories(gui)
include_directories(util)
include_directories("C:/msys64/ucrt64/include/opencv4")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRECTORIES})


add_executable(PlateRecognizeSystem
        main.cpp
        util/core.h
        gui/gui.h
        gui/AppWindow.cpp
        gui/AppWindow.h
)

target_link_libraries(PlateRecognizeSystem ${OpenCV_LIBS})
target_link_libraries(PlateRecognizeSystem
        Qt::Core
        Qt::Gui
        Qt::Widgets
)