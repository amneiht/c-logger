#include "logger.h"
#include "loggerconf.h"
int main(int argc, char **argv) {
	
	long maxsize = 5 * 1024 * 1024;
	logger_initFileLogger("/tmp/pika.log", maxsize, 2);
	logger_setdecorate(0);
	printf("start log\n");
	for (int i = 0; i < 1000; i = 1) {
		LOG_INFO("pika lmap");
		LOG_INFO("pika lmap");
		LOG_INFO("pika lmap");
		LOG_INFO("pika lmap");
		LOG_INFO("pika lmap");
		logger_flush();
		usleep(5 * 1000);
	}

	logger_exitFileLogger();
	

	return 0;
}
