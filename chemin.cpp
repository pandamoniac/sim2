#include <vector>
std::vector<int> Chemin(int n,int* p, int ind) //Renvoie le chemin de ind vers 0
{
    int i = ind ;
    std::vector<int> chemin(1,ind) ;
    while (p[i]!=0)
    {
        chemin.push_back(p[i]) ;
        i = p[i] ;
    }
    chemin.push_back(0) ;
    return(chemin);
}
