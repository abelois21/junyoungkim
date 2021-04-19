g++ -g -o runfile.o -std=c++17 $1
./runfile.o < ./input > ./output
./runfile.o < ./input2 >> ./output
cat ./output
