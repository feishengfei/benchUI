for dir in `ls .`
do 
  rm cmake_install.cmake Makefile
  rm -rf CMakeFile*
  if [ -d $dir ]
  then
#    echo $dir
    cd $dir
    fname=`echo $dir`
    echo $fname
  rm cmake_install.cmake *.bmp *.log
  rm Makefile
  rm -rf CMakeFile*
    cd ..
  fi
done
