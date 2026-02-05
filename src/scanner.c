#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "scanner.h" 

#include <stdlib.h>

#define MAX_STATES       1024
#define MAX_TRANSITIONS  4096

#define EPSILON '\0'
#define NO_TARGET (-1)

State      states[MAX_STATES];
Transition transitions[MAX_TRANSITIONS];

int state_count = 0;
int transition_count = 0;

static int is_literal(char c) {
    return isalnum(c);  // estendibile
}

static int can_end_expr(char c) {
    return is_literal(c) || c == ')' || c == '*';
}

static int can_start_expr(char c) {
    return is_literal(c) || c == '(';
}

static char *insert_concatenation(const char *re) {
    size_t len = strlen(re);
    // worst case: every char needs a '.'
    char *out = malloc(2 * len + 1);
    if (!out) return NULL;

    size_t j = 0;

    for (size_t i = 0; i < len; i++) {
        char curr = re[i];
        out[j++] = curr;

        if (i + 1 < len) {
            char next = re[i + 1];

            if (can_end_expr(curr) && can_start_expr(next)) {
                out[j++] = '.';
            }
        }
    }

    out[j] = '\0';
    return out;
}


static void push_frag(FragStack *s, Fragment f) {
    s->data[++s->top] = f;
}

static Fragment pop_frag(FragStack *s) {
    return s->data[s->top--];
}

static void push_op(OpStack *s, char op) {
    s->data[++s->top] = op;
}

static char pop_op(OpStack *s) {
    return s->data[s->top--];
}

static char peek_op(OpStack *s) {
    return s->data[s->top];
}

static int new_state(void) {
    int i = state_count++;
    states[i].first_transition = -1;
    return i;
}

static int new_transition(char symbol, int target) {
    int i = transition_count++;
    transitions[i].symbol = symbol;
    transitions[i].target = target;
    transitions[i].next = -1;
    return i;
}

static void add_transition(int state, int trans) {
    transitions[trans].next = states[state].first_transition;
    states[state].first_transition = trans;
}

static OutList *make_outlist(int t) {
    OutList *o = malloc(sizeof(OutList));
    o->transition = t;
    o->next = NULL;
    return o;
}

static OutList *append_outlist(OutList *a, OutList *b) {
    if (!a) return b;
    OutList *p = a;
    while (p->next) p = p->next;
    p->next = b;
    return a;
}

static void patch(OutList *list, int target) {
    while (list) {
        transitions[list->transition].target = target;
        list = list->next;
    }
}

static int precedence(char op) {
    switch (op) {
        case '*': return 3;
        case '.': return 2;
        case '|': return 1;
        default:  return 0;
    }
}

static void apply_operator(char op, FragStack *fs) {
    if (op == '*') {
        Fragment e = pop_frag(fs);

        int s = new_state();
        int t1 = new_transition(EPSILON, e.start);
        int t2 = new_transition(EPSILON, NO_TARGET);

        add_transition(s, t1);
        add_transition(s, t2);

        patch(e.out, s);

        Fragment r = { s, make_outlist(t2) };
        push_frag(fs, r);
    }

    else if (op == '.') {
        Fragment e2 = pop_frag(fs);
        Fragment e1 = pop_frag(fs);

        patch(e1.out, e2.start);

        Fragment r = { e1.start, e2.out };
        push_frag(fs, r);
    }

    else if (op == '|') {
        Fragment e2 = pop_frag(fs);
        Fragment e1 = pop_frag(fs);

        int s = new_state();

        int t1 = new_transition(EPSILON, e1.start);
        int t2 = new_transition(EPSILON, e2.start);

        add_transition(s, t1);
        add_transition(s, t2);

        Fragment r = {
            s,
            append_outlist(e1.out, e2.out)
        };
        push_frag(fs, r);
    }
}

Fragment thompson(const char *re) {
    FragStack fs = {.top = -1};
    OpStack   os = {.top = -1};

    char *ext_re = insert_concatenation(re);

    for (int i = 0; ext_re[i]; i++) {
        char c = ext_re[i];

        if (c == '(') {
            push_op(&os, c);
        }

        else if (c == ')') {
            while (peek_op(&os) != '(')
                apply_operator(pop_op(&os), &fs);
            pop_op(&os);
        }

        else if (c == '*' || c == '.' || c == '|') {
            while (os.top >= 0 &&
                   precedence(peek_op(&os)) >= precedence(c))
                apply_operator(pop_op(&os), &fs);
            push_op(&os, c);
        }

        else { // simbolo
            int s = new_state();
            int t = new_transition(c, NO_TARGET);
            add_transition(s, t);

            Fragment f = { s, make_outlist(t) };
            push_frag(&fs, f);
        }
    }

    while (os.top >= 0)
        apply_operator(pop_op(&os), &fs);

    return pop_frag(&fs);
}

int finish_nfa(Fragment f) {
    int final = new_state();
    patch(f.out, final);
    return f.start;
}

