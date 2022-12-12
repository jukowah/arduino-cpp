add_executable(mirrorgame components/actor.cpp main.cpp)

include("${CMAKE_CURRENT_SOURCE_DIR}/../vcpkg/scripts/buildsystems/vcpkg.cmake")

find_package(SDL2 CONFIG REQUIRED)
find_package(libtcod CONFIG REQUIRED)
target_link_libraries(
    mirrorgame
    PRIVATE
        SDL2::SDL2
        SDL2::SDL2main
        libtcod::libtcod
)

target_compile_features(mirrorgame PRIVATE cxx_std_20)
set_target_properties(mirrorgame PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/target")