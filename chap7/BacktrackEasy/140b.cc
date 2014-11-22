/* Title: 140
 * 考察点：简单的构造图，然后全排列节点遍历就行了
 * 忘记加endl结果调多调了2个小时*/
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

void test_graph(const map<char, vector<char> > &g);
int cal(const vector<char> &nodes, const map<char, vector<char> > &g);
bool already_in(const vector<char> &vec, char c);
int main()
{
    string temp;
    while (cin >> temp) {
        if (temp[0] == '#')
            break;
        temp.push_back(';');
        size_t pos = 0;
        map<char, vector<char> > graph;
        size_t next_pos = 0;
        while (next_pos = temp.find(';', pos)) {
            vector<char> vec;
            for (int i = pos+2; i < next_pos; i++) {
                vec.push_back(temp[i]);
            }

            if (graph.find(temp[pos]) == graph.end()) {
                graph[temp[pos]] = vec;
            }
            else {
                for (int i = 0; i < vec.size(); i++)
                    if (!already_in(graph[temp[pos]], vec[i]))
                    graph[temp[pos]].push_back(vec[i]);
            }

            pos = next_pos+1;
            if (pos == temp.size())
                break;
        }

        vector<char> nodes;
        sort(temp.begin(), temp.end());
        char last = 'a';
        for (int i = 0; i < temp.size(); i++) {
            if (temp[i] >= 'A' && temp[i] <= 'Z') {
                if (last != temp[i]) {
                nodes.push_back(temp[i]);
                last = temp[i];
                }
            }
        }

        vector<char> res = nodes;
        int min_bandwidth = 100;
        do {
            int bandwidth = cal(nodes, graph);
            if (bandwidth < min_bandwidth ) {
                min_bandwidth = bandwidth;
                res = nodes;
            }
        } while(next_permutation(nodes.begin(), nodes.end()));

        for (int i = 0; i < res.size(); i++) 
            cout << res[i] << " ";
        cout << "-> " << min_bandwidth << endl;
    }
}

bool already_in(const vector<char> &vec, char c)
{
    for (int i = 0; i < vec.size(); i++)
        if (vec[i] == c)
            return 1;
    return 0;
}

int cal(const vector<char> &nodes, const map<char, vector<char> > &g)
{
    map<char, int> position;
    for (int i = 0; i < nodes.size(); i++)
        position[nodes[i]] = i;

    int bandwidth = 1;
    for (map<char, vector<char> >::const_iterator it = g.begin(); it != g.end(); it++) {
        char s, t;
        s = it->first;
        for (int i = 0; i < it->second.size(); i++) {
            t = it->second[i];
            int dis = abs(position[s] - position[t]);
            bandwidth = bandwidth > dis ? bandwidth : dis;
        }
    }
    return bandwidth;
}

void test_graph(const map<char, vector<char> > &g)
{
    for (map<char, vector<char> >::const_iterator it = g.begin(); it != g.end(); it++) {
        cout << it->first << ": ";
        for (int i = 0; i < it->second.size(); i++)
            cout << it->second[i] << " ";
        cout << endl;
    }
}
