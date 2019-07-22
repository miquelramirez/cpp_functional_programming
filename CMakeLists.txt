cmake_minimum_required(VERSION 3.10)
project(functional_programming_cpp_doodads)

set(CMAKE_CXX_STANDARD 17)

set(dir ${PROJECT_SOURCE_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${dir}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${dir}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${dir}/bin")


## find_package will search for available TBBConfig using variables CMAKE_PREFIX_PATH and TBB_DIR.
#find_package(TBB REQUIRED tbb)

add_executable(ch2_averages src/ch2_averages.cxx)

if (MSVC)
else()
    SET(LINK_FLAGS
            "-L/usr/local")

    target_link_libraries(ch2_averages -ltbb)

    set_target_properties(ch2_averages PROPERTIES
            LINK_FLAGS ${LINK_FLAGS})
endif()

add_executable(ch2_string_trimming src/ch2_string_trimming.cxx)

add_executable(ch2_partitioning src/ch2_collection_partitioning.cxx)

add_executable(ch2_filter_n_transform src/ch2_filtering_and_transforming.cxx)