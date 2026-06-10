/* Statement:
You are given a list of n workers. The skill of the i-th worker is i. For the i-th
worker, you know that they are willing to be in a team if there are at most
lowi other workers with lower skill than i. You also know that the i-th worker
is willing to be in a team if there are at most highi workers with higher skill
than i. Find a team of maximum possible size that can be formed. Aim for an
O(n log2 n) time complexity algorithm.
*/

/*
I know that after worker i the following are true:
- if I am to take him, from the range [i + 1, n - 1] I can select at most high_i workers
- if I am to take him, I need to have selected at most low_i workers in the range [0, i - 1]

I will be doing a binary search on the team size

Furthermore, I used AI to generate me a nice markdown so you can test the code=)))
*/

#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>

struct Worker{
    int skill;
    int low;
    int high;

    Worker() = default;
    Worker(int skill, int low, int high) : skill(skill), low(low), high(high) {}
};

int n;
std::vector<Worker> v;

std::ifstream fin("workers.in");
std::ofstream fout("workers.out");

bool check(int mid){
    std::vector<std::pair<int, int>> workers;

    for (int i = 0; i < n; ++i) {
        int L = std::max(1, mid - v[i].high);
        int R = std::min(mid, v[i].low + 1);
        if (L <= R) {
            workers.push_back({L, R});
        }
    }

    if (workers.size() < mid) {
        return false;
    }
    
    std::sort(workers.begin(), workers.end());

    std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
    int idx = 0;

    for (int i = 1; i <= mid; ++i) {
        while (idx < workers.size() && workers[idx].first <= i) {
            pq.push(workers[idx].second);
            ++idx;
        }
        while (!pq.empty() && pq.top() < i) {
            pq.pop();
        }
        if (pq.empty()) {
            return false;
        }
        pq.pop();
    }
    return true;
}

int main(){
    fin >> n;

    for(int i = 0; i < n; ++i){
        int low, high;
        fin >> low >> high;
        v.push_back(Worker(i, low, high));
    }

    int lo = 1, hi = n, res = 0; 
    while(lo <= hi){
        int mid = lo + (hi - lo) / 2;
        if(check(mid)){
            res = mid;
            lo = mid + 1;
        }
        else{
            hi = mid - 1;
        }
    }

    fout << res;
}