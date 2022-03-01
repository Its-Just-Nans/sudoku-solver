allTest=$(ls -1 *.c)
for oneFile in $allTest; do
    gcc -Wall -o "${name}.out" "$oneFile" ../function.c
    ./"${name}.out"
    echo "================================"
done
