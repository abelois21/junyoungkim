g++ -g -o runfile.o -std=c++17 $1
./runfile.o < ./input > ./output
cat ./output
