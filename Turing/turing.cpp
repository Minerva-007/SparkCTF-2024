#include"stdio.h"
#include"string.h"

unsigned char arr[256]="**REDACTED**";
// i increment
// a add 5
// s subtract 3
// x xor with previous
// y xor with next
// d display

char command[1024]="aaiasiasassaiaasaiaiaaasssiasisaasiasissaiaasaiasisaisaisaiiaasaiassissaiasii";

int main()
{
	int index=0;
	for(int count=0;count<strlen(command);count++)
	{
		switch(command[count])
		{
			case 'a':
				arr[index]+=5;
				break;
			case 's':
				arr[index]-=3;
				break;
			case 'x':
				arr[index]=arr[index]^arr[index-1];
				break;
			case 'i':
				index++;
				break;
			case 'd':
				printf("%s",arr);				
		}
	}
}

