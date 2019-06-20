#include <math.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;
vector< int > seq; // исходная последовательность
vector< int > sub; // вектор слагаемых
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
//таблица вариантов раскроя
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
int sumVector(vector<int> x)
{
	int sum = 0;
	for (int i = 0; i < x.size(); i++)
			sum += x[i];
	return sum;
}


void write_sub(vector<vector<int>>& res)
{
	std::sort(sub.begin(), sub.end());
	do {
		res.emplace_back(sub);
	} while (std::next_permutation(sub.begin(), sub.end()));
}
//создание плана раскроя
void fun(int x, int c, vector<vector<int>>& res, size_t i = 0) //x-сумма c-кол-во аргументов
{
	if (c < 0 || x < 0) return;
	else if (!x && c) return;
	else if (x && !c) return;
	else if (!x && !c) write_sub(res);
	else
		for (; i < seq.size(); ++i)
		{
			sub.push_back(seq[i]);
			fun(x - seq[i], c - 1, res, i);
			sub.pop_back();
		}
}
void General(vector<mater> mat, vector<int> complect, vector<double> delta, vector<vector<int>>& Var0, vector<vector<int>>& Var1)
{
	int result = 0;
	Var0 = Variant(mat, delta, 0);
	Var1 = Variant(mat, delta, 1);
	int t = 0;

	
}
//выбор лучшего плана раскроя проверка на комплектность
void Resulting(vector<mater> mat,vector<int> complect, vector<vector<int>>& Var0, vector<vector<int>>& Var1, vector<int> &xVector, int &max) {
	for (int i = 0; i <= mat[0].value; i++)
		seq.emplace_back(i);
	vector<vector<int>> res1;
	fun(mat[0].value, Var0.size(), res1);
	seq.clear();
	for (int i = 0; i <= mat[1].value; i++)
		seq.emplace_back(i);
	vector<vector<int>> res2;
	fun(mat[1].value, Var1.size(), res2);
	seq.clear();
	int f = 0, s = 0, tmp = 0;

	for (int u = 0; u < res1.size(); ++u)
		for (int k = 0; k < res2.size(); ++k) {
			//Первое ограничение
			int f1 = 0, f2 = 0;
			for (int i = 0; i < Var0.size(); ++i)
				f1 += Var0[i][0] * res1[u][i];
			for (int j = 0; j < Var1.size(); ++j)
				f2 += Var1[j][0] * res2[k][j];
			f = (f1 + f2) / complect[0];
			//Второе ограничение
			int s1 = 0, s2 = 0;
			for (int i = 0; i < Var0.size(); ++i)
				s1 += Var0[i][1] * res1[u][i];
			for (int j = 0; j < Var1.size(); ++j)
				s2 += Var1[j][1] * res2[k][j];
			s = (s1 + s2) / complect[1];
			int fs = f + s;
			if (f == s && fs > max)
			{
				xVector.clear();
				max = fs;
				for (int e = 0; e < res1[u].size(); e++)
					xVector.push_back(res1[u][e]);
				xVector.insert(xVector.end(), res2[k].begin(), res2[k].end());
			}

		}
	max = max / 2;
}