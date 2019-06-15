#include <vector>
#include <math.h>
#include <iostream>
#include <fstream>


using namespace std;
double min(vector<double> src)
{
	double min = 99999;
	for (int i = 0; i < src.size(); i++)
		if (min > src[i])
			min = src[i];
	return min;
}
struct mater
{
	int value;//Объем поставки, число заготовок
	double length;//длинна каждого материала
};
double variety(double length, vector <double> delta, int i, int j)
{
	double result = 0;
	for (int R = 0; R < i; R++)
		for (int S = 0; S < j; S++)
		{
			length = length - delta[0] * R - delta[1] * S;
			if (length >= 0)
				result += 1;
		}
	return result;
}

vector<vector<int>> Variant(vector<mater> mat, vector<double> delta, int iter)
{
	vector<int> temp;
	vector<vector<int>> result;
	int ir = mat[iter].length / delta[0];
	int jr = mat[iter].length / delta[1];
	double mint = min(delta);
	double tmp;

	for (int k = 0; k <= ir; k++) {
		for (int d = 0; d <= jr; d++)
		{
			tmp = mat[iter].length - delta[0] * (double)k - delta[1] * (double)d;
			if (tmp >= 0)
			{
				if (tmp < mint && tmp != mat[iter].length)
				{
					temp.emplace_back(k);
					temp.emplace_back(d);
					result.emplace_back(temp);
					temp.clear();
				}
			}
		}

	}


	return result;
}
int sumVector(vector<vector<int>> x)
{
	int sum = 0;
	for (int i = 0; i < x.size(); i++)
		for (int j = 0; j < x[i].size(); j++)
			sum += x[i][j];
	return sum;
}
void General(vector<mater> mat, vector<int> complect, vector<double> delta, vector<vector<int>>& Var0, vector<vector<int>>& Var1)
{
	int result = 0;
	Var0 = Variant(mat, delta, 0);
	Var1 = Variant(mat, delta, 1);
	vector<vector<int>> resultVector;
	vector<int> temp;
	for (int i = 0; i < Var0[0].size(); i++) {
		for (int j = 0; j < Var1.size(); j++)
			temp.emplace_back(2);
		resultVector.emplace_back(temp);
		temp.clear();
	}
	int f = sumVector(resultVector);
	int fff = 2;


}
