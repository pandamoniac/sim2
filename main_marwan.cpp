#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "opt_path_to_file.hpp"
using namespace std;

//<<<<<<< HEAD
//=======



//>>>>>>> 595e98043ddef0044e19f5d1a65f2893293ed9fb
/**************************************************************************************************/













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
//testing opt_path_to_file function
vector<int> chem_opt;
for(int i=0;i<12;i++){chem_opt.push_back(12-i);}
opt_path_to_file(chem_opt,V_obs);
//Lecture point de depart point d'arrivée
/*
point* k=new point[2];
k=point_dep_arr();
*/
return(0);
}
