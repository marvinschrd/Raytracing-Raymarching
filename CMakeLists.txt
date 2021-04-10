cmake_minimum_required(VERSION 3.19 FATAL_ERROR)
project(CUDA_RayMarching LANGUAGES CXX CUDA)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE CUDA_RayMarching_SRC include/*.h src/*.cpp src/*.cu)

add_library(COMMON STATIC ${CUDA_RayMarching_SRC})

set(GOOGLE_TEST_DIR "externals/gtest")
set(BUILD_GMOCK OFF CACHE INTERNAL "")
set(INSTALL_GTEST OFF CACHE INTERNAL "")
add_subdirectory(${GOOGLE_TEST_DIR})
include_directories(${GOOGLE_TEST_DIR}/include)

set_target_properties(gtest PROPERTIES FOLDER Externals/GTest)
set_target_properties(gtest_main PROPERTIES FOLDER Externals/GTest)

target_include_directories(COMMON PUBLIC "${CMAKE_SOURCE_DIR}/include/")

set(main_project_dir "${CMAKE_SOURCE_DIR}/main/")
file(GLOB main_projects "${main_project_dir}/*.cpp")

file(GLOB_RECURSE TEST_FILES test/*.cpp)
add_executable(CommonTest ${TEST_FILES})
target_link_libraries(CommonTest PRIVATE COMMON)
target_link_libraries(CommonTest PRIVATE GTest::gtest GTest::gtest_main)

foreach(main_project_path ${main_projects})

    get_filename_component(main_project_name ${main_project_path} NAME)

    message("Main project path: ${main_project_path} and name: ${main_project_name}")

    add_executable(${main_project_name} ${main_project_path})
    target_link_librairies(${main_project_name} COMMON)

endforeach()