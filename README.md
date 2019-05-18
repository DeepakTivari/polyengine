
Polymorphicengine make:

     run make
     objdump -x virus | grep -w -E "main"

     add the offset of main function in the define _main_ in the polymorphic.c file

     make again & the virus is now polymorphic