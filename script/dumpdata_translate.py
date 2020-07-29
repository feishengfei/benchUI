#! /usr/bin/env python
# =================================================================
# Copyright (c) 2018 Botson Corp 
# Botson Confidential and Proprietary 
#
# Revision: 
# Date: 2018-11-27
# Author: 
# Descriptions: 
# 
# =================================================================

# How to
# gdb break function: cinstrp_dump_memory

import os

def create_config_file():
    cfg_file = open("config.txt", "w");
    cfg_file.write("reset\n");

    hexlist = os.popen("ls pa_input*.hex");
    for line in hexlist:
        cfg_file.write("load_mem %s\n" % (line.strip()));
    hexlist = os.popen("ls mmu_pagetable-*.hex");
    for line in hexlist:
        cfg_file.write("load_mem %s\n" % (line.strip()));

    cfg_tex = os.popen('grep {} messages'.format('"w: reg"'));
    for line in cfg_tex:
        data = line.strip().split();
        regindex = data[-3];
        regvalue = data[-1];
        cfg_file.write("writereg 2000%s %s\n" % (regindex, regvalue));

        if (regindex == "01a0"):
            cfg_file.write("wait posedge irq\n");
            cfg_file.write("writereg 20000024 00010581\n");
            cfg_file.write("writereg 20000028 00010581\n");
            cfg_file.write("writereg 20001004 ffffffff\n");
            cfg_file.write("writereg 20001008 ffffffff\n");
            cfg_file.write("writereg 20002004 ffffffff\n");
            cfg_file.write("writereg 20002008 ffffffff\n\n");
 
        if (regindex == "0180"):
            cfg_file.write("wait posedge irq\n");
            cfg_file.write("writereg 20000024 00010581\n");
            cfg_file.write("writereg 20000028 00010581\n");
            cfg_file.write("writereg 20001004 ffffffff\n");
            cfg_file.write("writereg 20001008 ffffffff\n");
            cfg_file.write("writereg 20002004 ffffffff\n");
            cfg_file.write("writereg 20002008 ffffffff\n\n");

        if (regindex == "18e0"):
            cfg_file.write("wait posedge irq\n");
            cfg_file.write("writereg 20000024 00010581\n");
            cfg_file.write("writereg 20000028 00010581\n");
            cfg_file.write("writereg 20001004 ffffffff\n");
            cfg_file.write("writereg 20001008 ffffffff\n");
            cfg_file.write("writereg 20002004 ffffffff\n");
            cfg_file.write("writereg 20002008 ffffffff\n\n");

   
        if (regindex == "1860"):
            cfg_file.write("wait posedge irq\n");
            cfg_file.write("writereg 20000024 00010581\n");
            cfg_file.write("writereg 20000028 00010581\n");
            cfg_file.write("writereg 20001004 ffffffff\n");
            cfg_file.write("writereg 20001008 ffffffff\n");
            cfg_file.write("writereg 20002004 ffffffff\n");
            cfg_file.write("writereg 20002008 ffffffff\n\n");

            break
#    cfg_file.write("dump_mem 12c6aa000 12c6ab000 > output_dmp.hex");
    cfg_file.close();

def create_pa_hex_file():
	addr_map = {};
	addr_map_log = os.popen('grep {} messages'.format("GBDUMP\ PHYS\ pa"));
	for line in addr_map_log.readlines():
		data = line.strip().split();
		vaddr = int(data[-1], 16);
		paddr = int(data[-2], 16);

		if ((vaddr in addr_map) and (addr_map[vaddr] != paddr)):
			pass
			# print ("warning: address map has exist but not same, update it:")
			# print ("old: %x -> %x, new is: %x -> %x" % (vaddr, addr_map[vaddr], vaddr, paddr));

		for var in range(vaddr, ((vaddr / 4096 + 1) * 4096), 4):
			index = var;
			value = paddr + (var - vaddr);
			addr_map[index] = value

	fileinlist = os.popen("ls input*.hex");
	for fileinname in fileinlist.readlines():
		filein = open(fileinname.strip(), "r");
		lines = filein.readlines();
		filein.close();

		fileout = open("pa_" + fileinname.strip(), "w");
		for line in lines:
			if line[0] == '#':
				fileout.write(line);
				continue;

			data = line.strip().split();
			# print data
			vaddr = int(data[0][:-1], 16);
			if (vaddr not in addr_map):
				# print "Error %lx not in trans map" % (vaddr)
				continue;
			fileout.write("%lx: %s %s %s %s # %lx\n" % (addr_map[vaddr], data[1], data[2], data[3], data[4], vaddr))
		fileout.close();

create_pa_hex_file();
create_config_file();
