/*ray_chaste_pixel_polygon.h*/

struct polygon
{
 double cx,cy;
 int sides;
 double radius;
 double radians;
 Color color;
 int step; //used only in star polygons of 5 or more sides
};

struct polygon main_polygon;

void init_polygon()
{
 main_polygon.cx=width/2;
 main_polygon.cy=height/2;
 main_polygon.sides=3;
 main_polygon.radius=height/2;
 main_polygon.radians=0;
 main_polygon.color=(Color){255,255,255,255};
 main_polygon.step=2;
}

/*PI does not need to be defined for Raylib because it is included in raylib.h . But here it is for later use by SDL,Allegro,etc*/
//#define PI 3.14159265358979323846f

/*these point arrays are temporary and not included in the polygon structure*/
int polygon_xpoints[0x1000],polygon_ypoints[0x1000];

/*
 this function created because the standard round function did not exist in C until 1999 standard.
 I only use 1989 standard.
*/
double bbm_round(double x)
{
 return x<0 ? ceil(x - 0.5) : floor(x + 0.5);
}

/*
function to get the points of a regular polygon and load them into the above arrays of x and y points
*/
void chaste_polygon_points()
{
 double angle,x,y;
 int i=0;
 while(i<main_polygon.sides)
 {
  angle=2*PI*i/main_polygon.sides+main_polygon.radians;
  x=main_polygon.cx+sin(angle)*main_polygon.radius;
  y=main_polygon.cy-cos(angle)*main_polygon.radius;
  polygon_xpoints[i]=bbm_round(x);
  polygon_ypoints[i]=bbm_round(y);
//  printf("angle==%f\n",angle);
//  printf("x==%f x==%f\n",x,y);
 // printf("xpoint[%d]==%d ypoint[%d]==%d\n",i,polygon_xpoints[i],i,polygon_ypoints[i]);
  i++;
 }
}


Vector2 polygon_vectors[0x1000];



/*
polygon

The polygon is filled. 
*/
void chaste_polygon_draw()
{
 int i,i1;
 chaste_polygon_points();
 
 i=0;
 while(i<main_polygon.sides)
 {
  polygon_vectors[i]=(Vector2){polygon_xpoints[i],polygon_ypoints[i]};
  i+=1;
 }
 
 i=0;
 while(i<main_polygon.sides)
 {
  i1=(i+1)%main_polygon.sides;
  //DrawTriangle(polygon_vectors[i],(Vector2){main_polygon.cx,main_polygon.cy},polygon_vectors[i1],main_polygon.color); //filled polygon
  //DrawTriangleLines(polygon_vectors[i],(Vector2){main_polygon.cx,main_polygon.cy},polygon_vectors[i1],main_polygon.color); //outline with lines to center
  //DrawLineV(polygon_vectors[i],polygon_vectors[i1],main_polygon.color); //outline only with outer points
  
  //DrawLine(polygon_xpoints[i],polygon_ypoints[i],polygon_xpoints[i1],polygon_ypoints[i1], main_polygon.color);
  
  chaste_line(polygon_xpoints[i],polygon_ypoints[i],polygon_xpoints[i1],polygon_ypoints[i1], main_polygon.color);
  
  i++;
 }
 
 chaste_flood_fill(main_polygon.cx,main_polygon.cy);
 
}




/*
polygon

The star polygon is filled. 
*/
void chaste_polygon_draw_star()
{
 int i,i1;
 chaste_polygon_points();
 
 i=0;
 while(i<main_polygon.sides)
 {
  polygon_vectors[i]=(Vector2){polygon_xpoints[i],polygon_ypoints[i]};
  i+=1;
 }
 
 i=0;
 while(i<main_polygon.sides)
 {
  i1=(i+main_polygon.step)%main_polygon.sides;
  //DrawTriangle(polygon_vectors[i],(Vector2){main_polygon.cx,main_polygon.cy},polygon_vectors[i1],main_polygon.color); //filled star polygon
  //DrawTriangleLines(polygon_vectors[i],center,polygon_vectors[i1],main_polygon.color); //outline with lines to center
  //DrawLineV(polygon_vectors[i],polygon_vectors[i1],main_polygon.color); //outline only with outer points
  
  //DrawLine(polygon_xpoints[i],polygon_ypoints[i],polygon_xpoints[i1],polygon_ypoints[i1], main_polygon.color);
  
  chaste_line(polygon_xpoints[i],polygon_ypoints[i],polygon_xpoints[i1],polygon_ypoints[i1], main_polygon.color);
  i++;
 }
 
 /*after all lines are drawn, optionally flood fill*/
 //chaste_flood_fill(main_polygon.cx,main_polygon.cy);
 
}






/*
 A special convex regular polygon function.
 It draws the outer lines of the polygon and also lines from the center to the corners.
 This splits them up into smaller triangles which can be filled.
 This is designed to reduce stack space when calling the recursive flood fill function.
*/
void chaste_polygon_draw_filled()
{
 int i,i1;
 chaste_polygon_points();
  
 i=0;
 while(i<main_polygon.sides)
 {
  i1=(i+1)%main_polygon.sides;
  chaste_line(polygon_xpoints[i],polygon_ypoints[i],polygon_xpoints[i1],polygon_ypoints[i1], main_polygon.color);
  chaste_line(polygon_xpoints[i],polygon_ypoints[i],main_polygon.cx,main_polygon.cy, main_polygon.color);
  i++;
 }
 
 i=0;
 while(i<main_polygon.sides)
 {
  int x1,y1,x2,y2;
  i1=(i+1)%main_polygon.sides;
  
  x1=(polygon_xpoints[i]+polygon_xpoints[i1])/2;
  y1=(polygon_ypoints[i]+polygon_ypoints[i1])/2;
  
  
  x2=(main_polygon.cx+x1)/2;
  y2=(main_polygon.cy+y1)/2;

  //chaste_line(main_polygon.cx,main_polygon.cy,x2,y2,main_polygon.color);
  //chaste_pixel(x2,y2,main_polygon.color);

   //c=ColorFromHSV(hue,1,1); hue+=61;
  
   chaste_flood_fill(x2,y2);
  i++;
 }
 
 //chaste_flood_fill(main_polygon.cx,main_polygon.cy);
 
}




//examples from the raylib cheatsheet for reminders on what I am doing
//void DrawTriangle(Vector2 v1, Vector2 v2, Vector2 v3, Color color);
//    void DrawTriangleFan(Vector2 *points, int pointCount, Color color);    // Draw a triangle fan defined by points (first vertex is the center)
//    void DrawTriangleStrip(Vector2 *points, int pointCount, Color color);  // Draw a triangle strip defined by points
//DrawLineV(Vector2 startPos, Vector2 endPos, Color color);

