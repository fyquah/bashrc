#include <string>
#include <iostream>
#include <cstdio>
using namespace std;

string exec(char *cmd, bool downcase = false) {
	FILE* pipe = popen(cmd, "r");
	if (!pipe) {
		return "";
	}
	char buffer[128];
	string result = "";
	while (!feof(pipe)) {
		if (fgets(buffer, 128, pipe) != NULL) {
			result += buffer;
		}
	}
	pclose(pipe);

	if (downcase) {
		for (int i = 0; i < result.length(); i++) {
			if (result[i] >= 'A' && result[i] <= 'Z') {
				result[i] -= ('A' - 'a');
			}
		}
	}

	return result;
}

string get_current_branch(string input) {
	int star = input.find("*");
	int newline = input.find("\n", star);
	return input.substr(star+2, newline-star-2);
}

short get_colored_string(string status, string branch) {
	if (status.find("untracked files") != string::npos) {
		return 31;
	} else if (status.find("to be committed") != string::npos || status.find("not staged") != string::npos) {
		return 33;
	} else {
		return 32;
	}
}

int main() {
	string status = exec("git status 2> /dev/null", true);
	string branch = exec("git branch 2> /dev/null");

	if (status.length() == 0 || branch.length() == 0) {
		cout << 29 << endl;
		return 0;
	}
	cout << get_colored_string(status , branch) << endl;

	return 0;
}