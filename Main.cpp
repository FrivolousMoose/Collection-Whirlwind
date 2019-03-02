#include "CollectionWhirlwindApp.h"

int main() {

	auto app = new CollectionWhirlwindApp();
	app->run("AIE", 960, 720, false);
	delete app;

	return 0;
}