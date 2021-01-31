cmake_minimum_required (VERSION 3.8)
project ("COVID_19_Emulator")

FILE(GLOB_RECURSE PIXEL_FILES   
                    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
                    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c
                    )

if( ${CMAKE_VERSION} VERSION_GREATER_EQUAL 3.16 )
    set ( CMAKE_UNITY_BUILD_BATCH_SIZE 16 )
endif()

SET(RW_DATA_PATH ${CMAKE_CURRENT_SOURCE_DIR})
configure_file (
  ${CMAKE_CURRENT_SOURCE_DIR}/sysconfig/SysConfig.h.in
  ${CMAKE_CURRENT_SOURCE_DIR}/sysconfig/SysConfig.h
  )

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/deps/opengl/libs)

add_executable (COVID_19_Emulator ${PIXEL_FILES})

MACRO( collect_head_dirs return_list )
    FILE(GLOB_RECURSE new_list 
                      ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
                      ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/src/*.tpp
                      )
    SET(dir_list "")
    FOREACH(file_path ${new_list})
        GET_FILENAME_COMPONENT(dir_path ${file_path} PATH)
        SET(dir_list ${dir_list} ${dir_path})
    ENDFOREACH()
    LIST(REMOVE_DUPLICATES dir_list)
    SET(${return_list} ${dir_list})
ENDMACRO()

collect_head_dirs( src_header_dirs )

target_include_directories ( COVID_19_Emulator PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/deps/opengl/include
    ${src_header_dirs}
    ${CMAKE_CURRENT_SOURCE_DIR}/sysconfig
    )
target_link_libraries(COVID_19_Emulator OpenGL32 glfw3)

