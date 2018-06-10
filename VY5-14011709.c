/*

Veri Yapilari ve Algoritmalari proje odevi

14011709-Muharrem Caglar Kurt

Dev-C

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
typedef struct STACK{
    int position;
    int capacity;
    char** array;
} STACK;


STACK* createStack(int capacity){
    int i;
    STACK* stack = (STACK*)malloc(sizeof(STACK));
    if(!stack){
        return NULL;
    }
    stack->position = -1;
    stack->capacity = capacity;
    stack->array = (char**)malloc(stack->capacity * sizeof(char*));
    if(!stack->array){
        return NULL;
    }
    for(i=0; i<stack->capacity; i++){
        stack->array[i] = (char*)malloc(sizeof(char));
    }
    return stack;
}
/*
 ..
 .
 .
 */
/*
 clear stack
 */
void clearStack(STACK* stack){
    stack->position = -1;
}

void infoPrint(STACK* stack, char* postfix){
    int i;
    printf("POSTFIX : %15s");
    printf("\t\t%s", "STACK : ");
    for(i=0; i<(stack->position) + 1; i++){
        printf("%s  ", stack->array[i]);
    }
    printf("\n");
}
/*
 if stack null true, not null false return.
 */
bool isEmpty(STACK* stack){
    if (stack->position == -1) {
        return true;
    }
    return false;
}
/*
 Stack value of the last element.
 */
char* topValue(STACK* stack){
    char* value = (char*)malloc(sizeof(char));
    strcpy(value, stack->array[stack->position]);
    return value;
}
/*
 Stack adds element.
 */
void push(STACK* stack, char* eleman){
    stack->position++;
    stack->array[stack->position] = (char*)malloc( (strlen(eleman)) * sizeof(char) );
    strcpy(stack->array[stack->position], eleman);
}
/*
 Stack attracts elements.
 */
char* pop(STACK* stack){
    char* eleman = (char*)malloc(sizeof(char));
    if( !isEmpty(stack) ){
        strcpy(eleman, stack->array[stack->position]);
        stack->array[stack->position] = NULL;
        stack->position--;
        return eleman;
    }
    return NULL;
}
/*
operation priority
 */
int priority(char x){
    if(x == '+' || x == '-')
        return 1;
    if(x == '*' || x == '/')
        return 2;
    if(x == '^')
        return 3;
    return -1;
}
/*
check whether it is variable
 */
bool isOperand(char *array){
    char x;
    if( strlen(array) == 1 ){
        x = array[0];
        if( (x >= 'a' && x <= 'z') || (x >= 'A' && x <= 'Z') ){
            return true;
        }
        return false;
    }
    return false;
}
/*
check variable is number
*/
bool isNumber(char *array){
    int number = atoi(array);
    if( number ){
        return true;
    }
    return false;
}
/*
delete spaces in operation
 */
char** nonSpace(char* ifade, int *boyut){
    char **new;
    const char*empty=" ";
    char* birkelime=NULL;
    new = (char**)malloc(50 * sizeof(char*));
    int i = 0;
    birkelime = strtok(ifade, empty);
    while(birkelime!=NULL){
        new[i] = (char*)malloc(sizeof(char));
        strcpy(new[i++], birkelime);
        birkelime=strtok(NULL,empty);
    }
    (*boyut) = i;
    return new;
    
}
/*
 infix to postfix.
 */
char* infixToPostfix(STACK* stack, char* ifade){
    int i, j, outputPosition, boyut, length;
    char* output;
    char* temp;
    char** new;
    output = (char*)malloc(50*sizeof(char));
    temp = (char*)malloc(sizeof(char));
    outputPosition = 0;
    boyut = 0;
    new = nonSpace(ifade, &boyut);
    clearStack(stack);
    for(i=0; i < boyut; i++){
        if( isOperand(new[i]) || isNumber(new[i])){
            length = (int)strlen(new[i]);
            if( length == 1){
                output[ outputPosition ] = new[i][0];
                output[ outputPosition +1 ] = ' ';
                outputPosition += 2;
            } else {
                for(j=0; j<length; j++){
                    output[ outputPosition++ ] = new[i][j];
                }
                output[ outputPosition++ ] = ' ';
            }
            
        } else if ( new[i][0] == '(' ){ 
            push(stack, new[i]);
        } else if ( new[i][0] == ')' ){
            while( !isEmpty(stack) && topValue(stack)[0]!='(' ){
                temp = pop(stack);
                for(j=0; j<strlen(temp); j++){
                    output[ outputPosition++ ] = temp[j];
                }
                output[ outputPosition ] = ' ';
                outputPosition++;
                pop(stack);
            }
        } else {
            while ( !isEmpty(stack) && (priority(new[i][0]) <= priority(topValue(stack)[0])) ){
                temp = pop(stack);
                for(j=0; j<strlen(temp); j++){
                    output[ outputPosition++ ] = temp[j];
                }
                output[ outputPosition ] = ' ';
                outputPosition++;
            }
            push(stack, new[i]);
        }
        output[ outputPosition ] = '\0';
        infoPrint(stack, output);
    }
    if( !isEmpty(stack) ){
        while (!isEmpty(stack)) {
            temp = pop(stack);
            for(j=0; j<strlen(temp); j++){
                output[ outputPosition++ ] = temp[j];
            }
            output[ outputPosition ] = ' ';
            outputPosition++;
        }
        output[ outputPosition ] = '\0';
        infoPrint(stack, output);
    } else {
        output[ outputPosition ] = '\0';
    }
 
    return output;
}
/*
 .
 .
 .
 .
 */
void processPrint(STACK* stack){
    int i;
    printf("\nSTACK : ");
    for(i=0; i<(stack->position) + 1; i++){
        printf("%s  ", stack->array[i]);
    }
}
char* intToChar(int number){
    char *charNumber;
    charNumber = (char*)malloc(sizeof(char));
    sprintf(charNumber, "%d", number);
    return charNumber;
}
int postfixToValue(STACK* stack, int* variables, char* postfix){
    int i, boyut, result, temp, value1, value2;
    char **postfixParca;
    char *charTemp;
    charTemp = (char*)malloc(sizeof(char));
    boyut = 0;
    result = 0;
    postfixParca = nonSpace(postfix, &boyut);
    clearStack(stack);
    for(i=0;i<boyut;i++){
        if( isOperand( postfixParca[i] ) ){
            temp = variables[ postfixParca[i][0] - 'A' ];
            charTemp = intToChar(temp);
            push(stack, charTemp);
        } else if ( isNumber( postfixParca[i] ) ){
            push(stack, postfixParca[i]);
        } else {
            value1 = atoi( pop(stack) );
            value2 = atoi( pop(stack) );
            if( postfixParca[i][0] == '+' ){
                temp = value2 + value1;
            } else if( postfixParca[i][0] == '-' ){
                temp = value2 - value1;
            } else if( postfixParca[i][0] == '*' ){
                temp = value2 * value1;
            } else if( postfixParca[i][0] == '/' ){
                temp = value2 / value1;
            }
            charTemp = intToChar(temp);
            push(stack, charTemp);
        }
        processPrint(stack);
    }
    result = atoi( pop(stack) );
    return result;
}
/*
 .
 .
 
 .
 .*/
char **readFile(int *rowNumber){
    int i;
    char **rows = (char**)malloc(20*sizeof(char*));
    char *temp = (char*)malloc(sizeof(char));
    FILE *fp = fopen("input.txt", "r");
    if (fp == NULL){
        puts("File not found");
        exit(-1);
    }
    i=0;
    while (!feof(fp)) {
        fgets(temp, 100, fp);
        rows[i] = (char*)malloc(sizeof(char));
        strcpy(rows[i++], temp);
    }
    (*rowNumber) = i;
    //rows = (char**)realloc(rows, (i-1)*sizeof(char*));
    return rows;
}
void ifadeAyir(char* row, char* left, char* right){
    int i, j, k;
    char temp[50];
    for(i=0; row[i]!='='; i++){
        temp[i] = row[i];
    }
    temp[i-1] = '\0';
    strcpy( left, temp );
    k = 0;
    for( j=i+2; row[j]!=';'; j++){
        temp[k++] = row[j];
    }
    temp[k-1] = '\0';
    strcpy(right, temp);
}
int main(int argc, char *argv[]) {
    int i, rowNumber=0, result=0, first;
    int *variables;
    int matrix[20][20];
    char *left, *right, *postfix;
    variables = (int*)calloc(58, sizeof(int));
    char** rows = readFile(&rowNumber);
    left = (char*)malloc(sizeof(char));
    right = (char*)malloc(sizeof(char));
    postfix = (char*)malloc(sizeof(char));
    STACK* stack = createStack(100);
    if( stack == NULL ){
        printf("Stack could not create!");
        return -1;
    }
    for(i=0; i<rowNumber; i++){
        ifadeAyir(rows[i], left, right);
        printf("\n-----------------------------------");
        printf("\n%d. OPERATION -> %s\n", i+1, rows[i]);
        postfix = infixToPostfix(stack, right);
        first = variables[left[0] - 'A'];
        result = postfixToValue(stack, variables, postfix);
        printf("\nVariable => %c\t\tFirst = %d \t\tThen = %d\n", left[0], first, result);
        variables[left[0] - 'A'] = result;
        matrix[i][0] = left[0] - 'A';
        matrix[i][1] = result;
    }
    printf("\nAll Results\n"); 
    for(i=0; i<rowNumber; i++){
        printf("\n-> %c = %d ", matrix[i][0] + 'A', matrix[i][1]);
    }
    printf("\n");
    return 0;
}

