#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS };

void dcl(void);
void dirdcl(void);
int gettoken();

int tokentype;
char token[MAXTOKEN];
char name[MAXTOKEN];
char datatype[MAXTOKEN];
char out[1000];

int main() {
    while (gettoken() != EOF) {
        strcpy(datatype, token);
        out[0] = '\0';
        dcl();
        if (tokentype != '\n')
            printf("syntax error\n");
        printf("%s: %s %s\n", name, out, datatype);
    }
    return 0;
}

void dcl(void) {
    int ns;
    char *out = "out";

    for (ns = 0; gettoken() == '*';)
        ++ns;

    dirdcl();
    while (ns-- > 0)
        strcat(out, " pointer to");
}

void dirdcl() {
    int type;

    if (tokentype == '(') {
        dcl();
        if (tokentype != ')')
            printf("error: missing )\n");

    } else if (tokentype == NAME)
        strcpy(name, token);
}
