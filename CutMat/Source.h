#pragma once
#include <vector>
#include <string>
struct mater
{
	int value;//����� ��������, ����� ���������
	double length;//������ ������� ���������
};
void General(std::vector<mater> mat, std::vector<int> complect, std::vector<double> delta, std::vector<std::vector<int>>& Var0, std::vector<std::vector<int>>& Var1);
void Resulting(std::vector<mater> mat, std::vector<int> complect, std::vector<std::vector<int>>& Var0, std::vector<std::vector<int>>& Var1, std::vector<int>& xVector, int& max);
