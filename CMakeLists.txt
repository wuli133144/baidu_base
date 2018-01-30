
project(demo_list)

cmake_minimum_required(VERSION 2.8)


aux_source_directory(./ list)

add_executable(demo_list ${list})


target_link_libraries(demo_list pthread)