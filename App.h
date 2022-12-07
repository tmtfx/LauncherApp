#ifndef APP_H
#define APP_H

#include <Application.h>

class App : public BApplication
{
public:
	App(void);
	virtual void			ArgvReceived(int32, char**);
	virtual void			RefsReceived(BMessage*);
};

#endif
