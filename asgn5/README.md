# Assignment 5: Public Key Cryptography

## Short Description: 
	In Assignment 5: Public Key Cryptography there are three main programs: a key generator: keygen, a encryptor: encrypt, and a decryptor: decrypt. The keygen program will be in charge of key generation, producing the RSA public and private key pairs. The encrypt program will encrypt files using a public key, and the decrypt program will decrypt the encrypted files using the corresponding private key.  
	


## Build 
        To build the keygen program manually, type "clang -Wall -Wextra -Werror -Wpedantic -o keygen keygen.c" on the command line.
	To build the encrypt program manually, type "clang -Wall -Wextra -Werror -Wpedantic -o encrypt encrypt.c" on the command line.
	To build the decrypt program manually, type "clang -Wall -Wextra -Werror -Wpedantic -o decrypt decrypt.c" on the command line.
	Alternatively, type "make" on the command line, using the Makefile provided.

## Running 
        To run the keygen program on the command line follow this structure for what to type: ./keygen -b <bits> -i <iterations>
	To run the encrypt program on the command line follow this structure for what to type: ./encrypt -i <input file name> -o <output file name>
        To run the decrypt program on the command line follow this structure for what to type: ./decrypt -i <encrypt's output file name> -o <final output file name>
	To get the usage statements and synopsis type "./ -h" on the command line.

## Cleaning 
        make clean
