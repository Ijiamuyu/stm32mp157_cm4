#!/bin/bash

CMD=$1
TARGET=$2
ARCH=arm
PROJECT_PATH=${PWD}
PROJECT=armcm4

function show_help()
{
    echo "./build.sh type(build or clean) [target(app or bl)]"
}

if [[ "${CMD}" == "build" ]]; then
    if [[ "${TARGET}" != "app" && "${TARGET}" != "bl" ]]; then
        echo "Invalid project to build!"
        echo "Build failed!"
        show_help
        exit 1
    fi
    rm -rf ${PROJECT_PATH}/build
    rm -rf ${PROJECT_PATH}/out
    mkdir ${PROJECT_PATH}/build
    mkdir ${PROJECT_PATH}/out
    cd ${PROJECT_PATH}/build
    cmake .. -G "MinGW Makefiles" -DBUILD_TARGET=${TARGET} -DTARGET_NAME=${PROJECT}_${TARGET}
    make
    if [[ $? == 0 ]]; then
        cp ${PROJECT_PATH}/build/${PROJECT}_${TARGET}.out ${PROJECT_PATH}/out
        cp ${PROJECT_PATH}/build/${PROJECT}_${TARGET}.map ${PROJECT_PATH}/out
        echo "Build success!"
    else
        echo "Build failed!"
        show_help
        exit 1
    fi
    arm-none-eabi-objdump -xdts ${PROJECT_PATH}/out/${PROJECT}_${TARGET}.out > ${PROJECT_PATH}/out/${PROJECT}_${TARGET}.s
fi

if [[ "${CMD}" == "clean" ]]; then
    rm -rf ${PROJECT_PATH}/build
    rm -rf ${PROJECT_PATH}/out
fi
