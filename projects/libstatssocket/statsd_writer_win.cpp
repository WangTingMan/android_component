
#include "statsd_writer.h"
#include <mutex>

__BEGIN_DECLS

static int statsdAvailable();
static int statsdOpen();
static void statsdClose();
static int statsdWrite(struct timespec* ts, struct iovec* vec, size_t nr);
static void statsdNoteDrop(int error, int tag);
static int statsdIsClosed();

struct android_log_transport_write statsdLoggerWrite = {
		.name = "statsd",
		.sock = 0,
		.available = statsdAvailable,
		.open = statsdOpen,
		.close = statsdClose,
		.write = statsdWrite,
		.noteDrop = statsdNoteDrop,
		.isClosed = statsdIsClosed,
};

static std::mutex s_mutex;

void statsd_writer_init_lock() { s_mutex.lock(); }

int statsd_writer_init_trylock()
{
	return s_mutex.try_lock() ? 1 : 0;
}

void statsd_writer_init_unlock()
{
	s_mutex.unlock();
}

static int statsdAvailable()
{ 
	return 0;
}

int statsdOpen()
{
	return 0;
}

void statsdClose()
{

}

int statsdWrite(struct timespec* ts, struct iovec* vec, size_t nr)
{
	return 0;
}

void statsdNoteDrop(int error, int tag)
{

}

int statsdIsClosed()
{
	return 0;
}

__END_DECLS
