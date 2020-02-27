#include "Neurone.h"
#include "EntreeDonnee.h"

/*
#Nombre neurone couche entree[0]
2
#Nombre neurone couche sortie[1]
2
#Nombre de couche cachee[2]
2
#Nombe de neurone par couche cachee[3]
2
#Type de fonction(0 = Sigmoide, 1 = tanh, 2 = xxx)[4]
1
#Taux d'apprentissage(n)[5]
0.1
#Poids minimum[6]
-0.5
#Poids maximum[7]
0.5
#Seuil minimum[8]
0
#Seuil maximum[9]
100
#Nombre de cycle apprentissage [10]
100
#Nombre de fenetre demandee par base de donnee 30-50-60 habituellement
30
#Nombre parametre/fenetre
12
*/

void CreerReseau(vector<vector<Neurone>> *, double*);
void CalculerValeursFonctionActivation(vector<vector<Neurone>> *);
vector<double> AssignerValeurEntrees(queue<vector<vector<double>>>);
void CalculerRetropropagation(vector<vector<Neurone>> *);
void CalculerSigmaRetropropagation(vector<vector<Neurone>> *);
void CalculerDeltaW(vector<vector<Neurone>> *, double);
void AjusterPoids(vector<vector<Neurone>> *);
void AfficherReseau(vector<vector<Neurone>> *);