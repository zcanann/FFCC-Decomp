#ifndef _EXCEPTION
#define _EXCEPTION

#ifdef __cplusplus

namespace std {

class exception {
public:
	exception() { }
	virtual ~exception() { }
	virtual const char* what() const;
};

class bad_exception : public exception {
public:
	bad_exception() { }
	virtual ~bad_exception();
	virtual const char* what() const;
};

typedef void (*unexpected_handler)();
unexpected_handler set_unexpected(unexpected_handler handler);
void unexpected();

typedef void (*terminate_handler)();
terminate_handler set_terminate(terminate_handler handler);
void terminate();

} // namespace std

using std::exception;
using std::bad_exception;
using std::terminate;
using std::terminate_handler;
using std::set_terminate;
using std::unexpected;
using std::unexpected_handler;
using std::set_unexpected;

#endif // __cplusplus

#endif
