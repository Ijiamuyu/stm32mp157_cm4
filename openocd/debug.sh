#!/bin/bash
path=$(pwd)

openocd -f ${path}/stlink.cfg -f ${path}/stm32l496x.cfg  -c init -c "reset halt" > $(pwd)/log.txt 
# 一些配置以及烧录语句,根据情况使用:

