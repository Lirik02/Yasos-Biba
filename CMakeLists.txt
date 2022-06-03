cmake_minimum_required(VERSION 3.21)
project(Roguelike)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


set(CMAKE_PREFIX_PATH ~/Qt/6.3.0/gcc_64)


find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)


add_executable(Roguelike
        model/bullet.cpp
        model/bullet.h
        model/sprite.cpp
        model/sprite.h

        view/customscene.cpp
        view/customscene.h
        view/widget.cpp
        view/widget.h

        controllers/target.cpp
        controllers/target.h
        controllers/hero.cpp
        controllers/hero.h

        main.cpp)

target_link_libraries(Roguelike Qt6::Core Qt6::Gui Qt6::Widgets)
