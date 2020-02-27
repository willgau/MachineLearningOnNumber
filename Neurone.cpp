#include <math.h>
#include <time.h>

#include "Neurone.h"

using namespace std;


double Init_Seuil(double min, double max)
{
	if (INIT_SEUIL)
	{
		return 0;
	}
	else
	{
		int range = (max-min * 10000);
		return (((rand() % range) - (range /2.0))/10000.0);//A valider valeur min/max seuils
	}
}
void Init_Poids(Neurone* neurone, double min, double max)
{
	int range = (max - min)*10000.0;
	for (int i = 0; i < neurone->nombreNeuroneCoucheSuivante; i++)
	{
		neurone->poidsSortie.push_back(((rand() % range) - (range / 2.0))/10000);
		neurone->deltaWNew.push_back(0);
		neurone->deltaWOld.push_back(0);
	}
}

void Init_Neurone(Neurone* neurone, double poidsMin, double poidsMax, double seuilMin, double seuilMax, double fonction)
{
	neurone->seuil = Init_Seuil(-10, 10);
	Init_Poids(neurone, -0.1,0.1);
	neurone->fonctionActivation = (int)fonction;
	neurone->valeur =0;
	neurone->outputActivation = 1;
	neurone->outputDesire = 0;
	neurone->sigma = 0;
}
