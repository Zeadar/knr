#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NUMBER '0'
#define CLEAR 'c'
#define SWAP 's'
#define DUP 'd'

#define MAXOP 100
#define MAXVAL 100

int getop(char[]);
void push(double);
double pop(void);
void print_elems(void);
void clear_elems(void);
void swap_elems(void);
void dup_elems(void);

int main() {
    int type;
    double op2;
    char s[MAXOP];

    while ((type = getop(s)) != EOF) {
        switch (type) {
        case SWAP:
            swap_elems();
            break;
        case DUP:
            dup_elems();
            break;
        case CLEAR:
            clear_elems();
            break;
        case NUMBER:
            push(atof(s));
            break;
        case '^':
            op2 = pop();
            push(pow(pop(), op2));
            break;
        case '+':
            push(pop() + pop());
            break;
        case '*':
            push(pop() * pop());
            break;
        case '-':
            op2 = pop();
            push(pop() - op2);
            break;
        case '/':
            op2 = pop();
            if (op2 != 0.0)
                push(pop() / op2);
            else
                printf("error: zero divisor\n");
            break;
        case '%':
            op2 = pop();
            push((int) pop() % (int) op2);
            break;
        case '\n':
            // printf("\t%.8f\n", pop());
            print_elems();
            break;
        default:
            printf("error: unknown command %s\n", s);
            break;
        }
    }

    return 0;
}

#define MAXVAL 100

int sp = 0;
double val[MAXVAL];

void push(double f) {
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

double pop(void) {
    if (sp > 0)
        return val[--sp];

    printf("error: cannot pop() empty stack\n");
    return 0.0;
}

void print_elems(void) {
    int i;
    printf("\t");
    for (i = 0; i < sp; ++i)
        printf("%.8f ", val[i]);
    putchar('\n');
}

void clear_elems(void) {
    sp = 0;
}

void dup_elems(void) {
    if (sp > 0)
        push(val[sp - 1]);
    else
        printf("Nothing to duplicate");
}

void swap_elems(void) {
    if (sp > 1) {
        double temp = val[sp - 1];
        val[sp - 1] = val[sp - 2];
        val[sp - 2] = temp;
    } else
        printf("Cannot swap less than two values");
}

int getch(void);
void ungetch(int);

int getop(char s[]) {
    int i, c;

    while ((s[0] = c = getch()) == ' ' || c == '\t');

    s[1] = '\0';

    if (!isdigit(c) && c != '.' && c != '-')
        return c;               //probably an operator

    i = 0;

    if (c == '-') {
        c = getch();

        if (!isdigit(c)) {
            ungetch(c);
            return '-';         //subtraction operator
        }

        s[++i] = c;
    }

    if (isdigit(c))
        while (isdigit(s[++i] = c = getch()));

    if (c == '.')
        while (isdigit(s[++i] = c = getch()));

    s[i] = '\0';

    if (c != EOF)
        ungetch(c);

    return NUMBER;
}

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}
