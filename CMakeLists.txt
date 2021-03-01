cmake_minimum_required(VERSION 3.5.0)
project(Crest)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")
set(src_dir ${PROJECT_SOURCE_DIR}/src)
set(lib_dir ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_BINARY_DIR}/Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_BINARY_DIR}/Release)

file(GLOB src_files "${src_dir}/*.cpp")
file(GLOB vendor_files "${src_dir}/vendor/*.cpp")

add_executable(${PROJECT_NAME} ${src_files} ${vendor_files})

# Headers
target_include_directories(${PROJECT_NAME} PRIVATE ${src_dir} ${src_dir}/vendor)

# Dependencies

## GLAD
add_subdirectory(${lib_dir}/glad)
target_link_libraries(${PROJECT_NAME} PRIVATE glad)

## GLFW
add_subdirectory(${lib_dir}/glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)

# GLM
add_subdirectory(${lib_dir}/glm)
target_link_libraries(${PROJECT_NAME} PRIVATE glm)
