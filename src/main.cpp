#include <iostream>
#include <iomanip>
#include <ctime>

#define IMG_ROOT_DIR "/boot/"
#define IMG_FORMAT   "jpg"

std::string getImageFileName() {
	auto t = std::time(nullptr);
	auto tm = *std::localtime(&t);

	std::stringstream ss;
	ss << std::put_time(&tm, "%d-%m-%Y_%H-%M-%S");
	return ss.str();
}

int exec(const char* cmd) {
	auto pipe = popen(cmd, "r");

	if (!pipe) {
		return -1;
	};

	return pclose(pipe);
}

int main() {
	std::stringstream ss;
	ss << "fswebcam -d /dev/video0 " << IMG_ROOT_DIR << getImageFileName() << "." << IMG_FORMAT;
	exec(ss.str().c_str());
	exec("sync");
	return 0;
}
