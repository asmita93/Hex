#include<stdio.h>
#include "HEX_STR.C"
#define MIDDLE 1
#define LEFT 2
#define RIGHT 3
int main(void)
{
    unsigned short int hex_point,hex_field , middle = FALSE;
    int i,j,bit_ind=0,k,bit_alone=0; //bit_alone help us to indicate that no field is visited  eventually tell us that it is alone node i.e no neigbhouring node is marked or visited
                                    //bit_ind help us to indicate that for which field we need to update all the weight of corresponding field

    printf("\n enter yours move:");
    scanf("%hd",&hex_point);

    if(hex_point%10 == hex_point/10)
    {
        middle = TRUE;
    }
    else if(hex/10 < 4)
    {
        middle = LEFT;
    }
    else
        middle = RIGHT;

    while(1)
    {

    for( i=0;i<6 && hex_board[hex_point/10][hex_point%10].field[i] !=71;i++ )
    {
        bit_ind =   0;
        hex_field = hex_board[hex_point/10][hex_point%10].field[i];
        printf("hex_field:%d\n",hex_field);

        for(j=0;j<6;j++)
        {
            if(hex_board[hex_field/10][hex_field%10].weight[j] ==  0 || hex_board[hex_field/10][hex_field%10].weight[j] ==  2)
            {
                bit_ind     =   1;
                bit_alone   =   1;
                printf("inner");
                break;
            }
        }

        if(bit_ind)
        {
                for(j=0;j<6;j++)
                {
                    if(hex_board[hex_field/10][hex_field%10].field[j]   ==  hex_board[hex_point/10][hex_point%10].name )
                    {
                        if(hex_board[hex_field/10][hex_field%10].field[j]!=71)
                        {
                            hex_board[hex_field/10][hex_field%10].weight[j] =   0;
                            printf("--->%d\n",hex_board[hex_field/10][hex_field%10].field[j]);
                            //break;

                        }
                    }

                }
               if( hex_board[hex_point/10][hex_point%10].weight[i] !=   -1)
                    hex_board[hex_point/10][hex_point%10].weight[i] =   0;

        }



    }
    if(bit_alone  ==  0)
        {
              hex_board[hex_point/10][hex_point%10].weight[0] =   2;

        }


    for(i=0;i<7;i++)
    {
        for(j=0;j<7;j++)
        {
            printf("{%d,{",hex_board[i][j].name);

            for(k=0;k<6;k++)
            {
                printf("%d,",hex_board[i][j].field[k]);
            }
            printf("},{");

            for(k=0;k<6;k++)
            {
                printf("%d,",hex_board[i][j].weight[k]);
            }
            printf("}\n");
        }
        printf("\n");
    }



    printf("\n enter yours move:");
    scanf("%hd",&hex_point);



    }
}
