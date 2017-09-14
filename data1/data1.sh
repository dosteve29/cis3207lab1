for f in *.txt;
do (cat "${f}"; echo ',') >> data1organized.csv;
done
