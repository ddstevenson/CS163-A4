all : a.out

a.out : client.cpp table.cpp
	g++ -g -Wall client.cpp table.cpp

clean:
	rm -f a.out *.tar

tar: *
	tar -cvf assignment4.tar *.cpp *.h a.out *.txt Makefile
