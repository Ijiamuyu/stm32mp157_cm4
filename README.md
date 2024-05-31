# stm32mp157_cm4
repository for stm32mp157-cm4 core, using cmake, gnu toolchain & openocd build

## toolchain
- arm build toolchain:GNU Arm Embedded Toolchain
- cmake
- make
- openocd

## build & run

- type ./build.sh build target(bl or app)
- cd openocd & type ./debug.sh
- open arm-gdb to listen remote port
