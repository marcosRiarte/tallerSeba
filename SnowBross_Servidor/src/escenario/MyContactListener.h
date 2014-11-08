#ifndef MYCONTACTLISTENER_H_
#define MYCONTACTLISTENER_H_

#include <Box2D/Box2D.h>

class MyContactListener : public b2ContactListener  {
	public:
		MyContactListener(int newID);
		void BeginContact(b2Contact* contact);

		void EndContact(b2Contact* contact);

		int numFootContacts;
		int ID;
  };


#endif /* MYCONTACTLISTENER_H_ */
