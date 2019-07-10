#include<stdio.h>
#include "bfs_for_endpt.c"

#define NULL_HEX_POINT 999
int main()  //this fn will accept the visited hex and current node which is currently marked
{
    hex_board_structure *endvertex[7] = {NULL};
    int i,endpoint = NULL_HEX_POINT,count=0,min=3276,j,q;
    if(find_continous())
    {
        short_dist_hex(endvertex);

         printf("\nvertex with shortest distance");
        for(i=0; endvertex[i]!=NULL;i++)
        {
            printf("\nhex[%d][%d]",endvertex[i]->name/10,endvertex[i]->name%10);
        }

        if(i==1)
        {
            endpoint = endvertex[0]->name;
        }
        else if(i > 1 )
        {
            for(i=0;endvertex[i]!=NULL;i++)
            {
                    for(j=0;j<6;j++)
                    {
                        if(hex_board[endvertex[i]->name/10][endvertex[i]->name%10].field[j]    ==   1)
                        {
                            count++;
                        }
                    }
                    if(min > count)
                    {
                        min =   count;
                        endpoint    =   endvertex[i]->name;
                    }
            }
        }
        printf("%d",endpoint);
    return endpoint;
        }
    return 0;
}

