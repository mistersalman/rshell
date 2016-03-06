# !/bin.bash
# test exit

cd ..
make
cd tests
echo test strating
../bin/rshell < exit.txt
echo && echo && echo && echo part 2
../bin/rshell < presedence_exit.txt
cd ..
make clean
cd tests
echo "finished"
