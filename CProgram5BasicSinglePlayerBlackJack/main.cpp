#include <iostream>
#include <sys/time.h>

//TO-DO: FIX THE SHUFFLE CARDS STATEMENT

void shuffleCards(char **array, size_t n){
    struct timeval tv;
    gettimeofday(&tv, NULL);
    unsigned int usec = tv.tv_usec;
    srand(usec);

    if(n > 1){
        size_t i;
        for (i = n-1; i > 0; i--){
            size_t j = (unsigned int) ((double(rand())/RAND_MAX)*(i+1));
            char *t = array[j];
            array[j] = array[i];
            array[i] = t;
        }
    }
}

void drawCard(char deck[][2], int cardNum, char* newCardType, int* newCardNum, char* newCardSuit){
    *newCardSuit = deck[cardNum][1];
    printf("Drew a suit of %c at spot %d\n", deck[cardNum][1], cardNum);
    switch(deck[cardNum][0]) {
        case 'A':
            *newCardNum = 1;
            *newCardType = 'A';
            break;

        case '2':
            *newCardNum = 2;
            *newCardType = '2';
            break;

        case '3':
            *newCardNum = 3;
            *newCardType = '3';
            break;

        case '4':
            *newCardNum = 4;
            *newCardType = '4';
            break;

        case '5':
            *newCardNum = 5;
            *newCardType = '5';
            break;

        case '6':
            *newCardNum = 6;
            *newCardType = '6';
            break;

        case '7':
            *newCardNum = 7;
            *newCardType = '7';
            break;

        case '8':
            *newCardNum = 8;
            *newCardType = '8';
            break;

        case '9':
            *newCardNum = 9;
            *newCardType = '9';
            break;

        case 'T':
            *newCardNum = 10;
            *newCardType = 'T';
            break;

        case 'J':
            *newCardNum = 10;
            *newCardType = 'J';
            break;

        case 'Q':
            *newCardNum = 10;
            *newCardType = 'Q';
            break;

        case 'K':
            *newCardNum = 10;
            *newCardType = 'K';
            break;
    }

    printf("Drew a type of %c\n", deck[cardNum][0]);

}

void checkCardsLeft(int cardNum, int numCards, char* deck){

}


int main() {
    const char CONTROL_NUMS[13] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};  //Set the card numbers from ace through ten, jack, queen, and king
    const char CONTROL_SUITS[4]= {'H','C','S','D'}; //Set the suits to Hearts, Clubs, Spades, and Diamonds

    char wantsToContinue = 'y';
    int deckSize = 1;
    int nextCardNum = 1;
    char drawnCardType;
    char drawnCardSuit;
    int drawnCardWorth;


    printf("Welcome, how many decks would you like to use?\nDecks: ");
    scanf("%d", &deckSize);
    getchar();

    char deck[deckSize * 52][2];

    for(int numDecksIn = 0; numDecksIn < deckSize; numDecksIn++) {
        for (int i = 0; i < 13; i++) {            //For loop for each card number     WORKING start for setting the control deck
            for (int j = 0; j < 4; j++) {         //For loop for each suit
                deck[i + j * 13 + 52 * numDecksIn][0] = {CONTROL_NUMS[i]};
                deck[i + j * 13 + 52 * numDecksIn][1] = {CONTROL_SUITS[j]};
            }
        }
    }

    char *holdDeck[deckSize * 52];
    for(int k = 0; k < deckSize * 52; k++){
        holdDeck[k] = &deck[k][0];
    }

    shuffleCards(holdDeck, deckSize * 52);

    for(int k = 0; k < deckSize * 52; k++){
        deck[k][0] = *holdDeck[k];
    }


    for(int numDecksIn = 0; numDecksIn < deckSize; numDecksIn++) {
        for (int i = 0; i < 13; i++) {            //For loop for each card number     WORKING start for setting the control deck
            for (int j = 0; j < 4; j++) {         //For loop for each suit
                printf("%c %c\n", deck[i + j * 13 + 52 * numDecksIn][0], deck[i + j * 13 + 52 * numDecksIn][1]);
            }
        }
    }




    while(wantsToContinue != 'N'){          //Main code
        drawCard( deck, nextCardNum, &drawnCardType, &drawnCardWorth, &drawnCardSuit);
        nextCardNum++;
        printf("You drew a %c of %c that is worth %d\n", drawnCardType, drawnCardSuit, drawnCardWorth);

        printf("Would you like to continue playing?\n(Y or N)");
        scanf("%c", &wantsToContinue);
        getchar();
    }
}

