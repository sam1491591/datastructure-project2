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
int floor2[1000][1005] = { 0 };
int dis[1000][1005] = { 0 };
int visited2[1000][1005] = { 0 };
int push[1000][1005] = { 0 };
int visited[1000][1005] = { 0 };

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
/*
void initial() {
	vector < vector < int > > bitch(m + 1, vector<int>(n + 1, 0));
	floor2 = bitch;
	dis = bitch;
	visited = bitch;
	visited2 = bitch;
	push = bitch;
}
*/

int main(int argc, char* argv[])
{
	//cout << "no file/n";
	/*
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
	*/
	cin >> m >> n >> b;
	map floor1;
	//cout << "!!!"<< endl;
	//initial();
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
			cin >> input1;
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
		//cout << tmp.x<<" "<<tmp.y << endl;
		floor1.findpath(tmp, tmpbattery, m, n);
		//floor1.outputvis(m, n);
	}
	//floor1.outputvis(m, n);
	cout << path.size() << endl;
	for (auto n : path)
	{
		cout << n.x << " " << n.y << endl;
	}

	//input.close();
	//output.close();
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
		if (s.y > 0 && visited[s.x][s.y - 1] == 0 && floor2[s.x][s.y - 1] == 0)
		{
			tilt up = tilt(s.x, s.y - 1);
			//cout <<"up: "<< up.x << " " << up.y << endl;
			dis[up.x][up.y] = dis[s.x][s.y] + 1;
			if (push[up.x][up.y] == 0)
			{
				push[up.x][up.y] = 1;
				q.push(up);
			}
		}
		if (s.y < n - 1 && visited[s.x][s.y + 1] == 0 && floor2[s.x][s.y + 1] == 0)
		{
			tilt down = tilt(s.x, s.y + 1);
			//cout <<"down: "<< down.x << " " << down.y << endl;
			dis[down.x][down.y] = dis[s.x][s.y] + 1;
			if (push[down.x][down.y] == 0)
			{
				push[down.x][down.y] = 1;
				q.push(down);
			}
		}
		if (s.x > 0 && visited[s.x - 1][s.y] == 0 && floor2[s.x - 1][s.y] == 0)
		{
			tilt left = tilt(s.x - 1, s.y);
			//cout <<"left: "<< left.x << " " << left.y << endl;
			dis[left.x][left.y] = dis[s.x][s.y] + 1;
			if (push[left.x][left.y] == 0)
			{
				push[left.x][left.y] = 1;
				q.push(left);
			}
		}
		if (s.x < m - 1 && visited[s.x + 1][s.y] == 0 && floor2[s.x + 1][s.y] == 0)
		{
			tilt right = tilt(s.x + 1, s.y);
			//cout <<"right: "<< right.x << " " << right.y << endl;
			dis[right.x][right.y] = dis[s.x][s.y] + 1;
			if (push[right.x][right.y] == 0)
			{
				push[right.x][right.y] = 1;
				q.push(right);
			}
		}
	}
}

tilt findpath_temp = tilt(0, 0);

void map::findpath(tilt a, int b, int m, int n)
{
	findpath_temp = a;
	//cout << a.x <<" "<< a.y << endl;
	while (true)
	{
	//cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<b<<endl;
		if ((dis[findpath_temp.x][findpath_temp.y] == b) || (dis[findpath_temp.x][findpath_temp.y] == b + 1))
		{
			visited2[findpath_temp.x][findpath_temp.y]++;
			goback(findpath_temp);
			return;
		}
		else
		{
			visited2[findpath_temp.x][findpath_temp.y]++;
			if ((dis[findpath_temp.x + 1][findpath_temp.y] > dis[findpath_temp.x][findpath_temp.y]) && (visited2[findpath_temp.x + 1][findpath_temp.y] == min(min(visited2[findpath_temp.x][findpath_temp.y + 1], visited2[findpath_temp.x][findpath_temp.y - 1]), min(visited2[findpath_temp.x + 1][findpath_temp.y], visited2[findpath_temp.x - 1][findpath_temp.y]))) && (findpath_temp.x < m - 1))
			{
				//cout << "find down!\n";
				b--;
				findpath_temp.x += 1;
				path.push_back(findpath_temp);
			}
			else if ((dis[findpath_temp.x - 1][findpath_temp.y] > dis[findpath_temp.x][findpath_temp.y]) && (visited2[findpath_temp.x - 1][findpath_temp.y] == min(min(visited2[findpath_temp.x][findpath_temp.y + 1], visited2[findpath_temp.x][findpath_temp.y - 1]), min(visited2[findpath_temp.x + 1][findpath_temp.y], visited2[findpath_temp.x - 1][findpath_temp.y]))) && (findpath_temp.x < m - 1))
			{
				//cout << "find up!\n";
				b--;
				findpath_temp.x -= 1;
				path.push_back(findpath_temp);
			}
			else if ((dis[findpath_temp.x][findpath_temp.y + 1] > dis[findpath_temp.x][findpath_temp.y]) && (visited2[findpath_temp.x][findpath_temp.y + 1] == min(min(visited2[findpath_temp.x][findpath_temp.y + 1], visited2[findpath_temp.x][findpath_temp.y - 1]), min(visited2[findpath_temp.x + 1][findpath_temp.y], visited2[findpath_temp.x - 1][findpath_temp.y]))) && (findpath_temp.x < m - 1))
			{
				//cout << "find right!\n";
				b--;
				findpath_temp.y += 1;
				path.push_back(findpath_temp);
			}
			else if ((dis[findpath_temp.x][findpath_temp.y - 1] > dis[findpath_temp.x][findpath_temp.y]) && (visited2[findpath_temp.x][findpath_temp.y - 1] == min(min(visited2[findpath_temp.x][findpath_temp.y + 1], visited2[findpath_temp.x][findpath_temp.y - 1]), min(visited2[findpath_temp.x + 1][findpath_temp.y], visited2[findpath_temp.x - 1][findpath_temp.y]))) && (findpath_temp.x < m - 1))
			{
				//cout << "find left!\n";
				b--;
				findpath_temp.y -= 1;
				path.push_back(findpath_temp);
			}
			else if (visited2[findpath_temp.x + 1][findpath_temp.y] == min(min(visited2[findpath_temp.x][findpath_temp.y + 1], visited2[findpath_temp.x][findpath_temp.y - 1]), min(visited2[findpath_temp.x + 1][findpath_temp.y], visited2[findpath_temp.x - 1][findpath_temp.y])) && (findpath_temp.x < m - 1))
			{
				//cout << "Find down!\n";
				b--;
				findpath_temp.x += 1;
				path.push_back(findpath_temp);
			}
			else if (visited2[findpath_temp.x - 1][findpath_temp.y] == min(min(visited2[findpath_temp.x][findpath_temp.y + 1], visited2[findpath_temp.x][findpath_temp.y - 1]), min(visited2[findpath_temp.x + 1][findpath_temp.y], visited2[findpath_temp.x - 1][findpath_temp.y])) && (findpath_temp.x < m - 1))
			{
				//cout << "Find up!\n";
				b--;
				findpath_temp.x -= 1;
				path.push_back(findpath_temp);
			}
			else if (visited2[findpath_temp.x][findpath_temp.y + 1] == min(min(visited2[findpath_temp.x][findpath_temp.y + 1], visited2[findpath_temp.x][findpath_temp.y - 1]), min(visited2[findpath_temp.x + 1][findpath_temp.y], visited2[findpath_temp.x - 1][findpath_temp.y])) && (findpath_temp.x < m - 1))
			{
				//cout << "Find right!\n";
				b--;
				findpath_temp.y += 1;
				path.push_back(findpath_temp);
			}
			else if (visited2[findpath_temp.x][findpath_temp.y - 1] == min(min(visited2[findpath_temp.x][findpath_temp.y + 1], visited2[findpath_temp.x][findpath_temp.y - 1]), min(visited2[findpath_temp.x + 1][findpath_temp.y], visited2[findpath_temp.x - 1][findpath_temp.y])) && (findpath_temp.x < m - 1))
			{
				//cout << "Find left!\n";
				b--;
				findpath_temp.y -= 1;
				path.push_back(findpath_temp);
			}
		}

	}
}

tilt goback_temp = tilt(0, 0);

void map::goback(tilt a)
{
	goback_temp = a;
	while (true)
	{
		//cout << goback_temp.x <<" "<< goback_temp.y << endl;
		if (goback_temp.x == rx && goback_temp.y == ry)
			return;
		if ((dis[goback_temp.x][goback_temp.y + 1] < dis[goback_temp.x][goback_temp.y] && (dis[goback_temp.x][goback_temp.y + 1] >= 0)) && (visited[goback_temp.x][goback_temp.y + 1] == min(min(visited2[goback_temp.x][goback_temp.y + 1], visited2[goback_temp.x][goback_temp.y - 1]), min(visited2[goback_temp.x + 1][goback_temp.y], visited2[goback_temp.x - 1][goback_temp.y]))))
		{
			//cout << "go right!\n";
			goback_temp.y += 1;
			visited2[goback_temp.x][goback_temp.y]++;
			path.push_back(goback_temp);
		}
		else if ((dis[goback_temp.x][goback_temp.y - 1] < dis[goback_temp.x][goback_temp.y] && (dis[goback_temp.x][goback_temp.y - 1] >= 0)) && (visited[goback_temp.x][goback_temp.y - 1] == min(min(visited2[goback_temp.x][goback_temp.y + 1], visited2[goback_temp.x][goback_temp.y - 1]), min(visited2[goback_temp.x + 1][goback_temp.y], visited2[goback_temp.x - 1][goback_temp.y]))))
		{
			//cout << "go left!\n";
			goback_temp.y -= 1;
			visited2[goback_temp.x][goback_temp.y]++;
			path.push_back(goback_temp);
		}
		else if ((dis[goback_temp.x + 1][goback_temp.y] < dis[goback_temp.x][goback_temp.y] && (dis[goback_temp.x + 1][goback_temp.y] >= 0)) && (visited[goback_temp.x + 1][goback_temp.y] == min(min(visited2[goback_temp.x][goback_temp.y + 1], visited2[goback_temp.x][goback_temp.y - 1]), min(visited2[goback_temp.x + 1][goback_temp.y], visited2[goback_temp.x - 1][goback_temp.y]))))
		{
			//cout << "go down!\n";
			goback_temp.x += 1;
			visited2[goback_temp.x][goback_temp.y]++;
			path.push_back(goback_temp);
		}
		else if ((dis[goback_temp.x - 1][goback_temp.y] < dis[goback_temp.x][goback_temp.y] && (dis[goback_temp.x - 1][goback_temp.y] >= 0)) && (visited[goback_temp.x - 1][goback_temp.y] == min(min(visited2[goback_temp.x][goback_temp.y + 1], visited2[goback_temp.x][goback_temp.y - 1]), min(visited2[goback_temp.x + 1][goback_temp.y], visited2[goback_temp.x - 1][goback_temp.y]))))
		{
			//cout << "go up!\n";
			goback_temp.x -= 1;
			visited2[goback_temp.x][goback_temp.y]++;
			path.push_back(goback_temp);
		}
		else if ((dis[goback_temp.x][goback_temp.y + 1] < dis[goback_temp.x][goback_temp.y] && (dis[goback_temp.x][goback_temp.y + 1] >= 0)))
		{
			//cout << "go right!\n";
			goback_temp.y += 1;
			visited2[goback_temp.x][goback_temp.y]++;
			path.push_back(goback_temp);
		}
		else if ((dis[goback_temp.x][goback_temp.y - 1] < dis[goback_temp.x][goback_temp.y] && (dis[goback_temp.x][goback_temp.y - 1] >= 0)))
		{
			//cout << "go left!\n";
			goback_temp.y -= 1;
			visited2[goback_temp.x][goback_temp.y]++;
			path.push_back(goback_temp);
		}
		else if ((dis[goback_temp.x + 1][goback_temp.y] < dis[goback_temp.x][goback_temp.y] && (dis[goback_temp.x + 1][goback_temp.y] >= 0)))
		{
			//cout << "go down!\n";
			goback_temp.x += 1;
			visited2[goback_temp.x][goback_temp.y]++;
			path.push_back(goback_temp);
		}
		else if ((dis[goback_temp.x - 1][goback_temp.y] < dis[goback_temp.x][goback_temp.y] && (dis[goback_temp.x - 1][goback_temp.y] >= 0)))
		{
			//cout << "go up!\n";
			goback_temp.x -= 1;
			visited2[goback_temp.x][goback_temp.y]++;
			path.push_back(goback_temp);
		}

	}
}

tilt gobackinverse_temp = tilt(0, 0);

void map::gobackinverse(tilt a)
{
	gobackinverse_temp = a;
	while (true)
	{
		//cout << gobackinverse_temp.x <<" "<< gobackinverse_temp.y << endl;
		if (gobackinverse_temp.x == rx && gobackinverse_temp.y == ry)
			return;
		if ((dis[gobackinverse_temp.x][gobackinverse_temp.y + 1] < dis[gobackinverse_temp.x][gobackinverse_temp.y] && (dis[gobackinverse_temp.x][gobackinverse_temp.y + 1] >= 0)) && (visited[gobackinverse_temp.x][gobackinverse_temp.y + 1] == min(min(visited2[gobackinverse_temp.x][gobackinverse_temp.y + 1], visited2[gobackinverse_temp.x][gobackinverse_temp.y - 1]), min(visited2[gobackinverse_temp.x + 1][gobackinverse_temp.y], visited2[gobackinverse_temp.x - 1][gobackinverse_temp.y]))))
		{
			//cout << "go right!\n";
			gobackinverse_temp.y += 1;
			visited2[gobackinverse_temp.x][gobackinverse_temp.y]++;
			pathinverse.push_back(gobackinverse_temp);
		}
		else if ((dis[gobackinverse_temp.x][gobackinverse_temp.y - 1] < dis[gobackinverse_temp.x][gobackinverse_temp.y] && (dis[gobackinverse_temp.x][gobackinverse_temp.y - 1] >= 0)) && (visited[gobackinverse_temp.x][gobackinverse_temp.y - 1] == min(min(visited2[gobackinverse_temp.x][gobackinverse_temp.y + 1], visited2[gobackinverse_temp.x][gobackinverse_temp.y - 1]), min(visited2[gobackinverse_temp.x + 1][gobackinverse_temp.y], visited2[gobackinverse_temp.x - 1][gobackinverse_temp.y]))))
		{
			//cout << "go left!\n";
			gobackinverse_temp.y -= 1;
			visited2[gobackinverse_temp.x][gobackinverse_temp.y]++;
			pathinverse.push_back(gobackinverse_temp);
		}
		else if ((dis[gobackinverse_temp.x + 1][gobackinverse_temp.y] < dis[gobackinverse_temp.x + 1][gobackinverse_temp.y] && (dis[gobackinverse_temp.x + 1][gobackinverse_temp.y] >= 0)) && (visited[gobackinverse_temp.x + 1][gobackinverse_temp.y] == min(min(visited2[gobackinverse_temp.x][gobackinverse_temp.y + 1], visited2[gobackinverse_temp.x][gobackinverse_temp.y - 1]), min(visited2[gobackinverse_temp.x + 1][gobackinverse_temp.y], visited2[gobackinverse_temp.x - 1][gobackinverse_temp.y]))))
		{
			//cout << "go down!\n";
			gobackinverse_temp.x += 1;
			visited2[gobackinverse_temp.x][gobackinverse_temp.y]++;
			pathinverse.push_back(gobackinverse_temp);
		}
		else if ((dis[gobackinverse_temp.x - 1][gobackinverse_temp.y] < dis[gobackinverse_temp.x][gobackinverse_temp.y] && (dis[gobackinverse_temp.x - 1][gobackinverse_temp.y] >= 0)) && (visited[gobackinverse_temp.x - 1][gobackinverse_temp.y] == min(min(visited2[gobackinverse_temp.x][gobackinverse_temp.y + 1], visited2[gobackinverse_temp.x][gobackinverse_temp.y - 1]), min(visited2[gobackinverse_temp.x + 1][gobackinverse_temp.y], visited2[gobackinverse_temp.x - 1][gobackinverse_temp.y]))))
		{
			//cout << "go up!\n";
			gobackinverse_temp.x -= 1;
			visited2[gobackinverse_temp.x][gobackinverse_temp.y]++;
			pathinverse.push_back(gobackinverse_temp);
		}
		else if ((dis[gobackinverse_temp.x][gobackinverse_temp.y + 1] < dis[gobackinverse_temp.x][gobackinverse_temp.y] && (dis[gobackinverse_temp.x][gobackinverse_temp.y + 1] >= 0)))
		{
			//cout << "go right!\n";
			gobackinverse_temp.y += 1;
			visited2[gobackinverse_temp.x][gobackinverse_temp.y]++;
			pathinverse.push_back(gobackinverse_temp);
		}
		else if ((dis[gobackinverse_temp.x][gobackinverse_temp.y - 1] < dis[gobackinverse_temp.x][gobackinverse_temp.y] && (dis[gobackinverse_temp.x][gobackinverse_temp.y - 1] >= 0)))
		{
			//cout << "go left!\n";
			gobackinverse_temp.y -= 1;
			visited2[gobackinverse_temp.x][gobackinverse_temp.y]++;
			pathinverse.push_back(gobackinverse_temp);
		}
		else if ((dis[gobackinverse_temp.x + 1][gobackinverse_temp.y] < dis[gobackinverse_temp.x][gobackinverse_temp.y] && (dis[gobackinverse_temp.x + 1][gobackinverse_temp.y] >= 0)))
		{
			//cout << "go down!\n";
			gobackinverse_temp.x += 1;
			visited2[gobackinverse_temp.x][gobackinverse_temp.y]++;
			pathinverse.push_back(gobackinverse_temp);
		}
		else if ((dis[gobackinverse_temp.x - 1][gobackinverse_temp.y] < dis[gobackinverse_temp.x][gobackinverse_temp.y] && (dis[gobackinverse_temp.x - 1][gobackinverse_temp.y] >= 0)))
		{
			//cout << "go up!\n";
			gobackinverse_temp.x -= 1;
			visited2[gobackinverse_temp.x][gobackinverse_temp.y]++;
			pathinverse.push_back(gobackinverse_temp);
		}

	}
}
/*
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
*/