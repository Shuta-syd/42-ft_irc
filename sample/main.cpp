#include <iostream>
#include <vector>
using namespace std;

int main() {
	vector<int> nbrs(10);
	for (int i = 0; i < 10; i++) {
		nbrs[i] = i;
	}
	vector<int>::iterator it = nbrs.begin();
	for (; it != nbrs.end(); it++) {
		if (*it == 1) {
			nbrs.erase(it);
		}
	}
	for (int i = 0; i < nbrs.size(); i++) {
		cout << nbrs[i] << endl;
	}
}
