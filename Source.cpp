#include <iostream>
#include <vector>
#include <filesystem>
#include <fstream>
#include <algorithm>
#include <string>

using namespace std;


vector <string> list_files(string dir)
{
	vector <string> result;
	for (const auto& entry : filesystem::directory_iterator(dir))
		result.push_back(entry.path().string().substr(5));
	return result;
}
void tn(string b, int size, int& n, int& k)
{
	int nspace = 0;
	for (int i = 0; i < size; i++)
	{
		if (b[i] == ' ')
		{
			nspace = i;
		}
	}
	n = stoi(b.substr(0, nspace));
	k = stoi(b.substr(nspace + 1));

}

int main()
{
	vector <string> data = list_files("data");
	ofstream fout;
	string b;
	fout.open("output.txt");
	int N, K;
	double buf;
	for (string x : data)
	{
		ifstream file("data/" + x);
		getline(file, b);
		int size1 = b.length();
		tn(b, size1, N, K);
		vector <int> pr(N);
		vector <int> m(N);
		vector <double> a(N);
		//cout << b << " " << size1 << " " << K << " " << N<<" " << endl;
		for (int i = 0; i < N; i++)
		{
			getline(file, b);
			int size2 = b.length();
			tn(b, size2, pr[i], m[i]);
			buf = double(pr[i]) / double(m[i]);
			a[i] = buf;
		}
		file.close();
		int S = 0, M = 0, maxn;
		double max = 0;
		bool flag = false;
		while (true)
		{
			for (int i = 0; i < N; i++)
			{
				if ((max < a[i]) && (M + m[i] < K))
				{
					max = a[i];
					maxn = i;
					flag = true;
				}
			}
			if (flag == false)
			{
				break;
			}
			if (flag == true)
			{
				S = S + pr[maxn];
				M = M + m[maxn];
				a[maxn] = 0;
				max = 0;
				flag = false;
				//cout << "+" << pr[maxn] << endl;
			}
		}
		cout << S << endl;
		fout << x << ":" << S << endl;
	}
	fout.close();
	return 0;
}