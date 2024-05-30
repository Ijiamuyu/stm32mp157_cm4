get_current_component_dir_and_name(component_dir component_name)
set(LINKER_SCRIPT "${component_dir}/arm_app.ld")
set(COMPILE_FLAGS -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard -g -O3 -Wall -Werror -ffunction-sections -fdata-sections -fno-common)
set(LINK_FLAGS "-mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard -lc -lm -lnosys -T ${LINKER_SCRIPT} -og -Wl,-Map,${PROJECT_BINARY_DIR}/${TARGET_NAME}.map,--cref -Wl,--gc-sections")

list(APPEND COMPILE_PROJECT_FLAGS ${COMPILE_FLAGS})
list(APPEND LINK_PROJECT_FLAGS ${LINK_FLAGS})

set(COMPILE_PROJECT_FLAGS ${COMPILE_PROJECT_FLAGS} PARENT_SCOPE)
set(LINK_PROJECT_FLAGS ${LINK_PROJECT_FLAGS} PARENT_SCOPE)