/*THIS PROGRAM IS FOR THE STRUCTURE OF HEX BOARD*/
#include<stdio.h>

typedef struct
{
    unsigned short int          name    ;
	unsigned short int         field[6] ;        //adjacent node co-ordinates in field
	short int                  weight[6];
	short int                  visited;
	short int                  color;
}hex_board_structure;

//intializing each vertex with its adjacent vertex

//in weight 1 means requested edge or there can be edge between them
//         -1 means there will be no edge in between them,
//          0 means there is an edge between them.
static hex_board_structure hex_board[7][7]  =   {
                                                        { //initializing zeroth row
                                                            {00,{01,   10, 71, 71, 71, 71},{0,1,-1,-1,-1,-1},0},
                                                            {01,{00,   02, 11, 10, 71, 71},{0,0,0,1,-1,-1},0},
                                                            {02,{01,   11, 12, 03, 71, 71},{0,1,1,0,-1,-1},0},
                                                            {03,{02,   13, 12, 04, 71, 71},{0,1,1,0,-1,-1},0},
                                                            {04,{05,   14, 13, 03, 71, 71},{1,1,1,0,-1,-1},0},
                                                            {05,{04,   14, 15, 06, 71, 71},{1,1,1,1,-1,-1},0},
                                                            {06,{05,   15, 16, 71, 71, 71},{1,1,1,1,-1,-1},0}
                                                        },
                                                        { //initializing 1st row
                                                            {10,{00,   01, 11, 20, 71, 71},{1,1,1,1,-1,-1},0},
                                                            {11,{10,   01, 02, 12, 21, 20},{1,0,1,1,1,1},0},
                                                            {12,{02,   11, 21, 22, 12, 03},{1,1,1,1,1,1},0},
                                                            {13,{03,   12, 22, 23, 14, 04},{1,1,1,1,1,1},0},
                                                            {14,{23,   24, 15, 04, 05, 13},{1,1,1,1,1,1},0},
                                                            {15,{24,   25, 16, 05, 06, 15},{1,1,1,1,1,1},0},
                                                            {16,{25,   26, 15, 06, 71, 71},{1,1,1,1,1,1},0}
                                                        },
                                                        //intializing 2nd row
                                                        {
                                                            {20,{30,   21, 11, 10, 71, 71},{1,1,1,1,-1,-1},0},
                                                            {21,{30,   31, 22, 12, 11, 20},{0,0,1,1,1,1},0},
                                                            {22,{12,   13, 23, 32, 31, 21},{1,1,1,1,1,1},0},
                                                            {23,{13,   14, 24, 33, 32, 22},{1,1,1,1,1,1},0},
                                                            {24,{14,   15, 25, 34, 33, 23},{1,1,1,1,1,1},0},
                                                            {25,{15,   16, 26, 35, 34, 24},{1,1,1,1,1,1},0},
                                                            {26,{16,   25, 35, 36, 71, 71},{1,1,1,1,-1,-1},0}
                                                        },
                                                    //intializing 3rd row
                                                        {
                                                            {30,{20,   21, 31, 40, 71, 71},{1,0,0,1,-1,-1},0},
                                                            {31,{21,   22, 32, 41, 40, 30},{0,1,1,1,1,0},0},
                                                            {32,{22,   23, 33, 42, 41, 31},{1,1,1,1,1,1},0},
                                                            {33,{23,   24, 34, 43, 42, 32},{1,1,1,1,1,1},0},
                                                            {34,{24,   25, 35, 43, 44, 33},{1,1,1,1,1,1},0},
                                                            {35,{25,   26, 36, 45, 44, 34},{1,1,1,1,1,1},0},
                                                            {36,{26,   35, 45, 46, 71, 71},{1,1,1,1,-1,-1},0}
                                                        },
                                                    //intializing 4th row
                                                        {
                                                            {40,{30,   31, 41, 50, 71, 71},{1,1,1,1,-1,-1},0},
                                                            {41,{40,   31, 32, 42, 51, 50},{1,1,1,1,1,1},0},
                                                            {42,{32,   33, 43, 52, 51, 41},{1,1,1,1,1,1},0},
                                                            {43,{33,   34, 44, 53, 52, 42},{1,1,1,1,1,1},0},
                                                            {44,{34,   35, 45, 54, 53, 43},{1,1,1,1,1,1},0},
                                                            {45,{35,   36, 46, 55, 54, 44},{1,1,1,1,1,1},0},
                                                            {46,{36,   45, 55, 56, 71, 71},{1,1,1,1,-1,-1},0}
                                                        },
                                                //intializing 5th row

                                                        {
                                                            {50,{40,   41, 51, 60, 71, 71},{1,1,1,1,-1,-1},0},
                                                            {51,{41,   42, 52, 61, 60, 50},{1,1,1,1,1,1},0},
                                                            {52,{42,   43, 53, 62, 61, 51},{1,1,0,0,0,1},0},
                                                            {53,{43,   44, 54, 63, 62, 52},{1,1,1,0,0,0},0},
                                                            {54,{44,   45, 55, 64, 63, 53},{1,1,1,1,1,1},0},
                                                            {55,{45,   46, 56, 65, 64, 54},{1,1,1,1,1,1},0},
                                                            {56,{46,   55, 65, 66, 71, 71},{1,1,1,1,-1,-1},0}
                                                        },
                                            //intializing 6th row
                                                        {
                                                            {60,{50,   51, 61, 71, 71, 71},{1,1,0,-1,-1,-1},0},
                                                            {61,{60,   51, 52, 62, 71, 71},{0,1,0,0,-1,-1},0},
                                                            {62,{61,   52, 53, 63, 71, 71},{0,0,0,0,-1,-1},0},
                                                            {63,{62,   53, 54, 64, 71, 71},{0,0,1,1,-1,-1},0},
                                                            {64,{63,   54, 55, 65, 71, 71},{1,1,1,1,-1,-1},0},
                                                            {65,{64,   55, 56, 66, 71, 71},{1,1,1,1,-1,-1},0},
                                                            {66,{65,   56, 71, 71, 71, 71},{1,1,-1,-1,-1,-1},0}
                                                        }
                                                    };


//defining a structure which gives an idea about which node(boundary nodes) in hex_board is adjacent to zeroth_node
typedef struct
{
    hex_board_structure         *point_to[7];
    unsigned short int           adjacent[7];
}zeroth_node;

//1 means there is an edge between them
//0 means there is no edge between them

zeroth_node zeroth_left     =   {{&hex_board[0][0],&hex_board[1][0],&hex_board[2][0],&hex_board[3][0],&hex_board[4][0],&hex_board[5][0],&hex_board[6][0]},{1,0,1,1,0,0,1}};
zeroth_node zeroth_right    =   {{&hex_board[0][6],&hex_board[1][6],&hex_board[2][6],&hex_board[3][6],&hex_board[4][6],&hex_board[5][6],&hex_board[6][6]},{0,0,0,0,0,0,0}};
zeroth_node zeroth_up       =   {{&hex_board[0][0],&hex_board[0][1],&hex_board[0][2],&hex_board[0][3],&hex_board[0][4],&hex_board[0][5],&hex_board[0][6]},{0,0,0,0,0,0,0}};
zeroth_node zeroth_down     =   {{&hex_board[6][0],&hex_board[6][1],&hex_board[6][2],&hex_board[6][3],&hex_board[6][4],&hex_board[6][4],&hex_board[6][6]},{0,0,0,0,0,0,0}};

/*main(void)
{
    hex_board_structure h = *(zeroth_left.point_to[1]);

    printf("%d",(zeroth_left.point_to[1])->field[1]);

}*/
