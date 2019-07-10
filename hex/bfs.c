#include    <stdio.h>
#include    "queue.c"


#define INFINITE    0
#define WHITE      -1
#define GREY        0
#define BLACK       1


void intialize_graph()      //initializing the graph in which initially the vertex having the color=white and visited i.e distance label=infinity
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

hex_board_structure *adjacent(hex_board_structure *vertex,int i,int bit)    //return the adjacent vertices
/***********************************************************************
*bit field indicating whether it is zeorth_node(0) or start_node(1)    *
*if(bit == 0)                                                          *
*    then its a zeroth node and we r searching a hex which is marked   *
*if(bit == 1)                                                          *
*    then its hex_node and we  r searching a hex which can be marked   *
************************************************************************/
{
    if(i<=5)            //there can be at most 6 adjacent vertices so this condition put here
    {
        if(vertex->field[i]<67 && vertex->field[i]>=0 && vertex->weight[i]==bit) //we r looking at the each field by running through the fields attribute
        {
            return &(hex_board[(int)(vertex->field[i]/10)][(int)(vertex->field[i]%10)]); //gives hex coordinate by dividing, quoteint will give x-coordinate and remainder will give y-coordinate
        }
    }
    return NULL;    //if it returns NULL then either we have traverse all adjacent vertices or no adjacent vertices

}

/***************************************************************************************************
*    bfs gives the max level which means its a leaf node in bfs tree                               *
*    if bfs accept zeroth                                                                          *
*        then it means we are applying a bfs from zeroth_node to search a node which are marked    *
*   if bfs accept start_node                                                                       *
*       then it means we are applying bfs from start_node which is hex_node and which can be marked*
****************************************************************************************************/


int bfs(zeroth_node *zeroth,hex_board_structure *start_node)  //bfs applying on given graph g and starting vertex in zeroth_node which we get from step-2 of main algorithm
{
    hex_board_structure *head_vertex, *adjacent_vertex;

    int i=1;    //i is used for counting the adjacent vertex
    int max=0;
    int bit=0;

    int init_q; //init_q = initializing queue with all the vertices which are attached to zeroth node

    intialize_graph();                         //initializing a graph

    if(zeroth!=NULL)
    {
        bit=0;
        for(init_q=0;init_q<7;init_q++)
        {
            if((zeroth->adjacent[init_q])!=0)
            {
                    enqueue((zeroth->point_to[init_q]));           //enqueue the vertices which are attached to zeroth node
                    (zeroth->point_to[init_q])->color   =   GREY;   //making all the vertices grey
                    (zeroth->point_to[init_q])->visited =   1   ;   //labeling each vertex with the visited distance 1
                   // printf("\n---->%d : %d",(zeroth->point_to[init_q]->name),(zeroth->point_to[init_q]->visited));
            }
        }
    }
    if(start_node!=NULL)
    {
        enqueue(start_node);
        bit=1;
    }

    while(front !=  -1)  //run the loop till the queue is empty
    {
        i=0;
        head_vertex =   queue[front];
        //printf("\nhead_vertex:[%d][%d]:%d",head_vertex->name/10,head_vertex->name%10,head_vertex->visited);
        //adjacent_vertex = adjacent(&head_vertex,i++);
        //printf("\nadjacent_vertex:[%d][%d]",adjacent_vertex->name/10,adjacent_vertex->name%10);
        while(i<6)
        {
            //printf("\n-->head:%d",head_vertex->name);
            adjacent_vertex    =   adjacent(head_vertex,i++,bit);
            if(adjacent_vertex)
            {
               // printf("\nadjacent:%d",adjacent_vertex->name);
                if(adjacent_vertex->color == WHITE)
                {

                    adjacent_vertex->color      =   GREY;
                    adjacent_vertex->visited    =   (head_vertex->visited) + 1;
                    enqueue(adjacent_vertex);
                    //printf("\nqueue:[%d][%d]",(queue[rear]->name)/10,(queue[rear]->name)%10);
                }
            }
        }
        head_vertex->color  =   BLACK;
        max=head_vertex->visited;
        //printf("\n--->%d:%d",head_vertex->name,head_vertex->visited);
        dequeue();
    }

    return max;

}

/*****************************************************************************************************************************
*Below function will give us leaf node as well as minimum distance from srcvertex.                                           *
* srcvertex accpet an array which will filled by all leaf nodes of bfs tree                                                  *
*                                                                                                                            *
* if bfsleafnode accepts zeroth_start_node                                                                                   *
*    then it means that we are applying bfs on zeroth node so that we can get all leaves                                     *
*                                                                                                                            *
* if bfsleafnode accepts both zeroth_start_node and start_node                                                               *
*  ---then zeroth_start_node tells us that which boundary side we need to search                                             *
*  ------if zeroth_start_node == zeroth_left                                                                                 *
*  ----------then it means we need to take care right boundary side                                                          *
*  ------if zeroth_start_node == zeroth_right                                                                                *
*  ----------then it means we need to take care left boundary side                                                           *
* ---and start_node is leaf node which is source node from where we start our search for minimum distance                    *
*                                                                                                                            *
*****************************************************************************************************************************/



//this function gives us a leafnodes in bfs tree which will gives us src vertex to find a node having minimum distance
int bfsleafnode(hex_board_structure *srcvertex[],zeroth_node *zeroth_start_node,hex_board_structure *start_node)
{
    int max; //it gives maximum visited node which let me find the last node. hence,gives endpoint
    int i=0,j=0,src=0;
    if(zeroth_start_node && start_node==NULL)
    {
        max =   bfs(zeroth_start_node,NULL);//passing zeroth_start_node which tell us that we need to apply bfs on zeroth_start_node
        //returns a maximum value by bfs algo..
        //this would help me to determine  which are the hex which are at the leaves of bfs tree
        //this is executed when when we apply bfs from zeroth_node

        for(i=0;i<7;i++)
        {
            for(j=0;j<7;j++)
            {
                if(hex_board[i][j].visited == max )//we traversing all the vertices and determining which all vertices secured a maximum level number
                {

                    srcvertex[src++] = &(hex_board[i][j]); //storing all the leaf vertices(hex) in the array srcvertex[]
                    //printf("\nhex[%d][%d]",srcvertex[src-1]->name/10,srcvertex[src-1]->name%10);
                }
            }
        }
    }

    if(start_node) //this tell us that we need to apply bfs in hex so that we can get minimum distance from start_node to opposite boundary side hex
    {
        bfs(NULL,start_node);
        int min;
        if((zeroth_start_node==(&zeroth_left)))//tells us which side boundary we need  to care..here we need to take care right hand side boundary
        {
            min=hex_board[0][6].visited;
            for(i=0;i<7;i++)
            {
                if(min>hex_board[i][6].visited)
                {
                    min = hex_board[i][6].visited;
                }
            }
        }
        if((zeroth_start_node == (&zeroth_right)))//tell us  that we need to take care left hand side boundary..
        {
            min = hex_board[0][0].visited;
            for(i=0;i<7;i++)
            {
                if(min > hex_board[i][0].visited)
                {
                    min = hex_board[i][0].visited;
                }
            }
        }
        return min;
    }
}



