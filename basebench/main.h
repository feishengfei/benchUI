#ifndef MAIN_H
#define MAIN_H

#include "info_page.h"
#include "cfg_page.h"
#include "conform_page.h"
#include "build_page.h"
#include "run_page.h"
#include <QApplication>
#include <QDebug>
#include <QString>

static info_Page *infoPage;
static cfg_Page *cfg;
static conform_Page *cfmPage;
static build_Page *buildPage;
static run_Page *runPage;

static QString libpath("");
static QString arch("x86_64");
static QString outformat("html");
static QString winsys("glfw");
static QString apiversion("All");
static QString module("All");

static bool en_gdb(false);
static bool en_dump(false);

#endif // MAIN_H
