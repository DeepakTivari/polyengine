git clean -xdf
make

objdump -x virus | grep -E "virus"