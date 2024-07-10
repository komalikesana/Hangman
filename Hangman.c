#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// List of sports
char *sports[] = {
    "hwnhpjy", "gfirnsyts", "mthpjd", "ymwtbgfqq", "pfgfiin", "atqqjdgfqq",
    "gfxpjygfqq", "wzlgd", "hmjxx", "hfwwtrx", "yjssnx", "kttygfqq",
    "pmtpmt", "ltqk", "gtcnsl", "xbnrrnsl", "fwhmjwd"
};

// Hash function to decode the sports name
void hashfunction(char *Word, char *word, int shift) {
    int length = strlen(Word);
    for (int i = 0; i < length; i++) {
        if (Word[i] >= 'a' && Word[i] <= 'z') {
            word[i] = (Word[i] - 'a' - shift + 26) % 26 + 'a';
        } else {
            word[i] = Word[i];
        }
    }
    word[length] = '\0';
}

// Function to display the hangman based on remaining attempts
void displayHangman(int attempts) {
    switch (attempts) {
        case 5:
            printf(" _______\n |     |\n |\n |\n |\n_|_\n");
            break;
        case 4:
            printf(" _______\n |     |\n |     O\n |\n |\n_|_\n");
            break;
        case 3:
            printf(" _______\n |     |\n |     O\n |     |\n |\n_|_\n");
            break;
        case 2:
            printf(" _______\n |     |\n |     O\n |    /|\\\n |\n_|_\n");
            break;
        case 1:
            printf(" _______\n |     |\n |     O\n |    /|\\\n |    /\n_|_\n");
            break;
        default:
            printf(" _______\n |     |\n |     O\n |    /|\\\n |    / \\\n_|_\n");
    }
}

// Function to play the hangman game
void play() {
    srand(time(NULL));
    char *Word = sports[rand() % (sizeof(sports) / sizeof(sports[0]))];
    char word[strlen(Word) + 1];
    hashfunction(Word, word, 5);

    printf("\nGuess the sport: ");
    char display[strlen(Word) + 1];
    for (int i = 0; i < strlen(Word); i++) {
        display[i] = '_';
    }
    display[strlen(Word)] = '\0';

    for (int i = 0; i < strlen(display); i++) {
        printf("%c ", display[i]);
    }
    printf("\n");

    int attempts = 5, count = 0;
    char guessedLetters[26]; // Array to track guessed letters
    int guessedLettersCount = 0;

    while (attempts) {
        char guess;
        printf("\nYou have %d chances to guess!!", attempts);
        printf("\nEnter a letter (lowercase): ");
        scanf(" %c", &guess);

        if (!(guess >= 'a' && guess <= 'z')) {
            printf("Invalid input. Please enter a lowercase letter.\n");
            continue;
        }

        // Check if the letter has already been guessed
        int alreadyGuessed = 0;
        for (int i = 0; i < guessedLettersCount; i++) {
            if (guessedLetters[i] == guess) {
                alreadyGuessed = 1;
                break;
            }
        }

        if (alreadyGuessed) {
            printf("You already guessed '%c'. Please try again.\n", guess);
            continue;
        }

        if (strchr(word, guess)) {
            for (int i = 0; i < strlen(word); i++) {
                if (word[i] == guess) {
                    display[i] = guess;
                    count++;
                }
            }
            guessedLetters[guessedLettersCount++] = guess; // Add the guessed letter to the array
            for (int i = 0; i < strlen(display); i++) {
                printf("%c ", display[i]);
            }
            printf("\n");
            if (count == strlen(word)) {
                break;
            }
        } else {
            guessedLetters[guessedLettersCount++] = guess; // Add the guessed letter to the array
            printf("Try again!\n");
            attempts--;
            displayHangman(attempts);
        }
    }

    if (attempts == 0) {
        printf("You lost!!!\n");
    } else {
        printf("You won!!\n");
    }
    printf("\nThe sport is: %s\n", word);
}

int main() {
    play();
    return 0;
}
