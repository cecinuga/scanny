#ifndef STRUCT
#define STRUCT

typedef struct Transition {
    char symbol;          // simbolo o EPSILON
    int  target;          // stato target
    int  next;            // prossima transizione dello stesso stato
} Transition;


typedef struct {
    int first_transition;  // indice nella transitions[]
} State;

typedef struct OutList {
    int transition;
    struct OutList *next;
} OutList;

typedef struct {
    int start;
    OutList *out;
} Fragment;

typedef struct {
    Fragment data[1024];
    int top;
} FragStack;

typedef struct {
    char data[1024];
    int top;
} OpStack;


Fragment thompson(const char *re);
int finish_nfa(Fragment f);

#endif