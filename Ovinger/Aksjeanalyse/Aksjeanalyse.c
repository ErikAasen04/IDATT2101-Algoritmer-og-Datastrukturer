#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    //sørger for at rand gir nye tilfeldige tall hver kjøring
    srand(time(NULL));

    //antall verdier som legges inn i kursendringslisten for hver gjennomgang
    int nValues[] = { 1000000, 10000000, 100000000, 200000000, 400000000, 800000000 };
    int numberTest = sizeof(nValues) / sizeof(nValues[0]);

    //genrering av liste med tilfeldige tall
    for (int t = 0; t < numberTest; t++) {

        int n = nValues[t];
        int* kursendring = malloc(n * sizeof(int));

        for (int f = 0; f < n; f++) {
            kursendring[f] = (rand() % 21) - 10;
        }

        //starten på algoritmen hvor tiden starter
        clock_t begin = clock();

        //variabler for profit
        int currentProfit = 0;
        int highestProfit = 0;

        //variabler for kjøp og salgsdager
        int buyDay = 0;
        int tempBuyDay = 0;
        int sellDay = 0;


        //løkken kjører gjennom hver verdi i listen og regner den totale kursendrignen
        for (int i = 0; i < n; i++) {
            currentProfit += kursendring[i];

            //hvis den totale kursendrignen er større enn den høyeste lagret, oppdater høyeste lagrede
            //lagrer salgsdag og kjøpsdag
            if (currentProfit > highestProfit) {
                highestProfit = currentProfit;
                sellDay = i;
                buyDay = tempBuyDay;
            }

            //hvis den totale kursen faller under 0, betyr det at denne salgsdatoen
            //gir tap og vi prøver derfor neste dag som potensiell kjøpsdag
            if (currentProfit < 0) {
                currentProfit = 0;
                tempBuyDay = i + 1;
            }
        }

        //slutter tidtaking for gjennomgangen
        clock_t end = clock();
        double timeSpent = (double)(end - begin) / CLOCKS_PER_SEC;

        printf("N = %5d, Total time spent: %f seconds %d\n", n, timeSpent, highestProfit);

        free(kursendring);
    }
    return 0;
}
