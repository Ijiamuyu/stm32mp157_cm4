#!/bin/bash
## This script combine the images of other subsystems to generate the release image.

input_image_1=$1
subsys_image_path=$2
output_image=$3

cat $input_image_1 > $output_image
for file in $(ls -a $subsys_image_path); do
    if [[ $file = *.img ]]; then
        cat $subsys_image_path/$file >> $output_image
    fi
done
