#include <Wt/WApplication>
#include "Authentication.h"


Wt::Auth::AuthService authService;
Wt::Auth::GoogleService *googleService = 0;
Authentication::Authentication(WContainerWidget *parent=0)
    : WContainerWidget(parent)
{

  {
    // Wt::WServer server("auth.xml");
    if (Wt::Auth::GoogleService::configured()) {
      googleService = new Wt::Auth::GoogleService(authService);
    }
    if (!googleService) {
      Wt::WText *k = new Wt::WText("This example requires a Google Auth service configuration");
      addWidget(k);
      return;
    }

    process_ = googleService->createProcess
      (googleService->authenticationScope());
    addWidget(new WBreak());
    Wt::WText *WG = new Wt::WText("Welcome to WebGrass");
    WG->setStyleClass("wgrass-loginpage");
    addWidget(WG);
    addWidget(new WBreak());
    Wt::WText *L = new Wt::WText("Login with Google");
    L->setStyleClass("wgrass-loginpage");
    addWidget(L);
    addWidget(new WBreak());
    Wt::WImage *ggi = new Wt::WImage("../resources/oauth-google.png");
    ggi->setStyleClass("wgrass-login");
    addWidget(ggi);  
    ggi->clicked().connect(process_,
			   &Wt::Auth::OAuthProcess::startAuthenticate);

    process_->authenticated().connect(this, &Authentication::authenticated);


  }
}

void Authentication::authenticated(const Wt::Auth::Identity& identity) {
    
    Wt::WText *g = new Wt::WText("Welcome, " + identity.name());
    addWidget(g);
    Wt::WApplication::instance()->setInternalPath("/start", true);
  }

