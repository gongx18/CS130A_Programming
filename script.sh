#! /bin/bash

# Results directory:
DIR=whatever
mkdir "$DIR"

# Defaults:
m=100000
n=9000
k=1

# Do stuff:
for k in {1..100}; do
  echo "Running with m=$m; n=$n; k=$k..."
  echo "$m" >> "$DIR/m.tsv"
  echo "$n" >> "$DIR/n.tsv"
  echo "$k" >> "$DIR/k.tsv"
  ./bloom -n "$n" -m "$m" -k "$k" -f -s pearson -i division   dataset2.txt >> "$DIR/pd.tsv"
  ./bloom -n "$n" -m "$m" -k "$k" -f -s pearson -i reciprocal dataset2.txt >> "$DIR/pr.tsv"
  ./bloom -n "$n" -m "$m" -k "$k" -f -s pearson -i squareroot dataset2.txt >> "$DIR/ps.tsv"
  ./bloom -n "$n" -m "$m" -k "$k" -f -s jenkins -i division   dataset2.txt >> "$DIR/jd.tsv"
  ./bloom -n "$n" -m "$m" -k "$k" -f -s jenkins -i reciprocal dataset2.txt >> "$DIR/jr.tsv"
  ./bloom -n "$n" -m "$m" -k "$k" -f -s jenkins -i squareroot dataset2.txt >> "$DIR/js.tsv"
done

# Concatenate all the results into one big TSV file:
paste "$DIR/m.tsv" "$DIR/n.tsv" "$DIR/k.tsv" "$DIR/pd.tsv" "$DIR/pr.tsv" "$DIR/ps.tsv" "$DIR/jd.tsv" "$DIR/jr.tsv" "$DIR/js.tsv" > "$DIR/all.tsv"
