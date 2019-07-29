#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>

struct variable{
	char name[20];
	int address;
	int size;
};

struct label{
	char name[10];
	int address;
};

struct interlanguage{
	int slno;
	int opcode;
	int parameters[4];
};

int isEqual(char *str1, char *str2);
int opcode(char * cmd);
int regcode(char * cmd);
char* getstr(int arr);
int getaddress(struct variable variables[], int n, char* name);
int getlabeladdress(struct label labels[], int labeltop, char * name);
int islabel(char *string);
int getnum(char*s);
int isarray(char* cmd, char * name);
char* remco(char * str);
void write(struct interlanguage intlang[], int instrns, struct variable variables[], int n, struct label labels[], int labeltop, int stack[], int *top, int ocode, char* command2, char *command3, char * command4);
void print(struct interlanguage intlang[], int instrns);
void updatesymboltable(struct variable variables[], int n, char* command3, int size);
void updatelabeltable(struct label labels[], int labeltop, char* command2, int instrns);
