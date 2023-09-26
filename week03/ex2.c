#include <stdio.h>
#include <math.h>

struct Point{
	double x;
	double y;
};

double distance(struct Point p1, struct Point p2){
	double dx = p2.x - p1.x;
	double dy = p2.y - p1.y;

	double distance = sqrt(dx*dx + dy*dy);
	return distance;
}

double area(struct Point A, struct Point B, struct Point C){
	double area = 0.5 * fabs((A.x - C.x) * (B.y - A.y) - (A.x - B.x) * (C.y - A.y));
	return area;
}

int main(){
	struct Point A = {2.5, 6};
	struct Point B = {1, 2.2};
	struct Point C = {10, 6};

	double dis = distance(A, B);
	double are = area(A, B, C);

	printf("Distance AB: %f\nArea of the triangle ABC: %f\n", dis, are);

	return 0;
}
