cmake_minimum_required(VERSION 3.16)

project(Restaurant VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()

qt_add_executable(Restaurant
        main/main.cpp
        view/DisplayInterfacesClass.cpp
        view/DisplayInterfacesClass.h
        view/view.cpp
        view/view.h
        view/view.ui
)

target_link_libraries(Restaurant PRIVATE Qt6::Widgets)

set_target_properties(Restaurant PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)