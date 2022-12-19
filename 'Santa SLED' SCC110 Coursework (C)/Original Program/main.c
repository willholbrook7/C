#include <stdio.h>
#include <stdlib.h>

#define sizeOfx 30
#define sizeOfy 30
#define startSled_x 0;
#define startSled_y 0;
#define startSled_orientation 0;

struct sled
{
    int  x,
         y,
         orientation,
         totalDistance;
};

///////////////// MAP //////////////////

void initialise_map(char map[sizeOfx][sizeOfy])   //FINISHED TESTED
{
    for (int y = 0; y < sizeOfy; y++)
    {
        for (int x = 0; x < sizeOfx; x++)
        {
            map[y][x] = '.';
            
        }
    }
}

void populate_map(FILE *mapFile, char map[sizeOfx][sizeOfy])  //FINISHED TESTED
{
    int coordinate_x;
    int coordinate_y;
    char map_entry;

    while (fscanf(mapFile, "%i,%i,%c", &coordinate_x, &coordinate_y, &map_entry) != EOF)
    {
        map[coordinate_x][coordinate_y] = map_entry;
    }
}

void print_map(char map[sizeOfx][sizeOfy])    //FINISHED TESTED
{
    for (int y = (sizeOfy-1); y >= 0; y--)
    {
        for (int x = 0; x < sizeOfx; x++)
        {
            printf("%c", map[x][y]);
        }
        printf("\n");
    }
    printf("\n");
}


///////////////// SLED /////////////////

int process_command(FILE *commandFile, char map[sizeOfx][sizeOfy], struct sled *ptr_sled1)    //FINISHED NOT TESTED
{
    char command[10];
    int command_value;
    int distanceTravelled = 0;

    while (fscanf(commandFile, "%s %i", &command, &command_value) != EOF)
    {
        if (command[0] == 'F')
        {
            //forward
            distanceTravelled = distanceTravelled + command_value;

            if (ptr_sled1->orientation == 0)
            {
                ptr_sled1->y = ptr_sled1->y + command_value;
            }
            else if (ptr_sled1->orientation == 90)
            {
                ptr_sled1->x = ptr_sled1->x + command_value;
            }
            else if (ptr_sled1->orientation == 180)
            {
                ptr_sled1->y = ptr_sled1->y - command_value;
            }
            else if (ptr_sled1->orientation == 270)
            {
                ptr_sled1->x = ptr_sled1->x - command_value;
            }
        }

        else if (command[0] == 'T')
        {
            //turn
            ptr_sled1->orientation = ptr_sled1->orientation + command_value;
            //what happens at 270 + anything?
            if (ptr_sled1->orientation >= 360)
            {
                ptr_sled1->orientation = ptr_sled1->orientation - 360;
            }
            else if (ptr_sled1->orientation < 0)
            {
                ptr_sled1->orientation = ptr_sled1->orientation + 360;
            }
        }

        else
        {
            printf("Error. Command file is written in an incorrect format.");
            exit(1);
        }
    }
    ptr_sled1->totalDistance = distanceTravelled;
    return 0;
}

void print_sled(struct sled *ptr_sled1) //FINISHED NOT TESTED
{
    printf("SLED Status:\n");
    printf("Location: %i,%i\n", ptr_sled1->x, ptr_sled1->y);
    printf("Orientation: %i\n", ptr_sled1->orientation);
    printf("Distance Travelled: %i\n", ptr_sled1->totalDistance);
    printf("\n");
}

void print_symbol(char map[sizeOfx][sizeOfy], struct sled *ptr_sled1) //FINISHED TESTED
{
    printf("SLED is flying over symbol '%c' at %i,%i.", map[ptr_sled1->x][ptr_sled1->y], ptr_sled1->x, ptr_sled1->y);
    printf("\n");
}


//////////////// MAIN() ////////////////

int main()
{
   char map[sizeOfx][sizeOfy];
   FILE *mapFile = fopen("map.txt", "r");
   FILE *commandFile = fopen("sledcommands.txt", "r");

   struct sled sled1;
   struct sled *ptr_sled1 = &sled1;
   ptr_sled1->x = startSled_x;
   ptr_sled1->y = startSled_y;
   ptr_sled1->orientation = startSled_orientation

    ///////////// PROGRAM //////////////

    initialise_map(map);
    populate_map(mapFile, map);
    print_map(map);

    process_command(commandFile, map, ptr_sled1);
    print_sled(ptr_sled1);
    print_symbol(map, ptr_sled1);
}