#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#define height 10
#define length 10
#define bomb 50

bool m[height][length] = {};
short hint[height][length] = {};
bool dug[height][length] = {};
bool flag[height][length] = {};
int show[height][length] = {};
int neighbor[height][length] = {};
bool over = 0, win = 0;
int cursor[2] = {0,0};
int t = (unsigned)time(NULL);
struct node {int i; int j;};
const node adder[8] = {{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};

void new_game (void) {
for (int i = 0; i < height; i++) {
	for (int j = 0; j < length; j++) m[i][j] = 0;}
	if(height * length < bomb) printf("Input Wrong!\n");
srand(t);
int temp_i, temp_j;
for (int b = 0; b < bomb; b ++) {
	t += rand(); srand(t); temp_i = rand() % height;
	t += rand(); srand(t); temp_j = rand() % length;
	if (m[temp_i][temp_j] == 1) b--; else {m[temp_i][temp_j] = 1;}}
for (int i = 0; i < height; i++) { for (int j = 0; j < length; j++) {
for (int temp = 0; temp < 8; temp++) {temp_i = i + adder[temp].i; temp_j = j + adder[temp].j;
if(temp_i >= 0 && temp_i < height && temp_j >= 0 && temp_j < length)hint[i][j] += m[temp_i][temp_j];
}}}
for (int i = 0; i < height; i++) {for (int j = 0; j < length; j++) {show[i][j] = hint[i][j];}}
}


void shows (void) {
	for (int i = 0; i < height; i++) {
	for (int j = 0; j < length; j++) {
		if(cursor[0] != i || cursor[1] != j) printf(" "); else printf(">");
		if(dug[i][j] != 0 && flag[i][j] == 0) {
			if(show[i][j] == 0) printf(" ");
			else if(show[i][j] == 9) printf("@");
			else printf("%d", show[i][j]);}
		else if (dug[i][j] == 0 && flag[i][j] == 1) printf("P");
		else printf("*");
		}
	printf("\n");}
}


void dig (int i, int j) {
	bool checked[height][length] = {};
	int temp = 1, neighbor_size = 1;
	node neighbor_list[2 * length * height] = {{0,0},{i,j}};
	dug[i][j] = 1;
	int list_i, list_j, temp_i, temp_j;
	if (m[i][j] == 1) {show[i][j] = 9; over = 1;}
	else {
		if (hint[i][j] == 0){ do {
		list_i = neighbor_list[temp].i; list_j = neighbor_list[temp].j;
		if (hint[list_i][list_j] == 0){
			checked[list_i][list_j] = 1;
			for (int temp2 = 0; temp2 < 8; temp2++) {
				temp_i = list_i + adder[temp2].i;
				temp_j = list_j + adder[temp2].j;
				if(temp_i >= 0 && temp_i < height && temp_j >= 0 && temp_j < length && checked[temp_i][temp_j] == 0)
				{neighbor_list[neighbor_size + 1] = {temp_i,temp_j}; neighbor_size++; dug[temp_i][temp_j] = 1; checked[temp_i][temp_j] = 1;}}}
		else if (hint[list_i][list_j] > 0) {checked[list_i][list_j] = 1; dug[list_i][list_j] = 1;}
		temp++;} while (temp <= neighbor_size);
}}}

void win_test (void) {
	win = 1;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < length; j++) {win = win && (flag[i][j]==m[i][j]);}}
}

void print_map (void) {
    for (int i = 0; i < height; i++) {
		for (int j = 0; j < length; j++)
	{if (m[i][j] == 0) {if(hint[i][j] != 0) printf(" %d", hint[i][j]); else printf("  ");} else printf(" @");}
	printf("\n");}
}

int main () {
    new_game();
    shows();
	printf("Press any keys to start.\nUse WASD or the direction keys to control the cursor.\nPress space button to dig. Press F to settle a flag.\n");
	while(over == 0) {
		char act;
		act = getche();
		switch (act) {
			case 'a': 
			case 'A': 
			case '\x4B': if(cursor[1] > 0) cursor[1]--; break;
			case 's': 
			case 'S': 
			case '\x50': if(cursor[0] < height - 1) cursor[0]++; break;
			case 'd': 
			case 'D': 
			case '\x4D': if(cursor[1] < length - 1) cursor[1]++; break;
			case 'w': 
			case 'W': 
			case '\x48': if(cursor[0] > 0) cursor[0]--; break;
			case ' ': if(dug[cursor[0]][cursor[1]] == 0 && flag[cursor[0]][cursor[1]] == 0) dig(cursor[0],cursor[1]); break;
			case 'f': 
			case 'F': if(dug[cursor[0]][cursor[1]] == 0) flag[cursor[0]][cursor[1]] = 1 - flag[cursor[0]][cursor[1]]; break;
			default: break;
		}
		system("cls");
		shows();
		if(over){system("cls");print_map();printf("Game Over!\n"); break;}
		win_test();
		if(win){system("cls");print_map();printf("You Win!\n"); break;}
	}
	return 0;
}
