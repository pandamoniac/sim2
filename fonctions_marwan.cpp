#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

<<<<<<< HEAD
=======


class point{
public:
float x;
float y;
bool operator==(const point& A){return((A.x==x)&&(A.y==y));}	
};
/*---------------------------------------------------------------*/
class obstacle{
public:
int n_sommets; //nombre de sommets
vector<point> sommets;
}; //fin classe obstacle


>>>>>>> 595e98043ddef0044e19f5d1a65f2893293ed9fb
/**************************************************************************************************/


float min(float x, float y){
if (x<y) return(x); else return(y);
}



float max(float x, float y){
if (x>y) return(x); else return(y);
}




float* equation_droite(float xa,float ya,float xb,float yb) { //passant par deux points A et B, sous la forme ax+by+c=0

float* E= new float[3];
E[0]=yb-ya; //coefficient a
E[1]=xa-xb; //coefficient b
E[2]=ya*xb-xa*yb; //coefficient c
return(E);
}

bool point_in_segment(point A, point B, point C){ //retourne true si C dans [AB], false sinon
return( (C.x<=max(A.x,B.x)) && (C.x>=min(A.x,B.x)) && (C.y<=max(A.y,B.y)) && (C.y>=min(A.y,B.y)) );
}





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








void lecture_obstacles(char* path,vector<obstacle>& V_obs,int& N){
fstream ff(path,ios::out | ios::in);
//ff.open(path,ios::out | ios::in);
char c;
char k;
point temp_p;
string temp="";
int k_temp=0; //nombre de points d'obstacle
obstacle temp_obs;
while (ff >> noskipws >> c) {
	if((c!=',') && (c!=';') && (c!='\n')) {temp=temp+c;}
	else if (c==',') { temp_p.x=stof(temp); temp.clear();}
	else if (c==';') {temp_p.y=stof(temp); temp.clear(); temp_obs.sommets.push_back(temp_p); k_temp++; /*stock nouvelle point dans une struc*/}
	else {N++; temp_obs.n_sommets=k_temp; /*modification du tableau d'obstacles*/ V_obs.push_back(temp_obs);k_temp=0;temp_obs.sommets.clear();}

} //end while

} //end lecture



point* point_dep_arr(){
point* V= new point[2];
cout<<"Donner les coordonnées du point de départ : "<<endl;
cout<<"x= ";
cin>>V[0].x;
cout<<"y= ";
cin>>V[0].y;

cout<<"Donner les coordonnées du point d'arrivée : "<<endl;
cout<<"x= ";
cin>>V[1].x;
cout<<"y= ";
cin>>V[1].y;
return(V);
}











int main(){
//test de la fonction intersection_segments
point A1,B1,A2,B2;
A1.x=1;A1.y=1;
B1.x=4;B1.y=2;
A2.x=3;A2.y=1;
B2.x=4;B2.y=4;



cout << intersection_segments(A1,B1,A2,B2) << endl;
/*
cout << intersection_segments(0,3,2,3,0,1,2,1) << endl;
cout << intersection_segments(3,2,5,5,5,3,7,3) << endl;
cout << intersection_segments(3.0,2.0,5.0,5.0,3.0,3.0,7.0,3.0) << endl;
cout << intersection_segments(6.0,1.0,6.0,3.0,4.0,2.0,7.0,2.0) << endl;
cout << intersection_segments(1.0,1.0,3.0,3.0,2.0,2.0,1.0,3.0) << endl;
cout <<"Test ! ! ! : "<<intersection_segments(1,1,4,1,2,1,3,1) << endl;
*/
//test de la fonction lecture
char test_path[]="obstacles.txt";
int N=0;
vector<obstacle> V_obs;
lecture_obstacles(test_path,V_obs,N);
cout<<N<<endl;
cout<<V_obs[6].n_sommets<<" , "<<V_obs[6].sommets[3].x<<"  "<<V_obs[6].sommets[3].y<<endl;
//Lecture point de depart point d'arrivée
point p_dep,p_arr;
cout<<"Donner les coordonnées du point de départ : "<<endl;
cout<<"x= ";
cin>>p_dep.x;
cout<<"y= ";
cin>>p_dep.y;

cout<<"Donner les coordonnées du point d'arrivée : "<<endl;
cout<<"x= ";
cin>>p_arr.x;
cout<<"y= ";
cin>>p_arr.y;
return(0);
}
