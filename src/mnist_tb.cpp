#include "iostream"
#include "fstream"
#include "mnist.h"

using namespace std;

int main(){
	int err = 0;
	bus_t *input_mem = new bus_t[H_1];
	bus_t *weight_mem = new bus_t[25685];
	bus_t str_temp;
	str str_in, str_out;
	ifstream infile;

	cout << "Read input.bin" << endl;
	infile.open("C:\\Users\\zhoux\\Desktop\\input.bin", ios::binary | ios::in);
	if(!infile.is_open()){
		cout << infile.is_open() << endl;
		return 1;
	}
	infile.read((char*)input_mem, sizeof(bus_t)*H_1);
	infile.close();

	cout << "Read weight.bin" << endl;
	infile.open("C:\\Users\\zhoux\\Desktop\\weight.bin", ios::binary | ios::in);
	if(!infile.is_open()){
		cout << infile.is_open() << endl;
		return 1;
	}
	infile.read((char*)weight_mem, sizeof(bus_t)*25685);
	infile.close();

	// read from file and execute str_in.write()
	for(int i=0; i<H_1; i++){
		str_temp = input_mem[i];
		str_in.write(str_temp);
	}
	for(int i=0; i<25685; i++){
			str_temp = weight_mem[i];
			str_in.write(str_temp);
		}

	cout << "Execute MNIST!" << endl;
	mnist(str_in, str_out);

	// output
	str_temp = str_out.read();

	for(int i=0; i<C_7; i++){
		cout << str_temp.data[i] << ", ";
	}
	cout << endl;

	if(err){
		cout << "Test failed!" << endl;
		return 1;
	}
	else{
		cout << "Test success!" << endl;
		return 0;
	}
}
