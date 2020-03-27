cmake_minimum_required(VERSION 3.16)
project(screen_triangle)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/modules)
set(CMAKE_CXX_STANDARD 17)

find_package(Corrade CONFIG REQUIRED PluginManager Containers TestSuite)
find_package(Magnum CONFIG REQUIRED GL SceneGraph MeshTools Sdl2Application Shaders Primitives)

corrade_add_resource(st_Rcs resources.conf)
add_executable(screen_triangle
        main.cpp
        screen_triangle_shader.cpp
        screen_triangle_shader.hpp
        ${st_Rcs}
        )
target_link_libraries(screen_triangle
    PRIVATE
        Magnum::GL
        Magnum::Magnum
        Magnum::MeshTools
        Magnum::Application
        Magnum::Shaders)