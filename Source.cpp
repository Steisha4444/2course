#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <math.h>
#include<fstream>

using namespace std;
#define INF 10000
HWND hwnd = GetConsoleWindow();
HDC dc = GetDC(hwnd);
const COLORREF white = RGB(255, 255, 255);
const COLORREF yellow = RGB(255, 255, 0);
const COLORREF green = RGB(0, 255, 0);
HPEN pen = CreatePen(PS_SOLID, 1, green);
HPEN pen1 = CreatePen(PS_SOLID, 1, white);
struct Point {
    int x;
    int y;
};
void drawline(int x[], int y[], int n ) {
    CreatePen(2, 4, green);
    SelectObject(dc, pen);
    for (int i = 1; i < n; i++) {
        MoveToEx(dc, x[i-1], y[i - 1], NULL);
        LineTo(dc, x[i], y[i]);

    }
  
}

void drawPoint(int x, int y) {

   

    CreatePen(40, 4, green);
    SelectObject(dc, pen1);
    SetPixel(dc, x, y, white);

}
int direction(Point a, Point b, Point c) {
    int v = (b.y - a.y) * (c.x - b.x) - (b.x - a.x) * (c.y - b.y);
    if (v == 0)
        return 0; // колінеарні
    return (v > 0) ? 1 : 2; // за або проти годинникової стрілки(під мінімальним кутом)
}
void convexHull(Point points[], int m) {
    if (m < 3)//не менше 3 точок
        return;
    int* n = new int[m];
    for (int i = 0; i < m; i++)
        n[i] = -1;
    int l = 0;
    for (int i = 1; i < m; i++)
        if (points[i].x < points[l].x)
            l = i; //крайня ліва
    int p = l, q;
    do {
        q = (p + 1) % m;
         for (int i = 0; i < m; i++)
            if (direction(points[p], points[i], points[q]) == 2)
                q = i;
        n[p] = q;
        p = q;
    } while (p != l);
    int* x = new int[m];
    int* y = new int[m];
    int j = 0;
    for (int i = 0; i < m; i++) {
        
        if (n[i] != -1) {
            x[j] = points[i].x;
            y[j] = points[i].y;
            j++;
        }
          //  cout << "(" << points[i].x << ", " << points[i].y << ")\n";
       
    }
    x[j] = x[0];
    y[j] = y[0];
    drawline(x, y, m);
}
int main() {
    int n ;
    ifstream f_in;
 //   f_in.open("points.txt");
    f_in.open("points3.txt");
    f_in >> n;

    Point* points = new Point[n] ;
    for (int i = 0; i < n; i++) {
        f_in >> points[i].x;
        f_in >> points[i].y;

    }

    for (int i = 0; i < n; i++) {
        //if (n[i] != -1)
            //  cout << "(" << points[i].x << ", " << points[i].y << ")\n";
            drawPoint(points[i].x, points[i].y);
    }
 //   cout << "The points in the convex hull are: ";
   
    convexHull(points, n);
    ReleaseDC(hwnd, dc);
    _getch();
    return 0;
}