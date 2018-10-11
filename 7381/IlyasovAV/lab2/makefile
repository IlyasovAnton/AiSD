all: lab2

lab2: main_lab2.o hierar_list.o
	g++ main_lab2.o hierar_list.o -o lab2

main_lab2.o: ./Source/main_lab2.cpp
	g++ -c ./Source/main_lab2.cpp

hierar_list.o: ./Source/hierar_list.cpp
	g++ -c ./Source/hierar_list.cpp

clean:
	rm main_lab2.o hierar_list.o
