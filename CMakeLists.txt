cmake_minimum_required(VERSION 3.10)

project(Moneta
    VERSION 0.0.03
    DESCRIPTION "An arena allocation library for trivial types."
    LANGUAGES CXX
)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# Do stuff depending on the compiler
if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

add_library(mnta_lib INTERFACE)
target_include_directories
(
    mnta_lib
        INTERFACE
            $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:include>
)

write_basic_package_version_file
(
    "${PROJECT_BINARY_DIR}/mntaConfigVersion.cmake"
    COMPATIBILITY SameMinorVersion
)

install
(
    TARGETS mnta
    EXPORT mntaTargets
        LIBRARY DESTINATION lib COMPONENT Runtime
        ARCHIVE DESTINATION lib COMPONENT Development
        RUNTIME DESTINATION bin COMPONENT Runtime
        PUBLIC_HEADER DESTINATION include COMPONENT Development
        BUNDLE DESTINATION bin COMPONENT Runtime
)

configure_package_config_file("${PROJECT_SOURCE_DIR}/cmake/mntaConfig.cmake.in"
                              "${PROJECT_BINARY_DIR}/mntaConfig.cmake"
                              INSTALL_DESTINATION lib/cmake/mnta)

install(EXPORT mntaTargets DESTINATION lib/cmake/mnta)
install(FILES "${PROJECT_BINARY_DIR}/mntaConfigVersion.cmake"
              "${PROJECT_BINARY_DIR}/mntaConfig.cmake"
        DESTINATION lib/cmake/mnta)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/ DESTINATION include)

add_library(Moneta::mnta ALIAS mnta_lib)
