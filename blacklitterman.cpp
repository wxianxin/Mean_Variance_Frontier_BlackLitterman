//Author: Steven Wang    Date:20151121

#include "blacklitterman.h"

BlackLitterman::BlackLitterman(portfolio port, int num_assets, int num_observations)
{
	cout << "Please input the risk-free rate:" << endl;
	cin >> this->rate_;
	
	cout << "Please input the level of accuracy of expected excess returns(tau):" << endl;
	cin>>this->tau_;
	
	cout << "Please input your degree of risk aversion(risk-aversion constant):" << endl;
	cin >> this->sigma_;
	

	this->market_weights_ = MatrixXd(num_assets, 1);
	for (int i = 0; i < num_assets; i++) {
		market_weights_(i, 0) = 1.0 / num_assets;
	}


	this->excess_return_matrix_ = MatrixXd(num_assets, num_observations - 1);
	for (int i = 0; i < num_assets; i++) {
		for (int c = 0; c < num_observations - 1; c++) {
			this->excess_return_matrix_(i, c) = port.GetReturnMatrix()(i, c) - rate_;
		}
	}


	this->expected_excess_return_matrix_ = MatrixXd(num_assets, 1);
	for (int i = 0; i < num_assets; i++) {
		this->expected_excess_return_matrix_(i, 0) = port.GetExpectedReturn()(i, 0) - rate_;
	}


	this->variance_excess_matrix_ = MatrixXd(num_assets, num_assets);
	for (int c = 0; c < num_assets; c++) {
		for (int k = c; k < num_assets; k++) {
			double sum = 0.0;
			for (int n = 0; n < num_observations - 1; n++) {
				sum += excess_return_matrix_(c, n)*excess_return_matrix_(k, n);
			}
			variance_excess_matrix_(c, k) = (sum / (num_observations - 1) - expected_excess_return_matrix_(c, 0)*expected_excess_return_matrix_(k, 0));
		}
	}
	//efficiency: calculate half of the covariance matrix
	for (int c = num_assets - 1; c > 0; c--) {
		for (int k = c - 1; k > -1; k--) {
			variance_excess_matrix_(c, k) = variance_excess_matrix_(k, c);
		}
	}


	cout << "How many views do you have?" << endl;
	cin >> this->num_views_;

	this->views_ = MatrixXd(num_views_, num_assets + 2);
	for (int k = 0; k < num_views_; k++) {
		cout << "Please input view " << k + 1 <<" :" << endl;
		for (int i = 0; i < num_assets + 2; i++) {
			if (i == num_assets) cout << "Please input the relative excess return of this view:" << endl;
			if (i == num_assets + 1) cout << "Please input your level of confidence about this view:" << endl;
			cin >> views_(k, i);
		}
	}

	this->p_ = MatrixXd(num_views_, num_assets);
	this->q_ = MatrixXd(num_views_, 1);
	this->o_ = MatrixXd::Zero(num_views_, num_views_);


	for (int k = 0; k < num_views_; k++) {
		for (int i = 0; i < num_assets; i++) {
			p_(k, i) = views_(k, i);
		}
		q_(k, 0) = views_(k, num_assets);
		o_(k, k) = views_(k, num_assets + 1);
	}

}

MatrixXd BlackLitterman::ComputeWeights()
{

	//u
	this->combined_expected_excess_return_matrix_ = ((tau_*variance_excess_matrix_).inverse() + p_.transpose()*o_.inverse()*p_).inverse()*
		((tau_*variance_excess_matrix_).inverse()*(sigma_*variance_excess_matrix_*market_weights_) + p_.transpose()*o_.inverse()*q_);

	MatrixXd lamda = tau_*(o_.inverse()*q_)*sigma_ - (o_*tau_ + p_*variance_excess_matrix_*p_.transpose()).inverse()*p_*variance_excess_matrix_*market_weights_ -
		(o_*tau_ + p_*variance_excess_matrix_*p_.transpose()).inverse()*p_*variance_excess_matrix_*p_.transpose()*tau_*o_.inverse()*q_*sigma_;


	this->b_l_weights_ = (market_weights_ - p_.transpose()*lamda).transpose();
	
	return b_l_weights_;
}
