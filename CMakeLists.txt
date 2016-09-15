project(my2048)

add_executable(my2048 main.c highscores.c jeu.c)

target_link_libraries(my2048 SDL SDL_image SDL_ttf m)

install(TARGETS my2048 RUNTIME DESTINATION bin)
