cmake_minimum_required(VERSION 3.17)
project(jeu_nim C)

set(CMAKE_C_STANDARD 99)
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc -lncurses")
set (CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS}")

add_executable(jeu_nim main.c m_distributions.c m_distributions.h nim_ihm.h nim_ihm.c nim.c nim.h nim_test.c nim_io.c nim_io.h codage_numerique.c codage_numerique_test.c codage_numerique.h)
target_link_libraries(jeu_nim ${CURSES_LIBRARIES})