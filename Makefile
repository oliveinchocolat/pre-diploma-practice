all: create_universal

create_universal: main.o read_and_write.o generation.o grad_algo.o mod_grad_algo.o get_universal_function.o
	g++ main.o read_and_write.o generation.o grad_algo.o mod_grad_algo.o get_universal_function.o -o create_universal
	
main.o:
	g++ main.cpp -w -std=c++11 -c
	
read_and_write.o:
	g++ read_and_write.cpp -w -std=c++11 -c
	
generation.o:
	g++ generation.cpp -w -std=c++11 -c
	
grad_algo.o:
	g++ grad_algo.cpp -w -std=c++11 -c
	
mod_grad_algo.o:
	g++ mod_grad_algo.cpp -w -std=c++11 -c
	
get_universal_function.o:
	g++ get_universal_function.cpp -w -std=c++11 -c

clean:
	rm -rf *.o create_universal

#	g++ main.cpp generation.cpp grad_algo.cpp mod_grad_algo.cpp read_and_write.cpp get_universal_function.cpp -o with -w -std=c++11
