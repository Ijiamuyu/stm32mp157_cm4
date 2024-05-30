get_current_component_dir_and_name(component_dir component_name)

################# Add include #################
list(APPEND DRIVERS_INCLUDE "${component_dir}")
###############################################

############## Add source files ###############
list(APPEND DRIVERS_SOURCE "${component_dir}/st_uart.c")

###############################################
set(DRIVERS_INCLUDE ${DRIVERS_INCLUDE} PARENT_SCOPE)
set(DRIVERS_SOURCE ${DRIVERS_SOURCE} PARENT_SCOPE)