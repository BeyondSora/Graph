#ifndef TEST_LOG_H
#define TEST_LOG_H

// Dependencies
#include <algorithm>
#include <sstream>
#include "test_Base.h"

#if defined(__GNUC__) || \
    defined(__MINGW32__) || \
    defined(__MINGW64__)
 #define FUNC __PRETTY_FUNCTION__
#else
 #define FUNC __func__
#endif

#define TEST_NAME __func__

#define __log_print TestLog().get()

#define __enter TestLog().get()            << "<--Enter-->         " << FUNC

#define __return(parm) do {\
                       TestLog().get()     << "<--Leave-->         " << FUNC;\
                       return (parm);\
                       } while (0)

#define __return_status(parm) do {\
                              outputTestStatus(parm, TEST_NAME);\
                              __return(parm);\
                              } while (0)

#define __checkpoint(parm) do {\
                           TestLog().get() << "<--CheckPoint-->    " << (parm);\
                           } while (0)

#define __print_graph(logic, graph) \
    do {\
        __log_print << "Graph " << graph;\
        __log_print << "=============";\
        IdentityList list = logic.verticesOf(graph);\
        std::for_each(list.begin(), list.end(),\
                [&] (Identity v) {\
                    std::stringstream buffer;\
                    buffer << v << " <--> ";\
                    IdentityList neighbours = logic.neighboursOf(v);\
                    std::for_each(neighbours.begin(), neighbours.end(),\
                        [&] (Identity n) {\
                            buffer << n << ", ";\
                        });\
                    __log_print << buffer.str();\
                });\
    } while (0)

class TestLog {
public:
    ~TestLog ();
    std::ostringstream& get ();
private:
    std::ostringstream os_;
};

void outputTestStatus (TestStatus status, const char *testName);

#endif//TEST_LOG_H
