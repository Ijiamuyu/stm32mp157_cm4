get_current_component_dir_and_name(component_dir component_name)

list(APPEND BSP_INCLUDE "${component_dir}")
list(APPEND BSP_ASM_SOURCE "${component_dir}/start.s")

set(BSP_INCLUDE ${BSP_INCLUDE} PARENT_SCOPE)
set(BSP_ASM_SOURCE ${BSP_ASM_SOURCE} PARENT_SCOPE)