#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <queue>
#include <climits>
#include <limits>
#include <vector>
using namespace std;

int rx, ry;
int m, n, b;
vector < vector < int > > floor2;
vector<vector<int> > dis;
vector<vector<int> > visited2;
vector<vector<int> > push;
vector<vector<int> > visited;

class tilt {
	friend class map;
public:
	int x;
	int y;
	tilt(int x, int y) {
		this->x = x;
		this->y = y;
	}
};

tilt tmp = tilt(0, 0);
int tmpbattery = 0;

int step = 0;
vector<tilt> path;
vector<tilt> pathinverse;

class map {
public:
	map() {}
	~map() {}
	void read_floor(int m, int n);
	void distancecheck(tilt, int, int);
	void outputdis(int m, int n) {
		for (int i = 0; i < m; i++)
		{
			cout << endl;
			for (int j = 0; j < n; j++)
			{
				cout << dis[i][j] << " ";
			}
		}
	}
	void findpath(tilt a, int b, int m, int n);
	void goback(tilt a);
	void outputvis(int m, int n) {
		for (int i = 0; i < m; i++)
		{
			cout << endl;
			for (int j = 0; j < n; j++)
			{
				//if (visited2[i][j] == INT_MAX);
				//else
				cout << visited2[i][j] << " ";
			}
		}
	}
	int checkclear(int m, int n, int b)
	{
		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (visited2[i][j] == 0)
				{
					tmp.x = i;
					tmp.y = j;
					tmpbattery = b - dis[i][j];
					return 1;
				}
			}
		}
		return 0;
	}
	void gobackinverse(tilt a);
	void addtilt(tilt a) {
		pathinverse.push_back(a);
		visited2[a.x][a.y]++;
	}
	//int floor1[1000][1005] = { 0 };
	//int dis[1000][1005] = { 0 };
	//int visited2[1000][1005] = { 0 };

	

	//int push[1000][1005] = { 0 };
	//int visited[1000][1005] = { 0 };
};

void initial() {
		vector < vector < int > > bitch(m + 1, vector<int>(n + 1, 0));
		floor2 = bitch;
		dis = bitch;
		visited = bitch;
		visited2 = bitch;
		push = bitch;
	}


int main(int argc, char* argv[])
{
	//cout << "no file/n";
	
	fstream input(argv[1], ios::in);
	fstream output("final.path", ios::out);
	if (!input)
	{
		cout << "no file/n";
	}
	if (!output)
	{
		cout << "can't output your answer";
	}
	
	input >> m >> n >> b;
	map floor1;
	//cout << "!!!"<< endl;
	initial();
	//floor1.read_floor(m,n,argc,argv);
	char input1;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			/*
			if (i == m || j == n)
			{
				floor1.floor1[i][j] = -2;
				floor1.dis[i][j] = INT_MIN;
				floor1.visited2[i][j] = INT_MAX;
			}
			*/
			//else
			//{
			input >> input1;
			/*
			if (input1 == '\n')
				cin >> input1;
			*/
			if (input1 == 'R')
			{

				floor2[i][j] = -1;
				rx = i;
				ry = j;
			}
			else if (input1 == '0')
				floor2[i][j] = 0;
			else
			{
				floor2[i][j] = 1;
				dis[i][j] = -1;
				visited2[i][j] = INT_MAX;
			}
			//cout <<input1<< "!\n";
		//}
		}
	}
	tilt R = tilt(rx, ry);
	floor1.distancecheck(R, m, n);
	//floor1.outputdis(m, n);
	//cout << endl;
	while (floor1.checkclear(m, n, b))
	{
		pathinverse.push_back(tmp);
		//floor1.addtilt(tmp);
		floor1.gobackinverse(tmp);
		while (!pathinverse.empty())
		{
			tilt last = pathinverse.back();
			pathinverse.pop_back();
			path.push_back(last);
		}
		floor1.findpath(tmp, tmpbattery, m, n);
		//cout << "not clear" << endl;
		//floor1.outputvis(m, n);
	}
	//floor1.outputvis(m, n);
	output << path.size() << endl;
	for (auto n : path)
	{
		output << n.x << " " << n.y << endl;
	}

	input.close();
	output.close();
}

void map::distancecheck(tilt a, int m, int n)
{
	//cout << "m: " << m << " n: " << n << endl;
	floor2[a.x][a.y] = 0;
	dis[a.x][a.y] = 0;
	queue <tilt> q;
	q.push(a);
	push[a.x][a.y] = 1;
	while (!q.empty())
	{
		tilt s = q.front();
		visited[s.x][s.y] = 1;
		//cout << s.x << " " << s.y << endl;
		q.pop();
		if (visited[s.x][s.y - 1] == 0 && floor2[s.x][s.y - 1] == 0 && s.y > 0)
		{
			tilt up = tilt(s.x, s.y - 1);
			dis[up.x][up.y] = dis[s.x][s.y] + 1;
			if (push[up.x][up.y] == 0)
			{
				push[up.x][up.y] = 1;
				q.push(up);
			}
		}
		if (visited[s.x][s.y + 1] == 0 && floor2[s.x][s.y + 1] == 0 && s.y < n - 1)
		{
			tilt down = tilt(s.x, s.y + 1);
			dis[down.x][down.y] = dis[s.x][s.y] + 1;
			if (push[down.x][down.y] == 0)
			{
				push[down.x][down.y] = 1;
				q.push(down);
			}
		}
		if (visited[s.x - 1][s.y] == 0 && floor2[s.x - 1][s.y] == 0 && s.x > 0)
		{
			tilt left = tilt(s.x - 1, s.y);
			dis[left.x][left.y] = dis[s.x][s.y] + 1;
			if (push[left.x][left.y] == 0)
			{
				push[left.x][left.y] = 1;
				q.push(left);
			}
		}
		if (visited[s.x + 1][s.y] == 0 && floor2[s.x + 1][s.y] == 0 && s.x < m - 1)
		{
			tilt right = tilt(s.x + 1, s.y);
			dis[right.x][right.y] = dis[s.x][s.y] + 1;
			if (push[right.x][right.y] == 0)
			{
				push[right.x][right.y] = 1;
				q.push(right);
			}
		}
	}
}

void map::findpath(tilt a, int b, int m, int n)
{
	//cout << a.x <<" "<< a.y << endl;
	//cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<b<<endl;
	if ((dis[a.x][a.y] == b) || (dis[a.x][a.y] == b + 1))
	{
		visited2[a.x][a.y]++;
		goback(a);
	}
	else
	{
		visited2[a.x][a.y]++;
		if ((dis[a.x + 1][a.y] > dis[a.x][a.y]) && (visited2[a.x + 1][a.y] == min(min(visited2[a.x][a.y + 1], visited2[a.x][a.y - 1]), min(visited2[a.x + 1][a.y], visited2[a.x - 1][a.y]))) && (a.x < m - 1))
		{
			//cout << "find down!\n";
			b--;
			tilt t = tilt(a.x + 1, a.y);
			path.push_back(t);
			findpath(t, b, m, n);
		}
		else if ((dis[a.x - 1][a.y] > dis[a.x][a.y]) && (visited2[a.x - 1][a.y] == min(min(visited2[a.x][a.y + 1], visited2[a.x][a.y - 1]), min(visited2[a.x + 1][a.y], visited2[a.x - 1][a.y]))) && (a.x > 0))
		{
			//cout << "find up!\n";
			b--;
			tilt t = tilt(a.x - 1, a.y);
			path.push_back(t);
			findpath(t, b, m, n);
		}
		else if ((dis[a.x][a.y + 1] > dis[a.x][a.y]) && (visited2[a.x][a.y + 1] == min(min(visited2[a.x][a.y + 1], visited2[a.x][a.y - 1]), min(visited2[a.x + 1][a.y], visited2[a.x - 1][a.y]))) && (a.y < n - 1))
		{
			//cout << "find right!\n";
			b--;
			tilt t = tilt(a.x, a.y + 1);
			path.push_back(t);
			findpath(t, b, m, n);
		}
		else if ((dis[a.x][a.y - 1] > dis[a.x][a.y]) && (visited2[a.x][a.y - 1] == min(min(visited2[a.x][a.y + 1], visited2[a.x][a.y - 1]), min(visited2[a.x + 1][a.y], visited2[a.x - 1][a.y]))) && (a.y > 0))
		{
			//cout << "find left!\n";
			b--;
			tilt t = tilt(a.x, a.y - 1);
			path.push_back(t);
			findpath(t, b, m, n);
		}
		else if (visited2[a.x + 1][a.y] == min(min(visited2[a.x][a.y + 1], visited2[a.x][a.y - 1]), min(visited2[a.x + 1][a.y], visited2[a.x - 1][a.y])) && (a.x < m - 1))
		{
			//cout << "Find down!\n";
			b--;
			tilt t = tilt(a.x + 1, a.y);
			path.push_back(t);
			findpath(t, b, m, n);
		}
		else if (visited2[a.x - 1][a.y] == min(min(visited2[a.x][a.y + 1], visited2[a.x][a.y - 1]), min(visited2[a.x + 1][a.y], visited2[a.x - 1][a.y])) && (a.x > 0))
		{
			//cout << "Find up!\n";
			b--;
			tilt t = tilt(a.x - 1, a.y);
			path.push_back(t);
			findpath(t, b, m, n);
		}
		else if (visited2[a.x][a.y + 1] == min(min(visited2[a.x][a.y + 1], visited2[a.x][a.y - 1]), min(visited2[a.x + 1][a.y], visited2[a.x - 1][a.y])) && (a.y < n - 1))
		{
			//cout << "Find right!\n";
			b--;
			tilt t = tilt(a.x, a.y + 1);
			path.push_back(t);
			findpath(t, b, m, n);
		}
		else if (visited2[a.x][a.y - 1] == min(min(visited2[a.x][a.y + 1], visited2[a.x][a.y - 1]), min(visited2[a.x + 1][a.y], visited2[a.x - 1][a.y])) && (a.y > 0))
		{
			//cout << "Find left!\n";
			b--;
			tilt t = tilt(a.x, a.y - 1);
			path.push_back(t);
			findpath(t, b, m, n);
		}
	}
}

void map::goback(tilt a)
{
	//cout << a.x <<" "<< a.y << endl;
	if (a.x == rx && a.y == ry)
		return;
	if ((dis[a.x][a.y + 1] < dis[a.x][a.y] && (dis[a.x][a.y + 1] >= 0)) && (visited[a.x][a.y + 1] == min(min(visited2[a.x][a.y + 1], visited2[a.x][a.y - 1]), min(visited2[a.x + 1][a.y], visited2[a.x - 1][a.y]))))
	{
		//cout << "go right!\n";
		tilt t = tilt(a.x, a.y + 1);
		visited2[t.x][t.y]++;
		path.push_back(t);
		goback(t);
	}
	else if ((dis[a.x][a.y - 1] < dis[a.x][a.y] && (dis[a.x][a.y - 1] >= 0)) && (visited[a.x][a.y - 1] == min(min(visited2[a.x][a.y + 1], visited2[a.x][a.y - 1]), min(visited2[a.x + 1][a.y], visited2[a.x - 1][a.y]))))
	{
		//cout << "go left!\n";
		tilt t = tilt(a.x, a.y - 1);
		visited2[t.x][t.y]++;
		path.push_back(t);
		goback(t);
	}
	else if ((dis[a.x + 1][a.y] < dis[a.x][a.y] && (dis[a.x + 1][a.y] >= 0)) && (visited[a.x + 1][a.y] == min(min(visited2[a.x][a.y + 1], visited2[a.x][a.y - 1]), min(visited2[a.x + 1][a.y], visited2[a.x - 1][a.y]))))
	{
		//cout << "go down!\n";
		tilt t = tilt(a.x + 1, a.y);
		visited2[t.x][t.y]++;
		path.push_back(t);
		goback(t);
	}
	else if ((dis[a.x - 1][a.y] < dis[a.x][a.y] && (dis[a.x - 1][a.y] >= 0)) && (visited[a.x - 1][a.y] == min(min(visited2[a.x][a.y + 1], visited2[a.x][a.y - 1]), min(visited2[a.x + 1][a.y], visited2[a.x - 1][a.y]))))
	{
		//cout << "go up!\n";
		tilt t = tilt(a.x - 1, a.y);
		visited2[t.x][t.y]++;
		path.push_back(t);
		goback(t);
	}
	else if ((dis[a.x][a.y + 1] < dis[a.x][a.y] && (dis[a.x][a.y + 1] >= 0)))
	{
		//cout << "go right!\n";
		tilt t = tilt(a.x, a.y + 1);
		visited2[t.x][t.y]++;
		path.push_back(t);
		goback(t);
	}
	else if ((dis[a.x][a.y - 1] < dis[a.x][a.y] && (dis[a.x][a.y - 1] >= 0)))
	{
		//cout << "go left!\n";
		tilt t = tilt(a.x, a.y - 1);
		visited2[t.x][t.y]++;
		path.push_back(t);
		goback(t);
	}
	else if ((dis[a.x + 1][a.y] < dis[a.x][a.y] && (dis[a.x + 1][a.y] >= 0)))
	{
		//cout << "go down!\n";
		tilt t = tilt(a.x + 1, a.y);
		visited2[t.x][t.y]++;
		path.push_back(t);
		goback(t);
	}
	else if ((dis[a.x - 1][a.y] < dis[a.x][a.y] && (dis[a.x - 1][a.y] >= 0)))
	{
		//cout << "go up!\n";
		tilt t = tilt(a.x - 1, a.y);
		visited2[t.x][t.y]++;
		path.push_back(t);
		goback(t);
	}
}

void map::gobackinverse(tilt a)
{
	//cout << a.x <<" "<< a.y << endl;
	if (a.x == rx && a.y == ry)
		return;
	if ((dis[a.x][a.y + 1] < dis[a.x][a.y] && (dis[a.x][a.y + 1] >= 0)) && (visited[a.x][a.y + 1] == min(min(visited2[a.x][a.y + 1], visited2[a.x][a.y - 1]), min(visited2[a.x + 1][a.y], visited2[a.x - 1][a.y]))))
	{
		//cout << "go right!\n";
		tilt t = tilt(a.x, a.y + 1);
		visited2[t.x][t.y]++;
		pathinverse.push_back(t);
		gobackinverse(t);
	}
	else if ((dis[a.x][a.y - 1] < dis[a.x][a.y] && (dis[a.x][a.y - 1] >= 0)) && (visited[a.x][a.y - 1] == min(min(visited2[a.x][a.y + 1], visited2[a.x][a.y - 1]), min(visited2[a.x + 1][a.y], visited2[a.x - 1][a.y]))))
	{
		//cout << "go left!\n";
		tilt t = tilt(a.x, a.y - 1);
		visited2[t.x][t.y]++;
		pathinverse.push_back(t);
		gobackinverse(t);
	}
	else if ((dis[a.x + 1][a.y] < dis[a.x][a.y] && (dis[a.x + 1][a.y] >= 0)) && (visited[a.x + 1][a.y] == min(min(visited2[a.x][a.y + 1], visited2[a.x][a.y - 1]), min(visited2[a.x + 1][a.y], visited2[a.x - 1][a.y]))))
	{
		//cout << "go down!\n";
		tilt t = tilt(a.x + 1, a.y);
		visited2[t.x][t.y]++;
		pathinverse.push_back(t);
		gobackinverse(t);
	}
	else if ((dis[a.x - 1][a.y] < dis[a.x][a.y] && (dis[a.x - 1][a.y] >= 0)) && (visited[a.x - 1][a.y] == min(min(visited2[a.x][a.y + 1], visited2[a.x][a.y - 1]), min(visited2[a.x + 1][a.y], visited2[a.x - 1][a.y]))))
	{
		//cout << "go up!\n";
		tilt t = tilt(a.x - 1, a.y);
		visited2[t.x][t.y]++;
		pathinverse.push_back(t);
		gobackinverse(t);
	}
	else if ((dis[a.x][a.y + 1] < dis[a.x][a.y] && (dis[a.x][a.y + 1] >= 0)))
	{
		//cout << "go right!\n";
		tilt t = tilt(a.x, a.y + 1);
		visited2[t.x][t.y]++;
		pathinverse.push_back(t);
		gobackinverse(t);
	}
	else if ((dis[a.x][a.y - 1] < dis[a.x][a.y] && (dis[a.x][a.y - 1] >= 0)))
	{
		//cout << "go left!\n";
		tilt t = tilt(a.x, a.y - 1);
		visited2[t.x][t.y]++;
		pathinverse.push_back(t);
		gobackinverse(t);
	}
	else if ((dis[a.x + 1][a.y] < dis[a.x][a.y] && (dis[a.x + 1][a.y] >= 0)))
	{
		//cout << "go down!\n";
		tilt t = tilt(a.x + 1, a.y);
		visited2[t.x][t.y]++;
		pathinverse.push_back(t);
		gobackinverse(t);
	}
	else if ((dis[a.x - 1][a.y] < dis[a.x][a.y] && (dis[a.x - 1][a.y] >= 0)))
	{
		//cout << "go up!\n";
		tilt t = tilt(a.x - 1, a.y);
		visited2[t.x][t.y]++;
		pathinverse.push_back(t);
		gobackinverse(t);
	}
}