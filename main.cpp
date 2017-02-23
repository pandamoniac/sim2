#include <iostream>
#include "dijkstra.hpp"
#include "chemin.hpp"
#include <map>
#include <vector>
using namespace std;

int main()
{
    /*Test 1 dijkstra (OK)*/
//    int* p = new int[3] ;
//    float* l = new float[3] ;
//    float* c1 = new float[3] ;
//    c1[0] = 0 ;
//    c1[1] = 1 ;
//    c1[2] = 4 ;
//    float* c2 = new float[3] ;
//    c2[0] = 1 ;
//    c2[1] = 0 ;
//    c2[2] = 2 ;
//    float* c3 = new float[3] ;
//    c3[0] = 4 ;
//    c3[1] = 2 ;
//    c3[2] = 0 ;
//    float** c = new float*[3] ;
//    c[0] = c1 ;
//    c[1] = c2 ;
//    c[2] = c3 ;
//    Dijkstra(3,c,l,p) ;
//    cout<<l[0]<<l[1]<<l[2] ;
//    cout<<p[0]<<p[1]<<p[2] ;

    /*Test 2 dijkstra (0K)*/
    int n = 6 ;
    int* p = new int[6] ;
    float* l = new float[6] ;
    float c1[6] = {0,3,7,4,3,30} ;
    float c2[6] = {3,0,2,1,2,13} ;
    float c3[6] = {7,2,0,8,9,14};
    float c4[6] = {4,1,8,0,12,12} ;
    float c5[6] = {3,2,9,12,0,2};
    float c6[6] = {30,13,14,12,2,0} ;
    float* c[6] = {c1,c2,c3,c4,c5,c6};
    Dijkstra(6,c,l,p) ;
    for (int i=0; i<n; i++) {cout<<l[i];}
    cout<<"\n" ;
    for (int i=0; i<n; i++) {cout<<p[i];}

    /*Test chemin (OK)*/
    std::vector<int> chemin ;
    chemin = Chemin(6,p,5);
    cout<<"\n" ;
    for (int i=0; i<chemin.size(); i++) {cout<<chemin[i];}
    return 0;
}
