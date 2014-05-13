1. store these files in a directory you are comfortable with
2. g++ color.cpp -o .color_code
3. g++ branch.cpp -o .branch_name
4. add (or edit, if export PS1 exists) ~/.bashrc (or ~/.bash_profile if you in Mac) with the following 

export PS1="\u@\h \w \[\e[0;\$(path_to/.color_code)m\]\$(path_to/.branch_name)\[\e[m\]$ "