/*
(C) 2011 Lab for Spatial Informatics, IIIT-H,India
This program is free software under the GNU General Public
License (>=v2). Read the file COPYING for details.
@author Mohammed Rashad K.M <rashadkm {at} gmail {dot} com>
*/
#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include <Wt/WComboBox>
#include <Wt/WContainerWidget>
#include <Wt/WString>
#include <Wt/WApplication>

#include "boost/random.hpp"
#include "boost/generator_iterator.hpp"  
#include "ogrsf_frmts.h"
#include "postgresql/libpq-fe.h"

using namespace std;


void Tokenize(const string& str,vector<string>& tokens,  const string& delimiters=",");



void CloseConn(PGconn *conn);

PGconn *ConnectDB(string);

#endif
