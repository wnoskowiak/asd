#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <cmath>
#include <set>
#include <algorithm>

struct fragType
{
    int begin, end;
    bool color;
    bool operator<(const fragType &a) const
    {
        return this->begin < a.begin;
    }
};

auto &road()
{
    static std::set<fragType> global_map;
    return global_map;
}

auto &how_many_white()
{
    static int km = 0;
    return km;
}

void corr(int del)
{
    // std::cout << del << "dupa corr " << std::endl;
    how_many_white() += del;
}

void addFragment(int begin, int end, bool color)
{
    // std::cout << "dupa" << std::endl;
    auto &street = road();
    if (street.size() == 0)
    {
        // std::cout << "dupa exit" << std::endl;
        street.insert({begin, end, color});
        // std::cout << begin << " " << end << " " << color << std::endl;
        return;
    }
    auto lower = street.upper_bound({begin, 0, false});
    auto higher = street.upper_bound({end, 0, false});
    lower--;
    higher--;
    // std::cout << begin << " " << 0 << " " << false << std::endl;
    // std::cout << (*lower).begin << " " << (*lower).end << " " << (*lower).color << std::endl;
    // std::cout << (*higher).begin << " " << (*higher).end << " " << (*higher).color << std::endl;
    int whites = 0;
    fragType left = *lower, right = *higher;
    if (lower != higher)
    {
        // std::cout << "dupa1" << std::endl;
        for (auto i = lower; i != higher; i++)
        {
            // std::cout << (*street.end()).begin << " " << (*street.end()).end << " " << (*street.end()).color << "dupa1" << std::endl;
            // std::cout<< (*i).begin << " " << (*i).end << " " << (*i).color <<std::endl;
            if ((*i).color)
            {
                whites += (*i).end - (*i).begin;
            }
        }
        street.erase(lower,higher);
        if ((*higher).color)
        {
            whites += (*higher).end - (*higher).begin;
        }
        street.erase(higher);
    }
    else
    {
        // std::cout << "dupa2" << std::endl;
        if ((*higher).color)
        {
            whites += (*higher).end - (*higher).begin;
        }
        street.erase(higher);
    }

    std::vector<fragType> a;
    if (left.begin != begin)
    {
        a.push_back({left.begin, begin, left.color});
        if (left.color == color)
        {
            a[0].end = end;
        }
        else
        {
            a.push_back({begin, end, color});
        }
    }
    else
    {
        a.push_back({begin, end, color});
    }
    if (right.color == color)
    {
        a[a.size() - 1].end = right.end;
    }
    else
    {
        a.push_back({end, right.end, right.color});
    }
    whites *= -1;
    for (int i = 0; i < a.size(); i++)
    {
        if (a[i].color)
        {
            whites += a[i].end - a[i].begin;
        }
        street.insert(a[i]);
    }
    corr(whites);
}

int main()
{
    std::cin.sync_with_stdio(false);
    int n, m, a, b;
    char eeee;
    std::cin >> n;
    std::cin >> m;

    // std::cout<<m<<std::endl;
    // std::set<fragType> gm{fragType{0,12,false}};
    // const auto dupa = fragType{2,5,true};
    // gm.insert(dupa);
    // auto lower = gm.lower_bound({1,5,true});
    // auto upper = gm.upper_bound({1,5,true});
    // for(auto it = gm.begin(); it != gm.end(); it++){
    //     std::cout << (*it).begin << " " << (*it).end << " " << (*it).color << std::endl;
    // }
    // std::cout << (*lower).begin << " " << (*lower).end << " " << (*lower).color << std::endl;
    // std::cout << (*upper).begin << " " << (*upper).end << " " << (*upper).color << std::endl;

    addFragment(0, n, false);
    // std::cin >> a;
    // std::cin >> b;
    // std::cin >> eeee;
    // std::cout << 7 << "\n";
    // // std::cout<<a<<00<<b<<('B'==eeee);
    // std::cin >> a;
    // std::cin >> b;
    // std::cin >> eeee;
    // std::cout << 3 << "\n";
    // std::cin >> a;
    // std::cin >> b;
    // std::cin >> eeee;
    // std::cout << 5 << "\n";
    // std::cin >> a;
    // std::cin >> b;
    // std::cin >> eeee;
    // std::cout << a << 00 << b << 00 << int('B' == eeee) << "\n";
    for (int i = 0; i < m; i++)
    {
        std::cin >> a;
        std::cin >> b;
        std::cin >> eeee;
        addFragment(a-1, b, (eeee == 'B'));
        std::cout << how_many_white() << std::endl;
    }
    // std::cout << how_many_white() << std::endl;
}