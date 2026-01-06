# CppFeature 子目录 CMakeLists.txt

# C++17 特性示例
add_executable(cpp17_features
    cpp17_features.cpp
)

# 设置C++17标准
target_compile_features(cpp17_features PRIVATE cxx_std_17)

# 添加pthread支持（用于std::thread等）
find_package(Threads REQUIRED)
target_link_libraries(cpp17_features PRIVATE Threads::Threads)

# GCC 8/9 需要手动链接 stdc++fs
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 9.1)
    target_link_libraries(cpp17_features PRIVATE stdc++fs)
endif()

