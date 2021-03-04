rm ./testoutput/test.s
./ifcc testoutput/test.c >> testoutput/test.s
as -o testoutput/test.o testoutput/test.s
gcc testoutput/test.o
./a.out
echo $?