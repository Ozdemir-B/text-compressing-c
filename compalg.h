#ifndef compalg
#define compalg

typedef struct triple;

const char* yaz(char a[]);

struct triple * lz77_encode(char *text, int searchBufferSize, int labSize);//returns an array of triples(struct)
//that holds the results sliding window given
//char * a is the string inside the txt file
//int x is the lenght of searchBuffer and y is the lenght of look ahead buffer

const char * read_from_txt(char * location); // returns a char array that holds the text inside the file

const char * deflate(char a[]);

const char * lz77_decode(struct triple * t);

void write_to_txt(char * string, char * location); //writes the string to the location 

#endif

/*lz77 also known as sliding windows compression algorithm*/