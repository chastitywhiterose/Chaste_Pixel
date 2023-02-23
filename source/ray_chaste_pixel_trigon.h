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
