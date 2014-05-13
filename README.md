1. store these files in a directory you are comfortable with
2. g++ color.cpp -o .color_code (feel free to rename it)
3. Add the following lines to ~/.bashrc

parse_git_branch() {
    git branch 2> /dev/null | sed -e '/^[^*]/d' -e 's/* \(.*\)/ (\1)/'
}

export PS1="\u@\h \w\[\033[\$(path_to/.color_code)m\]\$(parse_git_branch)\[\033[00m\] $ "

4. Hit source ~/.bashrc , and you are good to go!