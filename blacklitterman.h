//Author: Steven Wang    Date:20151121
#ifndef BLACKLITTERMAN_H_
#define BLACKLITTERMAN_H_

#include <Eigen/Eigen>
#include "portfolio.h"

using namespace std;
using namespace Eigen;

class BlackLitterman {

private:
	MatrixXd excess_return_matrix_;
	MatrixXd expected_excess_return_matrix_;
	MatrixXd variance_excess_matrix_;
	double rate_, tau_, sigma_;
	int num_views_;
	MatrixXd market_weights_;

	MatrixXd views_;
	MatrixXd p_;
	MatrixXd q_;
	MatrixXd o_;

	MatrixXd combined_expected_excess_return_matrix_;
	
	MatrixXd b_l_weights_;
	
public:
	BlackLitterman(portfolio port, int num_assets, int num_observations);
	MatrixXd ComputeWeights();
	
};


#endif