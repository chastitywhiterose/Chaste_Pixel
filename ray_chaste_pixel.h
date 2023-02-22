/*ray_chaste_pixel.h*/

/*
 the goal for this library is to be able to draw pixels one at a time and yet introduce a delay as the pixels are drawn to help
 create animations of things like lines being slowly drawn.
 
 Every graphics library has a pixel drawing function and in this case.
*/


int frame=0; /*keep track of frame number*/

/*saves the current window as an image file and increments frame number*/
void TakeScreenshot_frame()
{
 Image this_frame=LoadImageFromScreen();
 //int this_frame_width=this_frame.width;
 //int this_frame_height=this_frame.height;
 //printf("%d\n",this_frame.width);
 //printf("%d\n",this_frame.height);
 //return;
 char filename[256];
 sprintf(filename,"o/%08d.png",frame);
 printf("%s\n",filename);
 //TakeScreenshot(filename);
 ExportImage(this_frame,filename);
 frame++;
}


void second_delay_raylib(double seconds)
{
 double temptime0,temptime1; /*for creating artificial delays so I can see if my functions are working right*/
 
 temptime0=GetTime();
 temptime1=temptime0;
 temptime0+=seconds;
 
 while(temptime1<temptime0)
 {
  temptime1=GetTime();
  if(IsKeyPressed(KEY_ESCAPE))
  {
   printf("During Delay: The program will close now\n");
   temptime1=temptime0;break;
  }
 }
}


char pixels[0x1000000];


void chaste_pixel(int x,int y,Color color)
{
 /*begin and end one frame per pixel*/
 BeginDrawing();
 DrawPixel(x,y,color);
 EndDrawing();
 //second_delay_raylib(0.000000001);
 //TakeScreenshot_frame(); /*this is kinda buggy*/
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


