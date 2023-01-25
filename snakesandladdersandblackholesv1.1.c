#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <string.h>
#include <windows.h>

void printArray(); //prototype


int Welcome() {
	srand(time(NULL)); //seed rand
	printf("Welcome to Snakes and Ladders (and Blackholes)! Please read!\n");
	printf("The game has two players. Each player will take turns playing. Ladders (L) will move you up 10 spaces. Snakes (S) will move you down 6 spaces.\n");
	printf("Blackholes (B) will keep you in place. You must roll a 6 to get out of a black hole. Doing-so will move you up 6 spots.\n");
	printf("The first appearance of a snake symbol is not the snake itself, it just denotes the stop position.\n");
	printf("The game will play for 10 moves. Whichever player is in a higher position at the end or reaches the 100th spot first wins.\n");
	printf("Press any key to continue\n");
	_getch();
	printArray();
	printf("To begin the game you must roll a 6. Press any key to begin rolling. Good luck and have fun!\n");
	_getch();
	BeginRoll(); //call function 
	return 0;
}
int BeginRoll() { //function for beginning dice roll (call this in the welcome function)
	int dc = RollDice();
	if (dc == 6) {
		printf("You have rolled a 6, you may begin!\n");
	}
	if (dc != 6) {
		printf("You rolled a %d, you must roll a 6 to start, press any key to roll again.\n");
		_getch();
		BeginRoll();
	}
	return;
}
int RollDice() {
	int dice;
	dice = 1 + rand() % 6;
	return dice;
}

char boardArray2[10][10][8] = {
{"1   P1P2","2       ","3 S1    ","4       ","5       ","6       ","7       ","8       ","9 S1    ","10      "},
{"20      ","19      ","18S2    ","17B1    ","16      ","15      ","14L1    ","13      ","12S2    ","11      "},
{"21      ","22      ","23B1    ","24L1    ","25L2    ","26      ","27      ","28      ","29      ","30      "},
{"40L3    ","39      ","38S3    ","37      ","36B2    ","35L2    ","34      ","33      ","32S3    ","31      "},
{"41      ","42B2    ","43      ","44      ","45      ","46      ","47      ","48      ","49S4    ","50L3    "},
{"60      ","59L4    ","58S5    ","57      ","56L4    ","55S4    ","54      ","53      ","52      ","51      "},
{"61B3    ","62      ","63      ","64S5    ","65      ","66      ","67B3    ","68      ","69L4    ","70      "},
{"80      ","79L4    ","78      ","77B4    ","76      ","75      ","74      ","73      ","72L5    ","71B4    "},
{"81      ","82L5    ","83      ","84B5    ","85      ","86      ","87      ","88      ","89      ","90B5    "},
{"100     ","99      ","98      ","97      ","96      ","95      ","94      ","93      ","92      ","91      "}
};

int player1 = 0; //globals
int player2 = 0;
int stuck1 = 0;
int stuck2 = 0;
int i = 0;

void calcMove() {
	for (int i = 0; i < 10; i++) {
		if (player1 >= 100) {
			printf("\nPlayer 1 wins!");
			return;
		}
		else {
			if (player2 >= 100) {
				printf("\nPlayer 2 wins!");
				return;
			}
			else {
				if (i == 9 && player1 > player2) {
					printf("10 moves have been played, Player 1 wins!\n");
					return;
				}
			}
			if (i == 9 && player2 > player1) {
				printf("10 moves have been played, Player 2 wins!\n");
				return;
			}
			if (i == 9 && player1 == player2) {
				printf("10 moves have been played, both players occupy the same position. It's a tie!\n");
				return;
			}

			else {
				printf("Player 1, press any key to roll\n"); //receive input to begin dice roll
				_getch();
				int diceRoll = RollDice();
				printf("\n");
				printf("%s%d", "Player 1 rolled a ", diceRoll);
				printf("\n");

				int p1_i = player1 / 10;
				int p1_j;

				if ((player1 / 10) % 2 == 0) {
					p1_j = player1 % 10;
				}
				else {
					p1_j = 9 - (player1 % 10);
				}

				boardArray2[p1_i][p1_j][4] = ' ';
				boardArray2[p1_i][p1_j][5] = ' ';

				player1 = player1 + diceRoll;
				slb1();
				if ((player1 / 10) % 2 == 0) {
					boardArray2[player1 / 10][player1 % 10][4] = 'P';
					boardArray2[player1 / 10][player1 % 10][5] = '1';
				}
				else {
					boardArray2[player1 / 10][9 - (player1 % 10)][4] = 'P'; //redefines P1 and P2 token
					boardArray2[player1 / 10][9 - (player1 % 10)][5] = '1';
				}
				printArray();

				printf("Player 2, press any key to roll\n");
				_getch();
				diceRoll = RollDice(); //call function after every role
				printf("\n");
				printf("%s%d", "Player 2 rolled a ", diceRoll);
				printf("\n");


				if ((player2 / 10) % 2 == 0) {
					boardArray2[player2 / 10][player2 % 10][6] = ' ';
					boardArray2[player2 / 10][player2 % 10][7] = ' ';
				}
				else {
					boardArray2[player2 / 10][9 - (player2 % 10)][4] = ' '; //redefines P1 and P2 token
					boardArray2[player2 / 10][9 - (player2 % 10)][5] = ' ';
				}

				player2 = player2 + diceRoll;
				slb2();
				if ((player2 / 10) % 2 == 0) {
					boardArray2[player2 / 10][player2 % 10][6] = 'P';
					boardArray2[player2 / 10][player2 % 10][7] = '2';
				}
				else {
					boardArray2[player2 / 10][9 - (player2 % 10)][4] = 'P'; //redefines P1 and P2 token
					boardArray2[player2 / 10][9 - (player2 % 10)][5] = '2';
				}
				printArray();

			}
		}
	}
}
void printArray() { //prints the display
	printf("--------+--------+--------+--------+--------+--------+--------+--------+--------+---------+\n");
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			for (int k = 0; k < 8; k++) {
				printf("%c", boardArray2[i][j][k]);
			}
			printf("|");
		}
		printf("\n");
		printf("--------+--------+--------+--------+--------+--------+--------+--------+--------+---------+");
		printf("\n");
	}
}
int slb1() {
	int diceRoll = RollDice();
	int temp1 = 0;

	if (player1 == 8 || player1 == 17 || player1 == 37 || player1 == 54 || player1 == 63) { //snakes at 9  -> 3 , 18  -> 12, 38  -> 32, 55  -> 49, 64  -> 58
		player1 = player1 - 6;
		printf("\nPlayer 1 has hit a snake! Time for you to move back.\n");
	}
	else {
		if (player1 == 13 || player1 == 24 || player1 == 39 || player1 == 58 || player1 == 71) { //ladders at 14  -> 24 ,25  -> 35 ,40 -> 50, 59 -> 69, 72 -> 82
			player1 = player1 + 10;
			printf("\nPlayer 1 has hit a ladder! You get to move up\n");
		}
		else {
			if (player1 == 16 || player1 == 35 || player1 == 60 || player1 == 70 || player1 == 81) { //blackholes at 17,36,61,71,82
				stuck1 = 1;
				temp1 = player1;
				printf("\nYou are stuck in a blackhole! Roll a 6 to escape!\n");
			}
			if (stuck1 == 1 && diceRoll != 6 && temp1 == 16 || temp1 == 35 || temp1 == 60 || temp1 == 70 || temp1 == 81) {
				printf("\nYou need to roll a 6 to escape!");
				player1 = player1 - diceRoll;
			}
			if (temp1 == 16 || temp1 == 35 || temp1 == 60 || temp1 == 70 || temp1 == 81 && diceRoll == 6 && stuck1 == 1) {
				stuck1 = 0;
				player1 = player1;
				printf("\nYou rolled a 6, you are free!\n");
			}
		}
	}
}


int slb2() {
	int diceRoll = RollDice();
	int temp2 = 0;
	if (player2 == 8 || player2 == 17 || player2 == 37 || player2 == 54 || player2 == 63) {
		player2 = player2 - 6;
		printf("\nPlayer 2 has hit a snake! Time for you to move back.\n");
	}
	else {
		if (player2 == 13 || player2 == 24 || player2 == 39 || player2 == 58 || player2 == 71) {
			player2 = player2 + 10;
			printf("\nPlayer 2 has hit a ladder! You get to move up\n");
		}
		else {
			if (player2 == 16 || player2 == 35 || player2 == 60 || player2 == 70 || player2 == 81) { //blackholes at 17,36,61,71,82
				stuck2 = 1;
				temp2 = player2;
				printf("\nYou are stuck in a blackhole! Roll a 6 to escape!\n");
			}
			if (stuck2 == 1 && diceRoll != 6 && temp2 == 16 || temp2 == 35 || temp2 == 60 || temp2 == 70 || temp2 == 81) {
				printf("\nYou need to roll a 6 to escape!");
				player2 = player2 - diceRoll;
				if (temp2 == 16 || temp2 == 35 || temp2 == 60 || temp2 == 70 || temp2 == 81 && diceRoll == 6 && stuck2 == 1) {
					stuck2 = 0;
					player2 = player2;
					printf("\nYou rolled a 6, you are free!\n");


				}
			}
		}
	}
}


int main() {
	Welcome();
	printArray();
	calcMove();
}

