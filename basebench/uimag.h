#ifndef UIMAG_H
#define UIMAG_H

#include "info_page.h"
#include "cfg_page.h"
#include "select_page.h"
#include "conform_page.h"
#include "build_page.h"
#include "run_page.h"

class UImag
{
public:
    UImag();
    void startShow();
    void endShow();

    info_Page *Pg1_info;
    cfg_Page *Pg2_cfg;
    select_Page *Pg3_sel;
    conform_Page *Pg4_cfm;
    build_Page *Pg5_bld;
    run_Page *Pg6_run;
};

#endif // UIMAG_H
