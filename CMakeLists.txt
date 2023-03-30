cmake_minimum_required(VERSION 3.15)
project(LearnOpenGL)

set(CMAKE_CXX_STANDARD 11)

option(BLEND OFF)
option(IMPORT_ASSIMP OFF)
option(PHONG OFF)
option(BLIN_PHONG OFF)
option(FRAME_BUFFER OFF)
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

if(PHONG) 
    add_executable(phong ${CMAKE_CURRENT_SOURCE_DIR}/light/phong.cpp ${GLAD_SRC})
    target_link_libraries(phong ${LIBS})
endif()

if(BLIN_PHONG) 
    add_executable(blin_phong ${CMAKE_CURRENT_SOURCE_DIR}/light/blin_phong.cpp ${GLAD_SRC})
    target_link_libraries(blin_phong ${LIBS})
endif()

if(GOURAUD) 
    add_executable(gouraud ${CMAKE_CURRENT_SOURCE_DIR}/light/gouraud.cpp ${GLAD_SRC})
    target_link_libraries(gouraud ${LIBS})
endif()

if(BLEND)
    add_executable(blend ${CMAKE_CURRENT_SOURCE_DIR}/opengl/blend.cpp ${GLAD_SRC})
    target_link_libraries(blend ${LIBS})
endif()

if(FRAME_BUFFER)
    add_executable(frame ${CMAKE_CURRENT_SOURCE_DIR}/opengl/frame.cpp ${GLAD_SRC})
    target_link_libraries(frame ${LIBS})
endif()