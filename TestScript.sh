NumTestFiles=$(ls ./TestCases/Inputs/ | wc -l)
for i in $(seq 1 $NumTestFiles);  do
    ./Dijkstra < ./TestCases/Inputs/$i.txt > temp.txt
    if cmp temp.txt ./TestCases/Outputs/$i.txt > /dev/null; then
        echo "Passed test case $i.txt ✔"
    else
        echo "Failed test case $i.txt ✗"
    fi
done
rm temp.txt