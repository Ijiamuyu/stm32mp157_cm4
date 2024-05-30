for openocd 
cd openocd & ./debug.sh

for gdb
arm-none-eabi-gdb out/ezos_bl.out
target remote localhost:3333

