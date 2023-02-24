/*ray_chaste_pixel_trigon.h*/

/*
The purpose of this file is to find creating ways to manipulate triangles. Triangles are a special type of polygon in that any other polygon can be made from them.
*/

/*
raylib has a DrawPixel function which draws the pixels to screen. However it does not have the same for getting a pixel value from the screen.
Therefore I will reference my own global pixels array defined in ray_chaste_pixel.h

This is used to do my scan fill algorithm for filling any triangle or regular polygon
*/

/*scan fill an area. Works for only certain shapes including triangles*/
void chaste_scan_fill()
{
 int x,y,x1;
 y=0;
 while(y<height)
 {
  x=0;
  while(x<width)
  {
   //pixels[x+y*width]=0;
   if(pixels[x+y*width]!=0) /*find left edge*/
   {
    //printf("found left edge at x=%d,y=%d\n",x,y);
    
     x1=width;
     while(x1>0)
     {
      x1-=1;
      if(pixels[x1+y*width]!=0){break;} /*find right edge*/
     }
     
     while(x<x1) /*fill space between the two on this line*/
     {
      //pixels[x+y*width]=1;
      chaste_pixel(x,y,c);
      x+=1;
     }
    
   }
   
   x+=1;
  }
  c=ColorFromHSV(hue,1,1); hue+=1;
  y+=1;
 }
 hue+=6;
}


/*
 function to arbitrarily draw any triangle, not just the regular ones
*/
void chaste_trigon(int x0,int y0,int x1,int y1,int x2,int y2,Color color)
{
 chaste_line(x0,y0,x1,y1,c);
 chaste_line(x1,y1,x2,y2,c);
 chaste_line(x2,y2,x0,y0,c);
}





/*
 function to draw any triangle, but also draw corner to midpoint of lines
*/
void chaste_trigon_mid(int x0,int y0,int x1,int y1,int x2,int y2,Color color)
{
 int mx,my;
 

 chaste_line(x0,y0,x1,y1,c); /*line 0*/
 
 mx=(x0+x1)/2;
 my=(y0+y1)/2;
 chaste_line(mx,my,x2,y2,c); /*midpoint of line 0 to point 2*/
 
 
 chaste_line(x1,y1,x2,y2,c); /*line 1*/
 
 mx=(x1+x2)/2;
 my=(y1+y2)/2;
 chaste_line(mx,my,x0,y0,c); /*midpoint of line 1 to point 0*/
 
 chaste_line(x2,y2,x0,y0,c); /*line 2*/
 
 mx=(x2+x0)/2;
 my=(y2+y0)/2;
 chaste_line(mx,my,x1,y1,c); /*midpoint of line 2 to point 1*/
 
}







/*
 The flood fill algorithm is complex. I got the basic layout from here:
 https://rosettacode.org/wiki/Bitmap/Flood_fill#C
*/



/*
my flood fill algorithm for this project does not take a color argument because it is using assumed values of 0 and 1 just like my scan_fill function earlier in this file.
*/

int oldColor=0,newColor=1;

void chaste_flood_fill(int x,int y)
{
 if ( 0 <= x && x < height 
 &&   0 <= y && y < width 
 &&   pixels[x+y*width] == oldColor )
 {
  chaste_pixel(x,y,c);
  pixels[x+y*width] = newColor;
  chaste_flood_fill(x-1,y);
  chaste_flood_fill(x+1,y);
  chaste_flood_fill(x,y-1);
  chaste_flood_fill(x,y+1);
 }

}












/*find approximate center of a triangle and then fill from that spot*/
void chaste_trigon_fill(int x0,int y0,int x1,int y1,int x2,int y2,Color color)
{
 int mx,my,mx1,my1;
 

 chaste_line(x0,y0,x1,y1,c); /*line 0*/
 chaste_line(x1,y1,x2,y2,c); /*line 1*/
 chaste_line(x2,y2,x0,y0,c); /*line 2*/
 
 
 mx=(x0+x1)/2;
 my=(y0+y1)/2;
 mx1=(mx+x2)/2;
 my1=(my+y2)/2;
 
// chaste_line(mx1,my1,x2,y2,c); 
 //chaste_pixel(mx1,my1,c);
 
 chaste_flood_fill(mx1,my1);
 
 
}




/*
 Pixel Math Facts
 
 The resolution I usually use for my videos and my programs is 1280*720.
 This is a total of 921600 for the entire screen or image frame.
 This is slightly less than one million:
  1,000,000
 or 2 to the power of 20:
  1,048,576
  
  This means that you can expect each pixel takes about a megabyte if one byte is used for each pixel. However it is usually more than that.
  
  1920*1080 is a higher resolution that is
  2,073,600 pixels.
  slightly less than 2 to the power of 21:
  2097152
 
  And this is why video files are often very huge and take major compression to be able to transfer.
 
*/
