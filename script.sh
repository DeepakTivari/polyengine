# rm -rf virus virus.o
# make 

git clean -xdf
make

# objdump -x virus | grep -E "virus|decrypt"
# echo polymake virus 5a0 30 563

./polymake virus 5a0 30 563
chmod +x virus_morph
./virus_morph
md5sum virus_morph