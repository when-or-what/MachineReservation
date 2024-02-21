cmake_minimum_required(VERSION 3.0.0)
project(MachineReservation VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)

include_directories(include include/ent include/dao include/srv)

aux_source_directory(src SRC_LIST)
aux_source_directory(src/ent SRC_LIST)
aux_source_directory(src/dao SRC_LIST)
aux_source_directory(src/srv SRC_LIST)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

add_executable(mrrs ${SRC_LIST})