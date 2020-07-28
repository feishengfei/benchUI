#include "uimag.h"

UImag::UImag()
{
    Pg1_info = new info_Page;
    Pg2_cfg = new cfg_Page;
    Pg3_sel = new select_Page;
    Pg4_cfm = new conform_Page;
    Pg5_bld = new build_Page;
    Pg6_run = new run_Page;
}

void UImag::startShow()
{
    Pg1_info->show();
}

void UImag::endShow()
{
}
