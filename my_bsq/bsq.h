#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdbool.h>

#define AND ==          /*  adding of new terms to simplify the codes*/
#define OR ||
#define NOT !=
#define elif else if
#define end '\0'
#define dot '.'
#define X 'x'
                        /* - - - - - - - - - - - - - - - - - - - - - - */

typedef struct  s_square_info { /* template for data collection */
    int x, y, length;
} square;


/*    METHODS WE USE    */
void strcopy(char* des, char*src);
char* line(const int);
char** read_matrix(char*);
void print_matrix(char**);
bool exist(char*);

unsigned short **parse_binary(char*, int, int);
void replace(char**, square*);
// void print_binary(unsigned short**, int, int);
char* load_map(char*);
square* solver(unsigned short** , int, int); // Our dynamic function
void fill_0(unsigned short**, int, int);
void pt_malloc(unsigned short**, int, int);
int set_min(unsigned short**, int, int);

#define WIDTH int height(char* str) {\
        int len = 0;\
        for(int i=0; str[i] != end; i++)\
            if(str[i] == '\n') len++;\
        return len+1;\
    }
#define HEIGHT int width(char* s) {\
        int i=0;\
        while(s[i] != '\n')\
            i++;\
        return i;\
    }
WIDTH;
HEIGHT;