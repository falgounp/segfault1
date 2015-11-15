#define SIZE 7
#define NOOFPLAYERS 2
#include<allegro.h>
struct cards {
	int cvalue[10];
	char cname[11];
	int ctally;
	char csuit[11];
	BITMAP *card_pic[10];
};


/*Function definition*/

void endgame();
void tallythevalueofcards(int x);
void acecheck(); 
void drawacard();
void dealer_turn();
void player_turn();
void displays_hand();
void destroyimage();

