#rm -rf ../tmp/*
#rm -rf es*
#cp -r /home/botson/work/ericc/BTStestbench/samples/basic_test/es* ./
#echo > tmp.txt
#python modfile.py

for line in `cat tmp.txt`
do
 mv $line ../tmp/
done

#for dir in `ls .`
#do
#  if [ -d dir ]; then
#    pushd dir
#    sed -i '/^[[:blank:]]*eglSwapBuffer/a\#ifdef DUMP\n    break;\n#endif' *.cpp
#    popd
#  fi
#done

#mv ../tmp/es11* es11/
#mv ../tmp/es20* es20/
#mv ../tmp/es30* es30/
#mv ../tmp/es31* es31/
#mv ../tmp/es32* es32/

#python getfor.py
