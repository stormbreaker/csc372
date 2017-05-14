//AoA Program 2
//Half and Half
/******************************************************************************
* Analysis of Algorithms Half-and-Half
* Author:  Benjamin Kaiser
* Class: CSC 372 - Analysis of Algorithms
* Instructor: Dr. A Logar
* Teacher's Assistant: Dr. E Corwin
* Due: November 1, 2015
* Written:
* 	10-14-15: Assigned Program
* 	10-19-15: Started
*	10-20-15: Input/output
* 	10-22-15: Wrote own functions (minus area)
* 	10-25-15: Got Teacher functions (including area)
* 	10-31-15: Finished
* 	10-31-15: Documented
* Description:  Given a file with points describing polygons, this Program
* 	decides 1) the polygon is convex or concave.  If it is convex, then it
* 	computes the x-coordinate of where a line can be drawn vertically to
* 	split the polygon into exactly two pieces of equal area.  If the polygon
* 	is concave, the program automatically decides there is no solution.
* 	Answers are put into a file with the same name as the input file but with
* 	a .out extension.
* Usage: This Program can be run from the command line using command line
* 	arguments.  The first and only additional argument besides the program
* 	executable is the input file.  The output file is generated by the program
* 	by taking the input file name, dropping the file extension and appending
* 	a .out extension.
* Bugs: No known errors
******************************************************************************/

//preprocessor library includes
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

/******************************************************************************
* Structure for containing points in the 2-D Real Space
* Author: A Logar and E Corwin
* Description: Contains a structure which holds an x-coordinate and
* 	a y-coordinate coordinate for real numbers using doubles.
******************************************************************************/
struct point
  {
  double x;
  double y;
  };

double area(vector<point> p);
double bisect(double max, double min);
bool clockwise(point p[]);
double cross(point a, point b);
double direction(point a, point b, point c);
double getY(point p1, point p2, double x);
bool intersect(point p1, point p2, point p3, point p4);
double max(double a, double b);
double min(double a, double b);
bool on(point a, point b, point c);
bool turn(point a, point b, point c);

/******************************************************************************
* Main
* Author: Benjamin Kaiser
* Description: This function is the main processing function of this program.
*	It uses command line arguments, computes the output file and then begins
*	the scientific processing.  This consists of a couple of nested loops which
*	handle looping through all the points/line segments and bisecting the
*	polygon.
* Parameters: argc is the amount of command line arguments there are
*	argv is the character array containing each of the command line arguments
******************************************************************************/
int main(int argc, char** argv)
  {
  //input and output
  ifstream  fin;
  ofstream fout;

  fout << setprecision(5) << fixed; //set decimal output precision

  string test = "";
  test = argv[1];
  fin.open(test);

  //compute output file from input file
  int replaceIndex;
  replaceIndex = test.rfind('.');
  test.replace(replaceIndex, test.size() - replaceIndex, ".out");
  fout.open(test);

  int numpoints; //number of points in polygon
  bool convex = false; //whether polygon is convex or not
  vector<point> coords; //polygon
  vector<point> lefts; //used to store left half of polygon
  vector<point> rights; //used to store right half of polygon

  //vector<vpoint> vecs;
  vector<bool> turns; //contains direction of turns

  point temppoint; //for file IO

  int caseCount = 0; // case number

  point bisector[2]; //bisecting line
  point intersects[2]; // contains both intersect points
  double left, right; //area of left and right shapes

  //main processing loop to read in from file
  while (fin >> numpoints)
    {
    caseCount++;
    convex = true;
    double maxX = -999999;
    double minX = 999999;
    double maxY = -999999;
    double minY = 999999;

    //read points in and find min and max x and y
    for (int i = 0; i < numpoints; i++)
      {
      fin >> temppoint.x;
      if (temppoint.x < minX)
      	minX = temppoint.x;
      if (temppoint.x > maxX)
	maxX = temppoint.x;
      fin >> temppoint.y;
      if (temppoint.y < minY)
	minY = temppoint.y;
      if (temppoint.y > maxY)
	maxY = temppoint.y;
      coords.push_back(temppoint);
      }

      //append the first two points of polygon to the end avoid special case
      coords.push_back(coords[0]);
      coords.push_back(coords[1]);

      //move these out 1 unit to avoid the line end point running into
      //a polygon vertex
      maxY += 1;
      minY -= 1;

      //check for convexity
      for (int i = 0; i < numpoints; i++)
        {

	turns.push_back(turn(coords[i], coords[i+1], coords[i+2]));
	if (i > 0)
	  {
	  if (turns[i] != turns[i-1])
	    {
	    fout << "Case: " << caseCount << ": " << "No solution" << endl;
	    convex = false;
	    break;
	    //this means concave and print no solution
	    }
	  }
	}

	//do this if the polygon is convex
	if (convex == true)
	  {

	  //these check
	  bisector[0].y = minY;
	  bisector[1].y = maxY;

	  //bisection loop
	  do
	    {
	    bisector[0].x = bisector[1].x = bisect(maxX, minX);

            int count = 0;
	    for (int i = 0; i < numpoints; i++)
	      {
	      //load points into left half
	      if (coords[i].x < bisector[0].x)
	        {
		lefts.push_back(coords[i]);
		}

	      //load points into right half
	      else if (coords[i].x > bisector[0].x)
		{
		rights.push_back(coords[i]);
		}

		//load intersects into both left and right
		if (intersect(bisector[0], bisector[1], coords[i], coords[i+1]) == true && count < 2)
		  {
		  intersects[count].x = bisector[1].x;
		  double tempx = bisector[1].x;
		  intersects[count].y = getY(coords[i], coords[i+1], tempx);
		  // << "Intersects" << count << " x " << intersects[count].x << " y " << intersects[count].y << endl;
		  lefts.push_back(intersects[count]);
		  rights.push_back(intersects[count]);
		  count++;
		  }

		}
	      left = area(lefts);
	      right = area(rights);

	      //perform bisection
	      if (left - right > 1.0e-6)
		{
		maxX = bisector[1].x;
		}
	      else if (right - left > 1.0e-6)
		{
		minX = bisector[1].x;
		}

	      lefts.clear();
	      rights.clear();


	    } while (fabs(left - right) > 1.0e-6);

	  fout << "Case: " << caseCount << " " << bisector[1].x << endl;

	  turns.clear();
	  coords.clear();
	  }
	}

	return 0;
  }



/******************************************************************************
* Area
* Author: A Logar and E Corwin (modified by Benjamin Kaiser)
* Description: This function takes a bunch of points which describe a polygon
* 	and computes the area using trapezoids.  The higher points create a
* 	trapezoid and the points below create a trapezoid which is subtracted from
* 	the upper ones.
* Modifications: I changed the parameters from an array and the size of the
* 	array to a vector.
* Parameters: p is a vector of points which describe a polygon.
* 	This returns a double value of the area.
******************************************************************************/
double area(vector<point> p)
  {
  int i;
  int j;
  double result;
  result = 0;
  for (i = 0; i < p.size(); i++)
    {
    j = (i + 1) % p.size();
    result += p[i].x * p[j].y;
    result -= p[i].y * p[j].x;
    }
    return fabs(result / 2);
  }

/******************************************************************************
* Bisect
* Author: Benjamin Kaiser
* Description: This function takes two values and computes the midpoint of
* 	the two values.
* Parameters: max is the upper value to be passed in
* 	min is the lower value to be passed in.
* 	The function returns a double value as a result
******************************************************************************/

double bisect(double max, double min)
  {
  return (max + min)/2;
  }

/******************************************************************************
* Cross
* Author: A Logar and E Corwin
* Description: This function takes two vectors and computes the cross product
* 	between the two and returns it.
* Parameters: a is the first vector
* 	b is the second vector
******************************************************************************/
double cross(point a, point b)
  {
  //cout << "cross" << endl;
  return a.x * b.y - a.y * b.x;
  }

/******************************************************************************
* Direction
* Author: A Logar and E Corwin
* Description: This function takes three points, computes the vectors between
* 	then takes the cross product of those vectors and returns the result.
* 	If the cross product is close to 0 (within 1.0e-6), it simply returns 0.
* Parameters: a is the first point
* 	b is the second point
* 	c is the third point
******************************************************************************/
double direction(point a, point b, point c)
  {
  point ab;
  point bc;
  double result;

  ab.x = b.x - a.x;
  ab.y = b.y - a.y;
  bc.x = c.x - b.x;
  bc.y = c.y - b.y;
  result =  cross(ab, bc);
  if (fabs(result) < 1.0e-6)
    result = 0.0;
  return result;
  }

/******************************************************************************
* Direction
* Author: Benjamin Kaiser
* Description: This function takes two points and an x-coordinate value.
* 	It then uses the equation derived from similar triangles to compute
* 	the y-value of the point of intersection of two lines.
* Parameters: p1 is the first point defining the line
* 	p2 is the second point defining the line
* 	x is the value of the x-coordinate of the intersect.
******************************************************************************/
double getY(point p1, point p2, double x)
  {
  return ((x - p1.x)/(p2.x - p1.x)) * (p2.y - p1.y) + p1.y;
  }

/******************************************************************************
* Intersect
* Author: A Logar and E Corwin (also from the Analysis of Algorithms textbook)
* 	Textbook page 937 (second edition)
* Description: This function takes 4 points which define two distinct line
* 	segments.  It then calls the direction function and if the directions are
*	different going both ways, the line segments intersect and the function
*	returns true.
* Parameters: p1 is the first point defining the first line
* 	p2 is the second point defining the first line
* 	p3 is the first point defining the second line
*	p4 is the second point defining the second line
******************************************************************************/
bool intersect(point p1, point p2, point p3, point p4)
  {
  double d1;
  double d2;
  double d3;
  double d4;

  d1 = direction(p3, p4, p1);
  d2 = direction(p3, p4, p2);
  d3 = direction(p1, p2, p3);
  d4 = direction(p1, p2, p4);

  if ((((d1 > 0) && (d2 < 0)) || ((d1 < 0) && (d2 > 0))) && (((d3 > 0) && (d4 < 0)) || ((d3 < 0) && (d4 > 0))))
    return true;

  if ((d1 == 0) && on(p3, p4, p1))
    return true;

  if ((d2 == 0) && on(p3, p4, p2))
    return true;

  if ((d3 == 0) && on(p1, p2, p3))
    return true;

  if ((d4 == 0) && on(p1, p2, p4))
    return true;

  return false;
  }

/******************************************************************************
* Max
* Author: A Logar and E Corwin
* Description: This function takes two different double values and returns the
*	greater of the two.
* Parameters: a is the first value
*	b is the second value
******************************************************************************/
double max(double a, double b)
  {
  if (a > b)
    return a;
  return b;
  }

/******************************************************************************
* Min
* Author: A Logar and E Corwin
* Description: This function takes two different double values and returns the
*	smaller of the two.
* Parameters: a is the first value
*	b is the second value
******************************************************************************/
double min(double a, double b)
  {
  if (a < b)
    return a;
  return b;
  }

/******************************************************************************
* On
* Author: A Logar and E Corwin
* Description: This function takes three points and assumes a and b define a
*	line segment.  It then checks to see if the third point is between a and b.
*	It does this by calling the min and max functions.
* Parameters: a is the first point defining the line segment
*	b is the second point defining the line segment
*	c is the point in question.
******************************************************************************/
bool on(point a, point b, point c)
  {
  if (((min(a.x, b.x) <= c.x) && (c.x <= max(a.x, b.x))) &&((min(a.y, b.y) <= c.y) && (c.y <= max(a.y, b.y))))
    return true;
  return false;
  }

/******************************************************************************
* Turn
* Author: A Logar and E Corwin
* Description: This function returns the result of the direction function.
*	Essentially, it checks to see if it is a left turn.
* Parameters: a is the first point
*	b is the second point
*	c is the third point
******************************************************************************/
bool turn(point a, point b, point c)
  {
  return (direction(a, b, c) > 0);
  }
