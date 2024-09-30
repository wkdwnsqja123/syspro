#include <stdio.h>
#include <string.h>

#define MAX_LINES 5
#define MAX_LENGTH 100

int main() {
    char sentences[MAX_LINES][MAX_LENGTH];
    int lengths[MAX_LINES];

    for (int i = 0; i < MAX_LINES; i++) {
        fgets(sentences[i], MAX_LENGTH, stdin);
        sentences[i][strcspn(sentences[i], "\n")] = '\0';
        lengths[i] = strlen(sentences[i]);
    }

    for (int i = 0; i < MAX_LINES - 1; i++) {
        for (int j = i + 1; j < MAX_LINES; j++) {
            if (lengths[i] < lengths[j]) {
                int tempLength = lengths[i];
                lengths[i] = lengths[j];
                lengths[j] = tempLength;

                char tempSentence[MAX_LENGTH];
                strcpy(tempSentence, sentences[i]);
                strcpy(sentences[i], sentences[j]);
                strcpy(sentences[j], tempSentence);
            }
        }
    }

    for (int i = 0; i < MAX_LINES; i++) {
        printf("%s\n", sentences[i], lengths[i]);
    }

    return 0;
}
	       

