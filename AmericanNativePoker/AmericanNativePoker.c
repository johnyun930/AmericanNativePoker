// AmericanNativePoker.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#define DECK_SIZE 20
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

void shuffleDeck(int* deck) {
	srand((int)time(NULL));
	int temp, randnum;
	for (int i = DECK_SIZE; i > 0 ; i--) {
		 randnum = rand() % 20;
		 temp = deck[randnum];
		 deck[randnum] = deck[i-1];
		 deck[i-1] = temp;

	}
}

void cleanBuffer(void) {
	while (getchar() != '\n') {

	}
}

void makeNewDeck(int *deck) {
	
	int cardnum = 1;
	for (int i = 0; i < DECK_SIZE; i++) {
		deck[i] = cardnum;
		cardnum++;
		if (cardnum > 10) {
			cardnum = 1;
		}
	}
}

void cleanScreen(void) {
	Sleep(1000);
	system("cls");
}

int drawDeck(int deck[], int decknum) {
	int card = deck[decknum];
	deck[decknum] = 0;
	return card;
}



int play(void) {
	int playerchip = 30;
	int comchip = 30;
	int deck[DECK_SIZE];
	int numofdeck = DECK_SIZE;
	int playercard = 0;
	int computercard = 0;
	int firstplayer = 1;
	int totalchip = 0;
	int betting = 0;
	int raise = 0;
	int playerdie = 0;
	int compdie = 0;
	int draw = 0;

	while (playerchip !=0 && comchip != 0) {
		numofdeck = 20;
		makeNewDeck(deck);
		printf("Making a deck \n");
		shuffleDeck(deck);
		printf("Shuffling the deck \n");
		while (numofdeck != 0) {
			//cleanScreen();
			totalchip = 2;
			playerchip--;
			comchip--;
			if (playerchip != 0 && comchip != 0) {
				printf("Each player pay a chip to participate in the game \n");
				
				printf("Another player chip: %d , Player chips: %d \n", comchip, playerchip);

				
				//first betting for the player.
				if (firstplayer == 1) {
					computercard = drawDeck(deck, numofdeck - 1);
					numofdeck--;
					playercard = drawDeck(deck, numofdeck - 1);
					printf("Another player's card is %d \n", computercard);
					numofdeck--;
					if (comchip > 5) {
						if (playercard < 5) {
							betting = (rand() % 3) + 1;
						}
						else if (playercard == 10) {
							int choice = rand() % 2;
							if (choice == 0) {
								betting = (rand() % 5) + 1;
							}
							else {
								betting = 1;

							}
						}
						else {
							betting = (rand() % 2) + 1;

						}
					}
					else {
						betting = comchip;
					}
					comchip -= betting;
					printf("Another player bets %d chips \n", betting);
					if (comchip == 0) {
						printf("Another players plays All In \n");
					}
					while (1) {
						printf("Choose 1. Call, 2. Raise. 3.Die : ");
						int selection = getchar();
						cleanBuffer();
						if (selection == '1') {
							playerchip -= betting;
							totalchip += (betting * 2);

						}
						else if (selection == '2') {
							while (1) {
								printf("how many chips you want to raise? ");
								scanf_s("%d", &raise, 2);
								cleanBuffer();
								if (raise > playerchip) {
									printf("Sorry, you have only %d chips. Please try agin", playerchip);
									continue;
								}
								else if (raise < betting && (playerchip - raise) <= 0) {
									printf("Sorry, Raise needs to be more chips than last betting");
									continue;
								}
								break;
							}
									totalchip += (betting * 2);
									playerchip = playerchip - betting - raise;
									betting = raise;
									raise = 0;
									if (playerchip == 0) {
										printf("You play ALL IN \b");

										if (playercard > 8 && betting > 6) {
											compdie = 1;
											printf("Another player plays Die \b");
										}
										else {
											comchip -= betting;
											totalchip += (betting * 2);
											printf("Another player play call with %d \b", betting);
										}
										break;

									}
									else {
										if ((playercard < 4 || playercard >8) && betting <= 4) {
											//Raise 4chips.
											comchip -= (betting * 2);
											totalchip += (betting * 2);
											printf("Another player raises 4 more chip \n");
											continue;
											
										}
										else if (playercard < 5 && betting <= 10) {
											comchip -= betting;
											totalchip += (betting * 2);
											printf("Another player play call with %d \n", betting);
										}
										else if (playercard > 8) {
											compdie = 1;
											printf("Another player plays Die \n");
										}
										else {
											comchip -= betting;
											totalchip += (betting * 2);
											printf("Another player play call with %d", betting);
										}
										break;
									}
								
							
						}
						else if (selection == '3') {
							printf("You plays Die \n");
							playerdie = 1;

						}
						break;
					}
					if (compdie == 1) {
						printf("You wins Game \n");
						playerchip += (totalchip + betting);
						compdie = 0;
						firstplayer = 0;
						if (computercard == 10) {
							comchip -= 10;
							playerchip += 10;
							printf("Another player dies with the number 10, the player pays 10 chips for penalty\n");
						}
					}
					else if (playerdie == 1) {
						printf("Another player wins Game \n");
						comchip += (totalchip + betting);
						playerdie = 0;
						firstplayer = 1;
						if (playercard == 10) {
							playerchip -= 10;
							comchip += 10;
							printf("You dies with the number 10, you pays 10 chips for penalty\n");
						}
					}
					else {
						if (playercard > computercard) {
							printf("You wins Game \n");
							playerchip += totalchip;
							totalchip = 0;
							firstplayer = 0;
						}
						else if (computercard > playercard) {
							printf("Another player wins Game \n");
							comchip += totalchip;
							totalchip = 0;
							firstplayer = 1;
						}
						else {
							printf("The game is draw, all the chips go to next round \n");
							draw = 1;
						}
					}
					printf("Your card is %d, and player card is %d", playercard, computercard);
					betting = 0;
					Sleep(2000);

					if (draw != 1 && (playerchip <= 0 || comchip <= 0)) {
						
						break;
					}
					if (draw != 1) {
						totalchip = 0;
						}

				}
				else {
					printf("You are the first player \n");
					playercard = drawDeck(deck, numofdeck - 1);
					numofdeck--;
					computercard = drawDeck(deck, numofdeck - 1);
					numofdeck--;
					printf("Another player's card is %d \n", computercard);
					printf("Please Type how many coins you raise: ");
					while (1) {
						scanf_s("%d", &betting);
						if (betting > playerchip) {
							printf("Sorry, you have only %d chips. Try again \n", playerchip);
							printf("Please Type how many coins you raise: ");
							continue;
						}

						if (betting == playerchip) {
							printf("You play ALL IN \n");
							playerchip = 0;
						}
						else {
							playerchip -= betting;
						}

						if (playerchip == 0) {
							if (playercard > 8 && betting > 6) {
								compdie = 1;
								printf("Another player plays Die \n");
							}
							else {
								comchip -= betting;
								totalchip += (betting * 2);
								printf("Another player play call with %d. \n", betting);
							}
							break;
						}
						else if ((playercard < 4 || playercard >8) && betting <= 4)
						{
							//Raise 4chips.
							comchip -= (betting * 2);
							totalchip += (betting * 2);
							printf("Another player raises 4 more chip. \n");
							while (1) {
								printf("Choose 1. Call, 2. Raise. 3.Die : ");
								int selection = getchar();
								cleanBuffer();
								if (selection == '1') {
									playerchip -= betting;
									totalchip += (betting * 2);

								}
								else if (selection == '2') {
									while (1) {
										printf("how many chips you want to raise? ");
										scanf_s("%d", &raise);
										cleanBuffer();
										if (raise > playerchip) {
											printf("Sorry, you have only %d chips. Please try agin", playerchip);
											continue;
										}
										else if (raise < betting && (playerchip - raise) <= 0) {
											printf("Sorry, Raise needs to be more chips than last betting");
											continue;
										}
										break;
									}
									totalchip += (betting * 2);
									playerchip = playerchip - betting - raise;
									betting = raise;
									raise = 0;
									if (playerchip == 0) {
										printf("You play ALL IN \b");

										if (playercard > 8 && betting > 6) {
											compdie = 1;
											printf("Another player plays Die \b");
										}
										else {
											comchip -= betting;
											totalchip += (betting * 2);
											printf("Another player play call with %d \b", betting);
										}
										break;

									}
									else {
										if ((playercard < 4 || playercard >8) && betting <= 4) {
											//Raise 4chips.
											comchip -= (betting * 2);
											totalchip += (betting * 2);
											printf("Another player raises 4 more chip \n");
											continue;

										}
										else if (playercard < 5 && betting <= 10) {
											comchip -= betting;
											totalchip += (betting * 2);
											printf("Another player play call with %d \n", betting);
										}
										else if (playercard > 8) {
											compdie = 1;
											printf("Another player plays Die \n");
										}
										else {
											comchip -= betting;
											totalchip += (betting * 2);
											printf("Another player play call with %d", betting);
										}
										break;
									}


								}
							//while (1) {
							//	printf("Choose 1. Call, 2. Raise. 3.Die : ");
							//	int select = 0;
							//	scanf_s("%d", &select);
							//	if (select == 1) {
							//		printf("You play Call");
							//		playerchip -= betting;
							//		totalchip += (betting * 2);


							//	}
							//	else if (select ==2) {
							//			printf("how many chips you want to raise? ");
							//			scanf_s("%d", &raise);
							//			cleanBuffer();
							//			if (raise > playerchip) {
							//				printf("Sorry, you have only %d chips. Please try agin", playerchip);
							//				continue;
							//			}
							//			else if (raise < betting && (playerchip - raise) <= 0) {
							//				printf("Sorry, Raise needs to be more chips than last betting");
							//				continue;
							//			}
							//			else {
							//				totalchip += (betting * 2);
							//				playerchip = playerchip - betting - raise;
							//				betting = raise;
							//				raise = 0;
							//				if (playerchip == 0) {

							//					printf("You play ALL IN");

							//					if (playercard > 8 && betting > 6) {
							//						compdie = 1;
							//						printf("Another player plays Die \n");
							//					}
							//					else {
							//						comchip -= betting;
							//						totalchip += (betting * 2);
							//						printf("Another player play call with %d. \n", betting);
							//					}

							//				}
							//				else {
							//					if ((playercard < 4 || playercard >8) && betting <= 4) {
							//						//Raise 4chips.
							//						comchip -= (betting * 2);
							//						totalchip += (betting * 2);
							//						printf("Another player raises 4 more chip \n");
							//						continue;
							//					}
							//					else if (playercard < 5 && betting <= 10) {
							//						comchip -= betting;
							//						totalchip += (betting * 2);
							//						printf("Another player play call with %d \n", betting);
							//					}
							//					else if (playercard > 8) {
							//						compdie = 1;
							//						printf("Another player plays Die \n");
							//					}
							//					else {
							//						comchip -= betting;
							//						totalchip += (betting * 2);
							//						printf("Another player plays call with %d \n", betting);
							//					}
							//				}
							//			}
							//		
							//	}
								else if (selection == '3') {
									printf("You plays Die \n");
									playerdie = 1;
								}
								break;
							}

						}
						else if (playercard < 5 && betting <= 10) {
							comchip -= betting;
							totalchip += (betting * 2);
							printf("Another player play call with %d. \n", betting);
							break;
						}
						else if (playercard > 8) {
							compdie = 1;
							printf("Another player plays Die. \n");
							break;
						}
						else {
							comchip -= betting;
							totalchip += (betting * 2);
							printf("Another player play call with %d. \n", betting);
							break;
						}
					}
					if (compdie == 1) {
						printf("You wins Game \n");
						playerchip += (totalchip + betting);
						compdie = 0;
						firstplayer = 0;
						if (computercard == 10) {
							comchip -= 10;
							playerchip += 10;
							printf("Another player dies with the number 10, the player pays 10 chips for penalty\n");
						}
					}
					else if (playerdie == 1) {
						printf("Another player wins Game \b");
						comchip += (totalchip + betting);
						playerdie = 0;
						firstplayer = 1;
						if (playercard == 10) {
							playerchip -= 10;
							comchip += 10;
							printf("You dies with the number 10, you pays 10 chips for penalty\n");
						}
					}
					else {
						if (playercard > computercard) {
							printf("You wins Game \n");
							playerchip += totalchip;
							totalchip = 0;
							firstplayer = 0;
						}
						else if (computercard > playercard) {
							printf("Another player wins Game \n");
							comchip += totalchip;
							totalchip = 0;
							firstplayer = 1;
						}
						else {
							printf("The game is draw, all the chips go to next round \n");
							draw = 1;
						}
					}
					printf("Your card is %d, and player card is %d", playercard, computercard);
					Sleep(2000);
					betting = 0;
					totalchip = 0;
					if (draw != 1 && (playerchip <= 0 || comchip <= 0)) {
						break;
					}

				}

			}
			else {
				if (firstplayer == 1) {
					computercard = drawDeck(deck, numofdeck - 1);
					numofdeck--;
					playercard = drawDeck(deck, numofdeck - 1);
					numofdeck--;
				}
				else {

					playercard = drawDeck(deck, numofdeck - 1);
					numofdeck--;
					computercard = drawDeck(deck, numofdeck - 1);
					numofdeck--;
				}
				if (playercard > computercard) {
					printf("You wins Game \n");
					playerchip += totalchip;
					totalchip = 0;
					firstplayer = 0;
				}
				else if (computercard > playercard) {
					printf("Another player wins Game \n");
					comchip += totalchip;
					totalchip = 0;
					firstplayer = 1;
				}
				else {
					printf("The game is draw, all the chips go to next round \n");
					draw = 1;
				}
				printf("Your card is %d, and player card is %d", playercard, computercard);
				Sleep(2000);
				betting = 0;
				totalchip = 0;
				if (draw != 1 && (playerchip <= 0 || comchip <= 0)) {
					break;
				}
			}
					
			}
		}
		if (playerchip == 0) {
			printf("You lost \n");
		}
		else {
			printf("You win \n");
		}

}




	




int showRules(void) {
	printf("This American Native poker's copyright is on tvn \n ");
	printf("1. The deck is consist of two set of 1 to 10 cards. \n");
	printf("2. Each player has 30 chips for betting \n");
	printf("3. Each player gets one card from the deck and each player cannot see their own card \n");
	printf("4. Each player can only can see other players card \n");
	printf("5. Each player need to pay one chip to participate the game. \n");
	printf("6. First player starts to bet, the first player needs to raise at least 1 chips. \n");
	printf("7. There are two ways for the second player. \n");
	printf("a. Call: Pay the same number of chips which the first player raise. \n");
	printf("b. Raise: pay more chips which should be more than the first player pay. \n");
	printf("ex) first player bet 7 chips then second player need pay at least 14 chips becaue 7 for following up and 7 for raise");
	printf("8. If the second player raise, the first player can select also call and raise");
	printf("9. If the betting is finished, open two players card.");
	printf("10. Win players take all the chips which two players bet and the winner becomes the first player");
	printf("11. If the game is draw, the chips for this round will go next round, not players");
	printf("12. If one player is out of chips, then another player win the game ");
}


int main(void)
{
	
	int selection = 0;
	printf("Welcome to American Native Poker \n");
	while (1) {
		printf("Type 1 to play or 2 for rules: ");
		selection = getchar();
		cleanBuffer();
		if (selection == '1') {
			play();
		}
		else if (selection == '2') {
			cleanScreen();
			showRules();
		}
		else {
			printf("Please type 1 or 2 only please");
			
		}
	}
	
	

}

