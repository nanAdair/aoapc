/* Title: 10194
 * 考察点：字符串处理
 * sort使用
 * map使用*/
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cstdlib>
#include <algorithm>
using namespace std;

class Team
{
public:
    Team() {}
    Team(string &s):
        name(s),
        points(0),
        games(0),
        wins(0),
        ties(0),
        loses(0),
        gd(0),
        gs(0),
        ga(0)
    {}

    string name;
    int points;
    int games;
    int wins;
    int ties;
    int loses;
    int gd;
    int gs;
    int ga;
};

void analyze(map<string, Team> &teams, string &s);
bool cmp(const Team &t1, const Team &t2);
void output(const vector<Team> &teams);
string tolower(const string &s);

int main()
{
    int n;
    string temp;
    cin >> n;
    getline(cin, temp);

    for (int i = 0; i < n; i++) {
        map<string, Team> tournament;
        string tournament_name;
        getline(cin, tournament_name);

        int teams_num;
        cin >> teams_num;
        getline(cin, temp);
        for (int j = 0; j < teams_num; j++) {
            string team_name;
            getline(cin, team_name);

            tournament[team_name] = Team(team_name);
        }

        int games;
        cin >> games;
        getline(cin, temp);
        for (int j = 0; j < games; j++) {
            string result;
            getline(cin, result);
            analyze(tournament, result);
        }

        vector<Team> ranking;
        for (map<string, Team>::iterator it = tournament.begin(); it != tournament.end(); it++)
            ranking.push_back(it->second);

        sort(ranking.begin(), ranking.end(), cmp);

        cout << tournament_name << endl;
        output(ranking);

        if (i != n - 1)
            cout << endl;
    }
}

void analyze(map<string, Team> &teams, string &s)
{
    size_t jing1, jing2, a;
    jing1 = s.find_first_of("#");
    jing2 = s.find_last_of("#");
    a = s.find_first_of("@");

    string::iterator it = s.begin();
    string team1 (it, it + jing1);
    string score1 (it + jing1 + 1, it + a);
    string score2 (it + a + 1, it + jing2);
    string team2 (it + jing2 + 1, s.end());

    int s1, s2;
    s1 = atoi(score1.c_str());
    s2 = atoi(score2.c_str());

    teams[team1].games += 1;
    teams[team1].gs += s1;
    teams[team1].ga += s2;
    teams[team1].gd += (s1 - s2);

    teams[team2].games += 1;
    teams[team2].gs += s2;
    teams[team2].ga += s1;
    teams[team2].gd += (s2 - s1);

    if (s1 > s2) {
        teams[team1].points += 3;
        teams[team1].wins += 1;
        teams[team2].loses += 1;
    }
    else if (s1 < s2) {
        teams[team1].loses += 1;
        teams[team2].points += 3;
        teams[team2].wins += 1;
    }
    else {
        teams[team1].points += 1;
        teams[team1].ties += 1;
        teams[team2].points += 1;
        teams[team2].ties += 1;
    }
}

bool cmp(const Team &t1, const Team &t2)
{
    if (t1.points > t2.points)
        return 1;
    if (t1.points < t2.points)
        return 0;

    if (t1.wins > t2.wins)
        return 1;
    if (t1.wins < t2.wins)
        return 0;

    if (t1.gd > t2.gd)
        return 1;
    if (t1.gd < t2.gd)
        return 0;

    if (t1.gs > t2.gs)
        return 1;
    if (t1.gs < t2.gs)
        return 0;

    if (t1.games < t2.games)
        return 1;
    if (t1.games > t2.games)
        return 0;

    return tolower(t1.name) < tolower(t2.name);
}

string tolower(const string &s)
{
    string res;
    for (string::const_iterator it = s.begin(); it != s.end(); it++) {
        if (*it >= 'A' && *it <= 'Z')
            res.push_back(*it - 'A' + 'a');
        else
            res.push_back(*it);
    }
    return res;
}

void output(const vector<Team> &teams)
{
    int i = 1;
    for (vector<Team>::const_iterator it = teams.begin(); it != teams.end(); it++) {
        cout << i << ") ";
        cout << it->name << " " << it->points << "p, " << it->games << "g ("
            << it->wins << "-" << it->ties << "-" << it->loses << "), "
            << it->gd << "gd (" << it->gs << "-" << it->ga << ")" << endl;
        i++;
    }
}
