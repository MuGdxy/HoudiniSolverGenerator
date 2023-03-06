cmake_minimum_required(VERSION 3.18)
project(_EXAMPLE_SOLVER_)

if("$ENV{HOUDINI_Root}" STREQUAL "")
        message(FATAL_ERROR "Env{HOUDINI_Root} should be set to your houdini install path. e.g. HOUDINI_Root=D:/Houdini")
    endif()
    list( APPEND CMAKE_PREFIX_PATH "$ENV{MU_HOUDINI_PATH}/toolkit/cmake" )
    message(STATUS "HDK Package Dir: $ENV{HOUDINI_Root}/toolkit/cmake")
    
    # Locate Houdini's libraries and header files.
    # Registers an imported library target named 'Houdini'.
    find_package( Houdini REQUIRED )

    # get the default install dir for the plugin
    houdini_get_default_install_dir( H_OUTPUT_INSTDIR )
    message(STATUS "Houdini Plugin Install Dir: ${H_OUTPUT_INSTDIR}/dso")


    # recursively get all source files in "${PROJECT_SOURCE_DIR}/houdini"
    file(GLOB_RECURSE _EXAMPLE_SOLVER__SRC "${PROJECT_SOURCE_DIR}/houdini/*.cpp" "${PROJECT_SOURCE_DIR}/houdini/*.h")

    add_library(_EXAMPLE_SOLVER_ SHARED ${_EXAMPLE_SOLVER__SRC})
    target_link_libraries(_EXAMPLE_SOLVER_ Houdini)
    # config target using the function provided by the HDK
    houdini_configure_target(_EXAMPLE_SOLVER_)