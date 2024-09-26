#include <bits/stdc++.h>

using namespace std;

void combination(set<vector<int>> &result, vector<int> &comb, vector<int> &num, int start)
{
    if (comb.size() == 3)
    {
        result.insert(comb);
        return;
    }
    for (int i = start; i < num.size(); ++i)
    {
        comb.emplace_back(num[i]);
        combination(result, comb, num, i + 1);
        comb.pop_back();
    }
}

int main()
{
    int n, target;
    vector<int> vec;
    cin >> n >> target;
    int num;
    for (int i = 0; i < n; ++i)
    {
        cin >> num;
        vec.emplace_back(num);
    }
    sort(vec.begin(), vec.end());
    set<vector<int>> result;
    vector<int> comb;
    combination(result, comb, vec, 0);
    // delete unquie

    for (auto itr = result.begin(), end = result.end(); itr != end; ++itr)
    {
        int sum = 0;
        for (auto jtr = itr->begin(), jnd = itr->end(); jtr != jnd; ++jtr)
        {
            sum += *jtr;
        }
        if (sum == target)
        {
            for (auto jtr = itr->begin(), jnd = itr->end(); jtr != jnd; ++jtr)
            {
                cout << *jtr << " ";
            }
            cout << endl;
        }
    }

    return 0;
}
