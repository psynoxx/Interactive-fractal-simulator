cmake_minimum_required(VERSION 3.15)
project(example
  LANGUAGES CXX
  VERSION 1.0
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


add_subdirectory(src)
add_subdirectory(third_party/SFML-3.0.2)

set(IMGUI_DIR ${imgui_SOURCE_DIR})
set(IMGUI_SFML_FIND_SFML OFF)
set(IMGUI_SFML_IMGUI_DEMO ON)
set(IMGUI_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/IMGUIBASE
)
set(SFML_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/SFML-3.0.2/cmake
)
add_subdirectory(third_party/IMGUI) # needs dearIMGUI dependencies and wont config



target_link_libraries(example_exe PRIVATE sfml-graphics)
#956 IGUI-SFML.cpp