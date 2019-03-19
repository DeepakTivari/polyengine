# rm -rf virus virus.o
# make 

git clean -xdf
make

objdump -x virus | grep -E "virus|decrypt"
echo polyengine virus 730 30 5f8

# ./polyengine virus 6e0 30 5a8
# chmod +x virus_poly
# ./virus_poly