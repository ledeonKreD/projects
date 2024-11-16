#include <stdio.h>
#include <unistd.h>

#define SIZE_ROW 40
#define SIZE_COL 80
#define	LIVE '#' 
#define DEAD ' '

//Cursor movement
#define LEFT	'h'
#define UP	'j'
#define DOWN	'k'
#define RIGHT	'l'
#define CURSOR 'O'

//TODO:
//fix and refactor
//implement choices for tickspeed and variable size
//Cursor works, make prettier

long int tickspeed = 100;

//main Field, comparisons are done
char Field[SIZE_ROW][SIZE_COL];

//auxillary Field, 2nd generation gets set there
char Field_new[SIZE_ROW][SIZE_COL];
//print the contents of the Field as char
void printField(char Array[SIZE_ROW][SIZE_COL])
{
	for( int col = 0; col < SIZE_COL + 2; ++col )
	{
		printf("-");
	};
	printf("\n");

	for( int row = 0; row < SIZE_ROW; ++row )
	{
		printf("|");
		for( int col= 0; col < SIZE_COL; ++col )
		{
			printf("%c", Array[row][col]);
		}
		printf("|");
		printf("%c", '\n');
	};

	for( int col = 0; col < SIZE_COL + 2; ++col )
	{
		printf("-");
	};
	printf("\n");

}

//set the state of a cell
void setCell(char state, int row, int col)
{
	Field[row][col] = state;
}

//check a cell for neighbors;
//scans the whole 3x3 area and enumerates live cells
//if the checked cell is live, subtract 1 as to not count itself
int checkNeighbor(int row, int col)
{
	int neighbors = 0;

	for( int  rel_row = -1; rel_row < 2; ++rel_row )
	{
		for ( int rel_col = -1; rel_col < 2; ++rel_col )
		{
			if( Field[row + rel_row][col + rel_col] == LIVE )
			{
				neighbors++;
			}
		}
	}

	if( Field[row][col] == LIVE )
	{
		return neighbors - 1;
	}
	else
	{
		return neighbors;
	}
}

//return contents of a cell
char checkCell(int row, int col)
{
	return Field[row][col];
}

//interrupt loop until key input is given
void step()
{
	getchar();
}

void cursor()
{
	int user_in = 0;
	unsigned int cursor_pos[2] = {0, 0}; 
	unsigned int cursor_pos_prev[2] = {0, 0}; 

	while( (user_in = getchar()) != 'q' )
	{		
		cursor_pos_prev[0] = cursor_pos[0];
		cursor_pos_prev[1] = cursor_pos[1];

		switch( user_in )
		{
			
			case LEFT:
				cursor_pos[1] -= 1;
				break;
			case UP:
				cursor_pos[0] -= 1;
				break;
			case DOWN:
				cursor_pos[0] += 1;
				break;
			case RIGHT:
				cursor_pos[1] += 1;
				break;
			case 's':
				setCell(LIVE, cursor_pos[1], cursor_pos[0]);
				break;

		}

		char cell_old = checkCell(cursor_pos[1], cursor_pos[0]);
		Field[cursor_pos[1]][cursor_pos[0]] = CURSOR;
		printField(Field);
		Field[cursor_pos[1]][cursor_pos[0]] = cell_old;
	}
}

//place Glider (shape that moves across the field)
void setGlider()
{
	setCell(LIVE, 5, 5);
	setCell(LIVE, 6, 6);
	setCell(LIVE, 6, 7);
	setCell(LIVE, 5, 7);
	setCell(LIVE, 4, 7);
}

//place "Blinker" (1x3 row)
void setBlinker()
{
	setCell(LIVE, 3, 3);
	setCell(LIVE, 3, 4);
	setCell(LIVE, 3, 5);
}

int main()
{
	//populate Field
	for( int row = 0; row < SIZE_ROW; ++row )
	{
		for( int col = 0; col < SIZE_COL; ++col )
		{
			Field[row][col] = DEAD;
			//initial auxillary field has to be dead
			Field_new[row][col] = DEAD;
		}
	};

	setGlider();

	//main loop, check cells and apply rules
	for(;;)
	{
		printField(Field);
		for( int row = 0; row < SIZE_ROW; ++row )
		{
			for( int col = 0; col < SIZE_COL; ++col )
			{
				if( checkCell(row, col) == LIVE )
				{
					int neighbors;
					neighbors = checkNeighbor(row, col);

					//1st Rule: Live cell dies with <2 live neighbors
					if( neighbors < 2 )
					{
						Field_new[row][col] = DEAD;
					}
                    //2nd Rule: Live cell stays alive with 2-3 live neighbors
					else if( neighbors == 2 || neighbors == 3 )
					{
						Field_new[row][col] = LIVE;
					}
                    //3rd Rule: Live cell dies with more >3 neighbors
					else if( neighbors > 3 )
					{
						Field_new[row][col] = DEAD;
					}
                    //4th Rule: Dead cell comes to live with exactly 3 live neighbors
					else if( checkNeighbor(row, col) == 3 )
					{
						Field_new[row][col] = LIVE;
                    }
				}
			}
		}

		//copy newly set field back to primary field
		for( int row = 0; row < SIZE_ROW; ++row )
		{
			for( int col = 0; col < SIZE_COL; ++col )
			{
				Field[row][col] = Field_new[row][col];
			}
		};
		usleep(tickspeed * 1000);
		//cursor();
	}

	return 0;
}
