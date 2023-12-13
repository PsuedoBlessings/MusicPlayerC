#ifndef HEADER_H
#define HEADER_H // guard code

#define _CRT_SECURE_NO_WARNINGS 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

typedef enum menu

{
	LOAD = 1, STORE = 2, DISPLAY = 3, INSERT = 4,
	DELETE = 5, EDIT = 6, SORT = 7, RATE = 8, 
	PLAY = 9, SHUFFLE = 10, EXIT = 11
} MainMenu;

typedef struct duration
{
	int minutes; // 4 Bytes
	int seconds; // 4 Bytes
}Duration;

typedef struct record
{
	//song
	char artist[50]; // 50 Bytes // char *
	char albumTitle[50]; // 50 Bytes // char *
	char songTitle[50]; // 50 Bytes // char *
	char genre[20]; // 20 Bytes // char *
	Duration duration; // 8 Bytes // Duration
	int numberTimesPlayed; // 4 Bytes // int
	int rating; // 4 Bytes // int
}Record;

typedef struct node
{
	Record data;

	//link
	struct node* pNext; // 4 Bytes
	//link to itself
	struct node* pPrev;
}Node; // 186 Bytes

void print_menu(void);

int get_option(void);

Node* makeNode(char* str);

int insertFront(Node** pList, char* str);

void loading_Music(Node** pList, FILE* f);

void file_Print_Node(Node** pList, FILE* f);

void store_Music(Node** pList, FILE* f);

Node* print_Node(Node* pList);

void print_All_Nodes(Node* pList);

void print_Match_Nodes(Node* pList);

void display_Music(Node** pList, int option);

void insert_Function(Node** pList);

void delete_Node(Node** pList);

void delete_Function(Node** pList);

void edit_Node(Node** pList);

void edit_Function(Node** pList);

void rate_Node(Node** pList);

void rate_Functions(Node** pList);

void play_function(Node* pList);

#endif
