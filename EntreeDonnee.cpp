#include "EntreeDonnee.h"

#define NB_PARAMETRE 26

int total_desirer = 30;

enum Method { Energie_Statique, Energie_Dynamique, Interpolation };

vector<vector<double>> get_input(string nom);
vector<double> vector_String_2_Double(vector<string> svec);
vector<vector<double>> Ajust_Input_Parameter(vector<vector<double>> v, int nombre_total, const int total_desirer);
vector<vector<double>> Trie(vector<vector<double>> v, Method method, int nombre_total, int Nb_a_enlever);
vector<vector<double>> Retirer_X_Param(vector<vector<double>> v, int nombre_total, int Nb_a_enlever, int PARAM_TO_DELETE, Method Next_Method);
vector<vector<double>> mean_value(vector<vector<double>> v, int nombre_total, int Nb_a_enlever);
vector<vector<double>> Mean_Value_add(vector<vector<double>> v, int nombre_total, int total_desirer);


queue<vector<vector<double>>> readFile()
{
vector<string> v;
string line;
/*À CHANGER POUR LE BON NOM DU FICHIER
dans le fichier faire un CTR+F sur l'espace + replace with \n
mettre tout les fichiers dans le bon repertoire!!
*/
ifstream myfile ("D:\\Dropbox\\C# Projects\\ReseauNeuron778\\Debug\\info_train.txt");
int nombre_total;
bool GO_READ = 0;
vector<vector<double>> matrix;
vector<vector<double>> matrix2;

queue<vector<vector<double>>> myq;
queue<vector<vector<double>>> myq2;

  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
		if(!GO_READ){
			nombre_total = stoi(line);
			GO_READ=1;
		}
		else if(GO_READ){
			GO_READ=0;
			myq.push(get_input(line));
		}
		/*DEBUG PURPOSE*/
		
    }
    myfile.close();
  }

  else cout << "Unable to open file"; 


  /*DEBUG PURPOSE*/

	return myq;
}

vector<vector<double>> get_input(string nom)
{
vector<string> v;
string line;
ifstream myfile (nom);

vector<vector<double>> matrix;
vector<double> tempo;
double x=0;
int i=0;

  if (myfile.is_open())
  {
	  while ( getline (myfile,line, ' ')  )
    {
		i++;
		v.push_back(line);
		if(i==NB_PARAMETRE){
			i=0;	
			matrix.push_back(vector_String_2_Double(v));
			v.clear();
		}
    }
    myfile.close();
  }

  else cout << "Unable to open file"; 

		/*DEBUG PURPOSE
           cout << matrix[0][0] << " "<<endl;
		   cout << matrix[1][0] << " "<<endl;
		   cout << matrix[62][0] << " "<<endl;
		   //TEST POUR LES VALEURS
		   if(matrix[62][25] == 0)
			   cout<<"OUI"<<endl;
		   else
			   cout<<"NON"<<endl;
		   cout<<matrix.size()<<endl;*/

  //system("pause");
  
  return Ajust_Input_Parameter(matrix, matrix.size(), total_desirer);

}
vector<double> vector_String_2_Double(vector<string> svec){
	vector<double> dvec;
for (auto iter = svec.begin(); iter != svec.end(); ++iter)
{
    std::string const& element = *iter;

    dvec.push_back(stod(element));
}
return dvec;
}


vector<vector<double>> Ajust_Input_Parameter(vector<vector<double>> v, int nombre_total, const int total_desirer){

	int Nb_a_enlever = nombre_total - total_desirer;
	//Plus petit que 0 -> donc il faut en ajouter
	if(Nb_a_enlever < 0){
		v = Mean_Value_add(v,nombre_total,total_desirer);
	}
	//Plus grand que 0 -> il faut en enlever
	else if(Nb_a_enlever > 0){
		v =Trie(v,Energie_Statique,nombre_total,Nb_a_enlever);;
	}
	//Same donc on fait rien
	else
		NULL;

	return v;
}

vector<vector<double>> Trie(vector<vector<double>> v, Method method, int nombre_total, int Nb_a_enlever){

	switch(method){
	case(Energie_Statique) : v = Retirer_X_Param(v,nombre_total,Nb_a_enlever,12,Energie_Dynamique); break;
	case(Energie_Dynamique) : v = Retirer_X_Param(v,nombre_total,Nb_a_enlever,25,Interpolation); break;
	case(Interpolation) : v = mean_value(v,nombre_total,Nb_a_enlever);break;
	default: break;
	}
	return v;
}

vector<vector<double>> Retirer_X_Param(vector<vector<double>> v, int nombre_total, int Nb_a_enlever, int PARAM_TO_DELETE,Method Next_Method){
	bool DONE = 0;
	bool FINISH = 0;
	int i = 0;
	int enlever = 0;

	while(!DONE){
		
		 if(i==v.size()-1){
			DONE = 1;
			Nb_a_enlever = Nb_a_enlever - enlever;
		}
		 else if (v[i][PARAM_TO_DELETE] == 0){
			v.erase(v.begin()+i);
			enlever++;
			if(enlever == Nb_a_enlever){
				DONE = 1;
				FINISH = 1;
			}
		}
		else
			i++;
		
	
	}

	if(!FINISH)
		return Trie(v,Next_Method, v.size(), Nb_a_enlever);
	else
	{
		return v;
	}

}

vector<vector<double>> mean_value(vector<vector<double>> v, int nombre_total, int Nb_a_enlever){

	int TODO = v.size()-Nb_a_enlever;
	int i=0,j = 0;
	double Somme=0;
	while(j<=NB_PARAMETRE-1){

		Somme += v[nombre_total-i-1][j]; 

		if(i==Nb_a_enlever){
			v[nombre_total-i-1][j] = Somme/Nb_a_enlever;
			Somme = 0;
			j++;
			i=0;
		}
		else
			i++;
	}

	v.erase(v.begin()+TODO,v.begin()+v.size());

	return v;

}

//																		50				60
vector<vector<double>> Mean_Value_add(vector<vector<double>> v, int nombre_total, int total_desirer){
	
	int TODO = total_desirer - nombre_total;	//10
	int Paquet = int(floor(nombre_total/TODO));		//5
	double Somme = 0;

	vector<double> temp;
for(int w = 0; w < TODO; w++){
	for(int j=0;j<NB_PARAMETRE;j++){
		for(int i=0;i<Paquet;i++){
			Somme += v[i][j];
		}	
		temp.push_back(Somme/Paquet);
		Somme = 0;
		
	}
	v.push_back(temp);
	temp.clear();
}
return v;
}