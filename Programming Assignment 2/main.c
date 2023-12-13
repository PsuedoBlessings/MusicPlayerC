#include "Header.h"

int main(void)
{
	FILE* infile = fopen("musicPlayList.csv", "r");
	
	Node* pHead = NULL;
	
	int success = 0, option = 0, loaded = 0, exit = 0;

	// validates that infile was opened
	if (infile != NULL)
	{
		// makes sure that the input for the main menu is a valid input
		while (option < 1 || option > 11)
		{
			// if the user has exited the program
			while (!exit)
			{
				print_menu();
				option = get_option();
				if (option < 1 && option > 11)
				{
					system("cls");
					printf("You inputed an option that's not available\n");
				}
				// the main menu
				switch (option)
				{

				case LOAD:
					if (!loaded)
					{
						system("cls");
						loading_Music(&pHead, infile);
						loaded = 1;
						break;
					}

					else
					{
						system("cls");
						printf("You've already loaded your music!\n");
						break;
					}
				case STORE:
					// checks if the user has actually loaded the music yet
					if (!loaded)
					{
						system("cls");
						printf("You havent loaded the music yet (select option 1 to load music).\n");
						break;
					}
					system("cls");
					FILE* outfile = fopen("musicPlayList.csv", "w");
					store_Music(&pHead, outfile);
					break;
				case DISPLAY:
					if (!loaded)
					{
						system("cls");
						printf("You havent loaded the music yet (select option 1 to load music).\n");
						break;
					}
					system("cls");
					printf("(1)  Display All Songs\n(2)  Search Songs of Specific a Artist\n");
					display_Music(&pHead, get_option());
					break;
				case INSERT:
					if (!loaded)
					{
						system("cls");
						printf("You havent loaded the music yet (select option 1 to load music).\n");
						break;
					}
					insert_Function(&pHead);
					break;
				case DELETE:
					if (!loaded)
					{
						system("cls");
						printf("You havent loaded the music yet (select option 1 to load music).\n");
						break;
					}
					delete_Function(&pHead);
					break;
				case EDIT:
					if (!loaded)
					{
						system("cls");
						printf("You havent loaded the music yet (select option 1 to load music).\n");
						edit_Function(&pHead);
						break;
					}
					break;
				case SORT:
					if (!loaded)
					{
						system("cls");
						printf("You havent loaded the music yet (select option 1 to load music).\n");
						break;
					}
					sort_Function(&pHead);
					break;
				case RATE:
					if (!loaded)
					{
						system("cls");
						printf("You havent loaded the music yet (select option 1 to load music).\n");
						break;
					}

					rate_Functions(&pHead);

					break;
				case PLAY:
					if (!loaded)
					{
						system("cls");
						printf("You havent loaded the music yet (select option 1 to load music).\n");
						break;
					}
					play_function(pHead);
					break;
				case SHUFFLE:
					if (!loaded)
					{
						system("cls");
						printf("You havent loaded the music yet (select option 1 to load music).\n");
						break;
					}
					break;
				case EXIT:
					// the user wants to exit the program
					exit = 1;
					break;
				}
			}
		}
	}
	return 0;
}