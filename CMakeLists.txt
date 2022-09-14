cmake_minimum_required (VERSION 3.10)
project(paramfs)

option(WITHOUT_TEST "disables unit test" OFF)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(FUSE3 REQUIRED fuse3)


add_library(libparamfs STATIC
    src/paramfs/paramfs.cpp
    src/paramfs/status.cpp
    src/paramfs/param_error.cpp
    src/paramfs/registry.cpp
    src/paramfs/filesystem/filesystem.cpp
    src/paramfs/filesystem/directory.cpp
    src/paramfs/filesystem/static_file.cpp
)

set_target_properties(libparamfs PROPERTIES OUTPUT_NAME "paramfs")


target_include_directories(libparamfs PRIVATE
    src
    include
    ${FUSE3_INCLUDE_DIRS}
)

target_link_libraries(libparamfs PUBLIC
    ${FUSE3_LIBRARIES}
)

target_compile_options(libparamfs PUBLIC
    ${FUSE3_CFLAGS}
    ${FUSE3_CFLAGS_OTHER}
)

add_executable(paramfs
    src/app/main.cpp
    src/app/sample_provider.cpp
)

target_link_libraries(paramfs PRIVATE libparamfs)
target_include_directories(paramfs PRIVATE src/app include)

if(NOT ${WITHOUT_TEST})

pkg_check_modules(GMOCK REQUIRED gmock)
pkg_check_modules(GTEST REQUIRED gtest_main)

add_executable(alltests
    test-src/paramfs/test_status.cpp
)

target_include_directories(alltests PRIVATE
    src
    include
    ${GMOCK_INCLUDE_DIRS}
    ${GTEST_INCLUDE_DIRS}
)

target_link_libraries(alltests PRIVATE
    libparamfs
    ${GMOCK_LIBRARIES}
    ${GTEST_LIBRARIES}
)

target_compile_options(alltests PRIVATE
    ${GMOCK_CFLAGS}
    ${GMOCK_CFLAGS_OTHER}
    ${GTEST_CFLAGS}
    ${GTEST_CFLAGS_OTHER}
)


endif()