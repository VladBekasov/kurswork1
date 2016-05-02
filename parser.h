#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

void parserXMLtoTXT(char *str, char *buf){
	int i = 0;
	int n = 0;
	int find = 0;
	while (str[i] != '\0') {
		if (str[i] == '<' && str[i+1] == 'b' && str[i+2] == 'r' && str[i+3] == '>') {
			
			i += 4;	
			
			buf[n] = '\n';
			n++;
		}
		if (str[i] == '<' && str[i+1] == 'p' && str[i+2] == '>') {
			find = 1;
			i += 3;
		}
		if (str[i] == '<' && str[i+1] == '/' && str[i+2] == 'p' && str[i+3] == '>') {
			find = 0;
			i += 3;
			buf[n] = '\n';
			n++;
		}

		if (str[i] == '<') {
			while (str[i] != '>') {
				i++;
			}
		}
		if (find == 1) {
			buf[n] = str[i];
			n++;	
		}
		i++;
	}
}


