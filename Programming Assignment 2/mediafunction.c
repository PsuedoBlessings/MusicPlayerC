#include "Header.h"

/*************************************************************
 * Function: print_menu ()                                   *
 * Date Created: 2/1/2022                                    *
 * Date Last Modified:                                       *
 * Description: prints out the menu options                  *
 * Input parameters:                                         *
 * Returns:                                                  *
 * Preconditions:                                            *
 * Postconditions: prints the what's in the qoutation (refer *
 * to the function)                                          *
 *************************************************************/

void print_menu(void)
{
	printf("(1) load\n(2) store\n(3) display\n(4) insert\n(5) delete\n");
	printf("(6) edit\n(7) sort\n(8) rate\n(9) play\n(10) shuffle\n");
	printf("(11) exit\n");
}

/*************************************************************
 * Function: get_option ()                                   *
 * Date Created: 2/1/2022                                    *
 * Date Last Modified:                                       *
 * Description: Gets an integer from user and returns the    *
 * integer to use in other functions.                        *
 * Input parameters:                                         *
 * Returns: int option                                       *
 * Preconditions:                                            *
 * Postconditions: Get an integer from user                  *
 *************************************************************/

int get_option(void)
{
	int option = 0;
	scanf("%d", &option);
	return option;
}

/*************************************************************
 * Function: Node* makeNode ()                               *
 * Date Created: 2/1/2022                                    *
 * Date Last Modified:                                       *
 * Description: Creates a node to be used in a list, it      *
 * consists of artist, album, song, genre, duration, time    *
 * played, and rating. it also checks if the artist has a    *
 * a single name or not                                      *
 * Input parameters: FILE* f                                 *
 * Returns: Node* pMem                                       *
 * Preconditions: The file data must be seperated by commas  *
 * (commonly found in csv files) and organized               *
 * Postconditions: A Node will be made containing the        *
 * information in description and it's next node             *
 *************************************************************/

Node* makeNode(char* str)
{
	Node* pMem = (Node*)malloc(sizeof(Node)); // 58 bytes allocated

	if (pMem != NULL)
	{
		// allocated space for Node successfully
		// let's initialize it

		// this will tell us if it's a single name or not
		if (str[0] == '\"')
		{
			// this is not a signle name

			strcpy(pMem->data.artist, strtok(str, "\""));
			
		}

		else
		{
			// it's a single name
			strcpy(pMem->data.artist, strtok(str, ","));
		}

		//initalize rest of the node

		strcpy(pMem->data.albumTitle, strtok(NULL, ","));
		strcpy(pMem->data.songTitle, strtok(NULL, ","));
		strcpy(pMem->data.genre, strtok(NULL, ","));
		pMem->data.duration.minutes = atoi(strtok(NULL, ":"));
		pMem->data.duration.seconds = atoi(strtok(NULL, ","));
		pMem->data.numberTimesPlayed = atoi(strtok(NULL, ","));
		pMem->data.rating = atoi(strtok(NULL, ","));

		pMem->pNext = NULL;
	}
	return pMem;
}
/**********************LOADING FUNCTIONS*******************************/

/*************************************************************
 * Function: int insertFront(Node** pList, FILE* f,          *
 * Node** ptemp)                                             *
 * Date Created: 2/2/2022                                    *
 * Date Last Modified:                                       *
 * Description: Adds a node to the front of the list and     *
 * gives addresses of the previous and next node             *
 * Input parameters: Node** pList, FILE* f, Node** ptemp     *
 * Returns: int success                                      *
 * Preconditions: An input file that is organized by commas  *
 * an address of an adresss to a node and a temporay one of  *
 * the same properties                                       *
 * Postconditions: Makes a node and adds it to the front of  *
 * list and give it's next node's address and gives the      *
 * current node's address to the node after.                 *
 *************************************************************/

int insertFront(Node** pList, char* str)
{
	Node* pMem = makeNode(str); // allocate and initialize Node with movie data
	Node* temp = *pList;
	int success = 0;

	// think state of linked list
	// 2 states - empty, not empty

	if (pMem != NULL) // checks if space was allocated on the heap
	{
		// succeeded at allocating space on heap for Node
		if (*pList == NULL)
		{
			// the list is empty
			*pList = pMem;
			pMem->pNext = NULL;
			pMem->pPrev = NULL;
		}

		else
		{
			if (temp->pPrev == NULL) // checks if the node after has a Previous Node's adress
			{
				// the node doesn't have a previous Node's address
				temp->pPrev = pMem;
			}
			// this isn't the 
			pMem->pNext = *pList;
			*pList = pMem;
			pMem->pPrev = NULL;
		}

		success = 1;
	}

	return success;
}

void loading_Music(Node** pList, FILE* f)
{
	while (!feof(f)) // loads till end of file
	{
		int success = 0;
		char line[170] = { '\0' };
		fgets(line, 170, f);
		success = insertFront(pList, line);

		if (success == 0)
		{
			printf("the code had failed somewhere withing insertFront");
			return;
		}
	}
}
/********************************************************************/

/**************************STORE FUNCTIONS***************************/

void file_Print_Node(Node** pList, FILE* f)
{
	Node* pMem = *pList;
	
	int success = 0;

	if (pMem != NULL)
	{
		while (pMem->pNext != NULL)
		{
			/********storing artist*********/
			for (int index = 0; pMem->data.artist[index] == '\0'; index++)
			{
				if (pMem->data.artist[index] == ',')
				{
					fprintf(f, "\"");
					fprintf(f, ("%s", pMem->data.artist));
					fprintf(f, "\",");
					success = 1;
				}
			}
			if (success == 0)
			{
				fprintf(f, ("%s,", pMem->data.artist));
			}
			/***************************************/

			fprintf(f, ("%s,%s,%s,%d:%d,%d,%d\n", pMem->data.albumTitle, pMem->data.songTitle,
				pMem->data.genre, pMem->data.duration.minutes, pMem->data.duration.seconds,
				pMem->data.numberTimesPlayed, pMem->data.rating));
			/*fprintf(f, ("%s,", pMem->data.songTitle));
			fprintf(f, ("%s,", pMem->data.genre));
			fprintf(f, ("%d:", pMem->data.duration.minutes));
			fprintf(f, ("%d,", pMem->data.duration.seconds));
			fprintf(f, ("%s,", pMem->data.numberTimesPlayed));
			fprintf(f, ("%s", pMem->data.rating));*/
			pMem = pMem->pNext;
		}
	}
}

void store_Music(Node **pList, FILE* f)
{
		file_Print_Node(pList, f);
}
/********************************************************************/

/**************************DISPLAY FUNCTIONS***************************/
Node* print_Node(Node* pList)
{
	Node* pMem = pList;

	int success = 0;

	if (pMem != NULL)
	{
		/********displaying artist*********/
		for (int index = 0; pMem->data.artist[index] == '\0'; index++)
		{
			// checks if the artist name is a signle name or not.
			if (pMem->data.artist[index] == ',')
			{
				printf("Artist: ");
				printf("\"");
				printf("%s", pMem->data.artist);
				printf("\"\n");
				success = 1;
			}
		}
		if (success == 0)
		{
			printf("Artist: ");
			printf("%s\n", pMem->data.artist);
		}
		/***************************************/
		printf("Album: ");
		printf("%s\n", pMem->data.albumTitle);
		printf("Song: ");
		printf("%s\n", pMem->data.songTitle);
		printf("Genre: ");
		printf("%s\n", pMem->data.genre);
		printf("Duration: ");
		printf("%d:", pMem->data.duration.minutes);
		printf("%d\n\n", pMem->data.duration.seconds);
	}
	return pMem;
}

void print_All_Nodes(Node* pList)
{
	Node* pPos = print_Node(pList);

	// if the list is empty
	if (pPos == NULL)
	{
		return;
	}

	else
	{
		while (pPos->pNext != NULL)
		{
			// updates pPos to be revalutated by while condition 
			pPos = print_Node(pPos->pNext);
		}
	}

}

void print_Match_Nodes(Node* pList)
{
	Node* pMem = pList;

	int success = 0;
	char s[20] = { "" };

	if (pMem != NULL)
	{
		printf("What Artist would you like to display: ");
		fgets(s, 20, stdin);
		strtok(s, "\n");

		// looks for a space within the user inputed text 

		printf("Here are the results for %s\n\n", s);

		while (pMem->pNext != NULL)
		{
			if (strcmp(pMem->data.artist, s) == 0)
			{
				print_Node(pMem);
				pMem = pMem->pNext;
			}

			else
			{
				pMem = pMem->pNext;
			}
		}
	}
}

void display_Music(Node** pList, int option)
{
		
		// checks if option is valid
		if (option < 1 || option > 2)
		{
			system("cls");
			printf("You inputed an option that's not available\n");
		}

		switch (option)
		{
		// display all music
		case 1:
			print_All_Nodes(*pList);
			break;

		// display music that matches search
		case 2:
			print_Match_Nodes(*pList);
		}
}
/********************************************************************/

/**************************INSERT FUNCTION***************************/

void insert_Function (Node** pList)
{ 
	int success = 0;
	char singleName = '\0';
	char nodeInfo[170] = { '\0' };
	char songTitle[50] = { '\0' };
	char albumTitle[50] = { '\0' };
	char artist[20] = { '\0' };
	char firstName[20] = { '\0' };
	char lastName[20] = { '\0' };
	char genre[20] = { '\0' };
	char duration[7] = { '\0' };
	char timePlayed[7] = { '\0' };
	char rating[7] = { '\0' };
	
	printf("What is the name of the song: ");
	fgets(songTitle, 50, stdin);
	fgets(songTitle, 50, stdin);
	strtok(songTitle, "\n");
	
	printf("What is the name of the album %s is from: ", songTitle);
	fgets(albumTitle, 50, stdin);
	
	printf("does this artist have a more than one name (Y/N):");
	scanf("%c", &singleName);
	
	if (singleName == 'Y')
	{
		printf("What is the first name of the artist of %s: ", songTitle);
		fgets(firstName, 20, stdin);
		strtok(firstName, "\n");
		printf("What is the last name of the artist of %s: ", songTitle);
		fgets(lastName, 20, stdin);
		strcat(artist, firstName);
		strcat(artist, ", ");
		strcat(artist, lastName);
	}
	else
	{
		printf("Who is the artist of %s: ", songTitle);
		fgets(artist, 20, stdin);
		fgets(artist, 20, stdin);
	}
	

	printf("What genre is %s: ", songTitle);
	fgets(genre, 20, stdin);

	printf("How long is %s (format 1:23): ", songTitle);
	fgets(duration, 7, stdin);

	printf("How many times have you played %s: ", songTitle);
	fgets(timePlayed, 7, stdin);

	printf("What would you rate %s out of 1 to 5: ", songTitle);
	fgets(rating, 7, stdin);

	strtok(artist, "\n");
	strtok(albumTitle, "\n");
	strtok(genre, "\n");
	strtok(duration, "\n");
	strtok(timePlayed, "\n");
	strtok(rating, "\n");

	strcat(nodeInfo, artist);
	strcat(nodeInfo, ",");
	strcat(nodeInfo, albumTitle);
	strcat(nodeInfo, ",");
	strcat(nodeInfo, songTitle);
	strcat(nodeInfo, ",");
	strcat(nodeInfo, genre);
	strcat(nodeInfo, ",");
	strcat(nodeInfo, duration);
	strcat(nodeInfo, ",");
	strcat(nodeInfo, timePlayed);
	strcat(nodeInfo, ",");
	strcat(nodeInfo, rating);

	success = insertFront(pList, nodeInfo);

	if (success == 0)
	{
		printf("somwhere within insertFront failed within instert_function");
	}

}

/**************************DELETE FUNCTIONS***************************/

void delete_Node(Node* pList)
{
	Node* pCur = pList;
	Node* pNext = pCur->pNext;
	Node* pPrev = pCur->pPrev;
	pPrev->pNext = pNext;
	pNext->pPrev = pPrev;
	free(pCur);
}

void delete_Function(Node** pList)
{
	Node* pMem = *pList;

	int success = 0;
	char s[20] = { "" };

	if (pMem != NULL)
	{
		printf("What song would you like to delete: ");
		fgets(s, 20, stdin);
		fgets(s, 20, stdin);
		strtok(s, "\n");

		// looks for a space within the user inputed text 

		while (pMem->pNext != NULL)
		{
			if (strcmp(pMem->data.songTitle, s) == 0)
			{
				printf("Deleting %s\n", pMem->data.songTitle);
				delete_Node(pMem);
				printf("deletion successful\n");
				return;
			}

			else
			{
				pMem = pMem->pNext;
			}
		}
	}

}

/**************************EDIT FUNCTIONS***************************/

void edit_Node(Node** pList)
{
	Node* pCur = *pList;

	int option = 0;

	int exit = 0;

	char s[50];

	int i = 0;

	// makes sure that the input for the main menu is a valid input
	while (option < 1 || option > 8)
	{
		// if the user has exited the program
		while (!exit)
		{
			system("cls");

			printf("Changing Menu\n\n");

			printf("(1) Artist Title\n(2) Album Title\n(3) Song Title\n(4) Genre\n(5) Duration\n(6) Times Played\n(7) Rating\n(8) Exit\n");

			option = get_option();
			if (option < 1 && option > 8)
			{
				system("cls");
				printf("You inputed an option that's not available\n");
			}

			switch (option)
			{
			case 1:
				system("cls");
				printf("What shall the new artist name be: ");
				fgets(s, 50, stdin);
				strcpy(pCur->data.artist, s);
				break;
			case 2:
				system("cls");
				printf("What shall the new album title be: ");
				fgets(s, 50, stdin);
				strcpy(pCur->data.albumTitle, s);
				break;
			case 3:
				system("cls");
				printf("What shall the new song title be: ");
				fgets(s, 50, stdin);
				strcpy(pCur->data.songTitle, s);
				break;
			case 4:
				system("cls");
				printf("What shall the new genre be: ");
				fgets(s, 50, stdin);
				strcpy(pCur->data.genre, s);
				break;
			case 5:
				system("cls");
				printf("How many minutes is now: ");
				scanf("%d", &i);
				pCur->data.duration.minutes = i;
				printf("How many seconds is now: ");
				scanf("%d", &i);
				pCur->data.duration.seconds = i;
				break;
			case 6:
				system("cls");
				printf("How many times have it been played now: ");
				scanf("%d", &i);
				pCur->data.numberTimesPlayed = i;
				break;
			case 7:
				system("cls");
				printf("What would you rate it now: ");
				scanf("%d", &i);
				pCur->data.rating = i;
				break;
			case 8:
				exit = 1;
				break;
			}
		}
	}
}

void edit_Function (Node*pList)
{
	Node* pMem = pList;

	int success = 0;
	char artist[20] = { "" };
	char songTitle[50] = { "" };

	if (pMem != NULL)
	{
		printf("What Artist would you like to display: ");
		fgets(artist, 20, stdin);
		fgets(artist, 20, stdin);
		strtok(artist, "\n");

		// looks for a space within the user inputed text 

		printf("Here are the results for %s\n\n", artist);

		while (pMem->pNext != NULL)
		{
			if (strcmp(pMem->data.artist, artist) == 0)
			{
				print_Node(pMem);
				pMem = pMem->pNext;
			}

			else
			{
				pMem = pMem->pNext;
			}
		}

		printf("Which one of these songs do you want to edit: ");
		fgets(songTitle, 20, stdin);
		strtok(songTitle, "\n");

		while (pMem->pPrev != NULL)
		{
			if ((strcmp(pMem->data.songTitle, songTitle) == 0) && (strcmp(pMem->data.artist, artist) == 0))
			{
				edit_Node(pMem);
				return;
			}

			else
			{
				pMem = pMem->pPrev;
			}
		}

	}
}

/**************************RATING FUNCTIONS***************************/

void rate_Node(Node* pList)
{
	Node* pCur = pList;
	int rating = 0;

	while (rating < 1 || rating > 5)
	{
		printf("What do you want to rate %s (1-5): ", pCur->data.songTitle);
		rating = get_option();
		if (rating < 1 && rating > 5)
		{
			system("cls");
			printf("You inputed a rating that's not between 1 to 5\n");
		}

		pCur->data.rating = rating;
	}
}

void rate_Functions(Node**pList)
{
	Node* pMem = *pList;

	int success = 0;
	char songTitle[50] = { "" };

	printf("Which song do you want to rate: ");
	fgets(songTitle, 20, stdin);
	fgets(songTitle, 20, stdin);
	strtok(songTitle, "\n");

	while (pMem->pNext != NULL)
	{
		if (strcmp(pMem->data.songTitle, songTitle) == 0)
		{
			print_Node(pMem);
			rate_Node(pMem);
			return;
		}

		else
		{
			pMem = pMem->pNext;
		}
	}

}

/**************************PLAYING FUNCTIONS***************************/

void play_function (Node*pList)

{
	Node* pMem = pList;

	int success = 0;
	char songTitle[50] = { "" };

	printf("Which song do you play: ");
	fgets(songTitle, 20, stdin);
	fgets(songTitle, 20, stdin);
	strtok(songTitle, "\n");

	while (pMem->pNext != NULL)
	{
		if (strcmp(pMem->data.songTitle, songTitle) == 0)
		{
			printf("VV Playing VV\n\n");
			print_Node(pMem);
			return;
		}

		else
		{
			pMem = pMem->pNext;
		}
	}

}

/**************************SORTING FUNCTIONS***************************/

int node_Counter(Node** pList)
{
	int counter = 0;
	Node* pCur = *pList;

	while (pCur != NULL)
	{
		++counter;
		pCur = pCur->pNext;
	}
	return counter;
}

void sort_Artist(Node** pList)
{
	Node* pCur = *pList;
	Node* pNext = pCur->pNext;

	for (int size = node_Counter(pList); size != 0; size--)
	{
		int success = 0;

		for (int index = 0; pNext->data.artist[index] != '\0'; index++)
		{
			if (pCur->data.artist[index] < pNext->data.artist[index])
			{
				Node* pTemp = pCur;

				// switching nodes position
				pCur->pNext = pNext->pNext;
				pCur->pPrev = pNext->pPrev;
				pNext->pNext = pTemp->pNext;
				pNext->pPrev = pTemp->pPrev;
				// restarts the index back to 0 for the next comparsion
				success = 1;
				index = -1;
			}

		}

		if (success == 0)
		{
			pCur = pCur->pNext;
			pNext = pCur->pNext;
		}
	}
}

void sort_Album_Title(Node** pList)
{
	Node* pCur = *pList;
	Node* pNext = pCur->pNext;

	for (int size = node_Counter(pList); size != 0; size--)
	{
		int success = 0;
		
		for (int index = 0; pNext->data.albumTitle[index] != '\0'; index++)
		{
			if (pCur->data.albumTitle[index] < pNext->data.albumTitle[index])
			{
				Node* pTemp = pCur;

				// switching nodes position
				pCur->pNext = pNext->pNext;
				pCur->pPrev = pNext->pPrev;
				pNext->pNext = pTemp->pNext;
				pNext->pPrev = pTemp->pPrev;
				// restarts the index back to 0 for the next comparsion
				success = 1;
				index = -1;
			}

		}

		if (success == 0)
		{
			pCur = pCur->pNext;
			pNext = pCur->pNext;
		}
	}
}

void sort_Rating(Node** pList)
{
	Node* pCur = *pList;
	Node* pNext = pCur->pNext;

	for (int size = node_Counter(pList); size != 0; size--)
	{
		if (pCur->data.rating < pNext->data.rating)
		{
			Node* pTemp = pCur;
			
			// switching nodes position
			pCur->pNext = pNext->pNext;
			pCur->pPrev = pNext->pPrev;
			pNext->pNext = pTemp->pNext;
			pNext->pPrev = pTemp->pPrev;
		}

		else
		{
			pCur = pCur->pNext;
			pNext = pCur->pNext;
		}
		
	}
}

void sort_Times_Played(Node** pList)
{
	Node* pCur = *pList;
	Node* pNext = pCur->pNext;

	for (int size = node_Counter(pList); size != 0; size--)
	{
		if (pCur->data.numberTimesPlayed < pNext->data.numberTimesPlayed)
		{
			Node* pTemp = pCur;

			// switching nodes position
			pCur->pNext = pNext->pNext;
			pCur->pPrev = pNext->pPrev;
			pNext->pNext = pTemp->pNext;
			pNext->pPrev = pTemp->pPrev;
		}

		else
		{
			pCur = pCur->pNext;
			pNext = pCur->pNext;
		}

	}
}

void sort_Function(Node** pList)
{
	int option = 0;
	int exit = 0;
	while (option < 1 || option > 5)
	{
		// if the user has exited the program
		while (!exit)
		{
			system("cls");

			printf("Sorting Menu\n\n");

			printf("(1) Sort By Artist (A-Z)\n(2) Sort By Album Title (A-Z)\n(3) Sort By Rating\n(4) Sort By Numbers of Times Played\n(5) Exit\n");

			option = get_option();
			if (option < 1 && option > 5)
			{
				system("cls");
				printf("You inputed an option that's not available\n");
			}

			switch (option)
			{
			case 1:
				sort_Artist(pList);
				break;
			case 2:
				sort_Album_Title(pList);
				break;
			case 3:
				sort_Rating(pList);
				break;
			case 4:
				sort_Times_Played(pList);
				break;
			case 5:
				exit = 1;
				break;
			}
		}
	}

}
/**************************SHUFFLING FUNCTIONS***************************/



void shuffling_Function(Node** pList,int size)
{
	for (int size = node_Counter(pList), index = 0; size != 0; size--)
	{
		
	
	}
}