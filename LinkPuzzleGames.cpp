#include <iostream>
#include <ctime>
#include <windows.h>
#include "conio_yp.h"
#include <cmath>
#include <limits>

using namespace std;

int counter = 23;

enum DIRECTION
{
    NORTH = 0,
    EAST,
    SOUTH,
    WEST,
    NONE,
    TOTAL_DIRECTION
};

enum GRID_TYPE
{
    SOURCE = 0,
    TARGET,
    EMPTY,
    STRAIGHT_VERTICAL,
    STRAIGHT_HORIZONTAL,
    LSHAPE_0_DEGREE,
    LSHAPE_90_DEGREE,
    LSHAPE_180_DEGREE,
    LSHAPE_270_DEGREE,
    TSHAPE_0_DEGREE,
    TSHAPE_90_DEGREE,
    TSHAPE_180_DEGREE,
    TSHAPE_270_DEGREE,
    TOTAL_TYPE
};

struct Node
{
    GRID_TYPE type;
    char **sprite;
    int color;
    int colorOriginal;

    Node* northNode;
    Node* southNode;
    Node* eastNode;
    Node* westNode;

    bool isNorthNodeConnectable;
    bool isSouthNodeConnectable;
    bool isEastNodeConnectable;
    bool isWestNodeConnectable;

    void Initialize(GRID_TYPE type);
    void SetType(GRID_TYPE type);
    void CopySprite(char tempSprite[][3]);
};

//! initialize the 2 D Array
void Node::Initialize(GRID_TYPE type)
{
	for(int i=0; i<3; i++)
	{
		sprite = new char*[3]; //charsprite is 2D Array
		for(int j=0; j<3; j++)
		{
			sprite[j] = new char[3];
		}
	}
	
	SetType(type);
	
	colorOriginal = color;
}

//! setType to design the grid type layout
void Node::SetType(GRID_TYPE type)
{
	this->type = type;
	
	northNode = NULL; //always set node to NULL
	southNode = NULL;
	eastNode = NULL;
	westNode = NULL;
	
	if(type == SOURCE)
	{
		color = YELLOW;
		
		isNorthNodeConnectable = true;
		isSouthNodeConnectable = true;
		isEastNodeConnectable = true;
		isWestNodeConnectable = true;
		
		char tempSprite[3][3] = 
		{
			{'#', '#', '#'},
			{'#', '#', '#'},
			{'#', '#', '#'}
		};
		CopySprite(tempSprite);
	}
	else if(type == TARGET)
	{
		color = BLUE;
		
		isNorthNodeConnectable = true;
		isSouthNodeConnectable = true;
		isEastNodeConnectable = true;
		isWestNodeConnectable = true;
		
		char tempSprite[3][3] = 
		{
			{'#', '#', '#'},
			{'#', '#', '#'},
			{'#', '#', '#'}
		};
		CopySprite(tempSprite);
	}
	else if(type == EMPTY)
	{
		color = RED;
		
		isNorthNodeConnectable = false;
		isSouthNodeConnectable = false;
		isEastNodeConnectable = false;
		isWestNodeConnectable = false;
		
		char tempSprite[3][3] = 
		{
			{' ', ' ', ' '},
			{' ', ' ', ' '},
			{' ', ' ', ' '}
		};
		CopySprite(tempSprite);
	}
	else if(type == STRAIGHT_VERTICAL)
	{
		color = GREEN;
		
		isNorthNodeConnectable = true;
		isSouthNodeConnectable = true;
		isEastNodeConnectable = false;
		isWestNodeConnectable = false;
		
		char tempSprite[3][3] = 
		{
			{' ', '#', ' '},
			{' ', '#', ' '},
			{' ', '#', ' '}
		};
		CopySprite(tempSprite);
	}
	else if(type == STRAIGHT_HORIZONTAL)
	{
		color = CYAN;
		
		isNorthNodeConnectable = false;
		isSouthNodeConnectable = false;
		isEastNodeConnectable = true;
		isWestNodeConnectable = true;
		
		char tempSprite[3][3] = 
		{
			{' ', ' ', ' '},
			{'#', '#', '#'},
			{' ', ' ', ' '}
		};
		CopySprite(tempSprite);
	}
	else if(type == LSHAPE_0_DEGREE)//
	{
		color = MAGENTA;
		
		isNorthNodeConnectable = true;
		isSouthNodeConnectable = false;
		isEastNodeConnectable = true;
		isWestNodeConnectable = false;
		
		char tempSprite[3][3] = 
		{
			{' ', '#', ' '},
			{' ', '#', '#'},
			{' ', ' ', ' '}
		};
		CopySprite(tempSprite);
	}
	else if(type == LSHAPE_90_DEGREE)//
	{
		color = MAGENTA;
		
		isNorthNodeConnectable = false;
		isSouthNodeConnectable = true;
		isEastNodeConnectable = true;
		isWestNodeConnectable = false;
		
		char tempSprite[3][3] = 
		{
			{' ', ' ', ' '},
			{' ', '#', '#'},
			{' ', '#', ' '}
		};
		CopySprite(tempSprite);
	}
	else if(type == LSHAPE_180_DEGREE)//
	{
		color = MAGENTA;
		
		isNorthNodeConnectable = false;
		isSouthNodeConnectable = true;
		isEastNodeConnectable = false;
		isWestNodeConnectable = true;
		
		char tempSprite[3][3] = 
		{
			{' ', ' ', ' '},
			{'#', '#', ' '},
			{' ', '#', ' '}
		};
		CopySprite(tempSprite);
	}
	else if(type == LSHAPE_270_DEGREE)//
	{
		color = MAGENTA;
		
		isNorthNodeConnectable = true;
		isSouthNodeConnectable = false;
		isEastNodeConnectable = false;
		isWestNodeConnectable = true;
		
		char tempSprite[3][3] = 
		{
			{' ', '#', ' '},
			{'#', '#', ' '},
			{' ', ' ', ' '}
		};
		CopySprite(tempSprite);
	}
	else if(type == TSHAPE_0_DEGREE)//
	{
		color = LIGHTBLUE;
		
		isNorthNodeConnectable = false;
		isSouthNodeConnectable = true;
		isEastNodeConnectable = true;
		isWestNodeConnectable = true;
		
		char tempSprite[3][3] = 
		{
			{' ', ' ', ' '},
			{'#', '#', '#'},
			{' ', '#', ' '}
		};
		CopySprite(tempSprite);
	}
	else if(type == TSHAPE_90_DEGREE)//
	{
		color = LIGHTBLUE;
		
		isNorthNodeConnectable = true;
		isSouthNodeConnectable = true;
		isEastNodeConnectable = false;
		isWestNodeConnectable = true;
		
		char tempSprite[3][3] = 
		{
			{' ', '#', ' '},
			{'#', '#', ' '},
			{' ', '#', ' '}
		};
		CopySprite(tempSprite);
	}
	else if(type == TSHAPE_180_DEGREE)//
	{
		color = LIGHTBLUE;
		
		isNorthNodeConnectable = true;
		isSouthNodeConnectable = false;
		isEastNodeConnectable = true;
		isWestNodeConnectable = true;
		
		char tempSprite[3][3] = 
		{
			{' ', '#', ' '},
			{'#', '#', '#'},
			{' ', ' ', ' '}
		};
		CopySprite(tempSprite);
	}
	else if(type == TSHAPE_270_DEGREE)//
	{
		color = LIGHTBLUE;
		
		isNorthNodeConnectable = true;
		isSouthNodeConnectable = true;
		isEastNodeConnectable = true;
		isWestNodeConnectable = false;
		
		char tempSprite[3][3] = 
		{
			{' ', '#', ' '},
			{' ', '#', '#'},
			{' ', '#', ' '}
		};
		CopySprite(tempSprite);
	}
}

void Node::CopySprite(char tempSprite[][3])
{
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            sprite[i][j] = tempSprite[i][j];
        }
    }
}
//! map
Node** gridNode;
int totalRow = 0;
int totalCol = 0;
int sourceRow = 0;
int sourceCol = 0;
bool isSolved = false;

void MarkLink(Node* node, DIRECTION direction)
{
	node->color = YELLOW;
	
	//!north node
	if(node->northNode != NULL && direction != NORTH)
	{
		MarkLink(node->northNode, SOUTH);
	}
	//south node
	if(node->southNode != NULL && direction !=SOUTH)
	{
		MarkLink(node->southNode, NORTH);
	}
	//east node
	if(node->eastNode != NULL && direction != EAST)
	{
		MarkLink(node->eastNode, WEST); 
	}
	if(node->westNode != NULL && direction != WEST)
	{
		MarkLink(node->westNode, EAST);
	}
	//west node
}
void Unlink()
{
	for(int i  = 0; i < totalRow; i++)
	{
		for(int j = 0; j < totalCol; j++)
		{
			gridNode[i][j].color = gridNode[i][j].colorOriginal;
		
			gridNode[i][j].northNode = NULL;
			gridNode[i][j].southNode = NULL;
			gridNode[i][j].eastNode = NULL;
			gridNode[i][j].westNode = NULL;
		}
	}
}
//! check -> determine the all sources are connected to the target
//! make sure the connected grid all in yellow
bool ParseLink()
{
    bool isAllConnected = true;
    
    Node* currentNode = &gridNode[sourceRow][sourceCol];
    
	MarkLink(currentNode, NONE);
	
	//! check -> determine the all sources are connected to the target
	//! check if all target are in yellow
	//isAllConnected = false;//change later (maybe)
	for(int i=0; i<totalRow; i++)
    {
        for(int j=0; j<totalCol; j++)
        {
        	if(gridNode[i][j].type == TARGET)
        	{
        		if(gridNode[i][j].color != YELLOW)
        		{
        			isAllConnected = false;
    				return isAllConnected;
				}
			}
		}
	}
    return isAllConnected;
}

void ReinitializeLink()
{
	//! i = yPosition
	//! j = xPosition
	for(int i=0; i<totalRow; i++)
    {
        for(int j=0; j<totalCol; j++)
        {
            //! check north neighbour
            if(i > 0)
            {
            	if(gridNode[i][j].isNorthNodeConnectable && gridNode[i - 1][j].isSouthNodeConnectable)
            	{
            		gridNode[i][j].northNode = &gridNode[i-1][j];            		
				}
			}
			//check south neighbour
			if(i < totalRow - 1)
			{
				if(gridNode[i][j].isSouthNodeConnectable && gridNode[i + 1][j].isNorthNodeConnectable)
            	{
            		gridNode[i][j].southNode = &gridNode[i+1][j];
				}
			}
			//check east neighbour
			if(j < totalCol - 1)
			{
				if(gridNode[i][j].isEastNodeConnectable && gridNode[i][j + 1].isWestNodeConnectable)
            	{
            		gridNode[i][j].eastNode = &gridNode[i][j + 1];
				}
			}
			
			//check west neighbour
            if(j > 0)
            {
            	if(gridNode[i][j].isWestNodeConnectable && gridNode[i][j - 1].isEastNodeConnectable)
            	{
            		gridNode[i][j].westNode = &gridNode[i][j - 1];
				}
			}
        }
    }
}

//! grid level design
void InitializeGrid()
{
    totalRow = 6;
    totalCol = 9;

    GRID_TYPE tempGrid[6][9] =
    {
        {TARGET,TSHAPE_0_DEGREE,LSHAPE_270_DEGREE,EMPTY,EMPTY,EMPTY,LSHAPE_270_DEGREE,STRAIGHT_HORIZONTAL,TARGET},
        {EMPTY,EMPTY,STRAIGHT_HORIZONTAL,LSHAPE_270_DEGREE,LSHAPE_270_DEGREE,EMPTY,TSHAPE_0_DEGREE,EMPTY,EMPTY},
        {EMPTY, LSHAPE_270_DEGREE,TSHAPE_0_DEGREE,TSHAPE_0_DEGREE,TSHAPE_0_DEGREE,TSHAPE_0_DEGREE,TSHAPE_0_DEGREE,EMPTY,EMPTY},
        {TARGET,TSHAPE_0_DEGREE,LSHAPE_270_DEGREE,LSHAPE_270_DEGREE,EMPTY,LSHAPE_270_DEGREE,STRAIGHT_HORIZONTAL,LSHAPE_270_DEGREE,EMPTY},
        {EMPTY,TSHAPE_0_DEGREE,LSHAPE_270_DEGREE,STRAIGHT_HORIZONTAL,TSHAPE_0_DEGREE,LSHAPE_270_DEGREE,LSHAPE_270_DEGREE,LSHAPE_270_DEGREE,TARGET},
        {EMPTY,LSHAPE_270_DEGREE,LSHAPE_270_DEGREE,EMPTY,SOURCE,EMPTY,EMPTY,EMPTY,EMPTY}
    };

    gridNode = new Node*[totalRow];

    for(int i=0; i<totalRow; i++)
    {
        gridNode[i] = new Node[totalCol];
        for(int j=0; j<totalCol; j++)
        {
            Node tempNode;
            tempNode.Initialize(tempGrid[i][j]);
            if(tempGrid[i][j] == SOURCE)
            {
                sourceRow = i;
                sourceCol = j;
            }
            gridNode[i][j] = tempNode;
        }
    }
    ParseLink();
}

//! draw the designed level
void DrawGrid()
{
    system("CLS");

    //! top col guide
    for(int i=0; i<totalCol; i++)
    {
        textcolor(WHITE);
        gotoxy(i*4+4,3*totalRow+1+totalRow+2);
        cout<<"-----";
        textcolor(YELLOW);
        gotoxy(i*4+6,2);
        cout<<i;
    }
    //! left row guide
    for(int i=0; i<totalRow; i++)
    {
        textcolor(LIGHTCYAN);
        gotoxy(2,i*4+5);
        cout<<i;
    }
    //! draw the left border and grid
    for(int i=0; i<totalRow; i++)
    {
        for(int j=0; j<totalCol; j++)
        {
            textcolor(WHITE);
            int xPos = 2*j+3+j+1;
            int yPos = 3*i+1+i+2;
            gotoxy(xPos,yPos);
            cout<<"-------------";
            //! left boarder
            gotoxy(xPos+j,yPos+1);
            cout<<"|";
            gotoxy(xPos+j,yPos+2);
            cout<<"|";
            gotoxy(xPos+j,yPos+3);
            cout<<"|";

            //! Drawing the Grid
            textcolor(gridNode[i][j].color);
            for(int m=0; m<3; m++)
            {
                for(int n=0; n<3; n++)
                {
                    gotoxy(xPos+n+j+1,yPos+m+1);
                    cout<<gridNode[i][j].sprite[m][n];
                }
            }
        }
    }
    //! draw the right border
    for(int i=0; i<totalRow; i++)
    {
        textcolor(WHITE);
        int xPos=2*totalCol+4+totalCol;
        int yPos=3*i+1+i+2;
        gotoxy(xPos+totalCol,yPos+1);
        cout<<"|";
        gotoxy(xPos+totalCol,yPos+2);
        cout<<"|";
        gotoxy(xPos+totalCol,yPos+3);
        cout<<"|";
    }
}

void RotateGrid(int row, int col)
{
	if(gridNode[row][col].type == STRAIGHT_VERTICAL)
	{
		gridNode[row][col].type = STRAIGHT_HORIZONTAL;
	}
	else if(gridNode[row][col].type == STRAIGHT_HORIZONTAL)
	{
		gridNode[row][col].type = STRAIGHT_VERTICAL;
	}
	else if(gridNode[row][col].type == LSHAPE_0_DEGREE)
	{
		gridNode[row][col].type = LSHAPE_90_DEGREE;
	}
	else if(gridNode[row][col].type == LSHAPE_90_DEGREE)
	{
		gridNode[row][col].type = LSHAPE_180_DEGREE;
	}
	else if(gridNode[row][col].type == LSHAPE_180_DEGREE)
	{
		gridNode[row][col].type = LSHAPE_270_DEGREE;
	}
	else if(gridNode[row][col].type == LSHAPE_270_DEGREE)
	{
		gridNode[row][col].type = LSHAPE_0_DEGREE;
	}
	else if(gridNode[row][col].type == TSHAPE_0_DEGREE)
	{
		gridNode[row][col].type = TSHAPE_90_DEGREE;
	}
	else if(gridNode[row][col].type == TSHAPE_90_DEGREE)
	{
		gridNode[row][col].type = TSHAPE_180_DEGREE;
	}
	else if(gridNode[row][col].type == TSHAPE_180_DEGREE)
	{
		gridNode[row][col].type = TSHAPE_270_DEGREE;
	}
	else if(gridNode[row][col].type == TSHAPE_270_DEGREE)
	{
		gridNode[row][col].type = TSHAPE_0_DEGREE;
	}
	gridNode[row][col].SetType(gridNode[row][col].type);
}

void RotateGridMenu()
{
    int xPosRotate = -1;
    int yPosRotate = -1;
	
	if(counter <= 5)
		textcolor(LIGHTRED);
	else
		textcolor(LIGHTGREEN);
    
    gotoxy(44, 5);
	cout << "Moves Left : " << counter << endl;
	
	textcolor(YELLOW);
	
    while(yPosRotate < 0 || yPosRotate > 8)
    {
    	gotoxy(2,28);
    	cout<<"                                           ";
		gotoxy(2,28);
		cout<<"Key in COL value for rotation: ";
    	cin >> yPosRotate;
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
    }
    cin.clear();
   
    textcolor(LIGHTCYAN);
    while(xPosRotate < 0 || xPosRotate > 5)
    {
    	gotoxy(2,30);
    	cout<<"                                           ";
		gotoxy(2,30);
		cout<<"Key in ROW value for rotation: ";
    	cin >> xPosRotate;
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
    }
    cin.clear();
    RotateGrid(xPosRotate,yPosRotate);
    
    counter--;

    Unlink();
    ReinitializeLink();
    isSolved = ParseLink();
	gotoxy(2,32);
    system("PAUSE");
}

void WinningCondition()
{
	gotoxy(1,30);
	textcolor(YELLOW);
	if(!isSolved)
	{
		cout << "You lost with " << counter << " rotations left! " << endl;
	}
	else
	{
		cout << "Congratulations! You won with " << counter << " rotations left!";
		gotoxy(1,32);
		textcolor(WHITE);
		system("PAUSE");
	}
}

int main()
{
    system("mode con: cols=85 lines=38");
    InitializeGrid();
    Unlink();
    ReinitializeLink();
    isSolved = ParseLink();
    DrawGrid();
    do
    {
        RotateGridMenu();
        DrawGrid();
    }while(counter > 0 && !isSolved);
    WinningCondition();
    
    textcolor(LIGHTGREEN);
    
   
    cout << endl;
	cout << "Game OVER !!!" << endl;
	
	textcolor(WHITE);
	
    return 0;
}

//go reintialize
//markLink
//parselink

// Name : Muhamad Luqman bin Shamsuddin
// Student ID : 0114642
