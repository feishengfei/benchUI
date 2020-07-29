for dir in `ls .`
do 
  if [ -d $dir ]
  then
#    echo $dir
    cd $dir
    fname=`echo $dir`
    echo $fname
    ./${fname}
    cd ..
  fi
done
