cmake_minimum_required(VERSION 3.15)
project(LearnOpenGL)

set(CMAKE_CXX_STANDARD 11)

option(IMPORT_ASSIMP OFF)
option(PHONN ON)
option(BLIN_PHONN OFF)

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

if(PHONN) 
    add_executable(phonn ${CMAKE_CURRENT_SOURCE_DIR}/Light/phonn.cpp ${GLAD_SRC})
    target_link_libraries(phonn ${LIBS})
endif()

if(BLIN_PHONN) 
    add_executable(blin_phonn ${CMAKE_CURRENT_SOURCE_DIR}/blin_phonn.cpp ${GLAD_SRC})
    target_link_libraries(blin_phonn ${LIBS})
endif()