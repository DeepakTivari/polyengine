
Polymorphicengine make:

Compile:

     `make`

Integrate:

     `gcc -no-pie -nostartfiles <your obj/source> turbopolymorphic.o -o <executable name>`

     Note: ensure you source code/ object file must contain th `main` function
     WARNING: ensure the order of operations is preserved, `<you code>` then `turbopolymorphic.o` while linking above
     
Test:

     Check for polymorphic capability after each execution of the `<executable name>`

     `objdump -S <executable name> | grep <any executable function>`