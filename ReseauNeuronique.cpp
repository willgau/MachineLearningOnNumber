#include "ReseauNeuronique.h"

double eta = 0;
void CreerReseau(vector<vector<Neurone>> *reseau, double* config)
{
	queue<vector<vector<double>>> queueEntrees = readFile();
	vector<double> entrees = AssignerValeurEntrees(queueEntrees);
	int nombreDeCoucheCachee = (int)config[2];
	eta = config[5];

	for (int j = 0; j < nombreDeCoucheCachee + 2; j++)
	{
		vector<Neurone> couche;
		reseau->push_back(couche);
	}
	//Creer couche entree j=0
	for (int k = 0; k < config[0]; k++)//config[0]=Nb neurone couche entree
	{
		Neurone neurone;
		reseau[0][0].push_back(neurone);
		reseau[0][0][k].nombreNeuroneCoucheSuivante = config[3];
		reseau[0][0][k].numeroDeCouche = 0;
		Init_Neurone(&reseau[0][0][k], config[6], config[7], config[8], config[9], config[4]);		
	}
	//Assigner valeurs entrees
	for (int l = 0; l < entrees.size(); l++)
	{
		reseau[0][0][l].outputActivation = entrees[l];
	}
	
	//Creer couche sortie j=x+1
	for (int k = 0; k < config[1]; k++)//config[1]=Nb neurone couche sortie
	{
		Neurone neurone;
		reseau[0][nombreDeCoucheCachee + 1].push_back(neurone);
		reseau[0][nombreDeCoucheCachee + 1][k].nombreNeuroneCoucheSuivante = 0;
		reseau[0][nombreDeCoucheCachee + 1][k].numeroDeCouche = nombreDeCoucheCachee + 1;
		Init_Neurone(&reseau[0][nombreDeCoucheCachee + 1][k], config[6], config[7], config[8], config[9], config[4]);
	}
	//Creer couche cachee j=x
	for (int j = 0; j < nombreDeCoucheCachee - 1; j++)//-1 car derniere couche cachee differente puisque prochaine couche n'est pas cachee
	{
		for (int k = 0; k < (int)config[3]; k++)//config[3]=Nb neurone couche cachee
		{
			Neurone neurone;
			reseau[0][j + 1].push_back(neurone);
			reseau[0][j + 1][k].nombreNeuroneCoucheSuivante = config[3];
			reseau[0][j + 1][k].numeroDeCouche = j + 1;
			Init_Neurone(&reseau[0][j + 1][k], config[6], config[7], config[8], config[9], config[4]);
		}
		//Derniere couche cachee, le nombre de neurone couche suivante = config[1]		
	}
	for (int k = 0; k < config[3]; k++)//config[3]=Nb neurone couche cachee
	{
		Neurone neurone;
		reseau[0][nombreDeCoucheCachee].push_back(neurone);
		reseau[0][nombreDeCoucheCachee][k].nombreNeuroneCoucheSuivante = config[1];
		reseau[0][nombreDeCoucheCachee][k].numeroDeCouche = nombreDeCoucheCachee;
		Init_Neurone(&reseau[0][nombreDeCoucheCachee][k], config[6], config[7], config[8], config[9], config[4]);
	}
}
void CalculerValeursFonctionActivation(vector<vector<Neurone>> *reseau)//forward
{
	cout << "*********************CALCUL F(a)*********************" << endl;
	//Valeurs entree doivent avoir ete assignees avant
	double sommeWiXi = 0;
	for (int j = 1; j < reseau->size(); j++)
	{
		sommeWiXi = 0;
		//cout << endl << "COUCHE #" << j << endl;
		for (int k = 0; k < reseau[0][j].size(); k++)
		{
			sommeWiXi = 0;
			for (int l = 0; l < reseau[0][j - 1].size(); l++)
			{
				sommeWiXi += reseau[0][j - 1][l].poidsSortie[k] * reseau[0][j - 1][l].outputActivation;
			}
			if (reseau[0][j][k].fonctionActivation == 0)//Sigmo 1/(1+e^-iip)
			{
				sommeWiXi += reseau[0][j][k].seuil;
				reseau[0][j][k].valeur = sommeWiXi;
				reseau[0][j][k].outputActivation = ((exp(reseau[0][j][k].valeur)) / (exp(reseau[0][j][k].valeur) + 1));
		//		cout << "output pour couche#" << j << "  Neurone#" << k << ":    " << reseau[0][j][k].outputActivation << endl;
			}
			else if (reseau[0][j][k].fonctionActivation == 1)//tanh
			{

			}
			else if (reseau[0][j][k].fonctionActivation == 2)//Autre
			{

			}

		}
	}

}
void CalculerRetropropagation(vector<vector<Neurone>> *reseau)//backwards
{
	CalculerSigmaRetropropagation(reseau);
	CalculerDeltaW(reseau, eta);
	AjusterPoids(reseau);
}
void CalculerSigmaRetropropagation(vector<vector<Neurone>> *reseau)
{
	cout << "*********************RETROPROPAGATION*********************" << endl;
	double sigma = 0;
	double sommeWiXj = 0;
	for (int j = reseau->size() - 1; j > -1; j--)
	{
		sigma = 0;
	//	cout << endl << "COUCHE #" << j << endl;
		if (j == reseau->size() - 1)
		{
			for (int k = 0; k < reseau[0][j].size(); k++)
			{
		//		cout << endl << "NEURONE #" << k << endl;
				sigma = ((reseau[0][j][k].outputDesire - reseau[0][j][k].outputActivation)*((reseau[0][j][k].outputActivation)*(1 - reseau[0][j][k].outputActivation)));
				reseau[0][j][k].sigma = sigma;
		//		cout << endl << "SIGMA = " << sigma << endl;
			}
		}
		else
		{
			for (int k = 0; k < reseau[0][j].size(); k++)
			{
		//		cout << endl << "NEURONE #" << k << endl;
				for (int l = 0; l < reseau[0][j][k].poidsSortie.size(); l++)
				{
					sommeWiXj += reseau[0][j][k].poidsSortie[l] * reseau[0][j + 1][l].sigma;
					sigma = ((reseau[0][j][k].outputActivation)*(1 - reseau[0][j][k].outputActivation)) * sommeWiXj;
				}
				reseau[0][j][k].sigma = sigma;
			//	cout << endl << "SIGMA = " << sigma << endl;
			}
		}
	}
}
void CalculerDeltaW(vector<vector<Neurone>> *reseau, double eta)
{
	cout << "*********************DELTAW*********************" << endl;
	//Valeurs entree doivent avoir ete assignees avant
	for (int j = 0; j < reseau->size() - 1; j++)
	{
	//	cout << endl << "COUCHE #" << j << endl;
		for (int k = 0; k < reseau[0][j].size(); k++)
		{
	//		cout << endl << "NEURONE #" << k << endl;
			for (int l = 0; l < reseau[0][j + 1].size(); l++)
			{
				reseau[0][j][k].deltaWNew[l] = eta * reseau[0][j + 1][l].sigma *reseau[0][j][k].outputActivation;
	//			cout << "DeltaW " << l << " : " << reseau[0][j][k].deltaWNew[l] << endl;
			}
			reseau[0][j][k].deltaWOld = reseau[0][j][k].deltaWNew;
		}
	}
}
void AjusterPoids(vector<vector<Neurone>> *reseau)
{
	cout << "*********************MaJ DES POIDS********************" << endl;
	for (int j = 0; j < reseau->size() - 1; j++)
	{
	//	cout << endl << "COUCHE #" << j << endl;
		for (int k = 0; k < reseau[0][j].size(); k++)
		{
	//		cout << endl << "NEURONE #" << k << endl;
			for (int l = 0; l < reseau[0][j + 1].size(); l++)
			{
				reseau[0][j][k].poidsSortie[l] = reseau[0][j][k].poidsSortie[l] + reseau[0][j][k].deltaWNew[l];
	//			cout << "Poids " << l << " : " << reseau[0][j][k].poidsSortie[l] << endl;
			}
		}
	}

}
void AfficherReseau(vector<vector<Neurone>> *reseau)
{
	for (int j = 0; j < reseau[0].size(); j++)
	{
	//	cout << endl << "COUCHE #" << j << endl << endl;
		for (int k = 0; k < reseau[0][j].size(); k++)
		{
	//		cout << "NEURONE #" << k << endl;			
			for (int l = 0; l < reseau[0][j][k].poidsSortie.size(); l++)
			{
	//			cout << "POIDS #" << l << endl;
				cout << reseau[0][j][k].poidsSortie[l] << endl;
			}
		}
	}
}
vector<double> AssignerValeurEntrees(queue<vector<vector<double>>> queueEntree)
{
	vector<vector<double>> queueVector = queueEntree.front();
	vector<double> entree;
	for (int i = 0; i < queueVector.size();i++)
	{
		for (int j = 0; j < 12; j++)//12 = nombre para
		{
			entree.push_back(queueVector[i][j]);
		}
	}
	return entree;
}