#pragma once
#include<fstream>
#include<iostream>
#include"Declarations.h"
#include<NTL\ZZ.h>
#include<NTL\ZZ_pEX.h>
#include<NTL\ZZ_pE.h>

using namespace std;
using namespace NTL;

class GenerateParameters {
private:
	static void initialize();
	static void computePrimeAndSecret();
	static void writePrimeAndSecret();
	static void computePolynomial();
	static void writePolynomialInFile();
	static void computeSubsecrets();
	static void writeSubsecretsInFile();
	static void writeInfoForReconstruction();


public:
	static void generate();
};
void GenerateParameters::initialize() {
	cout << "Please enter the number of secrets: ";
	cin >> numberOfSecrets;

	cout << "Please enter the reconstruction number (k): ";
	cin >> reconstructionNumber;
}

void GenerateParameters::writePrimeAndSecret() {
	ofstream out(PRIME_AND_SECRET, fstream::trunc | fstream::out); 
	out << "Prime is: " << prime << '\n';

	out << "Secret is: " << secret;
	out.close();
}

void GenerateParameters::computePrimeAndSecret() {
	// First, we generate a prime number on 128 bits
	prime = GenPrime_ZZ(NUMBER_LENGTH);
	ZZ_p::init(prime);
	// Then, we choose a random secret, from the field Z_p 
	random(secret);
}

void GenerateParameters::computePolynomial() {
	// We set the degree of polynomial to k.
	polynomial.SetMaxLength(reconstructionNumber);
	// The free term is set to the secret. (P(0) = secret).
	SetCoeff(polynomial, 0, secret);
	ZZ_p temporary;
	for (int i = 1; i < reconstructionNumber ; ++i) {
		// We set a random number from Z_p as the i-th coefficient of the polynomial
		random(temporary);
		if (i + 1 == reconstructionNumber) {
			// We assure that the leading coefficient is not null
			while (temporary == 0) {
				random(temporary);
			}
		}
		SetCoeff(polynomial, i, temporary);
	}
}

void GenerateParameters::writePolynomialInFile() {
	ofstream out(POLYNOMIAL, fstream::trunc | fstream::out);
	out << polynomial;
	out.close();
}

void GenerateParameters::computeSubsecrets() {
	subsecrets = new ZZ_p[numberOfSecrets];
	ZZ_p temporary;
	temporary = 0;
	for (int i = 0; i < numberOfSecrets; ++i) {
		++temporary;
		subsecrets[i] = eval(polynomial, temporary);
	}
}

void GenerateParameters::writeSubsecretsInFile() {
	ofstream out(SUBSECRETS, fstream::trunc | fstream::out);

	for (int i = 0; i < numberOfSecrets; ++i) {
		out << subsecrets[i] << '\n';
	}
	out.close();
}

void GenerateParameters::writeInfoForReconstruction() {
	ofstream out(GENERATED, fstream::trunc | fstream::out);

	out << numberOfSecrets << '\n';
	out << reconstructionNumber << '\n';
	out << prime << '\n';

	bool* isChosen = new bool[numberOfSecrets];
	//Initialization
	for (int i = 0; i < numberOfSecrets; ++i) {
		isChosen[i] = false;
	}
	
	int foundIndexes = 0;
	int index;
	while (foundIndexes < reconstructionNumber) {
		index = RandomBnd(numberOfSecrets);
		if (!isChosen[index]) {
			isChosen[index] = true;
			++foundIndexes;
			out << index  + 1 << ' ' << subsecrets[index] << '\n';
		}
	}
	out.close();
}

void GenerateParameters::generate() {
	initialize();
	computePrimeAndSecret();
	writePrimeAndSecret();
	computePolynomial();
	writePolynomialInFile();
	computeSubsecrets();
	writeSubsecretsInFile();
	writeInfoForReconstruction();
}