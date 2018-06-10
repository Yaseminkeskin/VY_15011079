#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 100

char stack[SIZE] = {"\0"};
char stack1[SIZE] = {"\0"};
int top = 0;
int top1 = 0;
const int operatorValues[] = {1, 0, 0, 0, 0, 1};      // for priority 

void readFile(char*);                    
void infixToPostfix(char*, char*);
int isEmpty(char*);
int isFull(char*);
void push(char*, char);
char pop(char*);
int priority(char, char);
char last_element(char*);
void postfixSolution(char*);

int main() {

	int i;
	char operation[100] = "\0";
	char postfix[100] = "\0";
	
	readFile(operation);
	infixToPostfix(operation, postfix);
	printf(" Last Values:\n");
	printf(" ____________\n");
	postfixSolution(postfix);
	return 0;
}
   	
void readFile(char* target)    // This function reads data from text
{
	FILE* fp = fopen("input.txt","r");
	if(!fp)
	{
		printf("File not found!\n");
		exit(1);
	}
	char ch;
	int i=0;
	while(!feof(fp))
	{
		ch = fgetc(fp);
		target[i] = ch;
		i++;
	   	if(ch == ';')
		{
			target[i] = ' ';
			i++;
			fgetc(fp);
		}
		
   	}
   	printf(" Infix array:\n ______________\n");
   	printf(" %s\n\n", target);
   	fclose(fp);
}

int isEmpty(char* stackCopy)        // Stack control
{
	return top == 0;
}

int isFull(char* stackCopy)
{
	return top == SIZE;
}

void push(char* stackCopy, char value)
{
	if(isFull(stackCopy))
	{
		printf("Stack is full...\n");
		return;
	} 
	stackCopy[top] = value;
	top++;
}

char pop(char* stackCopy)
{
	if(isEmpty(stackCopy))
	{
		printf("Stack is empty... (pop)\n");
		return -1;
	}
	top--;
	return stackCopy[top];
}

char last_element(char* stackCopy)    //  This function finds last element in the stack
{
	if(isEmpty(stackCopy))
		return -1;
	return stackCopy[top-1];
}

int priority(char a, char b)        // this function find top priority operator 
{
	if(b == -1)
		return 1;
	return operatorValues[a-42] > operatorValues[b-42];
}

void infixToPostfix(char* infix, char* postfix) 
{
	int i, j=0, k;
	char ch_infix, stackpop;
	for(i=0 ; infix[i] != '\0' ; i++)
	{
		if(infix[i] == ';')
		{
			//  all stack' element send to postfix
		    while(!isEmpty(stack))
		    {
		    	postfix[j++] = pop(stack);
		    	postfix[j++] = ' ';
			}
			
			postfix[j++] = '\n';
			postfix[j++] = ' ';
			postfix[j] = '\0';
		}
		else if(infix[i]!=' ')
		{
			ch_infix = infix[i];  // ch_infix = ';'
			
			if(ch_infix == '(')
				push(stack, ch_infix);
			else if(ch_infix == ')')
			{
				stackpop = pop(stack);
				while(stackpop != '(')
				{
					 postfix[j++] = stackpop;
					 postfix[j++] = ' ';
					 stackpop = pop(stack);
				}
			}
			else if(isalnum(ch_infix) || ch_infix == '=')  
			{ 
				postfix[j++] = ch_infix;
				postfix[j++] = ' ';
			}
			else	// if ch is an operator
			{
				if(last_element(stack) != '(' && !priority(ch_infix, last_element(stack)))
				{
					while(!priority(ch_infix, last_element(stack))) 
					{
						stackpop = pop(stack);
						postfix[j++] = stackpop;
					 	postfix[j++] = ' ';	
					}
				}
				push(stack, ch_infix);
			}
		}
	}
	printf(" Infix to postfix :\n ___________________\n %s\n\n", postfix);
}

void postfixSolution(char*postfixS)
{
	int  op1, op2, op;
	int k ,j, i;
	char ch, value[50] = {"\0"};
	for(i=0; postfixS[i] != '\0' ; i++)
	{
		if(postfixS[i] == '=')
		{
			j = i-2;
			k = postfixS[j]-97;
		}
		if(postfixS[i] == '\n')
		{
			value[k] = pop(stack1);
			printf(" %c <- %d\n",k+97, value[k]);
		}
		
		else
		{
			ch = postfixS[i];
			if(isdigit(ch))
			{
				ch = ch - 48;
				push(stack1, ch);
			}
			else if(isalnum(ch))
			{
				ch = ch - 97;	
				push(stack1, value[ch]);	
			}
			else if(ch == '+')
			{
				op1 = pop(stack1);
				op2 = pop(stack1);
				op = op1 + op2;
				push(stack1, op);
		    }
		    else if(ch == '-')
			{
				op1 = pop(stack1);
				op2 = pop(stack1);
				op = op2 - op1;
				push(stack1, op);
		    }
			else if(ch == '*') 
			{
				op1 = pop(stack1);
				op2 = pop(stack1);
				op = op1 * op2;
				push(stack1, op);
		    }
		    else if(ch == '/')
		    {
				op1 = pop(stack1);
				op2 = pop(stack1);
			    op = op2 / op1;
				push(stack1, op);
			}
		}	
    }
}
