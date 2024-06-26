set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)
cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(EZOS C ASM CXX)

function(get_current_component_dir_and_name _ret_component_dir _ret_component_name)
    get_filename_component(_component_dir ${CMAKE_CURRENT_LIST_FILE} DIRECTORY)
    get_filename_component(_component_name ${_component_dir} NAME)
    set(${_ret_component_dir} ${_component_dir} PARENT_SCOPE)
    set(${_ret_component_name} ${_component_name} PARENT_SCOPE)
endfunction()

set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)
set(CMAKE_LINKER arm-none-eabi-ld)
set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
set(CMAKE_OBJDUMP arm-none-eabi-objdump)
set(CMAKE_SIZE arm-none-eabi-size)
set(CMAKE_GDB arm-none-eabi-gdb)

set(GLOBAL_INCLUDE "")
set(GLOBAL_SOURCE "")
set(GLOBAL_ASM_SOURCE "")
set(COMPILE_PROJECT_FLAGS "")
set(LINK_PROJECT_FLAGS "")

if(BUILD_TARGET STREQUAL app)
    add_subdirectory(algorithm)
    add_subdirectory(app)
elseif(BUILD_TARGET STREQUAL bl)
    add_subdirectory(bootloader)
else()
    message(FATAL_ERROR "Invalid project to build!")
endif()

add_subdirectory(bsp)
add_subdirectory(drivers)
add_subdirectory(modules)
add_subdirectory(os)
add_subdirectory(osal)
add_subdirectory(config)
add_subdirectory(test)

add_compile_options(${COMPILE_PROJECT_FLAGS})
set(CMAKE_EXE_LINKER_FLAGS ${LINK_PROJECT_FLAGS})

include_directories(${GLOBAL_INCLUDE})

add_executable(${TARGET_NAME}.out ${GLOBAL_ASM_SOURCE} ${GLOBAL_SOURCE})
