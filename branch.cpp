#include <string>
#include <iostream>
#include <cstdio>
#include <dirent.h>
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

int main() {
	if(opendir("./.git") == NULL) return 0;

	string status = exec("git status 2> /dev/null", true);
	string branch = exec("git branch 2> /dev/null");

	if (status.length() == 0 || branch.length() == 0) {
		return 0;
	}
	cout << "(" << get_current_branch(branch) << ")" << endl;

	return 0;
}