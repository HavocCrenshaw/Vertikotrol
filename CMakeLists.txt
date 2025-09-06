cmake_minimum_required(VERSION 4.1)
project(VERTIKOTROL LANGUAGES CXX)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")

add_library (common_flags INTERFACE)

add_library(window_system STATIC
  src/Window/MainWindow.cc
)

target_link_libraries(window_system PRIVATE common_flags)

include_directories("src")

target_compile_features(common_flags INTERFACE cxx_std_20)
target_compile_definitions(common_flags INTERFACE
  $<$<CONFIG:Debug>:DEBUG>
  $<$<CONFIG:Release>:NDEBUG>
)

add_executable(VERTIKOTROL src/Main.cc)

target_link_libraries(VERTIKOTROL PRIVATE
  window_system
)

if (MSVC)
  target_compile_options(common_flags INTERFACE /GR-)
  target_compile_options(common_flags INTERFACE /EHs-c-)
  target_compile_options(common_flags INTERFACE
    /permissive-
    /W4
    /WX
    /Zc:__cplusplus
    /Zc:preprocessor
    /wd4530
  )

  target_compile_definitions(common_flags INTERFACE
    UNICODE
    _UNICODE
  )

  target_compile_options(VERTIKOTROL PRIVATE /WX)

  target_link_libraries(VERTIKOTROL PRIVATE
    user32.lib
    gdi32.lib
  )

  target_link_options(VERTIKOTROL PRIVATE /SUBSYSTEM:WINDOWS)

  target_sources(VERTIKOTROL PRIVATE
    res/windows/app.manifest
  )
endif()
