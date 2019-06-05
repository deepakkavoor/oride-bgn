target:
		gcc -c bgn.c -I/usr/local/include/pbc -L/usr/local/lib -lpbc -lgmp
		# gcc -o test test.c -I ~/.local/include/pbc -L ~/.local/lib -Wl,-rpath ~/.local/lib  -l pbc
		gcc -Wall -static bgn.o test.c -o test -I/usr/local/include/pbc -L/usr/local/lib -lpbc -lgmp
		g++ -Wall -static bgn.o test_oride.cpp -o test_oride -I/usr/local/include/pbc -L/usr/local/lib -lpbc -lgmp -std=c++11
		