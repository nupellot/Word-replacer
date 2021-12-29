#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


int main(void) {
  FILE* base = fopen("base", "r+");
	FILE* source = fopen("source", "w");
	if (base == NULL || source == NULL) {
		printf("Ошибка открытия файла\n");
		exit(1);
	}

	// Делаем рандомайзер более рандомным.
	srand(time(NULL));
	// Объявляем используемые функции.
	char getRandomPunctuationMark();

	
	char c;
	// Подсчитываем количество слов в базе данных.
	int amountOfBaseWords = 0;
	while ((c = fgetc(base)) != EOF && c != '#') {
		if (c == '\n') amountOfBaseWords++;
	}
	printf("%d\n", amountOfBaseWords);

	// Выделение памяти под массив слов из базы данных.
	char** baseWords = (char**)malloc(sizeof(char) * 50 * amountOfBaseWords);
	for (int i = 0; i < amountOfBaseWords; i++) {
		// Под каждое конкретное слово в массиве.
		baseWords[i] = (char*)malloc(sizeof(char) * 50);
	}

	// Запись слов в базу данных.
	fseek(base, 0, 0);
	for (int i = 0; i < amountOfBaseWords; i++) {
		fscanf(base, "%s\n", baseWords[i]);
	}

	// Вывод считанных слов из базы данных.
	for (int i = 0; i < amountOfBaseWords; i++) {
		printf("%s\n", baseWords[i]);
	}	

	printf("Введите требуемое количество слов в файле:\n");
	int amountOfSourceWords;
	scanf("%d", &amountOfSourceWords);
	for (int i = 0; i < amountOfSourceWords; i++) {
		fprintf(source, "%s", baseWords[rand() % amountOfBaseWords]);
		if (rand() % 5 == 0) fprintf(source, "%c", getRandomPunctuationMark());
		fprintf(source, " ");
	}

	FILE* replacer = fopen("replacer", "r+");
	if (replacer == NULL) {
		printf("Ошибка открытия файла\n");
		exit(1);
	}
	char replaced[50];
	char replacing[50];
	fscanf(replacer, "%s", replaced);
	fscanf(replacer, "%s", replacing);
	printf("%s\n%s\n", replaced, replacing);
}

// Генератор случайного знака препинания.
char getRandomPunctuationMark() {
	int n = rand() % 5;
	if (n == 0) return '.';
	if (n == 1) return ',';
	if (n == 2) return ':';
	if (n == 3) return '!';
	if (n == 4) return '?';
	return -1;
}