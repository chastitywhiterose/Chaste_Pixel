/*ray_chaste_pixel.h*/

/*
 the goal for this library is to be able to draw pixels one at a time and yet introduce a delay as the pixels are drawn to help
 create animations of things like lines being slowly drawn.
 
 Every graphics library has a pixel drawing function and in this case.
*/





void second_delay_raylib(double seconds)
{
 double temptime0,temptime1; /*for creating artificial delays so I can see if my functions are working right*/
 
 temptime0=GetTime();
 temptime1=temptime0;
 temptime0+=seconds;
 
 while(temptime1<temptime0)
 {
  temptime1=GetTime();
  //BeginDrawing(); /*not required here but it can be used and slows things down for some reason*/
  EndDrawing(); /*required to refresh the screen*/
  if(IsKeyPressed(KEY_ESCAPE))
  {
   printf("During Delay: The program will close now\n");
   temptime1=temptime0;break;
  }
 }
}

void chaste_pixel(int x,int y,Color color)
{
 DrawPixel(x,y,color);
 second_delay_raylib(0.000000001);
}

/*
 The below function is my own version of this algorithm:
 https://rosettacode.org/wiki/Bitmap/Bresenham%27s_line_algorithm#C
*/
void chaste_line(int x0,int y0,int x1,int y1,Color color)
{
 int dx,dy,sx,sy,err,e2;
 dx= x1-x0; if(dx<0){dx=-dx;}
 dy= y1-y0; if(dy<0){dy=-dy;}
 if(x0<x1){sx=1;}else{sx=-1;}
 if(y0<y1){sy=1;}else{sy=-1;}
 if(dx>dy){err=dx;}else{err=-dy;}err>>=1;;
 while(1)
 {
  chaste_pixel(x0,y0,color); /*this is when the pixel is drawn*/
  if (x0==x1 && y0==y1) break;
  e2=err;
  if (e2 >-dx) { err -= dy; x0 += sx; }
  if (e2 < dy) { err += dx; y0 += sy; }
 }
}


