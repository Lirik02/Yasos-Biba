cmake_minimum_required(VERSION 3.20.2)
project(project_main_part)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH ~/Qt/6.3.0/gcc_64)

find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)

add_executable(project_main_part main.cpp view/view.cpp view/view.h controller/location_controller.cpp controller/location_controller.h controller/player_controller.cpp controller/player_controller.h model/location_model.cpp model/location_model.h view/scene.cpp view/scene.h model/character_model.cpp model/character_model.h)
target_link_libraries(project_main_part Qt6::Core Qt6::Gui Qt6::Widgets)