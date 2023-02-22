#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include <math.h>

const int width = 1280;
const int height = 720;

#include "ray_chaste_pixel.h"

#include "ray_chaste_pixel_polygon.h"


void keyboard()
{
 if(IsKeyPressed(KEY_ESCAPE))
 {
  printf("During main: The program will close now\n");
 }
}


int x,y;
Color c;

int main()
{
 x=100;
 y=200;
 c=(Color){255,255,255,255};
 
 init_polygon(); /*setup the polygon initial variables*/
 /*change a few polygon things for this game*/
 main_polygon.radius=height/2;
 main_polygon.sides=5;
 main_polygon.step=2;
 
 //main_polygon.cx=width*3/16;
 //main_polygon.cy=height*13/16;
 
 main_polygon.radius-=30;
 
 printf("radius %f\n",main_polygon.radius);

 InitWindow(width,height,"Chastity's Polygon using Raylib");
 SetTargetFPS(60);
 while(!WindowShouldClose())
 {
  BeginDrawing();
  ClearBackground((Color){0,0,0,255});

  
  //chaste_pixel(x,y,c);
  //chaste_line(200,200,300,350,c);
  //chaste_polygon_draw();
  //second_delay_raylib(1);
  
  chaste_polygon_draw_star();
  
  EndDrawing();
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
	
	
	find / name raylib.h
	
*/
