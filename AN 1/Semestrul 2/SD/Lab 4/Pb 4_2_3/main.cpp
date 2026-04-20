#include <fstream>
#include <vector>
#include <queue>

class InParser {
private:
	FILE *fin;
	char *buff;
	int sp;

	char read_ch() {
		++sp;
		if (sp == 4096) {
			sp = 0;
			fread(buff, 1, 4096, fin);
		}
		return buff[sp];
	}

public:
	InParser(const char* nume) {
		fin = fopen(nume, "r");
		buff = new char[4096]();
		sp = 4095;
	}
	
	InParser& operator >> (int &n) {
		char c;
		while (!isdigit(c = read_ch()) && c != '-');
		int sgn = 1;
		if (c == '-') {
			n = 0;
			sgn = -1;
		} else {
			n = c - '0';
		}
		while (isdigit(c = read_ch())) {
			n = 10 * n + c - '0';
		}
		n *= sgn;
		return *this;
	}
	
	InParser& operator >> (long long &n) {
		char c;
		n = 0;
		while (!isdigit(c = read_ch()) && c != '-');
		long long sgn = 1;
		if (c == '-') {
			n = 0;
			sgn = -1;
		} else {
			n = c - '0';
		}
		while (isdigit(c = read_ch())) {
			n = 10 * n + c - '0';
		}
		n *= sgn;
		return *this;
	}
};

InParser fin("dijkstra.in");
std::ofstream fout("dijkstra.out");

typedef std::pair<int, int> pii;
const int INF = 1e9;

int N, M;
std::vector<std::vector<pii> > G;
std::priority_queue<pii> pq;
std::vector<int> D;

int main(){
    fin >> N >> M;

    G.resize(N + 1);
    D.resize(N + 1, INF);

    for(int x, y, c; M--;){
        fin >> x >> y >> c;
        G[x].push_back({y, c});
    }

    D[1] = 0;
    pq.push({0, 1});

    while(!pq.empty()){
        auto [dist, node] = pq.top();
        pq.pop();

        if(-dist > D[node]) { continue; }

        for(pii p : G[node]){
            if(D[p.first] > D[node] + p.second){
                D[p.first] = D[node] + p.second;
                pq.push({-D[p.first], p.first});
            }
        }
    }

    for(int i = 2; i <= N; ++i){
        if(D[i] == INF){
            fout << "0 ";
        }
        else{
            fout << D[i] << ' ';
        }
    }
}