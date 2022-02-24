#include<bits/stdc++.h>
using namespace std;

int cntbrs, prjts;

struct contributor {
	pair<string,int> cr_name_skill;       // cr name and no of skills
	map<string,int> cr_details;    // skill name and level details
};
struct contributor crs[100000];

struct projects{
	string p_name;
	int days;
	int score;
	int best_before;
	int total_roles;
	vector<pair<string,int>> skl_req;	
    map<string, int> ord;		//skill & level required
};
struct projects pro[100000];

set<int> cntbrs_assigned;

vector<int> find_mentors(int mentee, int level, string skill){
    vector<int> ans;
    for(int i = 0; i < cntbrs; i++){
        if(crs[i].cr_details.find(skill) != crs[i].cr_details.end()){
            if(crs[i].cr_details[skill] >= level)
                ans.push_back(i);
        }
    }
    return ans;
}

bool canBeGiven(int cntbr, string role, int level){
    int aukat = crs[cntbr].cr_details[role];
    if(aukat >= level)
        return true;
    if(aukat + 1 != level)
        return false;
    vector<int> mentors = find_mentors(cntbr, level, role);
    for(auto i: mentors){
        if(cntbrs_assigned.find(i) != cntbrs_assigned.end())
            return true;
    }
    return false;
    
}

int giveContrubutor(string role, int level){
    for(int i = 0; i < cntbrs; i++){
        if(cntbrs_assigned.find(i) == cntbrs_assigned.end() && canBeGiven(i, role, level))
           return i; 
    }
    return -1;
}

int main(){
    ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
    
    cin >> cntbrs >> prjts;				// Taking contributors & Projects
    string c_name; 
	int noSkills;
    for(int i = 0; i < cntbrs; i++){
        cin >> c_name;
        cin >> noSkills;
        string skill_nm; int lev;

		crs[i].cr_name_skill.first = c_name;
		crs[i].cr_name_skill.second = noSkills;	//insert contbuitor name and total skills in cr_name_skills map;
		for(int j=0; j<noSkills; j++){
			cin >> skill_nm >> lev;
			crs[i].cr_details.insert( {skill_nm,lev } );	//insert contbuitor name and total skills in cr_name_skills map;
		}        
    }

	for(int i = 0; i < prjts; i++){
		cin >> pro[i].p_name;
		cin >> pro[i].days;
		cin >> pro[i].score;
		cin >> pro[i].best_before;
		cin >> pro[i].total_roles;
        string skl; int lev;
        for(int j = 0; j < pro[i].total_roles; j++){
            cin >> skl >> lev;
            pro[i].skl_req.push_back({skl,lev});
            pro[i].ord[skl] = j;
        }   
    }
    
    vector<pair<int, vector<int>>> ans(prjts);
    int tot = 0;
    int skills_covered = 0;
    for(int i = 0; i < prjts; i++){
        skills_covered = 0;
        for(auto j: pro[i].skl_req){
            int c = giveContrubutor(j.first, j.second);
            if(c != -1){
                //cout << i << " "<< j.first << " " << c << "\n";
                cntbrs_assigned.insert(c);
                ans[tot].first = i;
                ans[tot].second.push_back(c);
                skills_covered++;
                //cout << c << "* ";
            }
        }
        if(skills_covered == pro[i].total_roles){
            tot++;
        }
        else{
            ans[tot].second.clear();
        }
    }
    cout << tot << "\n";
    for(int i = 0; i < tot; i++){
        cout << pro[ans[i].first].p_name << "\n";
        for(auto i: ans[i].second)
            cout << crs[i].cr_name_skill.first << " ";
        cout << "\n";
    }


}