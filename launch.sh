linkToFoler="$(pwd)/"
echo "Compiling..."

if [[ "$OSTYPE" == "msys"* ]]; then
    nameOfCompiled="sudoku.exe"
else
    nameOfCompiled="sudoku.out"
fi
returnVal=$(gcc -Werror -Wall -o "${linkToFoler}${nameOfCompiled}" -g "${linkToFoler}main.c" "${linkToFoler}function.c" 2>&1)
long=$(echo "$returnVal" | wc -c)
if [ "$long" = "1" ]; then
    echo "Compiling finished"
    ./$nameOfCompiled
else
    echo "Compiling failed"
    echo "$returnVal"
fi
exit 0
