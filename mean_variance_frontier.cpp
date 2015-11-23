//Author: Steven Wang    Date:20151120

#include "mean_variance_frontier.h"

MatrixXd mean_variance_frontier::ComputeWeights(portfolio port, int num_assets, int num_observations, double expected_return) {
	MatrixXd i = MatrixXd(num_assets, 1);
	for (int c = 0; c < num_assets; c++)
	{
		i(c, 0) = 1.0;
	}

	MatrixXd A = i.transpose() * port.GetVarianceMatrix().inverse() * port.GetExpectedReturn();
	MatrixXd B = port.GetExpectedReturn().transpose() * port.GetVarianceMatrix().inverse() * port.GetExpectedReturn();
	MatrixXd C = i.transpose() * port.GetVarianceMatrix().inverse() * i;
	MatrixXd D = B*C - A*A;
	MatrixXd g = D.inverse()*(B*i.transpose() - A*port.GetExpectedReturn().transpose())*port.GetVarianceMatrix().inverse();
	MatrixXd h = D.inverse()*(C*port.GetExpectedReturn().transpose() - A*i.transpose())*port.GetVarianceMatrix().inverse();

	this->weights_ = g + h*expected_return;
	
	return weights_;

}



