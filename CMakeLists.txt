cmake_minimum_required(VERSION 3.5.0)
project(Crest)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")
set(src_dir ${PROJECT_SOURCE_DIR}/src)
set(libs_dir ${PROJECT_SOURCE_DIR}/libs)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_BINARY_DIR}/Debug)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_BINARY_DIR}/Release)

file(GLOB src_files
  ${src_dir}/*.cpp
  ${src_dir}/vendor/*/*.cpp
  ${src_dir}/demos/*.cpp
  ${src_dir}/demos/*/*.cpp)

file(GLOB header_files
  ${src_dir}/*.h
  ${src_dir}/vendor/*/*.h
  ${src_dir}/demos/*.h
  ${src_dir}/demos/*/*.h)

add_executable(${PROJECT_NAME} ${src_files} ${header_files})

# Headers
target_include_directories(${PROJECT_NAME} PRIVATE
  ${src_dir}
  ${src_dir}/vendor/imgui
  ${src_dir}/demos
  ${src_dir}/demos/DemoClearColor
  ${src_dir}/demos/DemoTexture2D
  ${src_dir}/demos/DemoCube
  ${src_dir}/demos/DemoModelLoader)

# Dependencies
## GLAD
add_subdirectory(${libs_dir}/glad)
target_link_libraries(${PROJECT_NAME} PRIVATE glad)

## GLFW
add_subdirectory(${libs_dir}/glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)

## GLM
add_subdirectory(${libs_dir}/glm)
target_link_libraries(${PROJECT_NAME} PRIVATE glm)

## IMGUI
add_subdirectory(${libs_dir}/imgui)
target_link_libraries(${PROJECT_NAME} PRIVATE dear_imgui)

## STB_IMAGE
add_subdirectory(${libs_dir}/stb_image)
target_link_libraries(${PROJECT_NAME} PRIVATE stb_image)

## TINY_OBJ_LOADER
add_subdirectory(${libs_dir}/tinyobjloader)
target_link_libraries(${PROJECT_NAME} PRIVATE tinyobjloader)

# Create symlink for resources in build folder after each build. Warning: Probably not working on windows
add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E create_symlink
        ${PROJECT_SOURCE_DIR}/res/
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/res)

# Create symlink for shaders in build folder after each build. Warning: Probably not working on windows
add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E create_symlink
        ${PROJECT_SOURCE_DIR}/shaders/
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/shaders)
