cmake_minimum_required(VERSION 3.0.0)
project(HelloSDL VERSION 0.1.0)

include(CTest)
enable_testing()

find_package(SDL2 REQUIRED)
include_directories(${PROJECT_NAME} ${SDL2_INCLUDE_DIRECTORIES})

add_executable(${PROJECT_NAME} main.cpp
                src/Game.cpp
                src/Collision.cpp
                src/Map.cpp
                src/GameObject.cpp
                src/TextureManager.cpp
                src/Vector2D.cpp)


target_include_directories(${PROJECT_NAME} PUBLIC src/ src/ECS/)
target_link_directories(${PROJECT_NAME} PRIVATE src/ src/ECS/)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
target_link_libraries(${PROJECT_NAME} SDL2_image)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
