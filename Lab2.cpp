#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <time.h>
#include <math.h>

#include "ReseauNeuronique.h"

using namespace std;

int xyz()
{
	double config[12] = {360,10,50,50,0,0.1,-0.5,0.5,0,100,10,30};
	vector<vector<Neurone>> reseau;
	clock_t t;
	srand(time(NULL));
	t = clock();

	CreerReseau(&reseau, config);
	//AfficherReseau(&reseau);
	for (int i = 0; i < config[10] ; i++)//nb cycles apprentissage
	{
		CalculerValeursFonctionActivation(&reseau);
		CalculerRetropropagation(&reseau);
	}
	
	t = clock() - t;
	double time_taken = ((double)t) / CLOCKS_PER_SEC;
	cout << "Time elapsed : " << time_taken << " seconds" << endl;

	system("PAUSE");

	return EXIT_SUCCESS;
}
