/*
(C) 2011 Lab for Spatial Informatics, IIIT-H,India
This program is free software under the GNU General Public
License (>=v2). Read the file COPYING for details.
@author Mohammed Rashad K.M <rashadkm {at} gmail {dot} com>
*/
#include "global.h"

/*
using namespace std;

void Tokenize(const string& str,vector<string>& tokens,  const string& delimiters)
{
 // Skip delimiters at beginning.
    string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    // Find first "non-delimiter".
    string::size_type pos     = str.find_first_of(delimiters, lastPos);

    while (string::npos != pos || string::npos != lastPos)
    {
        // Found a token, add it to the vector.


        tokens.push_back(str.substr(lastPos, pos - lastPos));
        // Skip delimiters.  Note the "not_of"
        lastPos = str.find_first_not_of(delimiters, pos);
        // Find next "non-delimiter"
        pos = str.find_first_of(delimiters, lastPos);
    }

}
void CloseConn(PGconn *conn)
{
    PQfinish(conn);

}

PGconn *ConnectDB(string db)
{
  PGconn *conn = NULL;

  // Make a connection to the database
string conn_string = "user=postgres password=postgres dbname=" + db + " hostaddr=127.0.0.1 port=5432";
  conn = PQconnectdb(conn_string.c_str());

  // Check to see that the backend connection was successfully made
    if (PQstatus(conn) != CONNECTION_OK)
    {
        printf("Connection to database failed\n");
        CloseConn(conn);
        return NULL;
    }

  //printf("Connection to database - OK\n");

  return conn;
}

*/
