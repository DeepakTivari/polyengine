rm -rf virus virus.o
make 
objdump -x virus | grep -E "virus|decrypt"


echo polyengine virus 730 30 5f8

