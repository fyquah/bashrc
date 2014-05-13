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

short get_code(string status) {
	if (status.find("untracked files") != string::npos)
		return 31;
	else if (status.find("to be committed") != string::npos || status.find("not staged") != string::npos)
		return 33;
	else 
		return 32;
	
}

int main() {
	if(opendir("./.git") == NULL){
		cout << 30 << endl;
		return 0;
	}

	string status = exec("git status 2> /dev/null", true);
	
	cout << get_code(status , branch) << endl;

	return 0;
}