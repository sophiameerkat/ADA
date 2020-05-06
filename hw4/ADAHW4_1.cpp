#include <iostream>
using namespace std;

#ifndef DIMACS
#include <cryptominisat5/cryptominisat.h>
#else
#include <fstream>
#include <vector>
#endif

namespace sat {

#ifndef DIMACS

CMSat::SATSolver solver;
std::vector<CMSat::Lit> lit_buf;

void Init(int n) { solver.new_vars(n + 1); }

void AddClause(std::vector<int> v) {
	lit_buf.clear();
	lit_buf.reserve(v.size());
	for (int x : v) lit_buf.emplace_back(abs(x), x < 0);
	solver.add_clause(lit_buf);
}

bool Solve() { return solver.solve() == CMSat::l_True; }

int GetResult(int id) {
	auto r = solver.get_model()[id];
	return r == CMSat::l_True ? 1 : r == CMSat::l_False ? -1 : 0;
}

#else

std::vector<std::vector<int>> clauses;
int n_vars;

void Init(int n) { n_vars = n; }

void AddClause(std::vector<int> v) { clauses.emplace_back(std::move(v)); }

bool Solve() {
	std::fstream fs("out.dimacs", fs.trunc | fs.out);
	fs << "p cnf " << n_vars << ' ' << clauses.size() << '\n';
	for (auto &v : clauses) {
		for (auto x : v) fs << x << ' ';
		fs << "0\n";
	}
	fs.close();
	exit(0);
}

int GetResult(int id) { return 0; }

#endif // DIMACS

}  // namespace sat

int r, c;
vector<int> v[130*130];
vector<int> p[130*130];
vector<int> e[2*130*130+260];
char in[130*130];
bool use[2*130*130+260];

void construct_cell(){
	for (int i = 1; i <= r; ++i){
		for (int j = 1; j <= c; ++j){
			v[(i-1)*c+j].push_back((i-1)*(2*c+1)+j);
			v[(i-1)*c+j].push_back((i-1)*(2*c+1)+j+c);
			v[(i-1)*c+j].push_back((i-1)*(2*c+1)+j+c+1);
			v[(i-1)*c+j].push_back((i)*(2*c+1)+j);
		}
	}
}

void construct_point(){
	for (int i = 0; i <= r; ++i){
		for (int j = 0; j <= c; ++j && i != 0){
			if ((i)*(c)+(i-1)*(c+1)+j+1 > 0)
				p[i*(c+1)+j+1].push_back((i)*(c)+(i-1)*(c+1)+j+1);
			if ((i)*(2*c+1)+j > 0 && j != 0)
				p[i*(c+1)+j+1].push_back((i)*(2*c+1)+j);
			if ((i)*(2*c+1)+j+1 > 0 && j != c)
				p[i*(c+1)+j+1].push_back((i)*(2*c+1)+j+1);
			if ((i+1)*(c)+i*(c+1)+j+1 > 0 && i != r)
				p[i*(c+1)+j+1].push_back((i+1)*(c)+i*(c+1)+j+1);
		}
	}
}

void construct_edge(){
	for (int i = 1; i <= (r+1)*(c+1); ++i){
		if (p[i].size() == 2){
			e[p[i][0]].push_back(p[i][1]);
			e[p[i][1]].push_back(p[i][0]);
		}
		else if (p[i].size() == 3){
			e[p[i][0]].push_back(p[i][1]);
			e[p[i][0]].push_back(p[i][2]);
			e[p[i][1]].push_back(p[i][0]);
			e[p[i][1]].push_back(p[i][2]);
			e[p[i][2]].push_back(p[i][0]);
			e[p[i][2]].push_back(p[i][1]);
		}
		else if (p[i].size() == 4){
			e[p[i][0]].push_back(p[i][1]);
			e[p[i][0]].push_back(p[i][2]);
			e[p[i][0]].push_back(p[i][3]);
			e[p[i][1]].push_back(p[i][0]);
			e[p[i][1]].push_back(p[i][2]);
			e[p[i][1]].push_back(p[i][3]);
			e[p[i][2]].push_back(p[i][0]);
			e[p[i][2]].push_back(p[i][1]);
			e[p[i][2]].push_back(p[i][3]);
			e[p[i][3]].push_back(p[i][0]);
			e[p[i][3]].push_back(p[i][1]);
			e[p[i][3]].push_back(p[i][2]);
		}
	}
}

void add_1(int i, vector<int> &tmp){
	tmp.push_back(-v[i][0]);
	tmp.push_back(-v[i][1]);
	sat::AddClause(tmp);
	tmp.clear();
	tmp.push_back(-v[i][0]);
	tmp.push_back(-v[i][2]);
	sat::AddClause(tmp);
	tmp.clear();
	tmp.push_back(-v[i][0]);
	tmp.push_back(-v[i][3]);
	sat::AddClause(tmp);
	tmp.clear();
	tmp.push_back(v[i][0]);
	tmp.push_back(v[i][1]);
	tmp.push_back(v[i][2]);
	tmp.push_back(v[i][3]);
	sat::AddClause(tmp);
	tmp.clear();
	tmp.push_back(-v[i][1]);
	tmp.push_back(-v[i][2]);
	sat::AddClause(tmp);
	tmp.clear();
	tmp.push_back(-v[i][1]);
	tmp.push_back(-v[i][3]);
	sat::AddClause(tmp);
	tmp.clear();
	tmp.push_back(-v[i][2]);
	tmp.push_back(-v[i][3]);
	sat::AddClause(tmp);
	tmp.clear();
}

void add_2(int i, vector<int> &tmp){
	tmp.push_back(-v[i][0]);
	tmp.push_back(-v[i][1]);
	tmp.push_back(-v[i][2]);
	sat::AddClause(tmp);
	tmp.clear();
	tmp.push_back(-v[i][0]);
	tmp.push_back(-v[i][1]);
	tmp.push_back(-v[i][3]);
	sat::AddClause(tmp);
	tmp.clear();
	tmp.push_back(-v[i][0]);
	tmp.push_back(-v[i][2]);
	tmp.push_back(-v[i][3]);
	sat::AddClause(tmp);
	tmp.clear();
	tmp.push_back(v[i][0]);
	tmp.push_back(v[i][1]);
	tmp.push_back(v[i][2]);
	sat::AddClause(tmp);
	tmp.clear();
	tmp.push_back(v[i][0]);
	tmp.push_back(v[i][1]);
	tmp.push_back(v[i][3]);
	sat::AddClause(tmp);
	tmp.clear();
	tmp.push_back(v[i][0]);
	tmp.push_back(v[i][2]);
	tmp.push_back(v[i][3]);
	sat::AddClause(tmp);
	tmp.clear();
	tmp.push_back(-v[i][1]);
	tmp.push_back(-v[i][2]);
	tmp.push_back(-v[i][3]);
	sat::AddClause(tmp);
	tmp.clear();
	tmp.push_back(v[i][1]);
	tmp.push_back(v[i][2]);
	tmp.push_back(v[i][3]);
	sat::AddClause(tmp);
	tmp.clear();
}

void add_3(int i, vector<int> &tmp){
	tmp.push_back(-v[i][0]);
	tmp.push_back(-v[i][1]);
	tmp.push_back(-v[i][2]);
	tmp.push_back(-v[i][3]);
	sat::AddClause(tmp);
	tmp.clear();
	tmp.push_back(v[i][0]);
	tmp.push_back(v[i][1]);
	sat::AddClause(tmp);
	tmp.clear();
	tmp.push_back(v[i][0]);
	tmp.push_back(v[i][2]);
	sat::AddClause(tmp);
	tmp.clear();
	tmp.push_back(v[i][0]);
	tmp.push_back(v[i][3]);
	sat::AddClause(tmp);
	tmp.clear();
	tmp.push_back(v[i][1]);
	tmp.push_back(v[i][2]);
	sat::AddClause(tmp);
	tmp.clear();
	tmp.push_back(v[i][1]);
	tmp.push_back(v[i][3]);
	sat::AddClause(tmp);
	tmp.clear();
	tmp.push_back(v[i][2]);
	tmp.push_back(v[i][3]);
	sat::AddClause(tmp);
	tmp.clear();
}

void add_to_clause_cell(){
	for (int i = 1; i <= r*c; ++i){
		vector<int> tmp;
		if (in[i] == '.')
			continue;
		if (in[i] - '0' == 0){
			tmp.push_back(-v[i][0]);
			sat::AddClause(tmp);
			tmp.clear();
			tmp.push_back(-v[i][1]);
			sat::AddClause(tmp);
			tmp.clear();
			tmp.push_back(-v[i][2]);
			sat::AddClause(tmp);
			tmp.clear();
			tmp.push_back(-v[i][3]);
			sat::AddClause(tmp);
			tmp.clear();
		}
		else if (in[i] - '0' == 1)
			add_1(i, tmp);
		else if (in[i] - '0' == 2)
			add_2(i, tmp);
		else if (in[i] - '0' == 3)
			add_3(i, tmp);
	}
}

void add_2_point(int i, vector<int> &t){
	t.push_back(-p[i][0]);
	t.push_back(-p[i][1]);
	t.push_back(-p[i][2]);
	sat::AddClause(t);
	t.clear();
	t.push_back(-p[i][0]);
	t.push_back(-p[i][1]);
	t.push_back(-p[i][3]);
	sat::AddClause(t);
	t.clear();
	t.push_back(-p[i][0]);
	t.push_back(p[i][1]);
	t.push_back(p[i][2]);
	t.push_back(p[i][3]);
	sat::AddClause(t);
	t.clear();
	t.push_back(-p[i][0]);
	t.push_back(-p[i][2]);
	t.push_back(-p[i][3]);
	sat::AddClause(t);
	t.clear();
	t.push_back(p[i][0]);
	t.push_back(-p[i][1]);
	t.push_back(p[i][2]);
	t.push_back(p[i][3]);
	sat::AddClause(t);
	t.clear();
	t.push_back(p[i][0]);
	t.push_back(p[i][1]);
	t.push_back(-p[i][2]);
	t.push_back(p[i][3]);
	sat::AddClause(t);
	t.clear();
	t.push_back(p[i][0]);
	t.push_back(p[i][1]);
	t.push_back(p[i][2]);
	t.push_back(-p[i][3]);
	sat::AddClause(t);
	t.clear();
	t.push_back(-p[i][1]);
	t.push_back(-p[i][2]);
	t.push_back(-p[i][3]);
	sat::AddClause(t);
	t.clear();
}

void add_3_point(int i, vector<int> &t){
	t.push_back(-p[i][0]);
	t.push_back(-p[i][1]);
	t.push_back(-p[i][2]);
	sat::AddClause(t);
	t.clear();
	t.push_back(-p[i][0]);
	t.push_back(p[i][1]);
	t.push_back(p[i][2]);
	sat::AddClause(t);
	t.clear();
	t.push_back(p[i][0]);
	t.push_back(-p[i][1]);
	t.push_back(p[i][2]);
	sat::AddClause(t);
	t.clear();
	t.push_back(p[i][0]);
	t.push_back(p[i][1]);
	t.push_back(-p[i][2]);
	sat::AddClause(t);
	t.clear();
}

void add_to_clause_point(){
	for (int i = 1; i <= (r+1)*(c+1); ++i){
		vector<int> t;
		if (p[i].size() == 2){
			t.push_back(-p[i][0]);
			t.push_back(p[i][1]);
			sat::AddClause(t);
			t.clear();
			t.push_back(p[i][0]);
			t.push_back(-p[i][1]);
			sat::AddClause(t);
			t.clear();
		}
		else if (p[i].size() == 3)
			add_3_point(i, t);
		else if (p[i].size() == 4){
			add_2_point(i, t);
		}
	}
}

void dfs(int point, vector<int> &an){
	for (int i = 0; i < e[point].size(); ++i){
		if (sat::GetResult(e[point][i]) == 1 && use[e[point][i]] == false){
			use[e[point][i]] = true;
			an.push_back(-e[point][i]);
			dfs(e[point][i], an);
		}
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> r >> c;
	sat::Init(2*r*c+r+c);
	for (int i = 1; i <= r; ++i){
		for (int j = 1; j <= c; ++j)
			cin >> in[(i-1)*c+j];
	}
	construct_cell();
	construct_point();
	construct_edge();
	add_to_clause_cell();
	add_to_clause_point();
	vector<int> an;
	while (sat::Solve()){
		for (int i = 1; i <= 2*r*c+r+c; ++i)
			use[i] = false;
		int cnt = 0;
		for (int i = 1; i <= 2*r*c+r+c; ++i){
			if (sat::GetResult(i) == 1 && use[i] == false){
				an.clear();
				dfs(i, an);
				sat::AddClause(an);
				cnt++;
			}
		}
		if (cnt == 1)
			break;		
	}
	for (int i = 1; i <= 2*r*c+r+c; ++i){
		if (sat::GetResult(i) == 1)
			cout << "1";
		else
			cout << "0";
	}
	return 0;
}