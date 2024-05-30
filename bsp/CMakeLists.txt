get_current_component_dir_and_name(component_dir component_name)

set(BSP_INCLUDE "")
set(BSP_SOURCE "")
set(BSP_ASM_SOURCE "")

list(APPEND BSP_INCLUDE "${component_dir}")

add_subdirectory(arch)
add_subdirectory(soc)

list(APPEND GLOBAL_INCLUDE ${BSP_INCLUDE})
list(APPEND GLOBAL_SOURCE ${BSP_SOURCE})
list(APPEND GLOBAL_ASM_SOURCE ${BSP_ASM_SOURCE})

set(GLOBAL_INCLUDE ${GLOBAL_INCLUDE} PARENT_SCOPE)
set(GLOBAL_SOURCE ${GLOBAL_SOURCE} PARENT_SCOPE)
set(GLOBAL_ASM_SOURCE ${GLOBAL_ASM_SOURCE} PARENT_SCOPE)