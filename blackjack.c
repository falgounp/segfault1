#include<stdio.h>
#include<stdlib.h>
#include<allegro.h>
#include"blackjack.h" 

int decks = 1;
int player_cash = 500;
struct cards playershand[NOOFPLAYERS];
int cards_used[14] = {0};
	


/* tally function calculates the total  value of the cards*/


void tallythevalueofcards(int x) {		
	int a = 0;
	int b = 0;
	int y;
	while(a < 10) {
		b = b + playershand[x].cvalue[a];
	}
	playershand[x].ctally =y;
	}

/* acecheck function checks if the ace has value of 1 or 11 in the case of the best hand*/

void acecheck(int x) {
	int a = 0;
        while(a < 10) {
    		if (playershand[x].cname[a] =='A') {
            		int y = 0;
            		int z = 10;
            		while(y < 10) {
            			z = z + playershand[a].cvalue[y];
			}
            		if (z < 22) {
                		playershand[a].cvalue[x]=11;
			}
           		else {
                		playershand[a].cvalue[x]=1;
                        } 
                 }
    	}
}



/*Endgame tells the game has ended i.e when the player wants to quit or has lost everything*/

void endgame()  {
	if(player_cash < 1) {
		alert("You lost it all your money! Better luck next time!", NULL, NULL, "&Ok", NULL, 'o', 'k');
	}
	else if(player_cash <= 500) {
		
	}
	else  {
		char finalcash[100];
		snprintf(finalcash, sizeof(finalcash),"Congo you have won %d cash ",player_cash);
	        alert("Amazing! You beat the house!", finalcash, NULL, "&Ok", NULL, 'o', 'k');
	}
	exit(EXIT_SUCCESS);
}


/*THE FUNCTION BELOW DRAWS CARDS RANDOMLY*/

void drawacard(int x) {
	int z = 1 + rand() % 13;
	int a = 0;
	int guard = 0;
	int y = 1 +rand() % 4;
	char csuit = 'd';
	
	while (playershand[x].cvalue[a] !=  0)
        	a = a + 1;
	
	while ((cards_used[z] > (decks * 4)) && (guard < 50)) {
        	z = 1 + rand () % 13;
        	guard = guard + 1;
        }
	
	if (guard > 49) {
        	endgame();
	}
	
	cards_used[z] = cards_used[z] + 1;
    	guard = 0;
	
	/*NAMES AND VALUES ARE ASSIGNED TO THE CARDS*/
	
	if ((z > 1) && (z < 10)) {
        	playershand[x].cvalue[a] = z;
        	playershand[x].cname[a] = ((char) '0' + z);
    	}
    	else if (z == 10) {
        	playershand[x].cvalue[a] = z;
        	playershand[x].cname[a] = 'T';
        }
        else if (z == 11) {
        	playershand[x].cvalue[a] = 10;
        	playershand[x].cname[a] = 'J';
        }
    	else if (z == 12) {
        	playershand[x].cvalue[a] = 10;
        	playershand[x].cname[a] = 'Q';
    	}
    	else if (z == 13) {
        	playershand[x].cvalue[a] = 10;
        	playershand[x].cname[a] = 'K';
    	}
    	else if (z == 1) {
        	playershand[x].cvalue[a] = 1;
        	playershand[x].cname[a] = 'A';
    	}	
	
	/*Assignments of the  Suits Randomly*/
    	
	if (y == 1)
        	csuit = 'c';
    	if (y == 2)
        	csuit = 'd';
   	if (y == 3)
        	csuit = 'h';
    	if (y == 4)
        	csuit ='s';
	acecheck(x);
	
	/*LINKING THE PICTURE IS REMAINGING*/
	
	char pic[20];
    	snprintf(pic, sizeof(pic), "card/%c.bmp", csuit);
    	playershand[a].card_pic[x]=load_bmp(pic, NULL);
	tallythevalueofcards(a);
	}
	
	/*displays the cards of the players*/
	
void display_hands () {
    	int p, x;
    	int y = 0;
	clear_bitmap(screen);
	
	/*Dealer hand*/
    	for (x = 0; playershand[0].cname[x] != 0; x++) {
        	blit(playershand[0].card_pic[x], screen, 0, y, 0, 10, 73, 97);
        	y = y + 75;
    	}
		
	/*Player Handers, displayed on bottom of screen*/
   	y = 10;
    	for (x = 0; playershand[1].cname[x] != 0; x++) {
        	blit(playershand[1].card_pic[x], screen, 0, 0, y, 300, 73, 97);
        	y = y + 75;
    	}
	textprintf_ex(screen, font, 10, 10, makecol(0, 0, 0), makecol(248, 248, 230), "         ");
    	textprintf_ex(screen, font, 10, 10, makecol(0, 0, 0), makecol(248, 248, 230), "  Cash   ");
    	textprintf_ex(screen, font, 10, 10, makecol(0, 0, 0), makecol(248, 248, 230), "   %d    ", player_cash);
    	textprintf_ex(screen, font, 10, 10, makecol(0, 0, 0), makecol(248, 248, 230), "         ");
	}
/*the dealer shows plays*/
void dealer_turn() {
	while (playershand[0].ctally < 17) {
        drawacard(0);
        display_hands();
    }
    if (playershand[0].ctally > 21) {
        playershand[0].ctally = 0;
        alert("IT IS A BUST!", NULL, NULL, "&Ok", NULL, 'o', 'k');
    }
}
/*the players turn to play*/
void player_turn() {
	int action=1;
	while (action != 2 && playershand[1].ctally < 21) {
        action=alert("What will you do?", NULL, NULL, "&Hit", "&Stand", 'h', 's');
        if (action == 1)
            	drawacard(1);
        	display_hands();
        	tallythevalueofcards(1);
    	}
	if (playershand[1].ctally > 21)
        alert("Player Busts!", NULL, NULL, "&Ok", NULL, 'o', 'k');
}

void destroyimage() {
	        
		int loop=0;
		for (loop = 0; loop < 11; loop++) {
	        	destroy_bitmap(playershand[0].card_pic[loop]);
	       		destroy_bitmap(playershand[1].card_pic[loop]);
    		}
}
