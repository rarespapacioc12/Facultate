/* Idee:
Observ ca pot sa mut bitii cum vreau in cadrul unei subsecvente
Tin sume partiale ca sa aflu cati biti am din fiecare pt o subsecventa data
Ideal bitii mari sa ii am singuri ca sa nu apara si cand ridic la putere
*/

#include <fstream>
#include <vector>

std::ifstream fin("sufle.in");
std::ofstream fout("sufle.out");

int N, Q;
std::vector<std::vector<int> > fr;

int main(){
    fin >> N >> Q;

    fr.resize(N + 1, std::vector<int>(20, 0));

    for(int x, i = 1; i <= N; ++i){
        fin >> x;
        for(int j = 0; j < 20; ++j){
            fr[i][j] = fr[i - 1][j] + ((x >> j) & 1);
        }
    }

    for(int l, r; Q--;){
        fin >> l >> r;
        std::vector<int> bits(20, 0);
        for(int i = 0; i < 20; ++i){
            bits[i] = fr[r][i] - fr[l - 1][i];
        }

        
    }
}
