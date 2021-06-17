for i in {1..5}
do
	perf stat ./sort > $i.txt
done
