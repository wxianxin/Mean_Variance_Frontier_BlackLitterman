//Author: Steven Wang    Date:20151120

#ifndef MEAN_VARIANCE_FRONTIER_H
#define MEAN_VARIANCE_FRONTIER_H

#include <vector>
#include "portfolio.h"

using namespace std;
using namespace Eigen;

class mean_variance_frontier {
private:
	MatrixXd weights_;

public:
	MatrixXd ComputeWeights(portfolio port, int num_assets, int num_observations, double expected_return);
};


#endif