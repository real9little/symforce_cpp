# ----------------------------------------------------------------------------
# SymForce - Copyright 2022, Skydio, Inc.
# This source code is under the Apache 2.0 license found in the LICENSE file.
# ----------------------------------------------------------------------------

# NOTE(aaron): This is the minimum version for FetchContent, not sure if we need newer; certainly no
# newer than 3.15 required
cmake_minimum_required(VERSION 3.11)

project(symforce_cpp)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


option(SYMFORCE_BUILD_OPT "Build symforce_opt and related targets for optimization" ON)
option(SYMFORCE_BUILD_EXAMPLES "Build the examples" ON)
option(SYMFORCE_BUILD_TESTS "Build the tests" ON)
option(SYMFORCE_BUILD_STATIC_LIBRARIES "Build libraries as static (symforce_cholesky is always built as shared)" OFF )

find_program(SYMFORCE_DEFAULT_PYTHON python3 NO_CACHE)
set(SYMFORCE_PYTHON "${SYMFORCE_DEFAULT_PYTHON}" CACHE STRING "Python executable to use")

set(SYMFORCE_EIGEN_TARGET "Eigen3::Eigen" CACHE STRING
        "Target to depend on for Eigen. Default is to find Eigen with find_package."
        )

if(SYMFORCE_BUILD_STATIC_LIBRARIES)
    set(SYMFORCE_LIBRARY_TYPE STATIC)
else()
    set(SYMFORCE_LIBRARY_TYPE SHARED)
endif()

include(FetchContent)

if(SYMFORCE_EIGEN_TARGET STREQUAL "Eigen3::Eigen")
    find_package(Eigen3 QUIET)
    if(NOT Eigen3_FOUND)
        message(STATUS "Eigen3 not found, adding with FetchContent")
        function(add_eigen)
            FetchContent_Declare(
                    eigen3
                    GIT_REPOSITORY https://gitlab.com/libeigen/eigen
                    GIT_TAG 3147391d946bb4b6c68edd901f2add6ac1f31f8c  # release 3.4.0
                    GIT_SHALLOW TRUE
            )

            set(EIGEN_BUILD_DOC OFF CACHE BOOL "Don't build Eigen docs")
            set(BUILD_TESTING OFF CACHE BOOL "Don't build Eigen tests")
            set(EIGEN_BUILD_PKGCONFIG OFF CACHE BOOL "Don't build Eigen pkg-config")
            FetchContent_MakeAvailable(eigen3)
        endfunction()

        add_eigen()

        # Enable use of Eigen3_ROOT, which is necessary for sophus to be able to find Eigen when
        # included this way
        # See https://cmake.org/cmake/help/latest/policy/CMP0074.html
        set(CMAKE_POLICY_DEFAULT_CMP0074 NEW CACHE STRING "" FORCE)
        set(Eigen3_ROOT "${FETCHCONTENT_BASE_DIR}/eigen3-src" CACHE PATH "Phooey" FORCE)
    else()
        message(STATUS "Eigen found at ${Eigen3_DIR}")
        include_directories(
                ${EIGEN3_INCLUDE_DIR}
        )
    endif()
endif()


# TODO(aaron): This goes away when we upgrade to Catch2 v3
add_library(
        symforce_catch2
        ${SYMFORCE_LIBRARY_TYPE}
        EXCLUDE_FROM_ALL  # Only build this if something needs it
        third_party/catch2/src/catch_amalgamated.cpp test/catch_main.cc
)

target_include_directories(
        symforce_catch2
        PUBLIC third_party/catch2/include
)

include(third_party/skymarshal/cmake/skymarshal.cmake)

add_skymarshal_bindings(symforce_lcmtypes
        ${CMAKE_CURRENT_BINARY_DIR}/lcmtypes
        ${CMAKE_CURRENT_SOURCE_DIR}/lcmtypes
        )

target_include_directories(symforce_lcmtypes_cpp
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/third_party/eigen_lcm/lcmtypes/eigen_lcm_lcm/cpp
        )

add_skymarshal_bindings(eigen_lcm
        ${CMAKE_CURRENT_BINARY_DIR}/lcmtypes
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/eigen_lcm/lcmtypes
        LANGUAGES python
        )

add_custom_target(symforce_eigen_lcm_py ALL DEPENDS eigen_lcm_py)

# Get SymForce version
execute_process(
        COMMAND ${SYMFORCE_PYTHON} -c "from _version import version; print(version, end='')"
        WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/symforce
        OUTPUT_VARIABLE SYMFORCE_VERSION
)
file(WRITE
        ${CMAKE_CURRENT_BINARY_DIR}/lcmtypes/python2.7/setup.py
        "
from setuptools import setup, find_packages
setup(
  name='lcmtypes',
  version='${SYMFORCE_VERSION}',
  description='lcmtype python bindings (installed by SymForce)',
  long_description='lcmtype python bindings (installed by SymForce)',
  author='Skydio, Inc',
  author_email='hayk@skydio.com',
  license='Apache 2.0',
  packages=find_packages(),
  zip_safe=False,
)
    "
        )


file(GLOB_RECURSE SYMFORCE_GEN_SOURCES CONFIGURE_DEPENDS sym/*.cc)
file(GLOB_RECURSE SYMFORCE_GEN_HEADERS CONFIGURE_DEPENDS sym/*.tcc sym/*.h)
list(FILTER SYMFORCE_GEN_SOURCES EXCLUDE REGEX "opt/*")
list(FILTER SYMFORCE_GEN_HEADERS EXCLUDE REGEX "opt/*")
add_library(
        symforce_gen
        ${SYMFORCE_LIBRARY_TYPE}
        ${SYMFORCE_GEN_SOURCES}
        ${SYMFORCE_GEN_HEADERS}
)
target_link_libraries(symforce_gen ${SYMFORCE_EIGEN_TARGET} symforce_lcmtypes_cpp)
target_include_directories(
        symforce_gen
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)


add_subdirectory(sym/opt)
