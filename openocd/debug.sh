#!/bin/bash
path=$(pwd)

openocd -f ${path}/stlink-dap.cfg -f ${path}/stm32mp15x.cfg  -c init -c "reset_config srst_only" > $(pwd)/log.txt 
# 一些配置以及烧录语句,根据情况使用:

