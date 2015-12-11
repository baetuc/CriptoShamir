#pragma once
#include<fstream>
#include<iostream>
#include"Declarations.h"
#include<NTL/ZZ_p.h>
#include<NTL/ZZ_pX.h>

using namespace std;
using namespace NTL;

class Reconstruction {
	static void initialize();
	static void constructSecret();
	static void writeFoundSecret();

public:
	static void reconstruct();
};

void Reconstruction::initialize() {
	ifstream in(GENERATED);

	in >> numberOfSecrets;
	in >> reconstructionNumber;
	in >> prime;

	ZZ_p::init(prime);

	subsecretsForReconstruction = new ZZ_p[reconstructionNumber];
	indexes = new int[reconstructionNumber];

	for (int i = 0; i < reconstructionNumber; ++i) {
		in >> indexes[i];
		in >> subsecretsForReconstruction[i];
	}
	in.close();
}

void Reconstruction::constructSecret() {
	ZZ_p result;
	ZZ_p factor;
	ZZ_p currentIndex, floatingIndex;
	result = 0;
	for (int i = 0; i < reconstructionNumber; ++i) {
		// this represents the summation

		// Now we compute the product: I_i * product_{j \in A \ {i}} (j / (j - i))
		factor = subsecretsForReconstruction[i];
		for (int j = 0; j < reconstructionNumber; ++j) {
			if (i != j) {
				currentIndex = indexes[i];
				floatingIndex = indexes[j];
				factor *= (floatingIndex / (floatingIndex - currentIndex));
			}
		}
		result += factor;
	}
	foundSecret = result;
}

void Reconstruction::writeFoundSecret() {
	ofstream out(FOUND_SECRET, fstream::trunc | fstream::out);

	out << foundSecret;
	out.close();
}

void Reconstruction::reconstruct() {
	initialize();
	constructSecret();
	writeFoundSecret();
}