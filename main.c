#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MIN_WORDS 10


int main(void) {
  FILE* base = fopen("base", "r+");
	if (base == NULL) {
		printf("Ошибка открытия файла\n");
		exit(1);
	}

	// Делаем рандомайзер более рандомным.
	srand(time(NULL));
	// Объявляем используемые функции.
	char getRandomPunctuationMark();
	void replace(int amountOfSourceWords, char** sourceWords);
	
	char c;
	// Подсчитываем количество слов в базе данных.
	int amountOfBaseWords = 0;
	while ((c = fgetc(base)) != EOF && c != '#') {
		if (c == '\n') amountOfBaseWords++;
	}

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
	fclose(base);

	// Получаем от пользователя требуемое количество слов в исходнике.
	printf("Введите требуемое количество слов в файле:\n");
	int amountOfSourceWords;
	scanf("%d", &amountOfSourceWords);
	if (amountOfSourceWords < MIN_WORDS) {
		printf("Слишком мало слов, введите больше\n");
		exit(2);
	}

	// Выделение памяти под массив слов в исходнике.
	char** sourceWords = (char**)malloc(sizeof(char) * 50 * amountOfSourceWords);
	for (int i = 0; i < amountOfSourceWords; i++) {
		// Под каждое конкретное слово в массиве.
		sourceWords[i] = (char*)malloc(sizeof(char) * 50);
	}
	// Создание массива слов в исходнике.
	for (int i = 0; i < amountOfSourceWords; i++) {
		sourceWords[i] = baseWords[rand() % amountOfBaseWords];
	}

  replace(amountOfSourceWords, sourceWords);

	// Открываем исходник для записи в него данных.
	FILE* source = fopen("source", "w");
	if (source == NULL) {
		printf("Ошибка открытия файла\n");
		exit(1);
	}
	// Записывае в файл измененный массив слов.
	for (int i = 0; i < amountOfSourceWords; i++) {
		fprintf(source, "%s", sourceWords[i]);
		if (rand() % 5 == 0) fprintf(source, "%c", getRandomPunctuationMark());
		fprintf(source, " ");
	}
	fclose(source);

	free(baseWords);
	free(sourceWords);
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

void replace(int amountOfSourceWords, char** sourceWords) {
	// Забираем из файла пару слов (заменяемое - заменитель).
	FILE* replacer = fopen("replacer", "r+");
	if (replacer == NULL) {
		printf("Ошибка открытия файла\n");
		exit(1);
	}
	char replaced[50];
	char replacing[50];
	fscanf(replacer, "%s", replaced);
	fscanf(replacer, "%s", replacing);
	fclose(replacer);

	// Производим замену слов.
	for (int i = 0; i < amountOfSourceWords; i++) {
		if (strcmp(sourceWords[i], replaced) == 0) {
			strcpy(sourceWords[i], replacing);
		}
	}
}