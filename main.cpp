// Author: Steven   Date:20151116
#include <iostream>
#include "portfolio.h"
#include "mean_variance_frontier.h"
#include "blacklitterman.h"
#include <iomanip>

using namespace std;

int main()
{
	cout << "Mean-variance frontier:" << endl << endl;
	int num_assets;
	int num_observations;
	double expected_return;

	cout << "Please input the number of assets:" << endl;
	cin >> num_assets;

	cout << "Please input the number of observations:" << endl;
	cin >> num_observations;

	cout << "Please input the expected return of the portfolio:" << endl;
	cin >> expected_return;
	
	portfolio port("data.txt", num_assets, num_observations);

	mean_variance_frontier weights;
	cout << endl <<"The frontier portfolio weights are:" << endl;
	for (int i = 0; i < num_assets; i++)
	{
		cout << setw(11) << port.GetTickers()[i];
	}
	cout << endl;
	cout << weights.ComputeWeights(port, num_assets, num_observations, expected_return) << endl;

//Mean-variance frontier ends
//*******************************************************************************************************
//BlackLitterman begins

	cout << endl << endl << "BLACKLITTERMAN:" << endl << endl;

	BlackLitterman blweights(port, num_assets, num_observations);

	cout << endl << "The portfolio weights of BlackLitterman approach is:" << endl ;

	for (int i = 0; i < num_assets; i++)
	{
		cout << setw(9) << port.GetTickers()[i];
	}
	cout << endl;

	cout << blweights.ComputeWeights() << endl << endl;
			
	return 0;
}