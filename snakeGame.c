#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <conio.h>

struct node{
    int x;
    int y;

    struct node *next;
};

typedef struct node snake;
snake *head=NULL;
snake *tail;

int map[120][120];
int score,i,j,level;
static int last_dir='w';

int sizeX = 90; 
int sizeY = 20;
int score = 0;
int xFood = 4;
int yFood = 10;

int xSFood = 6;
int ySFood = 6;

char foodDisplay='A';

char dir_snake = 'w';

void createBody(int x, int y){
    /*
        to create a body of a snake when it eats a food or at the beggining
    */

	snake *body = (snake *) malloc (sizeof(snake));    
	body->x = x;
	body->y = y;

	if (head==NULL){
		head = tail = body;
	}
	else{
		tail->next = body;
		tail = body;
		score=score + 1;
	}
	tail->next = NULL;
	
}

char random_alphabets()    // For Displaying random quotes in the start of the program
{   
    srand(time(0));
    int randomIndex = rand() % 26;
    char randomAlphabet = 'A' + randomIndex;
    return randomAlphabet;
}
void createFood(){

    /*
        to create a food.when food is eaten by the snake the food generated at random posintion inside the map
    */
	srand( time(NULL));
	map[yFood][xFood] = 0;
	do{
		xFood = rand() % (sizeX - 1) + 1;
		yFood = rand() % (sizeY - 1) + 1;
	} while (map[yFood][xFood] != 0);
    foodDisplay =random_alphabets();
	map[yFood][xFood] = 3; 
}


void createSuperFood(){

    /*
        to create a super food.when super food is eaten score is increased + 4
    */
	srand( time(NULL));
	map[yFood][xFood] = 0;
	do{
		xSFood = rand() % (sizeX - 1) + 1;
		ySFood = rand() % (sizeY - 1) + 1;
	} while (map[ySFood][xSFood] != 0);
	map[yFood][xFood] = 4; 
}


void createMap(){

    /*
        to create the map for the game 
    */
	for (i = 0; i < sizeY; i++){
		for (j = 0; j < sizeX; j++){
			if (i == 0 || i == sizeY - 1 || j == 0 || j == sizeX - 1) 
			        map[i][j] = 1;        // for the boarder
			else{ 
	             snake *t = head;
                int isSnakeBody = 0;  // Flag to check if the cell is part of the snake
                while (t != NULL) {
                    if (i == t->y && j == t->x) {
                        map[i][j] = 2;  // Cell is part of the snake
                        isSnakeBody = 1;
                        break;
                    }
                    t = t->next;
                }
                if (!isSnakeBody)  // Cell is not part of the snake
                    map[i][j] = 0;          //  for the blank or empty spaces
			}
		}
	}
	map[yFood][xFood] = 3;             //for the food
    if(score%5==0 && score!=0){         //for super food
        map[ySFood][xSFood] = 4;
    }
}

void viewmap(){

    /*
    to display the complete map with relative postion of snake and food
    */

    snake * p;
    // printf("viewing map \n");
    for( i=0;i<sizeY;i++){
        for( j=0;j<sizeX;j++){
            if(map[i][j]==1)
                printf("#");
            else if(map[i][j]==0)
                printf(" ");
            else if(map[i][j]==2){

                p=head;
                if(i==p->y && j==p->x)
                    printf("*");
                // printf("\n");
                // while(p!=NULL){
                // p=p->next;
                // }

                else
                    printf("*");
            }
                
            else if(map[i][j]==3)
                printf("%c",foodDisplay);
            else if(map[i][j]==4)
                printf("@");
        }
        
        printf("\n");
    }
    
    printf("\n");
    printf("score : %d",score);
    printf("\n");
    printf("\n");
    printf("press w - a - s - d");
    printf("\n");
}
 

void gameOverScren(){
    Sleep(2000);
    system("cls");
    printf("###################################################################################################################\n\n");
    
    printf("@@@@@@@@@@@@                               < < < SNAKE GAME  > > >                                       @@@@@@@@@@\n");

    printf("\nGAME OVER...\n");
    printf("\nYOUR SCORE IS :  %d\n",score);
    
    
    

    printf("\n###################################################################################################################\n");
}


void run(int change_x, int change_y) {

        /*
            to make the sanke move 
        */

    snake *t = head;
    int prev_x = head->x;
    int prev_y = head->y;

    // Update the coordinates of the head based on change in x and y
    head->x += change_x;
    head->y += change_y;

    if(map[head->y][head->x] == 1){         //check weather the snake head hit the boarder
        printf("\n");
        printf("game over hit you hit boarder");
        printf("score %d",score);
        printf("\n");
        gameOverScren();
        exit(0);
    }
    if(map[head->y][head->x] == 2){         //check weather the snake head hit the Snake
        printf("\n");
        printf("game over you hit snake ");
        printf("score %d",score);
        printf("\n");
        gameOverScren();
        exit(0);
    }
    if(head->x ==xFood && head->y == yFood){         //checks weather the snake head eats the food
        printf("\n");
        printf("eat food");
        printf("\n");
        createBody(xFood,yFood);
        createFood();
    }
    if(head->x ==xSFood && head->y == ySFood && score%5==0){         //checks weather the snake head eats the Super food
        printf("\n");
        printf("eat Super food");
        printf("\n");
        score=score+4;
        createSuperFood();
    }
    // Traverse the rest of the snake and update coordinates
    while (t->next != NULL) {           
        t = t->next;
        int temp_x = t->x;
        int temp_y = t->y;
        t->x = prev_x;
        t->y = prev_y;
        prev_x = temp_x;
        prev_y = temp_y;
    }
}


void move(){
    if (kbhit()){
        dir_snake = getch();
    }
    switch(dir_snake){
        case 'w': if(last_dir!='s')
                    {run(0,-1);}       //will pass the value to run() to move up
                    
                break;
        case 's': if(last_dir!='w')     //will pass the value to run() to move udown
                    {run(0,1);}
            
                break;
        case 'a':if(last_dir!='d')      //will pass the value to run() to move left
                    {run(-1,0);}
					    
                break;
        case 'd': if(last_dir!='a')     //will pass the value to run() to move right
                    {run(1,0);}
                
                break;
        case 'q': exit(0);              //quit
        default:
                
                printf("enter the correct choise :\nup - w\ndown - s \nleft - a \nright -d\nquit -q\n"); 
                dir_snake = getch();
                move();

    }
    if (level == 3)
    {
        Sleep(100);
    }
    else if (level == 2)
    {
        Sleep(400);
    }
    else{
        Sleep(650);
    }
    
    last_dir=dir_snake;
}

void play(){
    createMap();
    viewmap();
    move();
}
int froCover(){
    int ch;
    printf("###################################################################################################################\n\n");
    
    printf("@@@@@@@@@@@@                               < < < SNAKE GAME  > > >                                       @@@@@@@@@@\n");

    printf("\ninstructions\n");
    printf("\nup    -> w \ndown  -> s\nleft  -> a\nright -> d\nquit  -> q\n");

    printf("\npress 1 for to start\nor\npress 2 to quit\n");
    printf("\n###################################################################################################################\n");
    printf("\nenter your choice 1/2 : ");
    scanf("%d",&ch);
    printf("\nenter the difficulty :\neasy - 1\nmedium - 2\nhard - 3\n");
    scanf("%d",&level);
   
    
    return ch;
}
void menu(){
    int ch;
    

    ch = froCover();
    do{
        system("cls");
        play();
    }while(ch==1);
}
void freeSnakeMemory() {
    snake *current = head;
    while (current != NULL) {
        snake *temp = current;
        current = current->next;
        free(temp);
    }
}
int main()
{
    createBody(4, 4);
    menu();
    freeSnakeMemory();
    return 0;
}



