#ifndef STRUCT
#define STRUCT

/// @brief Represent a node of NFA produced by Thompson transormation.
/// if state is 1 it's an accepting state and other props are set to NULL.
typedef struct TNode {
    unsigned state : 1;
    char c;
    struct TNode *to;
    struct TNode *empty_to1; // empty-transition 1
    struct TNode *empty_to2; // empty-transition 2
} TNode;

#endif