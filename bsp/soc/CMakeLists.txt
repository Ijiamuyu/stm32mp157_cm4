get_current_component_dir_and_name(component_dir component_name)

set(SOC_INCLUDE "")
set(SOC_SOURCE "")

list(APPEND SOC_INCLUDE "${component_dir}")
add_subdirectory(stm32l4)

list(APPEND BSP_INCLUDE ${SOC_INCLUDE})
list(APPEND BSP_SOURCE ${SOC_SOURCE})

set(BSP_INCLUDE ${BSP_INCLUDE} PARENT_SCOPE)
set(BSP_SOURCE ${BSP_SOURCE} PARENT_SCOPE)
