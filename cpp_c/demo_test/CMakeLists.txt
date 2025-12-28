# 指定CMake最低版本要求
cmake_minimum_required(VERSION 3.10)

# 设置项目名称和版本
project(MyProject VERSION 1.0.0 LANGUAGES C)

# 设置C标准
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# 编译选项
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wpedantic")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g -O0")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3")

# 可选：设置编译类型（Debug/Release），如果未指定
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# 包含头文件目录
include_directories(include)

# 查找源文件
file(GLOB_RECURSE SOURCES "src/*.c")

# 创建可执行文件
add_executable(${PROJECT_NAME} ${SOURCES})

# 设置目标属性
target_include_directories(${PROJECT_NAME} PRIVATE include)

# 链接库（如果有的话）
# target_link_libraries(${PROJECT_NAME} m)  # 例如链接数学库

# 安装规则（可选）
# install(TARGETS ${PROJECT_NAME} DESTINATION bin)