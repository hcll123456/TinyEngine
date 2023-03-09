# CMakeList.txt: TinyEngine 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)
project(TinyEngine)

include_directories(${CMAKE_SOURCE_DIR}/OpenGL/include)

link_directories(${CMAKE_SOURCE_DIR}/OpenGL/Libs)



# 将源代码添加到此项目的可执行文件。
add_executable (TinyEngine 
    "TinyEngine.cpp" 
    "TinyEngine.h"
    "glad.c"
)


target_link_libraries(TinyEngine
    ${OPENGL_LIBRARIES}
    glfw3
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET TinyEngine PROPERTY CXX_STANDARD 20)
endif()

# TODO: 如有需要，请添加测试并安装目标。
