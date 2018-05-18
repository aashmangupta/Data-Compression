all : huffmanTree.o compressionAlg.o uncompress.o compressionAlg uncompress clean

huffmanTree.o : huffmanTree.c huffmanTree.h
	gcc -Wall -g -c huffmanTree.c

compressionAlg.o : compressionAlg.c huffmanTree.h
	gcc -Wall -g -c compressionAlg.c

uncompress.o : uncompress.c
	gcc -Wall -g -c uncompress.c

compressionAlg : compressionAlg.o huffmanTree.o 
	gcc -Wall -g -o compression compressionAlg.o huffmanTree.o

uncompress : uncompress.o
	gcc -Wall -g -o uncompress uncompress.o

clean :
	rm -f *.o
