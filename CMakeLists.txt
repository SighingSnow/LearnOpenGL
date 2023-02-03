cmake_minimum_required(VERSION 3.15)
project(LearnOpenGL)

set(CMAKE_CXX_STANDARD 11)

option(IMPORT_ASSIMP OFF)
option(DEPTH_TEST_EXE ON)

#
option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/3rd_party/glfw)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/3rd_party/glfw/include)
LIST(APPEND LIBS glfw ${GLFW_LIBRARIES})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/3rd_party/glad/include)
set(GLAD_SRC ${CMAKE_CURRENT_SOURCE_DIR}/3rd_party/glad/src/glad.c)
if(NOT WIN32)
    LIST(APPEND LIBS dl)
endif()

include_directories(3rd_party/glm)

if(IMPORT_ASSIMP)
    add_subdirectory(3rd_party/assimp)
endif()

# 
aux_source_directory(DepthTest/. {DepthTestSrc})

if(DEPTH_TEST_EXE) 
    add_executable(depthtest {DepthTestSrc})
    target_link_libraries(depthtest {LIBS})
endif()
