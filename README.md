Mean-Variance frontier and BlackLittermant

Please check "Input & Output.png" for quick reference of input and output.

0. Preset 

1) This program needs "eigen" library to perform matrix operations.

2) "data.txt" as an example input:
	
	(a) This file contains daily closing prices for 7 random picked stocks during the past year.(20141120-20151121)

	(b) Data was extracted from "Google Finance".

1. Mean-variance frontier

1) Input:

	(a) The program will try to read a file name "data.txt" in default directory.
	"data.txt" is tab-delimited DOS text file.

	(b) If you have N assets and I observations, this file will have I+1 rows and N columns.

	(c) The first row contains the names(tickers) of the assets(stocks).

	(d) User needs to input the number of assets and number of observations according to the hints showed in the program.


********************************************************************************
2) Codes for improving efficiency

	This program utilizes symmetry of covariance matrix, so it only needs to compute half of the covariance matrix.

********************************************************************************

2. BlackLitterman

0) Please be aware that all of the input should be consistent. For example, the data in backtest "data.txt" is daily closing pricea of a year. Therefore the risk-free rate and excess return should be expressed in terms of daily value.(which are very small). 

1) Input:

	(a) The BlackLitterman process is based on same the data from Mean-variance problem.

	(b) User needs specify:

		(1)equilibrium return(here defined as risk-free return);

		(2)tau：level of accuracy of expected excess returns(between 0 and 1, close to zero by definition)；

		(3)risk aversion constant;

		(4)number of views;

		(5)view: a view consists of P, Q, OMEGA
	
			Assume we have N assets, then a view would consist of (N + 2)parameters:

				P: The first N parameters is coefficient correponding to each asset;

				Q: The next ((N+1)th) parameter is relative difference of returns;
				
				OMEGA: The level of viewer's confidence about the view；

			In a word, user needs to input (N+2) parameters for a view.

