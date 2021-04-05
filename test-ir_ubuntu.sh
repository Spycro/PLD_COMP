make test_ir ANTLR4_BINDIR=/usr/bin  ANTLR4_INCDIR=/usr/include/antlr4-runtime ANTLR4_LIBDIR=/usr/lib/x86_64-linux-gnu/
./build/test_ir

rm ./build/test_ir.s
./build/test_ir >> ./build/test_ir.s
as -o ./build/test_ir.o ./build/test_ir.s
gcc -o ./build/test_exec ./build/test_ir.o
./build/test_exec
echo $?
