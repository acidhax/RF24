#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <unistd.h>
#include <RF24/RF24.h>

using namespace std;

RF24 radio(edison::Gp44,1);

// Radio pipe addresses for the 2 nodes to communicate.
const uint8_t pipes[][6] = {"1Node","2Node", "3Node", "4Node", "5Node", "6Node"};

int main(int argc, char** argv){
	radio.begin();

	// optionally, increase the delay between retries & # of retries
	radio.setRetries(0,0);

	// Dump the configuration of the rf unit for debugging
	radio.printDetails();
	string input = "";
	cout << "Choose your node number. #0-6 \n>";
	getline(cin,input);

	int radioNumber = (int)input[0]-48;

	cout << "input" << input << "\n";

	radio.openWritingPipe(pipes[radioNumber]);

	for (int i = 0; i < 6; i++) {
		if (i != radioNumber) {
			cout << i << "\n";
    		radio.openReadingPipe(i,pipes[i]);
		}
	}

}