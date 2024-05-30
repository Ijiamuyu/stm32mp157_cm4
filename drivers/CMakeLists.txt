get_current_component_dir_and_name(component_dir component_name)

set(DRIVER_INCLUDE "")
set(DRIVER_SOURCE "")
set(DRIVER_ASM_SOURCE "")

list(APPEND DRIVER_INCLUDE "${component_dir}")

add_subdirectory(uart)
add_subdirectory(gpio)

list(APPEND GLOBAL_INCLUDE ${DRIVER_INCLUDE})
list(APPEND GLOBAL_SOURCE ${DRIVER_SOURCE})

set(GLOBAL_INCLUDE ${GLOBAL_INCLUDE} PARENT_SCOPE)
set(GLOBAL_SOURCE ${GLOBAL_SOURCE} PARENT_SCOPE)
