# ~/.bashrc
#
# This file is sourced by all *interactive* bash shells on startup,
# including some apparently interactive shells such as scp and rcp
# that can't tolerate any output.  So make sure this doesn't display
# anything or bad things will happen !


# Test for an interactive shell.  There is no need to set anything
# past this point for scp and rcp, and it's important to refrain from
# outputting anything in those cases.
if [[ $- != *i* ]] ; then
	# Shell is non-interactive.  Be done now!
	return
fi


export PATH="$HOME/.linuxbrew/bin:$PATH"
export MANPATH="$HOME/.linuxbrew/share/man:$MANPATH"
export INFOPATH="$HOME/.linuxbrew/share/info:$INFOPATH"


# Put your fun stuff here.
function lazygit() { 
    git add -A 
    printf "Commit Message: " 
    read msg 
    git commit -m msg 
    git push 
}
export PS1="\[\e[1;34m\]\u\[\e[0m\]@\h:\[\e[0;31m\]\w\[\e[0m\]$ "
alias ls="ls -GFh --color"
alias l="ls -GFh --color"
alias sl="ls -GFh --color"
alias la="ls -GFhA --color"
export HISTCONTROL=ignoredups
LS_COLORS=$LS_COLORS:'di=0;36:' ; export LS_COLORS
function activate() {
    . ~/$1/venv/bin/activate
}
alias ll="ls -Gfhl --color"

alias ccat='pygmentize -g -O style=colorful,linenos=1'
alias rebash='source ~/.bashrc'

function glut() {
    gcc $1 -std=c99 -lGL -lGLU -lglut -lm
    ./a.out
}
function glum() {
    mpicc $1 -std=c99 -lGL -lGLU -lglut -lm
    mpirun -np $2 -hostfile hosts.txt a.out
}
