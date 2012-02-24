#include "DemoMap.h"

#include <iostream>
#include <cstdlib>

using namespace std;


namespace Demo
{

QColor GetColor( LandType landType,int height,int x,int y)
{
    LandType **landTypes = GetLandType();
    int r=0,g=0,b=0;
    int br=0,bg=0,bb=0;
    int count = 1;
  
for( int i = -1 ; i <= 1 ;i++)
	for(int j = -1;j <= 1 ;j++)

{
x = x + i;
y = y + j;
		  if( x >= 0 && x <= 32 && y >=0 && y <= 16)
		  {
  landType = landTypes[x][y]; 
  if( landType == grass )
  {
  	r = 0;g=255;b=0;
  }
  else if( landType == river )
  {
	r=0;g=0;b=255;
  } 
  else if( landType == land )
  {
	r=160;g=140;b=50;
  }
   else if( landType == swamp )
  {
	r=20;g=60;b=30;
  }
   else if( landType == camp )
  {
	r=160;g=90;b=50;
  }
     else if( landType == tree )
  {
  	r=90;g=200;b=70;
  }
    
  else if( landType == tundra )
  {
	r=140;g=220;b=80;
  }
     else if( landType == lake )
  {

	r=140;g=80;b=220;
  }
    
  else if( landType == rocky )
  {
	r=200;g=200;b=70;
  }
  else
  {
	r=0;g=255;b=0;
  }

count++;
bb += b;
br += r;
bg += g;
}

}

	return QColor(br/count,bg/count,bb/count,height);
	
}

int** GetHeight()
{
    int **map_height = new int*[16], i, j;

    for(i=0;i<16;i++)
    {
        map_height[i] = new int[32];
        for (j =0;j<32;j++ )
        {
            if (i>8)
            {
                map_height[i][j]= (100 + ((15-i)*50));
            }
            else
            {
                map_height[i][j]= (100 + ((15-i)*75));
            }
        }
 }


/*    for(j = 0; j < 16; j++)
    {
        cout << endl;
        for(i = 0; i < 32; i++)
            cout << map_height[j][i] << ' ';
    }*/

    return map_height;
}

int** GetRamp()
{
    int i, j;
    int **map_ramp = new int*[16];


    for (i =0;i<8;i++ )
    {
        map_ramp[i] = new int[32];
        for(j=0;j<32;j++)
        {
               map_ramp[i][j]= 25 + (rand() % 16);
        }
    }

    for (i =8;i<16;i++ )
    {
        map_ramp[i] = new int[32];
        for(j=0;j<32;j++)
        {
               map_ramp[i][j]= 10 + (rand() % 16);
        }
    }


//    for(j = 0; j < 16; j++)
//        {
//            cout << endl;
//            for(i = 0; i < 32; i++)
//                cout << map_ramp[i][j] << ' ';
//        }

    return map_ramp;
}

LandType** GetLandType()

{
    int i, j;
    LandType **map_type = new LandType*[16];
    for(i = 0; i < 16; i++)
    {
        map_type[i] = new LandType[32];
        for( j = 0; j < 32; j ++ )
          map_type[i][j] = grass;
    }


    ///////////start of grass type /////////////
    for(i=12;i<16;i++)
            for(j =0; j<32; j++ )
            {
                    map_type[i][j]= grass;
            }


    for(i=6;i<12;i++)
            for (j =28;j<32;j++ )
            {
                    map_type[i][j]= grass;
            }

    for(i=10;i<12;i++)
        for (j =2;j<9;j++ )
            {
                    map_type[i][j]= grass;
            }

       for(i=5;i<8;i++)
    for (j =10;j<19;j++ )

            {
                    map_type[i][j]= grass;
            }

    ////////////////end of grass type //////////////


    ///////////start of tundra type /////////////
            for(i=6;i<12;i++)
       for (int j =19;j<28;j++ )

            {
                    map_type[i][j]= tundra;
            }


    for(i=9;i<12;i++)
        for (j =9;j<19;j++ )

            {
                    map_type[i][j]= tundra;
            }

for(i=2;i<5;i++)
    for (j =11;j<19;j++ )

            {
                    map_type[i][j]= tundra;
            }


    ///////////end of tundra /////////////

    ///////////start of rocky /////////////
    for(i=0;i<2;i++)
            for (j =0;j<32;j++ )
            {
                    map_type[i][j]= rocky;
            }

        for(i=2;i<5;i++)
    for (j =0;j<11;j++ )

            {
                    map_type[i][j]= rocky;
            }


    for(i=2;i<6;i++)
    for (j =19;j<32;j++ )

            {
                    map_type[i][j]= rocky;
            }


    for(i=5;i<8;i++)
    for (j =0;j<9;j++ )

            {
                    map_type[i][j]= rocky;
            }

    for(i=8;i<12;i++)
    for (j =0;j<2;j++ )

            {
                    map_type[i][j]= rocky;
            }

            ///////////end of rocky /////////////

    ///////////start of lake type /////////////
    for(i=8;i<10;i++)
            for (j =2;j<9;j++ )
            {
                    map_type[i][j]= lake;
            }
    ///////////end of lake type /////////////


    ///////////start of river type /////////////
            for(j=10;j<14;j++)
                    map_type[5][j]= river;

            for(j=4;j<9;j++)
                    map_type[11][j]= river;

            for(i=5;i<9;i++)
                    map_type[i][9]= river;


            for(j=9;j<21;j++)
                    map_type[8][j]= river;

            map_type[9][20]= river;

            for(j=21;j<25;j++)
                    map_type[10][j]= river;

            map_type[11][25]= river;
            map_type[11][26]= river;
            map_type[10][5]= river;
    ///////////end of river type /////////////


    ////////////////start of camp type //////////////
            map_type[1][15]= camp;
            map_type[1][17]= camp;
    ////////////////end of camp type //////////////


    return map_type;
}


}
