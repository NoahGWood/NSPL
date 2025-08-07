cmake_minimum_required(VERSION 3.10)
project(NSPL VERSION 0.1.0 LANGUAGES CXX)

# --- Options ---
option(NSPL_BUILD_SHARED "Build NSPL as a shared library" OFF)
option(NSPL_BUILD_EXAMPLES "Build NSPL Examples" OFF)

# --- C++ standard --
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=default")

# --- Dependencies ---
find_package(SDL2 REQUIRED)
find_package(spdlog REQUIRED)

# --- Sources ---
file(GLOB_RECURSE NSPL_SOURCES
    src/*.cpp
    include/*.hpp
)

# --- Library target ---
add_library(NSPL ${NSPL_SOURCES})

if(NSPL_BUILD_SHARED)
    set_target_properties(NSPL PROPERTIES BUILD_SHARED_LIBS ON)
endif()

target_include_directories(NSPL
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${SDL2_INCLUDE_DIRS}
)

target_link_libraries(NSPL
    PUBLIC
        SDL2::SDL2
        spdlog::spdlog
)

if(NSPL_BUILD_EXAMPLES)
# Build main application executable
file(GLOB_RECURSE EXAMPLE_SOURCES
    examples/*.cpp
)
add_executable(NSPLApp ${EXAMPLE_SOURCES})
target_link_libraries(NSPLApp PRIVATE NSPL)
endif()

# --- Install (optional) ---
install(TARGETS NSPL
    EXPORT NSPLTargets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)
install(DIRECTORY include/ DESTINATION include)

# --- Export for other projects ---
export(EXPORT NSPLTargets FILE "${CMAKE_CURRENT_BINARY_DIR}/NSPLTargets.cmake")