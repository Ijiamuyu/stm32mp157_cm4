#!/bin/bash
function export_bin_data()
{
    bin_data=$(od -An -v -t u1 -w1 $1)
    bin_size=$(wc -c < $1)
    exp_file=$2
    bin_idx=0
    for ele in ${bin_data}; do
        bin_idx=$((bin_idx+1))
        red=$((bin_idx%10))
        printf "%#02x" "$ele" >> ${exp_file}
        if [[ ${bin_idx} != ${bin_size} ]]; then
            printf ", " >> ${exp_file}
        fi
        if [[ ${red} = 0 ]]; then
            printf "\r\n" >> ${exp_file}
        fi
    done
    if [[ ${bin_idx} != ${bin_size} ]]; then
        return 1
    fi
}

VERSION=$1
INPUT=$2
OUTPUT=$3
OBJCOPY=$4
OBJDUMP=$5

# Get the name of the input to create folder and store cache file.
input_name=$(echo "${INPUT%.out*}")
# Check that the input variable include path"/".
if [[ ${input_name} =~ .*/.* ]]; then
    input_name=$(echo "${input_name##*/}")
fi

if [[ ! -d "${input_name}" ]]; then
    mkdir ${input_name}
fi
cd ${input_name}

rm -rf *.h

${OBJCOPY} -j .uvt -j .dmc -j .ISR -j .text -O binary ${INPUT} itcm
${OBJCOPY} -j .data -O binary $INPUT dtcm

itcm_load_addr=$(${OBJDUMP} -h ${INPUT} | grep "\.uvt" | awk '{print $5}')
dtcm_load_addr=$(${OBJDUMP} -h ${INPUT} | grep "\.data" | awk '{print $5}')
itcm_file_size=$(wc -c < itcm)
dtcm_file_size=$(wc -c < dtcm)

echo "#ifndef _${OUTPUT^^}_H_" > ${OUTPUT}.h
echo "#define _${OUTPUT^^}_H_" >> ${OUTPUT}.h
echo "" >> ${OUTPUT}.h
echo "#include <stdint.h>" >> ${OUTPUT}.h
echo "" >> ${OUTPUT}.h
echo "#define ${OUTPUT^^}_VERSION \"${VERSION}\"" >> ${OUTPUT}.h
echo "#define ${OUTPUT^^}_ITCM_LOAD_ADDR (0x${itcm_load_addr})" >> ${OUTPUT}.h
echo "#define ${OUTPUT^^}_DTCM_LOAD_ADDR (0x${dtcm_load_addr})" >> ${OUTPUT}.h
echo "#define ${OUTPUT^^}_ITCM_SIZE (${itcm_file_size})" >> ${OUTPUT}.h
echo "#define ${OUTPUT^^}_DTCM_SIZE (${dtcm_file_size})" >> ${OUTPUT}.h
echo "" >> ${OUTPUT}.h
echo "uint8_t ${OUTPUT}_itcm[${OUTPUT^^}_ITCM_SIZE] = {" >> ${OUTPUT}.h
export_bin_data itcm ${OUTPUT}.h
if [[ $? != 0 ]]; then
    echo "Error:export itcm data error!"
    exit 1
fi
echo "};" >> ${OUTPUT}.h

echo "" >> ${OUTPUT}.h
echo "uint8_t ${OUTPUT}_dtcm[${OUTPUT^^}_DTCM_SIZE] = {" >> ${OUTPUT}.h
export_bin_data dtcm ${OUTPUT}.h
if [[ $? != 0 ]]; then
    echo "Error:export dtcm data error!"
    exit 1
fi
echo "};" >> ${OUTPUT}.h
echo "" >> ${OUTPUT}.h

echo "#endif // _${OUTPUT^^}_H_" >> ${OUTPUT}.h
echo "" >> ${OUTPUT}.h

exit 0
