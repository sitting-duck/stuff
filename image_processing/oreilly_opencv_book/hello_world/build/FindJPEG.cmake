

function(conan_message MESSAGE_OUTPUT)
    if(NOT CONAN_CMAKE_SILENT_OUTPUT)
        message(${ARGV${0}})
    endif()
endfunction()


macro(conan_find_apple_frameworks FRAMEWORKS_FOUND FRAMEWORKS FRAMEWORKS_DIRS)
    if(APPLE)
        foreach(_FRAMEWORK ${FRAMEWORKS})
            # https://cmake.org/pipermail/cmake-developers/2017-August/030199.html
            find_library(CONAN_FRAMEWORK_${_FRAMEWORK}_FOUND NAME ${_FRAMEWORK} PATHS ${FRAMEWORKS_DIRS} CMAKE_FIND_ROOT_PATH_BOTH)
            if(CONAN_FRAMEWORK_${_FRAMEWORK}_FOUND)
                list(APPEND ${FRAMEWORKS_FOUND} ${CONAN_FRAMEWORK_${_FRAMEWORK}_FOUND})
            else()
                message(FATAL_ERROR "Framework library ${_FRAMEWORK} not found in paths: ${FRAMEWORKS_DIRS}")
            endif()
        endforeach()
    endif()
endmacro()


function(conan_package_library_targets libraries package_libdir deps out_libraries out_libraries_target build_type package_name)
    unset(_CONAN_ACTUAL_TARGETS CACHE)
    unset(_CONAN_FOUND_SYSTEM_LIBS CACHE)
    foreach(_LIBRARY_NAME ${libraries})
        find_library(CONAN_FOUND_LIBRARY NAME ${_LIBRARY_NAME} PATHS ${package_libdir}
                     NO_DEFAULT_PATH NO_CMAKE_FIND_ROOT_PATH)
        if(CONAN_FOUND_LIBRARY)
            conan_message(STATUS "Library ${_LIBRARY_NAME} found ${CONAN_FOUND_LIBRARY}")
            list(APPEND _out_libraries ${CONAN_FOUND_LIBRARY})
            if(NOT ${CMAKE_VERSION} VERSION_LESS "3.0")
                # Create a micro-target for each lib/a found
                set(_LIB_NAME CONAN_LIB::${package_name}_${_LIBRARY_NAME}${build_type})
                if(NOT TARGET ${_LIB_NAME})
                    # Create a micro-target for each lib/a found
                    add_library(${_LIB_NAME} UNKNOWN IMPORTED)
                    set_target_properties(${_LIB_NAME} PROPERTIES IMPORTED_LOCATION ${CONAN_FOUND_LIBRARY})
                    set(_CONAN_ACTUAL_TARGETS ${_CONAN_ACTUAL_TARGETS} ${_LIB_NAME})
                else()
                    conan_message(STATUS "Skipping already existing target: ${_LIB_NAME}")
                endif()
                list(APPEND _out_libraries_target ${_LIB_NAME})
            endif()
            conan_message(STATUS "Found: ${CONAN_FOUND_LIBRARY}")
        else()
            conan_message(STATUS "Library ${_LIBRARY_NAME} not found in package, might be system one")
            list(APPEND _out_libraries_target ${_LIBRARY_NAME})
            list(APPEND _out_libraries ${_LIBRARY_NAME})
            set(_CONAN_FOUND_SYSTEM_LIBS "${_CONAN_FOUND_SYSTEM_LIBS};${_LIBRARY_NAME}")
        endif()
        unset(CONAN_FOUND_LIBRARY CACHE)
    endforeach()

    if(NOT ${CMAKE_VERSION} VERSION_LESS "3.0")
        # Add all dependencies to all targets
        string(REPLACE " " ";" deps_list "${deps}")
        foreach(_CONAN_ACTUAL_TARGET ${_CONAN_ACTUAL_TARGETS})
            set_property(TARGET ${_CONAN_ACTUAL_TARGET} PROPERTY INTERFACE_LINK_LIBRARIES "${_CONAN_FOUND_SYSTEM_LIBS};${deps_list}")
        endforeach()
    endif()

    set(${out_libraries} ${_out_libraries} PARENT_SCOPE)
    set(${out_libraries_target} ${_out_libraries_target} PARENT_SCOPE)
endfunction()


include(FindPackageHandleStandardArgs)

conan_message(STATUS "Conan: Using autogenerated FindJPEG.cmake")
# Global approach
set(JPEG_FOUND 1)
set(JPEG_VERSION "9d")

find_package_handle_standard_args(JPEG REQUIRED_VARS
                                  JPEG_VERSION VERSION_VAR JPEG_VERSION)
mark_as_advanced(JPEG_FOUND JPEG_VERSION)


set(JPEG_INCLUDE_DIRS "/home/duck/.conan/data/libjpeg/9d/_/_/package/d50a0d523d98c15bb147b18fa7d203887c38be8b/include")
set(JPEG_INCLUDE_DIR "/home/duck/.conan/data/libjpeg/9d/_/_/package/d50a0d523d98c15bb147b18fa7d203887c38be8b/include")
set(JPEG_INCLUDES "/home/duck/.conan/data/libjpeg/9d/_/_/package/d50a0d523d98c15bb147b18fa7d203887c38be8b/include")
set(JPEG_RES_DIRS )
set(JPEG_DEFINITIONS "-DLIBJPEG_STATIC")
set(JPEG_LINKER_FLAGS_LIST
        "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:>"
        "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:>"
        "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:>"
)
set(JPEG_COMPILE_DEFINITIONS "LIBJPEG_STATIC")
set(JPEG_COMPILE_OPTIONS_LIST "" "")
set(JPEG_COMPILE_OPTIONS_C "")
set(JPEG_COMPILE_OPTIONS_CXX "")
set(JPEG_LIBRARIES_TARGETS "") # Will be filled later, if CMake 3
set(JPEG_LIBRARIES "") # Will be filled later
set(JPEG_LIBS "") # Same as JPEG_LIBRARIES
set(JPEG_SYSTEM_LIBS )
set(JPEG_FRAMEWORK_DIRS )
set(JPEG_FRAMEWORKS )
set(JPEG_FRAMEWORKS_FOUND "") # Will be filled later
set(JPEG_BUILD_MODULES_PATHS )

conan_find_apple_frameworks(JPEG_FRAMEWORKS_FOUND "${JPEG_FRAMEWORKS}" "${JPEG_FRAMEWORK_DIRS}")

mark_as_advanced(JPEG_INCLUDE_DIRS
                 JPEG_INCLUDE_DIR
                 JPEG_INCLUDES
                 JPEG_DEFINITIONS
                 JPEG_LINKER_FLAGS_LIST
                 JPEG_COMPILE_DEFINITIONS
                 JPEG_COMPILE_OPTIONS_LIST
                 JPEG_LIBRARIES
                 JPEG_LIBS
                 JPEG_LIBRARIES_TARGETS)

# Find the real .lib/.a and add them to JPEG_LIBS and JPEG_LIBRARY_LIST
set(JPEG_LIBRARY_LIST jpeg)
set(JPEG_LIB_DIRS "/home/duck/.conan/data/libjpeg/9d/_/_/package/d50a0d523d98c15bb147b18fa7d203887c38be8b/lib")

# Gather all the libraries that should be linked to the targets (do not touch existing variables):
set(_JPEG_DEPENDENCIES "${JPEG_FRAMEWORKS_FOUND} ${JPEG_SYSTEM_LIBS} ")

conan_package_library_targets("${JPEG_LIBRARY_LIST}"  # libraries
                              "${JPEG_LIB_DIRS}"      # package_libdir
                              "${_JPEG_DEPENDENCIES}"  # deps
                              JPEG_LIBRARIES            # out_libraries
                              JPEG_LIBRARIES_TARGETS    # out_libraries_targets
                              ""                          # build_type
                              "JPEG")                                      # package_name

set(JPEG_LIBS ${JPEG_LIBRARIES})

foreach(_FRAMEWORK ${JPEG_FRAMEWORKS_FOUND})
    list(APPEND JPEG_LIBRARIES_TARGETS ${_FRAMEWORK})
    list(APPEND JPEG_LIBRARIES ${_FRAMEWORK})
endforeach()

foreach(_SYSTEM_LIB ${JPEG_SYSTEM_LIBS})
    list(APPEND JPEG_LIBRARIES_TARGETS ${_SYSTEM_LIB})
    list(APPEND JPEG_LIBRARIES ${_SYSTEM_LIB})
endforeach()

# We need to add our requirements too
set(JPEG_LIBRARIES_TARGETS "${JPEG_LIBRARIES_TARGETS};")
set(JPEG_LIBRARIES "${JPEG_LIBRARIES};")

set(CMAKE_MODULE_PATH "/home/duck/.conan/data/libjpeg/9d/_/_/package/d50a0d523d98c15bb147b18fa7d203887c38be8b/" ${CMAKE_MODULE_PATH})
set(CMAKE_PREFIX_PATH "/home/duck/.conan/data/libjpeg/9d/_/_/package/d50a0d523d98c15bb147b18fa7d203887c38be8b/" ${CMAKE_PREFIX_PATH})

foreach(_BUILD_MODULE_PATH ${JPEG_BUILD_MODULES_PATHS})
    include(${_BUILD_MODULE_PATH})
endforeach()

if(NOT ${CMAKE_VERSION} VERSION_LESS "3.0")
    # Target approach
    if(NOT TARGET JPEG::JPEG)
        add_library(JPEG::JPEG INTERFACE IMPORTED)
        if(JPEG_INCLUDE_DIRS)
            set_target_properties(JPEG::JPEG PROPERTIES INTERFACE_INCLUDE_DIRECTORIES
                                  "${JPEG_INCLUDE_DIRS}")
        endif()
        set_property(TARGET JPEG::JPEG PROPERTY INTERFACE_LINK_LIBRARIES
                     "${JPEG_LIBRARIES_TARGETS};${JPEG_LINKER_FLAGS_LIST}")
        set_property(TARGET JPEG::JPEG PROPERTY INTERFACE_COMPILE_DEFINITIONS
                     ${JPEG_COMPILE_DEFINITIONS})
        set_property(TARGET JPEG::JPEG PROPERTY INTERFACE_COMPILE_OPTIONS
                     "${JPEG_COMPILE_OPTIONS_LIST}")
        
    endif()
endif()
