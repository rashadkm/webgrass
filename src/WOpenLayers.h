/*
(C) 2011 Mohammed Rashad K.M <rashadkm {at} gmail {dot} com>
This program is free software under the GNU General Public
License (>=v2). Read the file COPYING for details.
*/
#ifndef WOPENLAYERS_H_
#define WOPENLAYERS_H_
#include <Wt/WCompositeWidget>
#include <Wt/WJavaScript>
#include <Wt/WSignal>
#include <vector>
#include <string>
using namespace std;
namespace Wt
{


class WOpenLayers : public WCompositeWidget
{
public:

  WOpenLayers(WContainerWidget *parent = 0);
  virtual ~WOpenLayers();
  JSignal<string> arguments_;
  JSignal<string>&getArgs(){return arguments_;}

protected:
  virtual void render(WFlags<RenderFlag> flags);

};

} //  

#endif // WOPENLAYERS_H_
