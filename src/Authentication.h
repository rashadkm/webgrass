#include <Wt/WApplication>
#include <Wt/WContainerWidget>
#include <Wt/WImage>
#include <Wt/WServer>
#include <Wt/WText>
#include <Wt/WBreak>

#include <Wt/Auth/AuthService>
#include <Wt/Auth/GoogleService>
#include "wgrassconfig.h"

using namespace Wt;

class Authentication : public Wt::WContainerWidget{
public:
	Authentication(WContainerWidget *parent);
	void authenticated(const Wt::Auth::Identity& identity);

private:
  	Wt::Auth::OAuthProcess* process_;
};