#include "Authentication.h"


Wt::Auth::AuthService authService;
Wt::Auth::GoogleService *googleService = 0;
Authentication::Authentication(WContainerWidget *parent=0)
    : WContainerWidget(parent)
{
  
  std::cout<<"hi there"<<std::endl;
  {
    if (Wt::Auth::GoogleService::configured()) {
      googleService = new Wt::Auth::GoogleService(authService);
    }
    if (!googleService) {
      Wt::WText *k = new Wt::WText("This example requires a Google Auth service "
		    "configuration");
      addWidget(k);
      return;
    }

    process_ = googleService->createProcess
      (googleService->authenticationScope());
    Wt::WImage *ggi = new Wt::WImage("../resources/oauth-google.png");
    addWidget(ggi);  
    ggi->clicked().connect(process_,
			   &Wt::Auth::OAuthProcess::startAuthenticate);

    process_->authenticated().connect(this, &Authentication::authenticated);
  }

 


}

void Authentication::authenticated(const Wt::Auth::Identity& identity) {
    
    Wt::WText *g = new Wt::WText("Welcome, " + identity.name());
    addWidget(g);
    // WApplication::instance()->setInternalPath("/start", true);
  }

