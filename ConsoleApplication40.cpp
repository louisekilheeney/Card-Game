// ConsoleApplication40.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include "string.h"
#include "stdarg.h"
#include "stdlib.h"
#include "time.h"

typedef enum S { CLUBS, DIAMONDS, HEARTS, SPADES } SUIT;
char suits[][10] = { "CLUBS", "DIAMONDS", "HEARTS", "SPADES" };

typedef enum F { TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE } FACE;
char faces[][10] = { "TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN", "EIGHT", "NINE", "TEN", "JACK", "QUEEN", "KING", "ACE" };

typedef struct
{
	SUIT suit;
	FACE face;
} card;

typedef struct
{
	card cards[5];
} hand;

hand dealHand(hand handsDealt[], int numHandsDealt);
char * printCard(card aCard); // returns pointer to string containing, for example, "ACE of HEARTS"
char * compareCards(card yourCard, card dealersCard);
bool fourAces(hand aHand);// returns true if the hand contains four ACES


void main()
{
	int i = 0;
	hand myHand, dealersHand;
	int seed = time(NULL);
	srand(seed);
	hand hands[10];

	myHand = dealHand(hands, 0);	// deal the first hand
	hands[0] = myHand;// add this new hand to the set of dealt hands
	dealersHand = dealHand(hands, 1);// deal another hand; let dealHand know what has already been dealt

	while (i<5)	// here you are just comparing each card one at a time in the two hands
	{
		printf("card#%d: %s (you) vs. %s (dealer). Winner: %s \n", i + 1, printCard(myHand.cards[i]), printCard(dealersHand.cards[i]), compareCards(myHand.cards[i], dealersHand.cards[i]));
		i++;
	}


	while (1)	// now try to deal 4 Aces !
	{
		myHand = dealHand(hands, 0);	// deal a new hand; assume new deck every time, so nothing dealt already
		if (fourAces(myHand)) break;	// does it contain 4 ACES?
		i++;							// keep track of number of hands dealt
	}
	printf("\n\n4 aces found after %d hands \n\n\n", i);	// print out how many hands it took to find 4 aces
}

// compares the FACE values of two cards (TWO is lowest, ACE is highest)
// returns pointer to string containing name of winner: "You" or "Dealer" (or "Draw" if the face values are the same)
char * compareCards(card yourCard, card dealersCard)
{
	char * sptr;
	sptr = (char *)malloc(10 * sizeof(char));

	if (yourCard.face < dealersCard.face) {
		sptr = "Dealer";
		return sptr;
	}
	else if (yourCard.face > dealersCard.face) {
		sptr = "You";
		return sptr;
	}
	sptr = "Draw";
	return sptr;
}

// returns pointer to string containing, for example, "ACE of HEARTS"
char * printCard(card aCard)
{
	char* sptr = (char*) malloc(strlen(faces[aCard.face]) + 4 + strlen(suits[aCard.suit]) + 1);
	sprintf(sptr, "%s of %s",faces[aCard.face], suits[aCard.suit]);
	//sptr = ("%s of %s", suits[aCard.suit], faces[aCard.face]);

	return sptr;
}

// function deals a random hand of cards - BUT .... same card CANNOT be dealt twice!
// so if same card already in the hand, you would need to draw again
// also, the card cannot appear in another hand either
hand dealHand(hand handsDealt[], int numHands)
{
	int i = -1, n = -1, l = 0;
	int k = 0;
	int found = 0;
	hand newHand;
	int ncards = 0;

	SUIT newSuit;
	FACE newFace;
	int j = 0;

	while (ncards < 5) {
		n = rand() % 13;
		i = rand() % 4;
		newSuit = S(i);
		newFace = F(n);
		for (j = 0; j < ncards; j++) {
			if (newHand.cards[j].face == newFace && newHand.cards[j].suit == newSuit) {
				break;
			}
		}

		if (j == ncards) {
			for (k = 0; k < numHands; k++) {
				for (l = 0; l < 5; l++) {
					for (int m = 0; m < ncards; m++) {
						if (newHand.cards[m].face == handsDealt[k].cards[l].face  && newHand.cards[m].suit == handsDealt[k].cards[l].suit) {
							break;
						}
					}

				}
			}
			if (k == numHands) {
				newHand.cards[ncards].face = newFace;
				newHand.cards[ncards].suit = newSuit;
				ncards++;
			}
		}
	}
	return newHand;
}

// returns true if the hand contains four ACES
bool fourAces(hand aHand)
{
	int i;
	int numAces = 0;
	bool fourAces = false;

	for (i = 0; i <= 4; i++) {
		if (aHand.cards[i].face == ACE) {
			numAces++;
		}
	}
	if (numAces == 4) {
		return true;
		//printf("four Aces");
	}
	return fourAces;
}




