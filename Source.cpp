#include "Header.h"


int main()
{
	char s[20];
	gets(s);
	FILE* fname = fopen(s, "r+");
	//FILE* fout = fopen("out.txt", "w+");
	if (!(fname))
		exit(1);
	char command1[7] = "", command2[7] = "", command3[7] = "", command4[7] = "";
	struct variable variables[25];
	struct label labels[10];
	struct interlanguage intlang[50];
	int stack[10];
	int n = 0, symbolsize = 1, labeltop = 0, instrns = 0,top=0;
	while (fgets(s,20,fname))
	{
		sscanf(s, "%s %s %s %s", command1, command2,command3,command4);
		if (isEqual(command1, "DATA"))
		{
			symbolsize = isarray(command2,command3);
			if (n == 0)
			{
				strcpy(variables[0].name, command3);
				variables[0].address = 0;
				variables[0].size = symbolsize;
				n++;
			}
			else
			{
				updatesymboltable(variables, n, command3, symbolsize);
				n++;
			}
		}
		else if (isEqual(command1, "CONST"))
		{
			symbolsize = isarray(command2, command3);
			if (n == 0)
			{
				strcpy(variables[0].name, command3);
				variables[0].address = 0;
				variables[0].size = 0;
				n++;
			}
			else
			{
				updatesymboltable(variables, n, command3,0);
				n++;
			}
		}
		else if (opcode(command1))
		{
			int ocode = opcode(command1);
			if (ocode != 1)
			{
				write(intlang, instrns, variables, n, labels, labeltop, stack, &top, ocode, command2, command3, command4);
				instrns++;
			}
			else
			{
				if (command3[strlen(command3) - 1] == 'X')
				{
					ocode = 1;
					write(intlang, instrns, variables, n, labels, labeltop, stack, &top, ocode, command2, command3, command4);
					instrns++;
				}
				else
				{
					ocode = 2;
					write(intlang, instrns, variables, n, labels, labeltop, stack, &top, ocode, command2, command3, command4);
					instrns++;
				}
			}
		}
		else if (islabel(command1) && !isEqual(command1, "START:") && !isEqual(command1, "END"))
		{
			updatelabeltable(labels,labeltop,remco(command1),instrns);
			labeltop++;
		}
		else if (isEqual(command1, "ELSE"))
		{
			intlang[instrns].slno = instrns;
			intlang[instrns].opcode = 6;
			intlang[instrns].parameters[0] = 9999;
			intlang[instrns].parameters[1] = -1;
			intlang[instrns].parameters[2] = -1;
			intlang[instrns].parameters[3] = -1;
			stack[top] = instrns;
			top++;
			updatelabeltable(labels, labeltop, "ELSE", instrns + 1);
			labeltop++;
			instrns++;
		}
		else if (isEqual(command1, "ENDIF"))
		{
			updatelabeltable(labels, labeltop, "ENDIF", instrns);
			labeltop++;
			int in = stack[--top];
			if (intlang[in].opcode == 6)
			{
				intlang[in].parameters[0] = labels[--labeltop].address;
				int x = stack[--top];
				intlang[x].parameters[3] = labels[--labeltop].address;
			}
			if (intlang[in].opcode == 7)
			{
				intlang[in].parameters[3] = labels[--labeltop].address;
			}
		}
	}
	print(intlang, instrns);
	fclose(fname);
	_getch();
}