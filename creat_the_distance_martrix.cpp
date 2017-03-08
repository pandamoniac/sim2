#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;



class point {
public:
	float x;
	float y;
	bool operator==(const point& A) { return((A.x == x) && (A.y == y)); }
};
/*---------------------------------------------------------------*/
class obstacle {
public:
	int n_sommets; //nombre de sommets
	vector<point> sommets;
}; //fin classe obstacle


   /**************************************************************************************************/


float min(float x, float y) {
	if (x<y) return(x); else return(y);
}



float max(float x, float y) {
	if (x>y) return(x); else return(y);
}




float* equation_droite(float xa, float ya, float xb, float yb) { //passant par deux points A et B, sous la forme ax+by+c=0

	float* E = new float[3];
	E[0] = yb - ya; //coefficient a
	E[1] = xa - xb; //coefficient b
	E[2] = ya*xb - xa*yb; //coefficient c
	return(E);
}

bool point_in_segment(point A, point B, point C) { //retourne true si C dans [AB], false sinon
	return((C.x <= max(A.x, B.x)) && (C.x >= min(A.x, B.x)) && (C.y <= max(A.y, B.y)) && (C.y >= min(A.y, B.y)));
}




bool intersection_segments(point A1, point B1, point A2, point B2) { //[A1,B1] et [A2,B2]
	float* E1 = equation_droite(A1.x, A1.y, B1.x, B1.y);
	float* E2 = equation_droite(A2.x, A2.y, B2.x, B2.y);

	if ((E1[0] * E2[1] - E2[0] * E1[1] == 0) || (E1[1] * E2[0] - E2[1] * E1[0] == 0)) {
		/*if( (x<=max(xa1,xb1)) && (x>=min(xa1,xb1)) && (y<=max(ya1,yb1)) && (y>=min(ya1,yb1)) || )*/ return(false);
	}
	else {
		point int_point; //point intersection entre les deux segments
		int_point.x = (E1[1] * E2[2] - E2[1] * E1[2]) / (E1[0] * E2[1] - E2[0] * E1[1]); // coordonnées pt d'intersection
		int_point.y = (E2[2] * E1[0] - E2[0] * E1[2]) / (E1[1] * E2[0] - E2[1] * E1[0]); // coordonnées pt d'intersection
		if ((point_in_segment(A1, B1, int_point)) && (point_in_segment(A2, B2, int_point))) {

			if ((int_point == A1) || (int_point == A2) || (int_point == B1) || (int_point == B2)) return(false); else return(true);
		}
		else return(false);

	}

}//fin intersection_segments



void lecture_obstacles(char* path, vector<obstacle>& V_obs, int& N) {
	fstream ff(path, ios::out | ios::in);
	//ff.open(path,ios::out | ios::in);
	char c;
	char k;
	point temp_p;
	string temp = "";
	int k_temp = 0; //nombre de points d'obstacle
	obstacle temp_obs;
	while (ff >> noskipws >> c) {
		if ((c != ',') && (c != ';') && (c != '\n')) { temp = temp + c; }
		else if (c == ',') { temp_p.x = stof(temp); temp.clear(); }
		else if (c == ';') { temp_p.y = stof(temp); temp.clear(); temp_obs.sommets.push_back(temp_p); k_temp++; /*stock nouvelle point dans une struc*/ }
		else { N++; temp_obs.n_sommets = k_temp; /*modification du tableau d'obstacles*/ V_obs.push_back(temp_obs); k_temp = 0; temp_obs.sommets.clear(); }






	} //end while

} //end lecture

point point_dep() {
	point p_dep;
	cout << "Donner les coordonnées du point de départ : " << endl;
	cout << "x= ";
	cin >> p_dep.x;
	cout << "y= ";
	cin >> p_dep.y;
	return (p_dep);
}

point point_arr() {
	point p_arr;
	cout << "Donner les coordonnées du point d'arrivée : " << endl;
	cout << "x= ";
	cin >> p_arr.x;
	cout << "y= ";
	cin >> p_arr.y;
	return (p_arr);
}








bool intersection_new(point A1, point B1, point A2, point B2) { //for judge the diagonal cross the polygon 
	float* E1 = equation_droite(A1.x, A1.y, B1.x, B1.y);
	float* E2 = equation_droite(A2.x, A2.y, B2.x, B2.y);

	if ((E1[0] * E2[1] - E2[0] * E1[1] == 0) || (E1[1] * E2[0] - E2[1] * E1[0] == 0)) {
		/*if( (x<=max(xa1,xb1)) && (x>=min(xa1,xb1)) && (y<=max(ya1,yb1)) && (y>=min(ya1,yb1)) || )*/ return(false);
	}
	else {
		point int_point; //point intersection entre les deux segments
		int_point.x = (E1[1] * E2[2] - E2[1] * E1[2]) / (E1[0] * E2[1] - E2[0] * E1[1]); // coordonnées pt d'intersection
		int_point.y = (E2[2] * E1[0] - E2[0] * E1[2]) / (E1[1] * E2[0] - E2[1] * E1[0]); // coordonnées pt d'intersection
		if ((point_in_segment(A1, B1, int_point)) && (point_in_segment(A2, B2, int_point))) {
			if ((int_point == A1 && int_point == A2) || (int_point == A1 && int_point == B2) || (int_point == A2 && int_point == B1) || (int_point == B1 && int_point == B2)) return(false); else return(true);
		}
		else return(false);

	}

}

bool directly_reachable(point A, point B, obstacle& obs)	//Si l'obstacle obs bloque le segment AB
{
	for (int i = 0; i < obs.n_sommets - 1; i++)
	{
		if (intersection_new(A, B, obs.sommets[i], obs.sommets[i + 1]))
		{
			return false;
		}
	}
	if (intersection_new(A, B, obs.sommets[obs.n_sommets - 1], obs.sommets[0]))

		return false;
	return true;
}

bool directly_reachable(point A, point B, vector<obstacle>& V_obs, int N) //Si les obstacles bloquent le segment AB 
{
	for (int i = 0; i < N; i++)
	{
		if (!directly_reachable(A, B, V_obs[i]))
			return false;
	}
	return true;

}

double point_prod(const point A, const point B, const point C)//calcul the scalar product
{
	double vec_1x = A.x - B.x;
	double vec_2x = C.x - B.x;
	double vec_1y = A.y - B.y;
	double vec_2y = C.y - B.y;
	return vec_1x * vec_2x + vec_1y * vec_2y;
}

double cross_prod(const point A, const point B, const point C)//calcul the cross product
{
	double vec_1x = A.x - B.x;
	double vec_2x = C.x - B.x;
	double vec_1y = A.y - B.y;
	double vec_2y = C.y - B.y;
	return vec_1x * vec_2y - vec_2x * vec_1y;
}

double norm(const point A, const point B)//calcul the norm
{
	double vec_x = A.x - B.x;
	double vec_y = A.y - B.y;
	return sqrt(vec_x*vec_x + vec_y*vec_y);
}

bool superior_angle(const point A, const point B, const point C) // judge whether the angle is bigger than 180 degree.
{
	if (cross_prod(A, B, C) < 0)
		return true;
	return false;
}


bool in(const point A, const point B, const point C, const point D)//judge whether BD is in the polygon.
{
	if (superior_angle(A, B, D) && superior_angle(D, B, C))
		return true;
	else if (!superior_angle(A, B, C))
	{
		double alpha = acos(point_prod(A, B, D) / norm(A, B) / norm(D, B));
		double beta = acos(point_prod(D, B, C) / norm(D, B) / norm(C, B));
		double gamma = acos(point_prod(A, B, C) / norm(A, B) / norm(C, B));
		if ((alpha == beta + gamma) || (beta == alpha + gamma))
			return true;
		return false;
	}
	return false;
}





#define INFINITY 1e10;
struct vertex_mapping	//Pour lier le sommet dans la matrice de distance et le sommet de quelle obstacle
{
	int obstacle_number;
	int point_number;
};

class distance_matrix	//Enregistrer l'information de distance
{
public:
	double** matrix;	//La matrice de distance
	int nombre_sommet;	//le nombre de sommet
	int nb_matrix;
	vector<vertex_mapping> vertice;	//Pour lier le sommet dans la matrice de distance et le sommet de quelle obstacle

	distance_matrix(point p_dep, point p_arr, vector<obstacle>& V_obs, int N);	//Construire la matrice
	void display();
	void display_vertax_mapping();
	~distance_matrix();
};

distance_matrix::distance_matrix(point p_dep, point p_arr, vector<obstacle>& V_obs, int N)
{
	nombre_sommet = 0;
	for (int i = 0; i < N; i++)	//Compter les sommets
	{
		nombre_sommet += V_obs[i].n_sommets;
	}
	nb_matrix = nombre_sommet + 2;
	matrix = new double*[nb_matrix];
	//Creer l'assemblé  de 2D
	for (int i = 0; i <nb_matrix; i++)
	{
		matrix[i] = new double[nb_matrix];
	}
	int obstacle_count = 0;
	int point_count = 0;


	vertex_mapping temp_vertex;
	for (int i = 0; i < nombre_sommet; )	//Construire le lien entre les sommets de matrice et les sommets des obstacles
	{
		if (point_count < V_obs[obstacle_count].n_sommets)
		{
			temp_vertex.obstacle_number = obstacle_count;
			temp_vertex.point_number = point_count;
			vertice.push_back(temp_vertex);
			point_count++;
			i++;
		}
		else
		{
			obstacle_count++;
			point_count = 0;
		}
	}


	display_vertax_mapping();	//Seulement pour debugging

	double delta_x, delta_y;
	for (int i = 0; i < nombre_sommet; i++)
	{
		if (directly_reachable(p_dep, V_obs[vertice[i].obstacle_number].sommets[vertice[i].point_number], V_obs, N))
		{
			delta_x = p_dep.x - V_obs[vertice[i].obstacle_number].sommets[vertice[i].point_number].x;
			delta_y = p_dep.y - V_obs[vertice[i].obstacle_number].sommets[vertice[i].point_number].y;
			matrix[0][i + 1] = sqrt(delta_x*delta_x + delta_y*delta_y);
		}
		else matrix[0][i + 1] = INFINITY + 1;
	}
	if (directly_reachable(p_dep, p_arr, V_obs, N))
	{
		matrix[0][nb_matrix - 1] = sqrt((p_dep.x - p_arr.x)*(p_dep.x - p_arr.x) + (p_arr.x - p_arr.y)*(p_arr.x - p_arr.y));
	}
	else matrix[0][nb_matrix - 1] = INFINITY + 1;
	matrix[0][0] = 0;
	for (int i = 0; i < nb_matrix; i++)
	{
		matrix[i][0] = matrix[0][i];
	}

	for (int i = 0; i < nombre_sommet; i++)
	{
		if (directly_reachable(p_arr, V_obs[vertice[i].obstacle_number].sommets[vertice[i].point_number], V_obs, N))
		{
			delta_x = p_arr.x - V_obs[vertice[i].obstacle_number].sommets[vertice[i].point_number].x;
			delta_y = p_arr.y - V_obs[vertice[i].obstacle_number].sommets[vertice[i].point_number].y;
			matrix[nb_matrix - 1][i + 1] = sqrt(delta_x*delta_x + delta_y*delta_y);
		}
		else matrix[nb_matrix - 1][i + 1] = INFINITY + 1;
	}

	matrix[nb_matrix - 1][nb_matrix - 1] = 0;
	for (int i = 0; i < nb_matrix; i++)
		matrix[i][nb_matrix - 1] = matrix[nb_matrix - 1][i];

	for (int i = 0; i < nombre_sommet; i++)	//Calculer la matrice
	{
		for (int j = 0; j < nombre_sommet; j++)
		{
			if (directly_reachable(V_obs[vertice[i].obstacle_number].sommets[vertice[i].point_number], V_obs[vertice[j].obstacle_number].sommets[vertice[j].point_number], V_obs, N))
				//Si les deux points peuvent lient sans traverser les bords des obstacles
			{
				delta_x = V_obs[vertice[i].obstacle_number].sommets[vertice[i].point_number].x - V_obs[vertice[j].obstacle_number].sommets[vertice[j].point_number].x;
				delta_y = V_obs[vertice[i].obstacle_number].sommets[vertice[i].point_number].y - V_obs[vertice[j].obstacle_number].sommets[vertice[j].point_number].y;
				matrix[i + 1][j + 1] = sqrt(delta_x*delta_x + delta_y*delta_y);
			}
			else
				matrix[i + 1][j + 1] = INFINITY + 1;
		}
	}

	for (int i = 0; i < N; i++)
	{
		int nom = 0;
		for (int j = 1; j < V_obs[i].n_sommets - 1; j++)
		{
			int nom_j = nom + j;
			for (int k = 0; k < V_obs[i].n_sommets; k++)
			{
				int nom_k = nom + k;
				if (in(V_obs[vertice[nom_j - 1].obstacle_number].sommets[vertice[nom_j - 1].point_number], V_obs[vertice[nom_j].obstacle_number].sommets[vertice[nom_j].point_number], V_obs[vertice[nom_j + 1].obstacle_number].sommets[vertice[nom_j + 1].point_number], V_obs[vertice[nom_k].obstacle_number].sommets[vertice[nom_k].point_number]))
					matrix[nom_j + 1][nom_k + 1] = INFINITY + 1;
			}
		}



		for (int h = 0; h < V_obs[i].n_sommets; h++)
		{
			int nom_h = nom + h;
			if (in(V_obs[vertice[nom + V_obs[i].n_sommets - 1].obstacle_number].sommets[vertice[nom + V_obs[i].n_sommets - 1].point_number], V_obs[vertice[nom].obstacle_number].sommets[vertice[nom].point_number], V_obs[vertice[nom + 1].obstacle_number].sommets[vertice[nom + 1].point_number], V_obs[vertice[nom_h].obstacle_number].sommets[vertice[nom_h].point_number]))
				matrix[nom + 1][nom_h + 1] = INFINITY + 1;
			if (in(V_obs[vertice[nom + V_obs[i].n_sommets - 2].obstacle_number].sommets[vertice[nom + V_obs[i].n_sommets - 2].point_number], V_obs[vertice[nom + V_obs[i].n_sommets - 1].obstacle_number].sommets[vertice[nom + V_obs[i].n_sommets - 1].point_number], V_obs[vertice[nom].obstacle_number].sommets[vertice[nom].point_number], V_obs[vertice[nom_h].obstacle_number].sommets[vertice[nom_h].point_number]))

				matrix[nom + V_obs[i].n_sommets][nom_h + 1] = INFINITY + 1;
		}
		nom += V_obs[i].n_sommets - 1;
	}
}



void distance_matrix::display()
{
	for (int i = 0; i < nb_matrix; i++)
	{
		for (int j = 0; j < nb_matrix; j++)
		{

			cout << matrix[i][j] << "\t";

		}
		cout << endl;
	}
}

void distance_matrix::display_vertax_mapping()
{
	for (int i = 0; i < nombre_sommet; i++)
	{
		cout << i << "\tobstacle" << vertice[i].obstacle_number << "\tpoint" << vertice[i].point_number << endl;
	}
}




distance_matrix::~distance_matrix()
{
	for (int i = 0; i < nb_matrix; i++)
	{
		delete[] matrix[i];
	}
	delete[] matrix;
}



int main() {
	//test de la fonction intersection_segments
	point A1, B1, A2, B2;
	A1.x = 1; A1.y = 1;
	B1.x = 4; B1.y = 2;
	A2.x = 3; A2.y = 1;
	B2.x = 4; B2.y = 4;



	cout << intersection_segments(A1, B1, A2, B2) << endl;

	char test_path[] = "obstacles.txt";
	int N = 0;
	vector<obstacle> V_obs;
	lecture_obstacles(test_path, V_obs, N);
	cout << N << endl;
	/*cout << V_obs[6].n_sommets << " , " << V_obs[6].sommets[3].x << "  " << V_obs[6].sommets[3].y << endl;*/
	//Lecture point de depart point d'arrivée


	point p_dep, p_arr;
	p_dep = point_dep();
	p_arr = point_arr();



	system("pause");


	distance_matrix dist_matrix(p_dep, p_arr, V_obs, N);
	dist_matrix.display();	//Seulement pour debugging


	system("pause");

	return(0);
}
