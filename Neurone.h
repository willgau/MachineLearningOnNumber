#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

#define INIT_SEUIL 1


struct Neurone
{
	int numeroDeCouche;
	int nombreNeuroneCoucheSuivante;
	int fonctionActivation;

	double seuil;
	double valeur; //i de la couche
	double sigma;
	vector<double> deltaWOld;
	vector<double> deltaWNew;
	double outputActivation;//Sortie apres fonction activation.
	double outputDesire;//Seulement sur couche sortie

	vector<double> poidsSortie;

};

void Init_Neurone(Neurone*,double,double,double,double,double);
void CreerCouche(vector<Neurone>*);