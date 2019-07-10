#include    <stdio.h>
#include    "shortestdistance.c"

#define INFINITE    0
#define WHITE      -1
#define GREY        0
#define BLACK       1
#define true        1
#define false       0

typedef struct
{
    int name;
    unsigned short int mark;
}visited_hex;

void intialize_graph_endpt()      //initializing the graph in which initially the vertex having the color=white and visited i.e distance label=infinity
{
    int i,j;

    for(i=0;i<7;i++)
    {
         for(j=0;j<7;j++)
        {
                hex_board[i][j].color   =   WHITE;      //intializing the color of vertex to white
                hex_board[i][j].visited =   INFINITE;   //intializing the label of vertex to infinite
        }
    }
}

hex_board_structure *adjacent_endpt(hex_board_structure *vertex,int i)    //return the adjacent vertices
{
    if(i<=5)            //there can be at most 6 adjacent vertices so this condition put here
    {
        if(vertex->field[i]<67 && vertex->field[i]>=0 && vertex->weight[i]==0) //we r looking at the each field by running through the fields attribute
        {
            return &(hex_board[(int)(vertex->field[i]/10)][(int)(vertex->field[i]%10)]); //gives hex coordinate by dividing, quoteint will give x-coordinate and remainder will give y-coordinate
        }
    }
    return NULL;    //if it returns NULL then either we have traverse all adjacent vertices or no adjacent vertices

}



int bfs_endpt(zeroth_node *zeroth,visited_hex *visited_hex)  //bfs applying on given graph g and starting vertex in zeroth_node which we get from step-2 of main algorithm
{
    hex_board_structure *head_vertex, *adjacent_vertex;

    int i=1;    //i is used for counting the adjacent vertex
    int max=0;

    int init_q; //init_q = initializing queue with all the vertices which are attached to zeroth node

    intialize_graph_endpt();                         //initializing a graph


        for(init_q=0;init_q<7;init_q++)
        {
            if((zeroth->adjacent[init_q])!=0)
            {
                    enqueue((zeroth->point_to[init_q]));           //enqueue the vertices which are attached to zeroth node
                    (zeroth->point_to[init_q])->color   =   GREY;   //making all the vertices grey
                    (zeroth->point_to[init_q])->visited =   1   ;   //labeling each vertex with the visited distance 1
            }
        }

    while(front !=  -1)  //run the loop till the queue is empty
    {
        i=0;
        head_vertex =   queue[front];
        //printf("\nhead_vertex:[%d][%d]",head_vertex.name/10,head_vertex.name%10);
        //adjacent_vertex = adjacent(&head_vertex,i++);
        //printf("\nadjacent_vertex:[%d][%d]",adjacent_vertex->name/10,adjacent_vertex->name%10);
        while(i<6)
        {
            adjacent_vertex    =   adjacent_endpt(head_vertex,i++);
            if(adjacent_vertex)
            {
                if(adjacent_vertex->color == WHITE)
                {
                    adjacent_vertex->color      =   GREY;
                    adjacent_vertex->visited    =   (head_vertex->visited) + 1;
                    enqueue(adjacent_vertex);
                    //printf("\nqueue:[%d][%d]",(queue[rear].name)/10,(queue[rear].name)%10);
                }
            }
        }
        head_vertex->color  =   BLACK;
        max=head_vertex->visited;

        printf("\nbfs:%d",head_vertex->name);
        if(head_vertex->name/10 == 0 || head_vertex->name%10 == 0 )
        {
            visited_hex[head_vertex->name].name = head_vertex->name;
        }
        visited_hex[head_vertex->name].mark = 1;
        printf(":visted:%d : %d",visited_hex[head_vertex->name].name,head_vertex->visited);
        dequeue();
    }

}
int find_continous(void)
{

    visited_hex visited_hex[66]={0,0};
    int i,j,k;
    for(i=0;i<7;i++)
    {
        for(j=0;j<7;j++)
        {
            for(k=0;k<6;k++)
            {
                if(hex_board[i][j].weight[k] == 0)
                {
                    visited_hex[hex_board[i][j].field[k]].name = hex_board[i][j].field[k];
                    printf("\nvisited_hex:%d",visited_hex[hex_board[i][j].field[k]].name);
                }
                 if(hex_board[i][j].weight[k]    ==  2)
                 {
                        visited_hex[hex_board[i][j].name].name  =   hex_board[i][j].name;
                        printf("\nvisited_hex:%d",visited_hex[hex_board[i][j].name].name);

                }
               // printf("visited_hex[%d][%d]:%d",visited_hex[hex_board[i][j].name].name/10,visited_hex[hex_board[i][j].name].name%10,visited_hex[hex_board[i][j]].mark);
            }
        }
    }

    printf("\nbfs visited:\n");
    bfs_endpt(&zeroth_left,visited_hex);

     printf("\nhex visited by both traversal:");
    for(i=0;i<66;i++)
    {
        if(visited_hex[i].mark == 1)
        {
           printf("\nhex[%d][%d]",visited_hex[i].name/10,visited_hex[i].name%10);
        }
        else if(visited_hex[i].mark == 0 && visited_hex[i].name != 0)
        {

            printf("\nhex[%d][%d] not visited",visited_hex[i].name/10,visited_hex[i].name%10);
            printf("\ndiscontinous");
            return false;
        }
    }
    return true;
}



