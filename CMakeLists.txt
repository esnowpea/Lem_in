cmake_minimum_required(VERSION 3.15)
project(Lem_in C)

set(CMAKE_C_STANDARD 90)

add_executable(Lem_in src/main.c src/parsing.c src/init.c src/terminate.c src/solution.c src/print.c src/solution.c src/print_result.c src/parsing_add_vertex.c src/parsing_add_edge.c src/parsing_last_chek.c src/print_result_start_step_ants.c src/print_result_start_step_ants_2.c src/print_result_start_step_ants_3.c src/print_result_step_ants_room.c src/print_current_position_ants.c)
target_include_directories(Lem_in PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/inc)
target_include_directories(Lem_in PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(Lem_in PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/lib/Libft/inc)
set(FT ${CMAKE_CURRENT_SOURCE_DIR}/lib/Libft/libft.a)
target_link_libraries(Lem_in ${FT})

target_include_directories(Lem_in PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/lib/Libftprintf/inc)
set(FT_Printf ${CMAKE_CURRENT_SOURCE_DIR}/lib/Libftprintf/libftprintf.a)
target_link_libraries(Lem_in ${FT_Printf})