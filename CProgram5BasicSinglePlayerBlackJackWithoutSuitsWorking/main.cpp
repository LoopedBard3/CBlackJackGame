#include <iostream>
#include <sys/time.h>

//TO-DO: FIX THE SHUFFLE CARDS STATEMENT

void shuffleCards(char *array, size_t n){
    struct timeval tv;
    gettimeofday(&tv, NULL);
    unsigned int usec = tv.tv_usec;
    srand(usec);

    if(n > 1){
        size_t i;
        for (i = n-1; i > 0; i--){
            size_t j = (unsigned int) ((double(rand())/RAND_MAX)*(i+1));
            char t = array[j];
            array[j] = array[i];
            array[i] = t;
        }
    }
}

void drawCard(char *deck, int cardNum, char* newCardType, int* newCardNum){
    switch(deck[cardNum]) {
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
}

int main() {
    const char CONTROL_NUMS[13] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};  //Set the card numbers from ace through ten, jack, queen, and king

    char wantsToContinue = 'y';
    char holdHand = 'n';
    int dealerScore = 0;
    int playerScore = 0;
    int deckSize = 1;
    int nextCardNum = 1;
    char drawnCardType;
    int drawnCardWorth;


    printf("Welcome, how many decks would you like to use?\nDecks: ");
    scanf("%d", &deckSize);
    getchar();

    char deck[deckSize * 52];

    for(int numDecksIn = 0; numDecksIn < deckSize; numDecksIn++) {
        for (int i = 0; i < 13; i++) {            //For loop for each card number     WORKING start for setting the control deck
            for (int j = 0; j < 4; j++) {         //For loop for each suit
                deck[i + j * 13 + 52 * numDecksIn] = {CONTROL_NUMS[i]};
            }
        }
    }



    shuffleCards(deck, (size_t)deckSize * 52);





    while(wantsToContinue != 'N' && wantsToContinue != 'n'){          //Main code
        if((double)nextCardNum/(deckSize*52) > (double)3/4){
            shuffleCards(deck, (size_t)deckSize * 52);
            nextCardNum = 1;
            printf("The deck(s) have been reshuffled!\n");
        }

        drawCard( deck, nextCardNum++, &drawnCardType, &drawnCardWorth);
        if(drawnCardType != 'A') {
            playerScore = 0 + drawnCardWorth;
            printf("You drew a %c, you now have %d points! \nLets draw your second card!\n", drawnCardType,
                   playerScore);
        }else{
            printf("You drew an ACE! Would you like to count it as 1 or 11?\ninput number: ");
            scanf("%d", &drawnCardWorth);
            playerScore = 0 + drawnCardWorth;
            printf("You now have %d points! \nLets draw your second card!\n", playerScore);
        }
        holdHand = 'n';

        while(holdHand != 'y' && holdHand != 'Y') {
            drawCard( deck, nextCardNum++, &drawnCardType, &drawnCardWorth);
            if(drawnCardType != 'A'){
                playerScore += drawnCardWorth;
                if(playerScore < 21) {
                    printf("You drew a %c, you now have %d points! \nWould you like to stop drawing?\n(Y or N): ", drawnCardType,
                           playerScore);
                    scanf("%c", &holdHand);
                    getchar();
                }else if(playerScore == 21){
                    printf("Looks like you got 21 by drawing a %c! Lets see if you can beat the dealer!\n", drawnCardType);
                    holdHand = 'y';
                }else{
                    printf("Looks like you broke by drawing a %c. Lets see what the dealer gets!\n", drawnCardType);
                    holdHand = 'y';
                }
            }else{
                if(playerScore < 11) {
                    printf("You drew an ACE! Would you like to count it as 1 or 11?\ninput number: ");
                    scanf(" %d ", &drawnCardWorth);
                    if(drawnCardWorth != 1){
                        drawnCardWorth = 11;
                    }
                    getchar();
                    playerScore += drawnCardWorth;
                    printf("You now have %d points! \nLets draw your second card!\n", playerScore);
                }else{
                    printf("You drew an ACE! It counts as 1 so you now have %d points!\n?Would you like to stop drawing?\n(Y or N): ", playerScore);
                    scanf("%c", &holdHand);
                    getchar();
                }
            }

        }
        dealerScore = 0;

        while(dealerScore < 17){
            drawCard( deck, nextCardNum++, &drawnCardType, &drawnCardWorth);
            if(drawnCardType != 'A') {
                dealerScore += drawnCardWorth;
                printf("The dealer drew a %c, they now have %d points! \nLets draw their second card!\n", drawnCardType,
                       dealerScore);
            }else{
                if(dealerScore < 11){
                    dealerScore += 11;
                    printf("The dealer drew an ACE and is counting it as 11, they now have %d points\n", dealerScore);
                }else{
                    dealerScore += 1;
                    printf("The dealer drew an ACE and is counting it as 1, they now have %d points\n", dealerScore);
                }
            }
        }


        if(dealerScore > 21 && playerScore > 21 || dealerScore == playerScore){
            printf("\nYou both tied! You both had a %d points!\n", playerScore);
        }else if(dealerScore > 21 || playerScore > dealerScore && playerScore < 21){
            printf("\nYou won! You had %d points while the dealer had %d points!\n", playerScore, dealerScore);
        }else if(playerScore > 21 || dealerScore > playerScore && playerScore < 21){
            printf("\nThe dealer won! He had %d points while you only had %d points!\n", dealerScore, playerScore);
        }

        printf("\nWould you like to continue playing?\n(Y or N)");
        scanf("%c", &wantsToContinue);
        getchar();
    }
}

