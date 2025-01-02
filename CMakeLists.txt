cmake_minimum_required(VERSION 3.28)
project(my_hash_table)

set(CMAKE_C_STANDARD 11)

#set(CMAKE_CXX_STANDARD 14)

# 包含头文件目录
include_directories(src)

# 公共源文件列表
set(SRC_FILES
        src/hash_table.c
        src/hash_table.h
        src/prime.c
        src/prime.h
)

# 主程序
add_executable(my_hash_table
        ${SRC_FILES}
        src/main.c
)
#target_link_libraries(my_hash_table m)

# 功能测试程序
add_executable(functional_tests
        ${SRC_FILES}
        tests/test_functional.c
)
#target_link_libraries(functional_tests m)

# 性能测试程序
add_executable(performance_tests
        ${SRC_FILES}
        tests/test_performance.c
)
# 在 Linux 上添加数学库 (libm)
if(UNIX AND NOT APPLE)
	target_link_libraries(performance_tests m)
	target_link_libraries(my_hash_table m)
	target_link_libraries(functional_tests m)
elseif(WIN32)
    message(STATUS "Building on Windows, no need to link libm.")
endif()

# 设置 Debug 模式特定的选项
set(CMAKE_BUILD_TYPE Debug)
