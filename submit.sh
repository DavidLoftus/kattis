if test $# -lt 1; then
	echo "usage: $0 <problem>"
	exit 1
fi

PROBLEM=$1

if [ ! -d "$PROBLEM" ]; then
	echo "no such problem on local machine."
	exit 2
fi

shopt -s extglob
files="$PROBLEM"/!(test).?pp

python3 submit.py "$PROBLEM/$PROBLEM.cpp" $files

