#include <bits/stdc++.h>
// cradit "https://www.youtube.com/watch?v=cjWnW0hdF1Y"

using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<double> wight;
    vector<int> price(n);

    int price1, w;
    for (int i = 0; i < n; i++)
    {
        cin >> price1 >> w;
        wight.emplace_back((double)w / (double)price1);
        price[i] = price1;
    }

    vector<pair<int, vector<int>>> LTS(n);
    for (auto &element : LTS)
    {
        element.first = 1;
    }

    for (int i = n - 1; i >= 0; i--)
    {
        LTS[i].second.emplace_back(i);
        for (int j = 1 + i; j < n; ++j)
        {
            if (wight[i] < wight[j])
            {
                if (LTS[i].first < LTS[j].first + 1)
                {
                    LTS[i].first = 1 + LTS[j].first;
                    LTS[i].second = LTS[j].second;
                    LTS[i].second.emplace_back(i);
                }
            }
        }
    }

    sort(LTS.begin(), LTS.end()); // change to using merge sort
    reverse(LTS.begin(), LTS.end());

    vector<int> ans(n, 0);
    auto itr = LTS.begin();
    int sum = 0;

    for (auto itr = LTS.begin(); itr != LTS.end(); ++itr)
    {
        cout << itr->first << " ";
        for (auto jtr = itr->second.rbegin(); jtr != itr->second.rend(); ++jtr)
        {
            cout << *jtr << " ";
        }
        cout << endl;
    }

    for (auto jtr = itr->second.rbegin(); jtr != itr->second.rend(); ++jtr)
    {
        cout << *jtr << " ";
        ans[*jtr] = 1;
    }
    cout << endl;

    for (int i = 0; i < n; i++)
    {
        cout << ans[i] << " ";
        if (ans[i] == 1)
        {
            sum += price[i];
        }
    }
    // cout << endl;
    // cout << sum << endl;

    return 0;
}