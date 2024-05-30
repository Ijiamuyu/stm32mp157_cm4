# arm bl __libc_init_array失败的bug
armC语言库初始化失败，在bl __libc_init_array会触发硬件异常，若删去bl __libc_init_array，则在调用C语言标准库的时候会触发异常，经查询arm编译器的C语言库选择错误。

# 解决
添加以下语句，使用硬件浮点库
```
set(COMPILE_FLAGS -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard -g -O3 -Wall -Werror -ffunction-sections -fdata-sections -fno-common)
set(LINK_FLAGS "-mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard -lc -lm -lnosys -T ${LINKER_SCRIPT} -og -Wl,-Map,${PROJECT_BINARY_DIR}/${TARGET_NAME}.map,--cref -Wl,--gc-sections")
```

**注意**
- 在 CMake 中，CMAKE_EXE_LINKER_FLAGS 是一个预定义的变量，用于存储可执行文件的链接器标志。它是CMake 提供的用于控制链接器行为的变量之一。
- add_compile_options适用于编译阶段，用于为源文件的编译阶段添加选项。