#include "App.h"
using namespace std;
#include<fstream>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <cstring>
#include <stdio.h>
#include <string>
#include <limits.h>
#include <unistd.h>
#include <Path.h>
#include <StorageKit.h>
#include <Entry.h>
#include <Message.h>

App::App(void)
	:	BApplication("application/x-vnd.dw-LauncherApp")
{
	
}

void
App::RefsReceived(BMessage* message)
{
	int32 index = 0;
	while (message->HasRef("refs", index)) {
		entry_ref ref;
		message->FindRef("refs", index++, &ref);
		BEntry entr;
		entr.SetTo(&ref);
		BPath path;
		entr.GetPath(&path);
/*		std::ofstream out("/boot/home/test.txt");
		out << path.Path();
		out.close();*/
		std::stringstream stream;
		stream << "/bin/python /boot/home/config/non-packaged/bin/HaiPO "<< path.Path()<<" &";
		system(stream.str().c_str());
		}
	be_app->PostMessage(B_QUIT_REQUESTED);
}

void
App::ArgvReceived(int32 argc, char** argv)
{
	BMessage message(B_REFS_RECEIVED);
	for (int32 i = 1; i < argc; i++) {
		entry_ref ref;
		BEntry entry(argv[i]);
		
		if (entry.Exists() && entry.GetRef(&ref) == B_OK)
			message.AddRef("refs", &ref);
			

			
	}

	RefsReceived(&message);
}
int
main(int,char **)
{

  App *app = new App();
  app->Run();

  return 0;
}

