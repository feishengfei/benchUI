import os
import sys




if __name__ == '__main__':
    var = sys.argv[1]
    dump = sys.argv[2]
    print("----------------------" + var + "------------------------")
    if dump == "dump":
        os.environ['LD_LIBRARY_PATH']='/home/botson/work/gblib_dumping_20190815/lib'
        os.environ['DUMP_ALL']='1'
        os.system("rmmod /home/botson/work/gblib/gb.ko")
        os.system("insmod /home/botson/work/gblib/gb.ko")
        os.system("./" + var)
        os.environ['DUMP_ALL']='0'
    else:
        os.environ['DUMP_ALL']='0'
        os.system("./" + var)
#    print("LD_LIBRARY_PATH : " os.environ['LD_LIBRARY_PATH'])
#    print("DUMP_ALL : " os.environ['DUMP_ALL'])
