#include "classes.hpp"
#include <vector>

float min(float x, float y){
if (x<y) return(x); else return(y);
}

/**************************************************/

float max(float x, float y){
if (x>y) return(x); else return(y);
}
/**************************************************/
float* equation_droite(float xa,float ya,float xb,float yb) { //passant par deux points A et B, sous la forme ax+by+c=0

float* E= new float[3];
E[0]=yb-ya; //coefficient a
E[1]=xa-xb; //coefficient b
E[2]=ya*xb-xa*yb; //coefficient c
return(E);
}

/*********************************************************************************************/
bool point_in_segment(point A, point B, point C){ //retourne true si C dans [AB], false sinon
return( (C.x<=max(A.x,B.x)) && (C.x>=min(A.x,B.x)) && (C.y<=max(A.y,B.y)) && (C.y>=min(A.y,B.y)) );
}



/*********************************************************************************************/



bool intersection_segments(point A1, point B1, point A2, point B2){ //[A1,B1] et [A2,B2]
float* E1=equation_droite(A1.x,A1.y,B1.x,B1.y);
float* E2=equation_droite(A2.x,A2.y,B2.x,B2.y);

if( (E1[0]*E2[1]-E2[0]*E1[1]==0) || (E1[1]*E2[0]-E2[1]*E1[0]==0) ){
	/*if( (x<=max(xa1,xb1)) && (x>=min(xa1,xb1)) && (y<=max(ya1,yb1)) && (y>=min(ya1,yb1)) || )*/ return(false);
	}
else{
	point int_point; //point intersection entre les deux segments
	int_point.x=(E1[1]*E2[2]-E2[1]*E1[2])/(E1[0]*E2[1]-E2[0]*E1[1]); // coordonnées pt d'intersection
	int_point.y=(E2[2]*E1[0]-E2[0]*E1[2])/(E1[1]*E2[0]-E2[1]*E1[0]); // coordonnées pt d'intersection
	if( (point_in_segment(A1,B1,int_point)) && (point_in_segment(A2,B2,int_point)) ) {

		if( (int_point==A1) || (int_point==A2) || (int_point==B1) || (int_point==B2) ) return(false); else return(true);
	}
	else return(false);

}

}//fin intersection_segments

