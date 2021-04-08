make test_ir ANTLR4_BINDIR=/usr/bin ANTLR4_LIBDIR=/shares/public/tp/ANTLR4-CPP/lib ANTLR4_INCDIR=/shares/public/tp/ANTLR4-CPP/antlr4-runtime
./build/test_ir

rm ./build/test_ir.s
./build/test_ir >> ./build/test_ir.s
as -o ./build/test_ir.o ./build/test_ir.s
gcc -o ./build/test_exec ./build/test_ir.o
./build/test_exec
echo $?
