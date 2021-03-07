cmake_minimum_required(VERSION 3.5)
project(dear_imgui)

add_library(dear_imgui src/imgui.cpp src/imgui_draw.cpp src/imgui_demo.cpp src/imgui_widgets.cpp src/imgui_tables.cpp)
target_include_directories(dear_imgui PUBLIC include/)
