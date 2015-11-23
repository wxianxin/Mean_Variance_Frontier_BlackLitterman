//Author: Steven Wang    Date:20151120

#ifndef PORTFOLIO_H_
#define PORTFOLIO_H_

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <Eigen/Eigen>

using namespace std;
using namespace Eigen;

class portfolio {
private:
	int num_assets_, num_observations_;
	vector<string> tickers_;
	MatrixXd price_matrix_;
	MatrixXd return_matrix_;
	MatrixXd expected_return_matrix_;
	MatrixXd variance_matrix_;

public:
	portfolio(string fileName, int numofAssets, int numofObservations);
	MatrixXd GetExpectedReturn();
	MatrixXd GetVarianceMatrix();
	vector<string> GetTickers();
	MatrixXd GetReturnMatrix();

};


#endif