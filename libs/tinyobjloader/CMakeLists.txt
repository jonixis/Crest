cmake_minimum_required(VERSION 3.5)
project(tinyobjloader)

add_library(tinyobjloader src/tiny_obj_loader.cc)
target_include_directories(tinyobjloader PUBLIC include/)
