!/bin/

cd ..
make
cd tests
../bin/rshell < precedence.txt
cd ..
make clean
cd tests
echo finished
