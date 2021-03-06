# -*- mode: cmake; tab-width: 4; indent-tabs-mode: nil -*-
#
# Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
# MA 02110-1301, USA.
#

#
# macro to create CTest tests for each boost unit tests
#
macro(add_boost_tests test_module)
    foreach(cpp_file ${ARGN})
        file(READ "${cpp_file}" contents)
        string(REGEX MATCHALL "BOOST_AUTO_TEST_CASE\\(([A-Za-z_0-9]+)\\)"
            found_tests ${contents})

        foreach(hit ${found_tests})
            string(REGEX REPLACE "BOOST_AUTO_TEST_CASE(\\([A-Za-z_0-9]+\\))"
                "\\1" test_name ${hit})
            string(REPLACE "(" "" test_name ${test_name})
            string(REPLACE ")" "" test_name ${test_name})

            string(REPLACE "_spec.cpp" "" test_suite ${cpp_file})
            string(REPLACE "spec/" "" test_suite ${test_suite})

            set(spec_cmd ${stage_bin_dir}/creris_${test_module}_spec)
            add_test(${test_module}/${test_suite}/${test_name}
                ${CMAKE_COMMAND} -E chdir ${stage_bin_dir}
                ${spec_cmd} --run_test=${test_suite}/${test_name})
        endforeach()
    endforeach()
endmacro()

#
# compiler and linker flags
#

# enable as many warnings as possible
set(warning_flags "-Wall -Wextra")

# issue all the warnings demanded by strict iso c and iso c++
set(warning_flags "${warning_flags} -pedantic")

# treat warnings as errors
set(warning_flags "${warning_flags} -Werror")

# definition shadows another
# FIXME: causes too many problems.
# set(warning_flags "${warning_flags} -Wshadow")

# do not issue warnings for system headers
set(warning_flags "${warning_flags} -Wno-system-headers")

# overloaded virtual function has a different signature
set(warning_flags "${warning_flags} -Woverloaded-virtual")

# make string constants const char*
set(warning_flags "${warning_flags} -Wwrite-strings")

# debug flags
if(WITH_DEBUG)
    set(optimisation_flags "-g -O0")
else()
    set(optimisation_flags "-O3")
endif()

if(WITH_PROFILING)
    # enable code profiling options
    set(profiling_flags "-fprofile-arcs -ftest-coverage")
endif()

# enable RTTI
# -fvisibility=hidden
set(other_flags "-frtti -fvisibility-inlines-hidden -fvisibility=default")

# set the flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${optimisation_flags}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${warning_flags}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${profiling_flags}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${other_flags}")

# ignore fuzzy link errors
if (WIN32)
    set(CMAKE_EXE_LINKER_FLAGS
        "${CMAKE_EXE_LINKER_FLAGS} -Wl,-enable-stdcall-fixup")
    set(CMAKE_SHARED_LINKER_FLAGS
        "${CMAKE_SHARED_LINKER_FLAGS} -Wl,-enable-stdcall-fixup")
endif()

# parameters for boost tests
set(boost_test_parameters "")

file(GLOB_RECURSE all_hpp_files RELATIVE
    "${CMAKE_SOURCE_DIR}/"
    "${CMAKE_SOURCE_DIR}/projects/*.hpp")

set(header_validation_template "build/templates/cpp/header_validation.cpp.in")
set(header_validation_files "")

set(ignore_file false)
set(file_counter "0")
foreach(hpp_file ${all_hpp_files})
#    if (hpp_file MATCHES "credit_risk")
#        set(ignore_file true)
#    endif()

    if(NOT ignore_file)
        set(input_filename ${CMAKE_SOURCE_DIR}/${header_validation_template})
        set(output_filename "${CMAKE_BINARY_DIR}/${hpp_file}_hv.cpp")
        set(DUMMY_FUNCTION "")
        string(REGEX REPLACE "\\." "_" DUMMY_FUNCTION "dummy_${file_counter}")
        set(header_validation_target ${CMAKE_SOURCE_DIR}/${hpp_file})
        configure_file(${input_filename} ${output_filename})
        set(header_validation_files
            ${header_validation_files} ${output_filename})
    endif()
    set(ignore_file false)
    math(EXPR file_counter "${file_counter} + 1")
endforeach()

add_library(header_validation STATIC ${header_validation_files})
set_target_properties(header_validation
    PROPERTIES OUTPUT_NAME creris_header_validation)
set_target_properties(header_validation
    PROPERTIES VERSION ${CRERIS_VERSION} SOVERSION ${CRERIS_MAJOR_VERSION})

# user includes
include_directories(
    ${CMAKE_SOURCE_DIR}/projects/daemon/include
    ${CMAKE_SOURCE_DIR}/projects/driver/include
    ${CMAKE_SOURCE_DIR}/projects/utility/include
    ${CMAKE_SOURCE_DIR}/projects/batcher/include
    ${CMAKE_SOURCE_DIR}/projects/processor/include
    ${CMAKE_SOURCE_DIR}/projects/cache/include
    ${CMAKE_SOURCE_DIR}/projects/credit_risk/include
    )

#
# add all projects
#
#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/daemon/spec)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/daemon/src)
#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/driver/spec)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/driver/src)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/utility/spec)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/utility/src)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/batcher/src)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/processor/src)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/cache/src)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/credit_risk/src)
