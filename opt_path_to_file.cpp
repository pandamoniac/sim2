#include "lecture.hpp"
#include<vector>
void opt_path_to_file(vector<int> chem_opt,vector<obstacle> V_obs){
/*
N_chem : taille du chemin optimale
chem_opt : le chemin optimale
V_obs : vecteur contenant les obstacles
*/
fstream ff("chemin_opt.txt",ios::out | ios::in);
int j=0;
int k;
cout<<"ok"<<endl;
for(int i=0;i<chem_opt.size();i++){
	k=chem_opt[i];
	while( (j<V_obs.size())&&(k/(V_obs[j].sommets.size())!=0) ){
		k=k-V_obs[j].sommets.size();		
		j++;
	}//end of while loop
        cout<<"ok for i="<<i<<"j="<<j<<"and k="<<k<<endl; 
	//maintenant qu'on a l'obstacle à lequel appartient le ième noeud du chemin optimal,  l'objet point associé au noeud est V_obs[j].sommets[k] 
	//Donc il reste que l'ecriture coordonnées du ième noeud dans un fichier fichier
	ff<<V_obs[j].sommets[k].x<<","<<V_obs[j].sommets[k].y<<";";
	j=0;
}//end of the "i"  for loop

ff.close();
}//end of function
