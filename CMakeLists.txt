cmake_minimum_required(VERSION 3.12)

# set the project name
project(gtk-checkers)

set (CMAKE_EXPORT_COMPILE_COMMANDS ON)

set (MY_COMPILE_FLAGS "-Wall" "-Wextra" "-Werror")

if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
  set (MY_COMPILE_FLAGS ${MY_COMPILE_FLAGS} "-DDEBUG_MODE")
elseif (${CMAKE_BUILD_TYPE} STREQUAL "Release")
  set (MY_COMPILE_FLAGS ${MY_COMPILE_FLAGS} "-O")
endif()

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK gtkmm-3.0 REQUIRED)

add_executable(checkers
               src/board.cpp
               src/controller.cpp
               src/ColorMapper.cpp
               src/CheckerPlayer.cpp
               src/CheckerSquare.cpp
               src/CheckerPiece.cpp
               src/Checkers.cpp
               src/GameManager.cpp
               src/FinishDialog.cpp
               src/main.cpp)
target_include_directories(checkers PUBLIC ${GTK_INCLUDE_DIRS} include)
target_compile_features(checkers PRIVATE cxx_std_11)
target_compile_options(checkers PRIVATE ${MY_COMPILE_FLAGS})
target_link_libraries(checkers PRIVATE ${GTK_LIBRARIES})
