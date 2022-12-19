#include <stdio.h>
#include <string.h>

char *AskForStringAndWait(char *prompt)
{
    char lineBuf[100];
    int debug = 1;
    // Read in a string into lineBuf
    printf("%s", prompt);
    while (!fgets(lineBuf, 100, stdin))
    printf("A string please: ");
    // Convert trailing newline character into the end of string marker
    char *r = strchr(lineBuf, '\n');
    if (r) {
    *r = '\0';
    if (debug) {
    printf ("debug\n"); 
    }
    }
    return strdup(lineBuf);
}

int main () 
{
    char *s;
    s = AskForStringAndWait("What's Your Name?");
    printf ("Your name is %s.\n",s);
}
