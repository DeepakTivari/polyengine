
Polymorphicengine make:

     run make
     objdump -x virus | grep -w -E "_start|main|decrypt_engine.decryption_function"

     add the VMA addresses to the polymorphic.c in their respective regions

     make again & the virus is now polymorphic