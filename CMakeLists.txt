cmake_minimum_required(VERSION 3.23)
project(GameTemplate LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)

# Download and add SFML as a dependency
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

# Download and add tmxlite (tiled editor loader) as a dependency
FetchContent_Declare(
    TMXLITE
    GIT_REPOSITORY https://github.com/fallahn/tmxlite.git
    GIT_TAG v1.4.4
    SOURCE_SUBDIR tmxlite)
FetchContent_MakeAvailable(TMXLITE)


set(PROJECT_HEADERS 
    include/Utils/Constants.h
    include/Utils/ObjectPool.h

    include/Core/AssetManager.h
    include/Core/Game.h
    include/Core/World.h
    include/Core/BulletManager.h
    include/Core/EnemyManager.h
    include/Core/CollisionManager.h
    include/Core/PowerUpManager.h
    include/Core/SoundManager.h

    include/Gameplay/Enemy.h
    include/Gameplay/GameObject.h
    include/Gameplay/Player.h
    include/Gameplay/Bullet.h
    include/Gameplay/SimpleEnemy.h
    include/Gameplay/PowerUp.h

    include/Render/SFMLOrthogonalLayer.h

    include/UI/UIScreenMainMenu.h
    include/UI/UIManager.h
)

set(PROJECT_SOURCES 

    src/Core/AssetManager.cpp
    src/Core/Game.cpp
    src/Core/World.cpp
    src/Core/BulletManager.cpp
    src/Core/EnemyManager.cpp
    src/Core/CollisionManager.cpp
    src/Core/PowerUpManager.cpp
    src/Core/SoundManager.cpp

    src/Gameplay/Enemy.cpp
    src/Gameplay/Player.cpp
    src/Gameplay/Bullet.cpp
    src/Gameplay/SimpleEnemy.cpp
    src/Gameplay/PowerUp.cpp

    src/main.cpp

    src/UI/UIManager.cpp
)

set(PROJECT_FILES 
  ${PROJECT_HEADERS} 
  ${PROJECT_SOURCES}
)

include_directories(${PROJECT_NAME} PRIVATE ${tmxlite_INCLUDE_DIR} include)

add_executable(${PROJECT_NAME} ${PROJECT_FILES})

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set_property(TARGET ${PROJECT_NAME} PROPERTY
    VS_DEBUGGER_WORKING_DIRECTORY 
    "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIG>")

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD 
    COMMAND ${CMAKE_COMMAND} -E copy_directory 
    "${CMAKE_SOURCE_DIR}/data" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/data")

target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics sfml-audio tmxlite)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

target_compile_definitions(${PROJECT_NAME} PUBLIC DEBUG_MODE=0)

if(WIN32)
    add_custom_command(
        TARGET ${PROJECT_NAME}
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:${PROJECT_NAME}>
        VERBATIM)
endif()
