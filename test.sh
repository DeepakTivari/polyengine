
md5arr[1000]
for i in {1..1000}
do
   ./virus
   md5arr[i]=$(md5sum virus)
done

j=0
for i in {1..1000}
do
   if [[ $j != $i ]]
    then
      if [[ $md5arr[j] == $md5arr[i] ]]
      then
         echo "match"
      fi
   fi

   if [[ $j <= 999 ]]
    then
      if [[ $i == 999 ]]; then
         j=$j+1
         i=0
         echo "reset"
      fi
   fi

done
echo "complete"
