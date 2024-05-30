get_current_component_dir_and_name(component_dir component_name)

set(STM32L4_INCLUDE "")
set(STM32L4_SOURCE "")

list(APPEND SOC_INCLUDE "${component_dir}/include")
list(APPEND SOC_SOURCE "${component_dir}/system.c")
list(APPEND SOC_SOURCE "${component_dir}/reg_access.c")
list(APPEND SOC_SOURCE "${component_dir}/soc_init.c")
list(APPEND SOC_SOURCE "${component_dir}/rcc_clk.c")

list(APPEND SOC_INCLUDE ${STM32L4_INCLUDE})
list(APPEND SOC_SOURCE ${STM32L4_SOURCE})

set(SOC_INCLUDE ${SOC_INCLUDE} PARENT_SCOPE)
set(SOC_SOURCE ${SOC_SOURCE} PARENT_SCOPE)
