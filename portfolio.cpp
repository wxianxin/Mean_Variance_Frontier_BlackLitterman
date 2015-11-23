//Author: Steven Wang    Date:20151120

#include "portfolio.h"

portfolio::portfolio(string fileName, int num_assets, int num_observations) {
	
	this->num_assets_ = num_assets;
	this->num_observations_ = num_observations;

	ifstream infile;
	infile.open("data.txt");
	
	//use cerr instead of cout, to output error message
	if (infile.fail()) {
		cerr << "Error Opening File" << endl;
		exit(1);
	}

	string tempTicker;


	for (int i = 0; i < this->num_assets_; i++) {
		infile >> tempTicker;
		this->tickers_.push_back(tempTicker);
	}


	this->price_matrix_ = MatrixXd(num_assets, num_observations);
	for (int c = 0; c < this->num_observations_; c++) {
		for (int i = 0; i < this->num_assets_; i++) {
			infile >> this->price_matrix_(i, c);
		}
	}


	this->return_matrix_ = MatrixXd(num_assets, num_observations - 1);
	for (int i = 0; i < this->num_assets_; i++) {
		for (int c = 0; c < this->num_observations_ - 1; c++) {
			this->return_matrix_(i, c) = (this->price_matrix_(i, c + 1) - this->price_matrix_(i, c)) / this->price_matrix_(i, c);
		}
	}


	this->expected_return_matrix_ = MatrixXd(num_assets, 1);
	for (int i = 0; i < num_assets; i++) {
		double sum = 0.0;
		for (int c = 0; c < num_observations - 1; c++) {
			sum += return_matrix_(i, c);
		}
		this->expected_return_matrix_(i, 0) = sum / (num_observations - 1);
	}


	this->variance_matrix_ = MatrixXd(num_assets, num_assets);
	for (int c = 0; c < num_assets; c++) {
		for (int k = c; k < num_assets; k++) {
			double sum = 0.0;
			for (int n = 0; n < num_observations - 1; n++) {
				sum += return_matrix_(c, n)*return_matrix_(k, n);
				//sum += (return_matrix_(c, n) - expected_return_matrix(c, 0))*(return_matrix_(k, n) - expected_return_matrix(k, 0));
			}
			//variance_matrix_(c, k) = sum / (num_observations - 1);
			variance_matrix_(c, k) = (sum / (num_observations - 1) - expected_return_matrix_(c, 0)*expected_return_matrix_(k, 0));
		}
	}
	//efficiency: calculate half of the covariance matrix
	for (int c = num_assets - 1; c > 0; c--) {
		for (int k = c - 1; k > -1; k--) {
			variance_matrix_(c, k) = variance_matrix_(k, c);
		}
	}
	
}

MatrixXd portfolio::GetExpectedReturn()
{
	return	this->expected_return_matrix_;
}

MatrixXd portfolio::GetVarianceMatrix()
{
	return this->variance_matrix_;
}

vector<string> portfolio::GetTickers()
{
	return this->tickers_;
}

MatrixXd portfolio::GetReturnMatrix()
{
	return this->return_matrix_;
}

