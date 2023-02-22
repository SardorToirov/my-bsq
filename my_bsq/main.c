/*
*   My Bsq program for QWASAR
*   Created by Mirjamol Mirislomov and Sardor Toirov
*   Date: 2022-11-29
*/

#include "bsq.h"
int main(int ac, char** av)
{
    if (ac < 2) {
        puts("less argument");
        exit(1);
    } elif (!exist(av[1])) {
        puts("Map not found");
        exit(1);
    }
    char* map=load_map(av[1]);
    unsigned short**mat =  parse_binary(map, width(map), height(map));
    square* info = solver(mat, width(map), height(map));
    char** char_map = read_matrix(av[1]);
    replace(char_map, info); 
    print_matrix(char_map);
    // print_binary(mat, height(map), width(map));
}

void strcopy(char* des, char* src)
{
    int i = 0;
    do
        des[i] = src[i], i++;
    while (src[i] != end);
}

char* line(const int fd)
{
    char temp[100];
    int i = 0, r;
    char c;
    while ((r = read(fd, &c, 1)) >= 0)
    {
        if (r == 0 && i == r) return NULL;
        if (c == '\n' || r == 0) break;
        temp[i++] = c;
    }
    temp[i] = '\0';
    char* ret = (char*)malloc(sizeof(char) * i);
    strcopy(ret, temp);
    return ret;
}
char** read_matrix(char* map)
{
    const int fd = open(map, O_RDONLY);
    int num_lines = atoi(line(fd));
    char* row = line(fd);  // for find length of line
    char** matrix = (char**)malloc(num_lines * strlen(row) + 1);
    matrix[0] = row;
    int i = 1;
    while ((row = line(fd)) != NULL)
        matrix[i++] = row;
    matrix[i] = NULL;
    return matrix;
}
void print_matrix(char** matrix)
{
    for (int i = 0; matrix[i]; i++)
    {
        printf("%s\n", matrix[i]);
    }
}

void replace(char **map, square *location) {
    for(int i=0; i <= location->length; i++) {
        for(int j=0; j <= location->length; j++) {
            map[location->y-i][location->x-j] = X;
        }
    }
}

bool exist(char* file) {
    return (access(file, F_OK) == 0) ? true : false; 
}

// void print_binary(unsigned short** mat, int x, int y) {
//     for(int i=0; i < y; i++) {
//         for(int j=0; j < x; j++) {
//             printf("%hu", mat[i][j]);
//         }
//         puts("");
//     }
// }
char* load_map(char*file) {
    int fd = open(file, O_RDONLY);
    struct stat fs;
    stat(file, &fs);
    char *lines = line(fd);
    char* map = malloc(fs.st_size+1 - strlen(lines));
    int r; off_t readable = fs.st_size - strlen(lines);
    if(( r = read(fd, map, readable)) > 0) {
        map[readable] = '\0';
    }
    return map;
}

unsigned short** parse_binary(char* my_map, int width, int height) {
    unsigned short **map = malloc(sizeof(unsigned short *) * height);
    if (!map)
        return NULL;
    for(int l=0; l < height; l++) // init short array
        map[l] = malloc(sizeof(unsigned short*) * width);

     int l = 0,j=0;
     for(int i=0; my_map[i]!=end; i++)
        if (my_map[i] == '\n') l++, j=0;
        else
            map[l][j++] = (my_map[i] == '.'); // fill array
    return map;
}
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
void fill_0(unsigned short **mt, int w, int h) {
    for(int i=0; i<w; i++)
        mt[0][i] = 0;
    for(int i=0;i<h; i++)
        mt[i][0] = 0;
}
void pt_malloc(unsigned short **mt, int w, int h) {
    for(int i=0; i < h; i++)
        mt[i] = malloc(sizeof(unsigned short*) * (w+1));
}
square* solver(unsigned short** matrix, int w, int h) {
    square* ans = malloc(sizeof(square));
    ans->x = 0;
    ans->y = 0;
    ans->length = 0;
    unsigned short **temp = malloc(sizeof(unsigned short*) * (h+1));
    pt_malloc(temp, w+1, h+1);
    fill_0(temp, w+1, h+1);
    int len;
    for(int i=0; i < h; i++) {
        for(int j=0; j<w; j++) {
            if(matrix[i][j] != 0) {
                len = set_min(temp, j+1, i+1);
                if(len > ans->length) {
                    ans->x = j;
                    ans->y = i;
                    ans->length = len;
                }
            }
            else
                temp[i+1][j+1] = matrix[i][j];
        }
    }
    // print_binary(temp, w+1, h+1);
    return ans;
}
int set_min(unsigned short **mt, int x, int y) { // set minimum
    unsigned short min = mt[y][x-1];
    if (min > mt[y-1][x])
        min = mt[y-1][x];
    if (min > mt[y-1][x-1])
        min = mt[y-1][x-1];
    if(min != 0) {
        mt[y][x] = min+1;
        return (int)min;
    }
    else
        mt[y][x] = 1;
    return 0;
}
//  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *