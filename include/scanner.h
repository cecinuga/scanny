#ifndef STRUCT
#define STRUCT

typedef enum TransactionType {
    TRANSACTION_TOKEN,
    TRANSACTION_EPSILON
} TransactionType;

typedef struct Fragment {
    int start;
    int *outs;
} Fragment;

typedef struct State {
    int id;
    int *outs;
} State;

typedef struct Transaction {
    TransactionType typo;
    char token;
    int target;
} Transaction;

int thompson(char *input);

#endif