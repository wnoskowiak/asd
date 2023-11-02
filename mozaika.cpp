#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <cmath>
#include <map>

int main()
{
    std::map<int, unsigned long> memory;
    std::cin.sync_with_stdio(false);
    int n, m, head, temp;
    std::cin >> m;
    std::cin >> n;
    unsigned long lengths[n + 1], cache, t_cache, sum;
    head = 1;
    for (int i = 0; i < n + 1; i++)
    {
        lengths[i] = 1;
    }
    memory.insert({1, n+1});

    for (int i = 0; i < m; i++)
    {

        std::cin >> temp;
        if (temp <= head)
        {
            std::cout << memory[temp] << " ";
        }
        else
        {
            for (int k = head; k < temp; k++)
            {
                cache = lengths[0];
                lengths[0] = (cache + lengths[1]) % 1000000000;
                sum = lengths[0];
                for (int j = 1; j < n; j++)
                {
                    t_cache = lengths[j];
                    lengths[j] = (cache + lengths[j] + lengths[j + 1]) % 1000000000;
                    sum += lengths[j];
                    sum %= 1000000000;
                    cache = t_cache;
                }
                lengths[n] = (cache + lengths[n]) % 1000000000;
                sum += lengths[n];
                sum %= 1000000000;
                head++;
                memory.insert({head, sum});
                
            }
            std::cout << sum << " ";
        }
    }
}