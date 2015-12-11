#pragma once
#include<NTL\ZZ.h>
#include<NTL\ZZ_pEX.h>
#include<NTL\ZZ_pE.h>


using namespace std;
using namespace NTL;

#define NUMBER_LENGTH 128
#define POLYNOMIAL "polynomial.txt"
#define GENERATED "generated.txt"
#define PRIME_AND_SECRET "primeAndSecret.txt"
#define SUBSECRETS "subsecrets.txt"
#define FOUND_SECRET "foundSecret.txt"

ZZ prime;
ZZ_p secret;
ZZ_pX polynomial;
int numberOfSecrets;
int reconstructionNumber;
ZZ_p* subsecrets;
ZZ_p* subsecretsForReconstruction;
int* indexes;
ZZ_p foundSecret;




