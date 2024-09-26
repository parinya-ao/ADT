#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<pair<int, int>> v(n);
    vector<double> wight;

    for (int i = 0; i < n; i++)
    {
        cin >> v[i].first >> v[i].second;
        wight.emplace_back(v[i].second / v[i].first);
    }

    // for (auto itr = v.begin(), ite = v.end(); itr != ite; ++itr)
    // {
    //     cout << itr->first << " " << itr->second << endl;
    // }
    for (auto itr = wight.begin(), ite = wight.end(); itr != ite; ++itr)
    {
        cout << *itr << endl;
    }

    return 0;
}