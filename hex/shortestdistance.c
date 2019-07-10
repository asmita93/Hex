#include<stdio.h>
#include "bfs.c"

void short_dist_hex(hex_board_structure *endvertex[])
{
    hex_board_structure *srcvertex[7]   =   {NULL};//store all the endpoint from which we extract the hex which is having minimum distance

    bfsleafnode(srcvertex,&zeroth_left,NULL);

    int i=0,j=0,min=32767,min_index=0;
    hex_board_structure *shortest_vertex[7] =   {NULL};//this gives us hex which have minimum distance from srcvertex to boundary side hex

    for(i=0;i<7 && srcvertex[i]!=NULL;i++)
    {
        printf("\n\n--------------\n");

        printf("\nendpoint:%d:hexboard[%d][%d],distance:%d",i,srcvertex[i]->name/10,srcvertex[i]->name%10,srcvertex[i]->visited);

        j=bfsleafnode(NULL,&zeroth_left,srcvertex[i]);

        if(min>j)
        {
            min =   j;
            endvertex[min_index++]      = srcvertex[i];
        }
        else if(min == j)
        {

            endvertex[min_index++]    = srcvertex[i];
        }
    }


}



