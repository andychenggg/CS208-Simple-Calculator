PROJECT(Project2)
include_directories(include)
aux_source_directory(./src DIR_SRCS)
add_executable(Project2 ${DIR_SRCS} main.cpp)