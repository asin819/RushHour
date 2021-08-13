#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define NUM_ROWS 8
#define NUM_COLS 8

#define SPACE 0
#define WALL -1
#define EXIT -2

/***********************************************************/
/***********************************************************/
/******* ADD THE REQUIRED FUNCTIONS BELOW THIS POINT *******/
/***********************************************************/
/***********************************************************/

// Your function definitions should go here...

void InitialiseRoad(int road[NUM_ROWS][NUM_COLS], char side, int pos){
    
    for(int i=0; i<NUM_ROWS; i++){
        for(int j=0; j<NUM_COLS; j++){
            road[i][j] = SPACE;
        }        
    }

    for(int i=0; i<NUM_COLS; i++){
        road[0][i] = WALL;
        road[NUM_ROWS-1][i] = WALL;
    }
    for(int i=0; i<NUM_ROWS; i++){
        road[i][0] = WALL;
        road[i][NUM_COLS-1] = WALL;
    }
    
    
    
    int row = 0;
    int col = 0;
    int dir = 0; // 1 for horizontal 0 for vertical
    if(side=='N'){
        row = 0;
        dir = 1;
    } else if (side =='E'){
        col = NUM_COLS-1;
        dir = 0;
    } else if (side=='S'){
         row = NUM_ROWS-1;;
         dir = 1;
    } else if (side=='W'){
        col = 0;
        dir = 0;
    }
    
    
    if (dir==1){
        road[row][pos] = EXIT;
    } else if (dir==0){
        road[pos][col] = EXIT;
    }
}


void PrintRoad(int road[NUM_ROWS][NUM_COLS]){

    for(int i=0; i<NUM_ROWS; i++){
        for(int j=0; j<NUM_COLS; j++){
            if(road[i][j]==-1){
                road[i][j]= (char)35;
            } else if (road[i][j]==-2){
                road[i][j]= (char)79;
            } else if (road[i][j]==SPACE){
                road[i][j] = (char)32;
            }
        }
    }
    for (int i = 0; i < NUM_ROWS; i++)
    {
        for (int j = 0; j< NUM_COLS; j++)
        {
            printf("%c", road[i][j] );
        }
        printf("\n");
    }
}

double PercentUsed(int road[NUM_ROWS][NUM_COLS]){
	
	// Initialising the variables that will be used to 
	// count the empty spaces and the used spaces
	double roadCounter = 0;
	double usedCounter = 0;

	// Seeing the given array is in -1 or #
	// 0 represents -1 and 1 represents #
	int mode = 0;
	if(road[0][0]==WALL){
		mode = 0;
	}else{
		mode = 1;
	}
	// Using nested for loops to go through the array
	// and counting the space and non space elements
	if(mode==1){
		for(int i=0; i<NUM_ROWS; i++){
			for(int j=0; j<NUM_COLS; j++){
				if(road[i][j]!='#' && road[i][j]!='O'){
					roadCounter++;
					if (road[i][j]!=(char)32){
						usedCounter++;
					}
				}
			}
		}
	}else{
		for(int i=0; i<NUM_ROWS; i++){
			for(int j=0; j<NUM_COLS; j++){
				if(road[i][j]!=WALL && road[i][j]!=EXIT){
					roadCounter++;
					if (road[i][j]!=SPACE){
						usedCounter++;
					}
				}
			}
		}		
	}

	// Returning the percentage of the road used
	return (usedCounter/roadCounter)*100;

}

int Helper_IsCarPresent(int road[NUM_ROWS][NUM_COLS], char car){

    for(int i=0; i<NUM_ROWS; i++){
        for(int j=0; j<NUM_COLS; j++){
            if(road[i][j]!='#' && road[i][j]!='O'){
                if(road[i][j]== car){
                    return 1;
                }
            }
        }
    }
    return 0;
}


int Helper_IsRoadEmpty(int road[NUM_ROWS][NUM_COLS], int row, int col, int size){

    // We will first find whether our elememts are in the form of -1 or #
    int mode = 0;
    if(road[0][0]==-1){
        mode = 1; // Mode 1 for -1 borders and Mode 0 for # borders.
    }

    if(mode==0){
        // If the size is less than zero, then the space we are searching 
        // for is vertically oriented.
        if(size<0){

            // Taking the magnitude of the size
            int sizeMag = size*-1;

            // Searching through the whole section, if any of the elements
            // are not space, we immediately return false.
            for (int i=row; i<(row+sizeMag); i++){
                if(road[i][col]!=(char)32){
                    return 0;
                }
            }
            // If the searched section is empty, we return true.
            return 1;
        }
        // If the size is greater than zero, it means it is horizontally 
        // oriented and we repeat the same prccess we did above.    
        else{
            for(int i=col; i<(col+size); i++){
                if(road[row][i]!=(char)32){
                    return 0;
                }
            }
            return 1;
        }
    }
    // Using the same process again but for a different mode value
    else{
        if(size<0){
            int sizeMag = size*-1;
            for (int i=row; i<(row+sizeMag); i++){
                if(road[i][col]!=SPACE){
                    return 0;
                }
            }
            return 1;
        }
        else{
            for(int i=col; i<(col+size); i++){
                if(road[row][i]!=SPACE){
                    return 0;
                }
            }
            return 1;
        }        
    }    
}
    

void AddCar(int road[NUM_ROWS][NUM_COLS], int row, int col, int size){
    
    int search = 65;
    int foundCar = 0;
    
    for(int i=search; i<91; i++){
        foundCar = Helper_IsCarPresent(road, (char)i);
        if(foundCar==1){
            search++;
        }    
    }

    int empty = Helper_IsRoadEmpty(road, row, col, size);
    if(empty == 1){
        if(size<0){
            int sizeMag = size*-1;
            for(int i=row; i<(row+sizeMag); i++){
                road[i][col] = (char)search;
            }
        } else{
            for(int i=col; i<(col+size); i++){
                road[row][i] = (char)search;
            }
        }
    }       
}


void FindCar(int road[NUM_ROWS][NUM_COLS], char move, int *rowStart, int *colStart, int *rowEnd, int *colEnd){
    int foundCar = 0;
    for(int i=0; i<NUM_ROWS; i++){
        for(int j=0; j<NUM_COLS; j++){
            if(foundCar==0){
                if(road[i][j]==move){
                    foundCar = 1;
                    *rowStart = i;
                    *colStart = j;
                }    
            }
        }
    }
    
    int rowLength = 0;
    int colLength = 0;
    
    for(int i=*rowStart; i<NUM_ROWS; i++){
        if(road[i][*colStart]==move){
            rowLength++;
        }
    }
    for(int i=*colStart; i<NUM_COLS; i++){
        if(road[*rowStart][i]==move){
            colLength++;
        }
    }
    
    *rowEnd = *rowStart+rowLength-1;
    *colEnd = *colStart+colLength-1;
}   


int Helper_FindMove(int road[NUM_ROWS][NUM_COLS], int end1, int end2, int fix, char orientation){

    int isSpace = 0;
    int stopper = 0;
    int horzSpace = 0;
    int vertSpace = 0;

    if(orientation=='H'){
        if(road[fix][end1-1]==(char)32){
            isSpace = 1;
        } else if(road[fix][end2+1]==(char)32){
            isSpace = -1;
        } else{
            return 0;
        }

        if(isSpace==1){
            for(int i=end1-1; i>0; i--){
                if(stopper==0){
                    if(road[fix][i]==(char)32){
                        horzSpace++;
                    }else{
                        stopper = 1;
                    }
                }
            }

        } else if(isSpace==-1){
            for(int i=end2+1; i<NUM_COLS; i++){
                if(stopper==0){
                    if(road[fix][i]==(char)32){
                        horzSpace--;
                    }else{
                        stopper = 1;
                    }
                }
            }
        }

        return horzSpace;
    } 


    else{
        if(road[end1-1][fix]==(char)32){
            isSpace = 1;
        } else if(road[end2+1][fix]==(char)32){
            isSpace = -1;
        } else{
            return 0;
        }

        if(isSpace==1){
            for(int i=end1-1; i>0; i--){
                if(stopper==0){
                    if(road[i][fix]==(char)32){
                        vertSpace++;
                    }else{
                        stopper = 1;
                    }
                }
            }
        } else if(isSpace==-1){
            for(int i=end2+1; i<NUM_ROWS; i++){
                if(stopper==0){
                    if(road[i][fix]==(char)32){
                        vertSpace--;
                    }else{
                        stopper = 1;
                    }
                }
            }
        }

        return vertSpace;
    }
} 


int MoveCar(int road[NUM_ROWS][NUM_COLS], int r0, int c0, int r1, int c1){
    
    char currentCar = road[r0][c0];
    char orientation;
    int findMoveResult = 0;
    int move = 0;
    char moveDirection = 'e';


    if(r0==r1){
        orientation = 'H';
        findMoveResult = Helper_FindMove(road, c0, c1, r0, 'H');
        if(findMoveResult>0){
            move = findMoveResult;
            moveDirection = 'L';
        } else if(findMoveResult<0){
            move = findMoveResult*-1;
            moveDirection = 'R';
        } else{
            return 0;
        }
    } 

    else{
        orientation = 'V';
        findMoveResult = Helper_FindMove(road, r0, r1, c0, 'V');
        if(findMoveResult>0){
            move = findMoveResult;
            moveDirection = 'U';
        } else if(findMoveResult<0){
            move = findMoveResult*-1;
            moveDirection = 'D';
        } else{
            return 0;
        }
    }
    
    if(moveDirection == 'U'){
        for(int i=r0; i<r1+1; i++){
            road[i-move][c0] = road[i][c0];
            road[i][c0] = 0;
        }
    } else if(moveDirection == 'D'){
        for(int i=r1; i>r0-1; i--){
            road[i+move][c0] = road[i][c0];
            road[i][c0] = 0;
        }
    } else if(moveDirection == 'L'){
        for(int i=c0; i<c1+1; i++){
            road[r0][i-move] = road[r0][i];
            road[r0][i] = 0;
        }
    } else if(moveDirection == 'R'){
        for(int i=c1; i>c0-1; i--){
            road[r0][i+move] = road[r0][i];
            road[r0][i] = 0;
        }
    }

    int gameEnd = 0;
    int xPosO = 0;
    int yPosO = 0;
    for(int i=0; i<NUM_ROWS; i++){
        for(int j=0; j<NUM_COLS; j++){
            if(road[i][j]=='O'){
                xPosO = i;
                yPosO = j;
            }
        }
    }
    
    if(xPosO==0){
        if(road[1][yPosO]==currentCar && road[2][yPosO]==currentCar){
            gameEnd = 1;
        }
    }else if(xPosO==NUM_ROWS-1){
        if(road[NUM_ROWS-2][yPosO]==currentCar && road[NUM_ROWS-3][yPosO]==currentCar){
            gameEnd = 1;
        }
    }else if(yPosO == 0){
        if(road[xPosO][1]==currentCar && road[xPosO][2]==currentCar){
            gameEnd = 1;
        }
    }else if(yPosO == NUM_COLS-1){
        if(road[xPosO][NUM_COLS-2]==currentCar && road[xPosO][NUM_COLS-3]){
            gameEnd = 1;
        }
    }

    return gameEnd;
}



/***********************************************************/
/***********************************************************/
/********* DO NOT MODIFY ANY CODE BELOW THIS POINT *********/
/***********************************************************/
/***********************************************************/

/* Function to obtain capital letter as input */
char GetMove(void)
{
	char move;
	printf("\nMove car: ");
	scanf("%c", &move);
	// Ignore non-capital letter inputs
	while ((move < 'A') || (move > 'Z')) {
		scanf("%c", &move);
	}
	return move;
}

/* The main Traffic Jam simulation */
int main(void)
{
	int gameOver = 0;
	int road[NUM_ROWS][NUM_COLS];
	int rowStart, colStart, rowEnd, colEnd;
	char input;

	/* Print banner */
	printf(" _____           __  __ _            _                                        \n");
	printf("|_   _| __ __ _ / _|/ _(_) ___      | | __ _ _ __ ___           ____          \n");
	printf("  | || '__/ _` | |_| |_| |/ __|  _  | |/ _` | '_ ` _ \\  --   __/  |_\\_      \n");
	printf("  | || | | (_| |  _|  _| | (__  | |_| | (_| | | | | | | --- |  _     _``-.    \n");
	printf("  |_||_|  \\__,_|_| |_| |_|\\___|  \\___/ \\__,_|_| |_| |_| --  '-(_)---(_)--'\n\n");

	/* Initialise the road and add cars */
	InitialiseRoad(road, 'N', 4);
	//PrintRoad(road);
	AddCar(road, 3, 3, 2);
	AddCar(road, 1, 1, 2);
	AddCar(road, 2, 1, 3);
	AddCar(road, 3, 2, -2);
	AddCar(road, 5, 2, -2);
	AddCar(road, 4, 4, -2);
	AddCar(road, 6, 3, 3);
	AddCar(road, 1, 5, -3);
	AddCar(road, 2, 6, -2);

	/* Print status */
	printf("ENGGEN131 2020 - C Project\nTraffic Jam!  There is a lot of traffic on the road!\n");
	printf("In fact, %.2f%% of the road is cars!\n\n", PercentUsed(road));

	/* Main simulation loop */
	while (!gameOver) {
		PrintRoad(road);
		input = GetMove();
		FindCar(road, input, &rowStart, &colStart, &rowEnd, &colEnd);
		gameOver = MoveCar(road, rowStart, colStart, rowEnd, colEnd);
	}

	/* A car has exited - the simulation is over */
	PrintRoad(road);
	printf("\nCongratulations, you're on your way again!");

	return 0;
}
