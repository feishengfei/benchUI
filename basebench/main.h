#ifndef MAIN_H
#define MAIN_H

#include "info_page.h"
#include "cfg_page.h"
#include "conform_page.h"
#include "build_page.h"
#include "run_page.h"
#include "select_page.h"
#include <QApplication>
#include <QDebug>
#include <QString>

namespace GB_CFG {
static QString libpath("");
static QString arch("x86_64");
static QString outformat("html");
static QString winsys("glfw");
//static QString apiversion("gl43");
//static QString module("coverage");

static bool en_gdb(false);
static bool en_dump(false);

//static QStringList runlist;
}


//typedef struct {
//    QString name;
//    Qt::CheckState state;
//} caseInfo;

struct cfg_info {
    QString libpath;
    QString arch;
    QString outformat;
    QString winsys;
    QString apiversion;
    QString module;

    bool en_gdb;
    bool en_dump;

    QStringList runlist;
};

static info_Page *infoPage;
static cfg_Page *cfg;
static conform_Page *cfmPage;
static build_Page *buildPage;
static run_Page *runPage;
static select_Page *selectPage;

#endif // MAIN_H
