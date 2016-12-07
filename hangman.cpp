#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<time.h>

void gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void hangman_(int parts, char * word_with_blanks){
	gotoxy(0, 0);
	char * FULL[] = { "    ==========   \n" ,"        |        \n","      (^ ^)      \n","     /  |  \\    \n","        /\\      \n"};
	for (int i = 0; i <= parts; i++)
		printf("%s", FULL[i]);
	for (int i = parts; i < 5; i++)
		printf("\n");
	printf("WORD : %s", word_with_blanks);
}

bool _check_(char * word, char letter, char * spaces_word, int * spaces){
	bool is_there = false;
	int pos = 0;
	*spaces = 0;
	while (word[pos] != 0){
		if (word[pos] == letter || word[pos] + 'A' - 'a' == letter){
			is_there = true;
		}
		if (word[pos] == letter){
			spaces_word[pos] = letter;
		}
		if (spaces_word[pos] == '_')
			(*spaces)++;
		pos++;
	}
	return is_there;
}

void fail(char * word){
	gotoxy(0, 9);
	printf("Failed..... word is '%s'", word);
}

void success(char * word){
	gotoxy(0, 9);
	printf("Success. The man is safe... :) word is '%s'", word);
}

void __init__(char * word){
	char spaces[100]; int i = 0;
	while (word[i] != 0 && word[i] != '\n')
		spaces[i++] = '_';
	spaces[i] = 0;
	int spaces_count = 0, len = i;
	int CHANCES = 6;
	word[len] = 0;
	hangman_(-1, spaces);
	while (true){
		gotoxy(0, 9);
		printf("\nENTER A LETTER :  \b");
		char ch = getchar();
		fflush(stdin);
		system("cls");
		if (!_check_(word, ch, spaces, &spaces_count)){
			CHANCES--;
			if (CHANCES == 0){
				fail(word); return;
			}
		} 
		hangman_(5 - CHANCES, spaces);
		if (spaces_count == 0){
			success(word); return;
		}
	}
}

void word_from_file(FILE * fp, int line, char * word){
	int curr = 0;
	while (true){
		char ch = fgetc(fp);
		if (ch == '\n')
			curr++;
		if (curr + 1 == line){
			break;
		}
	}
	int pos = 0;
	while (true){
		word[pos++] = fgetc(fp);
		if (word[pos - 1] == '\n' || word[pos - 1] == -1)
			break;
	}
	word[pos] = 0;
}

void main(){
	char letter[100];
	FILE * fp = fopen("dicts.baba", "r");
	srand(time(NULL));
	int num = rand();
	word_from_file(fp, num % 113821, letter);
	fclose(fp);
	__init__(letter);
	_getch();
}