#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include <math.h>

const int width = 1280;
const int height = 720;

Color c; /*global color used when drawing pixels*/
int hue;

#include "ray_chaste_pixel.h"
#include "ray_chaste_pixel_polygon.h"
#include "ray_chaste_pixel_trigon.h"




void keyboard()
{
 if(IsKeyPressed(KEY_ESCAPE))
 {
  printf("During main: The program will close now\n");
 }
}




int main()
{
 int x,y;

 x=100;
 y=200;
 c=(Color){255,255,255,255};
 
 hue=0;
 
 c=ColorFromHSV(hue,1,1);
 
 init_polygon(); /*setup the polygon initial variables*/
 /*change a few polygon things for this game*/
 main_polygon.radius=height/2;
 main_polygon.sides=4;
 main_polygon.step=1;
 
 //main_polygon.cx=width*3/16;
 //main_polygon.cy=height*13/16;
 
 //main_polygon.radius-=30;
 
 main_polygon.radius=320;
 
 printf("radius %f\n",main_polygon.radius);

 InitWindow(width,height,"Chastity's Polygon using Raylib");
 SetTargetFPS(60);
 while(!WindowShouldClose())
 {
  clear_pixels();
 
  BeginDrawing();
  ClearBackground((Color){0,0,0,255});
  
  //chaste_polygon_draw();
  chaste_polygon_draw_star();
  
  chaste_scan_fill();
  
  
  
  
  //main_polygon.color=ColorFromHSV(hue,1,1); hue++;
  
  main_polygon.radians+=PI/180;
  
  EndDrawing();
  //chaste_pixel(x,y,c);
  
  //chaste_line(200,200,300,350,c);
  //second_delay_raylib(1);
  
  //return 0;
 }
 CloseWindow();
 return 0;
}

/*
raylib_linux:
	gcc -Wall -std=c99 -pedantic main.c -o main -lraylib -lOpenGL -lm -lpthread -ldl -lrt -lX11 && ./main
raylib_windows:
	gcc -Wall -std=c99 -pedantic main.c -o main -I/usr/local/include -L/usr/local/lib -lraylib -lopengl32 -lgdi32 -lwinmm -lpthread -static && ./main
	strip main.exe
	
*/
