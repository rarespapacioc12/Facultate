// Submisie pe leetcode - https://leetcode.com/problems/remove-all-adjacent-duplicates-in-string-ii/submissions/1950466753/
// Nu stiu daca asa era intended, dar vad ca intra

#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

string s;
int k;

int main(){
    cin >> s;
    cin >> k;
    string sol = "";
    stack<pair<int, int> > S;
    int cur = 0, len = 0, n = s.length();
    for(int i = 0; i < n; ++i){
        len = 1;
        cur = i;
        i++;
        while(i < n && s[i] == s[cur] && len < k){
            ++i;
            ++len;
        }
        --i;
        if(len < k){
            if(S.empty()){
                S.push({cur, len});
            }
            else{
                if(s[S.top().first] == s[cur]){
                    if(S.top().second + len == k){
                        S.pop();
                    }
                    else if(S.top().second + len > k){
                        pair<int, int> p = S.top();
                        S.pop();
                        int newLen = p.second + len - k;
                        S.push({i - newLen + 1, newLen});
                    }
                    else{
                        pair<int, int> p = S.top();
                        S.pop();
                        S.push({p.first, p.second + len});
                    }
                }
                else{
                    S.push({cur, len});
                }
            }
        }
        if(i == n - 1)
            break;
    }
    vector<pair<int, int> > v;
    for(;!S.empty(); S.pop())
        v.push_back(S.top());
    reverse(v.begin(), v.end());
    for(auto [x, y] : v){
        for(int i = 0; i < y; ++i)
            sol += s[x];
    }
    std::cout << sol;
}