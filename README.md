# Data-Compression

1.	In this project I'm basically trying to implement a data compression algorithm using huffman trees.

2.	In Version 1.0 I'm only going to be able to parse through letters(a-z), but I intend to add other characters
	later on.

3.	The changes in Version 1.1:
		-Uncompression finally works.
		-Added a random.c program that can generate a randomized data file, which can then be used to test my
		compression and decompression software.

4. 	Version 1.2:
		-Compression and uncompression works with special characters(not just lower-case alphabets) :)

## Compile Instructions ##

* To compile compressionAlg run: run gcc compressionAlg.c huffmanTree.c
* To compile uncompress run: gcc uncompress.c

## What needs to be done ##

* Currently the 1's and 0's are being saved as 8 bit characters instead of 1 bit.
* Can't manipulate bits individually because bits starting with 0 (and some other cases) can't be identified by the computer.
* 0100 1011 - won't be recognized by machine and will be represented by '?'
