for dir in `ls .`
do 
  if [ -d $dir ]
  then
#    echo $dir
    cd $dir
    fname=`echo $dir`
    echo $fname
#    ./${fname}
# replace    
#     sed -i "s/simple_framework1/framework_lib/g" ./CMakeLists.txt    
# delete    
     sed -i "/#define WINDOW_W/d" ./CMakeLists.txt    
#     sed -i "s/__FILE__/\"$fname\"/g" ./*.cpp
#     sed -i "s/\/\/string file =/string file =/g" ./*.cpp
    cd ..
  fi
done
<<<<<<< HEAD
=======

#     sed -i "s/string/string1/g" `grep -rl "string" ./`
>>>>>>> 549860349127a063faa1d3a00b35b62bb548fbe0
