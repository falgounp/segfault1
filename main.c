#include<stdlib.h>
#include<stdio.h>
#include<allegro.h>
#include<time.h>
#include<getopt.h>
#include"blackjack.h"

const int scrx = 640;
const int scry = 480;


extern int decks;
extern int player_cash;
extern struct cards playershand[NOOFPLAYERS];
extern int cards_used[14];


int main(int argc, char **argv) {
	
					/*General function initalization*/			
	if (allegro_init()) {
    		allegro_message("Cannot initalize Allegro.\n");
    		return 1;
  	}

					/*Set the window title when in a GUI environment*/
  	set_window_title("BLACKJACK");    	
	
					/*Install Keyboard*/
	if (install_keyboard()) {
    		allegro_message("Cannot initalize keyboard input.\n");
    		return 1;
  	}
	
					/*Install mouse*/	
	install_mouse();
	if (install_mouse() == -1) {
	/* Display an error message */
		allegro_message("Error! %s", allegro_error);
	/* And exit the program! */
		return -1;
	}
  	
	
					/*set graphics mode, trying all acceptable depths*/
 	set_color_depth(32);
  	if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, 500, 500, 0, 0)) {
    		set_color_depth(24);
    		if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, 500, 500, 0, 0)) {
      			set_color_depth(16);
      			if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, 500, 500, 0, 0)) {
        			set_color_depth(15);
        			if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, 500, 500, 0, 0)) {
          				allegro_message("Video Error: %s.\n", allegro_error);
          				return 1;
        			}
      			}
    		}
  	}
	
	/*set text background color to bright blue*/
  	
      	    	
    	argc -= optind;
    	argv += optind;
    	
	if (argv[0]) {
        	decks = atoi (argv[0]);
	}
	
	srand(time(NULL));
	
	int x = 0, i;
    	while (x != -1) {
        	display_hands();
        	int bet = 50;
        	int alert_val = alert3("Please place your bet", NULL, NULL, "&50", "&100", "15&0", '5', '1', '0');
        	bet = alert_val * 50;
        	player_cash = player_cash - bet;
        	display_hands();
        	drawacard(0);
        	drawacard(1);
        	drawacard(1);
        	display_hands();
        	player_turn();
        	if (playershand[1].ctally < 22)	{
            		dealer_turn();
            		display_hands();
        	}
        	if ((playershand[0].ctally > playershand[1].ctally) || (playershand[0].ctally == playershand[1].ctally || playershand[1].ctally > 21)) {
            		alert("Dealer wins!", NULL, NULL, "&Ok", NULL, 'o', 'k');
        	}
        	else {
            		alert("Player wins!", NULL, NULL, "&Ok", NULL, 'o', 'k');
            		player_cash = player_cash + (bet * 2);
            		display_hands();
        	}


        	if (player_cash < 1)
            		endgame();
        	for (i = 0; i < 2; i++) {
            		for (x = 0; x < 10; x++) {
                		playershand[i].cname[x] = 0;
                		playershand[i].csuit[x] = 0;
                		playershand[i].cvalue[x] = 0;
            	}
            	playershand[i].ctally = 0;
        	}

        	if (alert("Continue or Quit?", NULL, NULL, "&Continue", "&Quit", 'c', 'q') == 2) {
            		exit(EXIT_SUCCESS);
    		}
		destroyimage();
	
    	}
	return 0;
}
END_OF_MAIN();		
