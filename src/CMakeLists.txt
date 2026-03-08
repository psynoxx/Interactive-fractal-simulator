file(GLOB SRC_FILES
    LIST_DIRECTORIES true
    CMAKE_CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)
message(STATUS "SRC_FILES:")
foreach(f IN LISTS SRC_FILES)
    message(STATUS "  ${f}")
endforeach()

add_executable(example_exe ${SRC_FILES})
target_link_libraries(example_exe PRIVATE ImGui-SFML::ImGui-SFML)
