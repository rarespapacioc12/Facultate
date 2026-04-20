// Castel ONI 2023
/* Idee:
fac baleiere pe linii si dupa joc pe coloane cu sume partiale pe map
*/

#include <fstream>
#include <vector>
#include <algorithm>

const int INF = 2e9;

std::ifstream fin("castel.in");
std::ofstream fout("castel.out");

struct dreptunghi{
    int x1, y2, x2, y1;
};

int N;
std::vector<dreptunghi> R;

int main(){

    fin >> N;

    R.resize(N + 2);
    
    for(int i = 1; i <= N + 1; ++i){
        fin >> R[i].x1 >> R[i].y2 >> R[i].x2 >> R[i].y1;
    }

    std::vector<int> prefX1(N + 3, 0), prefX2(N + 3, INF);
    std::vector<int> prefY1(N + 3, 0), prefY2(N + 3, INF);

    for(int i = 1; i <= N + 1; ++i){
        prefX1[i] = std::max(prefX1[i - 1], R[i].x1);
        prefX2[i] = std::min(prefX2[i - 1], R[i].x2);
        prefY1[i] = std::max(prefY1[i - 1], R[i].y1);
        prefY2[i] = std::min(prefY2[i - 1], R[i].y2);
    }

    std::vector<int> suffX1(N + 3, 0), suffX2(N + 3, INF);
    std::vector<int> suffY1(N + 3, 0), suffY2(N + 3, INF);

    for(int i = N + 1; i >= 1; --i){
        suffX1[i] = std::max(suffX1[i + 1], R[i].x1);
        suffX2[i] = std::min(suffX2[i + 1], R[i].x2);
        suffY1[i] = std::max(suffY1[i + 1], R[i].y1);
        suffY2[i] = std::min(suffY2[i + 1], R[i].y2);
    }

    long long minDist = -1;
    int bestX = -1, bestY = -1;

    for(int i = 1; i <= N + 1; ++i){
        int X1 = std::max(prefX1[i - 1], suffX1[i + 1]);
        int X2 = std::min(prefX2[i - 1], suffX2[i + 1]);
        int Y1 = std::max(prefY1[i - 1], suffY1[i + 1]);
        int Y2 = std::min(prefY2[i - 1], suffY2[i + 1]);

        if(X1 <= X2 && Y1 <= Y2){
            long long dist = 1LL * X1 * X1 + 1LL * Y1 * Y1; 
            
            if(minDist == -1 || dist < minDist){
                minDist = dist;
                bestX = X1;
                bestY = Y1;
            }
            else if (dist == minDist){
                if (X1 < bestX) {
                    bestX = X1;
                    bestY = Y1;
                }
            }
        }
    }

    if(minDist != -1){
        fout << bestX << " " << bestY << "\n";
    }
    else{
        fout << "NU\n";
    }
}