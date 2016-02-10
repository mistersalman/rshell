# !/bin.bash
# test exit

cd ..
make
cd tests
echo test strating
../rshell.out < exit.txt
echo "finished"
