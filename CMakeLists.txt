cmake_minimum_required(VERSION 3.20.2)
project(project_main_part)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "~/Qt/6.2.4/macos/lib/cmake")

find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)

add_executable(project_main_part
        main.cpp

        model/location_model.cpp
        model/location_model.h
        model/character_model.cpp
        model/character_model.h
        model/characteristics.cpp
        model/characteristics.h

        view/view.cpp
        view/view.h
        view/scene.cpp
        view/scene.h

        controller/location_controller.cpp
        controller/location_controller.h
        controller/player_controller.cpp
        controller/player_controller.h
        )
target_link_libraries(project_main_part Qt6::Core Qt6::Gui Qt6::Widgets)