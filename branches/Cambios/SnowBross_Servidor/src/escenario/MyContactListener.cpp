#include "MyContactListener.h"

MyContactListener::MyContactListener(int newID) {
	numFootContacts = 0;
	ID=newID;
}

void MyContactListener::BeginContact(b2Contact* contact) {
          //check if fixture A was the foot sensor
          void* fixtureUserData = contact->GetFixtureA()->GetUserData();
          if ( (int)fixtureUserData == ID )
              numFootContacts++;
          //check if fixture B was the foot sensor
          fixtureUserData = contact->GetFixtureB()->GetUserData();
          if ( (int)fixtureUserData == ID )
              numFootContacts++;
}

void MyContactListener::EndContact(b2Contact* contact) {
          //check if fixture A was the foot sensor
          void* fixtureUserData = contact->GetFixtureA()->GetUserData();
          if ( (int)fixtureUserData == ID )
              numFootContacts--;
          //check if fixture B was the foot sensor
          fixtureUserData = contact->GetFixtureB()->GetUserData();
          if ( (int)fixtureUserData == ID )
        	  numFootContacts--;
}
