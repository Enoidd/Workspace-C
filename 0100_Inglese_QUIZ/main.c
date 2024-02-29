#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struct per memorizzare una domanda e le relative risposte
typedef struct {
    char question[200];
    char answers[4][50];
    char correct_answer;
} Question;

// Funzione per verificare la risposta data dall'utente
int check_answer(char user_answer, char correct_answer) {
    return (user_answer == correct_answer);
}

int main() {
    // Array di domande e risposte corrette
    Question questions[100] = {
        {"01. This shop ______ every day ___ 9am.", {"a. opens / at", "b. closes / on", "c. closed / in", "d. closing / at"}, 'a'},
        {"02. He said he _____ a good film ____ a long time.", {"a. had not seen / for", "b. was seeing / since", "c. saw / in", "d. will see / from"}, 'a'},
        // Aggiungi le altre domande e risposte corrette qui
    };

    int num_questions = 100; // Numero totale di domande

    int num_wrong_answers = 0; // Contatore delle risposte sbagliate

    printf("Benvenuto al test di grammatica inglese!\n");

    // Ciclo attraverso tutte le domande
    for (int i = 0; i < num_questions; i++) {
        // Mostra la domanda
        printf("\n%s\n", questions[i].question);

        // Mostra le risposte possibili
        for (int j = 0; j < 4; j++) {
            printf("%s\n", questions[i].answers[j]);
        }

        // Input della risposta dall'utente
        printf("Inserisci la risposta (a, b, c, d): ");
        char user_answer;
        scanf(" %c", &user_answer);

        // Verifica della risposta
        if (!check_answer(user_answer, questions[i].correct_answer)) {
            printf("Sbagliato!\n");
            num_wrong_answers++;
        }
    }

    // Mostra il numero di risposte sbagliate
    printf("\nHai risposto sbagliato a %d domande.\n", num_wrong_answers);

    // Chiede se l'utente vuole ripetere il test
    char repeat;
    printf("Vuoi ripetere il test? (y/n): ");
    scanf(" %c", &repeat);

    // Se l'utente vuole ripetere il test, richiama la main
    if (repeat == 'y' || repeat == 'Y') {
        main();
    }

    return 0;
}
