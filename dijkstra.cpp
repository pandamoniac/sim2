#include <map>

int TrouveMin(std::map<int,int> T, float* l)
{
    int i = T.begin()->first ;
    float v = l[i] ;
    for(std::map<int,int>::iterator it = T.begin(); it != T.end();++it)
    {
        int j = (it->first) ;
        if (l[j]<v)
        {
            v = l[j] ;
            i = j ;
        }
    }
    return(i) ;
}

/*l : liste des distances à 1, de taille n*/
/*p : liste des prédecesseurs, de taille n*/
void Dijkstra(int n, float** c, float* l, int* p)
{
    std::map<int,int> T ; /*sommets non traités*/
    for (int i=1; i<n; i++)
    {
        l[i] = c[0][i] ;
        p[i] = 0 ;
        T.insert(std::pair<int,int>(i,i)) ;
    }

    while (!T.empty())
    {
        int k = TrouveMin(T,l) ;
        T.erase(k) ;
        for(std::map<int,int>::iterator it = T.begin(); it != T.end();++it)
        {
            int j = it->first ;
            if(l[j]>l[k]+c[k][j])
            {
                l[j] = l[k] + c[k][j] ;
                p[j] = k ;
            }
        }
    }
}
