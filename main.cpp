#include <iostream>
#include "dijkstra.hpp"
#include "chemin.hpp"
//Include finaux à ajouter
#include <map>
#include <vector>
using namespace std;

int main()
{
    //Lecture fichier et création de V_obs, vecteur des obstacles et de N, le nombre d'obstacles
    vector<obstacle> V_obs;
    int N ;
    lecture_obstacles(test_path,V_obs,N);
    //Transformation des obstacles en matrice de poids
    M = distance_matrix(V_obs, N);
    //Recherche du plus court chemin à partir de la matrice des poids
    float* l = new float[N] ;
    int* p = new int[N] ;
    Dijkstra(N,M.matrix,l,p) ;
    Chemin(N, p, N-1) ;
    //Ecriture dans fichier
    //A FAIRE
    //Affichage
    system("matlab -nodekstop \n affichage") ;

}
