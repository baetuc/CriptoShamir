#include<iostream>
#include"Generation.h"
#include"Reconstruction.h"

using namespace std;

int main() {
	int option;

	cout << "Please enter 1 for secret and subsecrets generation, or 2 for secret reconstruction: ";
	cin >> option;
	switch (option) {
	case 1: 
		GenerateParameters::generate();
		cout << "Secret and subsecrets were generated. Please check in specific file.\n";
		break;

	case 2:
		Reconstruction::reconstruct();
		cout << "Secret was reconstructed. Please check in specific file.\n";
		break;

	default:
		cout << "Please enter a valid option, next time. Have a nice day!\n";
	}
	return 0;
}