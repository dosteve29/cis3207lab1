for f in *.txt;
do (cat "${f}"; echo ',') >> data2organized.csv;
done
