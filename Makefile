CXX = g++
COMP_FLAGS = -Iinclude -Wall -Wextra -std=c++17 -O3
OBJ = out.o inp.o jfmt.o main.o tok.o num.o

main: $(OBJ)
	$(CXX) $(OBJ) $(COMP_FLAGS) -o main 

main.o: main.cpp
	$(CXX) $(COMP_FLAGS) -c main.cpp -o main.o

jfmt.o: src/json_fmt.cpp
	$(CXX) $(COMP_FLAGS) -c src/json_fmt.cpp -o jfmt.o

inp.o: src/inp_file.cpp
	$(CXX) $(COMP_FLAGS) -c src/inp_file.cpp -o inp.o 

out.o: src/out_file.cpp
	$(CXX) $(COMP_FLAGS) -c src/out_file.cpp -o out.o

tok.o: src/tokenizer.cpp
	$(CXX) $(COMP_FLAGS) -c src/tokenizer.cpp -o tok.o

num.o: src/numbers.cpp
	$(CXX) $(COMP_FLAGS) -c src/numbers.cpp -o num.o

clean:
	rm -f *.o main *.json