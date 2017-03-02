#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include  "functions1.hpp"
using namespace std ;

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
ff.close();
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
