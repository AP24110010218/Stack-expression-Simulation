#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100

// Stack for characters (operators)
char stackOp[MAX];
int topOp = -1;

// Stack for integers (operands)
int stackVal[MAX];
int topVal = -1;

// Operator stack functions
void pushOp(char x) {
    stackOp[++topOp] = x;
}

char popOp() {
    return stackOp[topOp--];
}

// Value stack functions
void pushVal(int x) {
    stackVal[++topVal] = x;
}

int popVal() {
    return stackVal[topVal--];
}

// Check precedence
int precedence(char op) {
    if (op == '*' || op == '/')
        return 2;
    if (op == '+' || op == '-')
        return 1;
    return 0;
}

// Convert infix to postfix
void infixToPostfix(char infix[], char postfix[]) {
    int i, k = 0;
    for (i = 0; infix[i] != '\0'; i++) {

        if (isdigit(infix[i])) {  
            while (isdigit(infix[i])) { 
                postfix[k++] = infix[i++];
            }
            postfix[k++] = ' ';
            i--;
        }

        else if (infix[i] == '(') {
            pushOp(infix[i]);
        }

        else if (infix[i] == ')') {
            while (topOp != -1 && stackOp[topOp] != '(') {
                postfix[k++] = popOp();
                postfix[k++] = ' ';
            }
            popOp(); 
        }

        else { 
            while (topOp != -1 && precedence(stackOp[topOp]) >= precedence(infix[i])) {
                postfix[k++] = popOp();
                postfix[k++] = ' ';
            }
            pushOp(infix[i]);
        }
    }

    while (topOp != -1) {
        postfix[k++] = popOp();
        postfix[k++] = ' ';
    }

    postfix[k] = '\0';
}

// Evaluate postfix
int evaluatePostfix(char postfix[]) {
    int i;
    for (i = 0; postfix[i] != '\0'; i++) {

        if (isdigit(postfix[i])) { 
            int num = 0;
            while (isdigit(postfix[i])) {
                num = num * 10 + (postfix[i] - '0');
                i++;
            }
            pushVal(num);
        }
        
        else if (postfix[i] == '+' || postfix[i] == '-' ||
                 postfix[i] == '*' || postfix[i] == '/') {

            int val2 = popVal();
            int val1 = popVal();

            switch (postfix[i]) {
                case '+': pushVal(val1 + val2); break;
                case '-': pushVal(val1 - val2); break;
                case '*': pushVal(val1 * val2); break;
                case '/': pushVal(val1 / val2); break;
            }
        }
    }
    return popVal();
}

// MAIN PROGRAM
int main() {
    char infix[MAX], postfix[MAX];

    printf("Enter an infix expression: ");
    fgets(infix, MAX, stdin);

    infixToPostfix(infix, postfix);

    printf("\nPostfix Expression: %s\n", postfix);
    printf("Evaluation Result = %d\n", evaluatePostfix(postfix));

    return 0;
}
