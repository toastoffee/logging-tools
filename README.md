# logging-tools
a c++11 implementation of logging system

### one-file

include the log.hpp file to use.

```c++
#include "log.hpp"
```

### custom-appender

the tools implements both sync and async appender base class which can be derived to change the log destination.

### appender-implementations

the tools implements four appenders that can be used directly.

```c++
// ostream appender
SyncOstreamAppender syncOstreamAppender(std::cout);
AsyncOstreamAppender asyncOstreamAppender(std::cout);

// file appender
SyncFileAppender syncFileAppender("./test1.log");
AsyncFileAppender asyncFileAppender("./test1.log");
```

### usage-guide

#### sync appender

```c++
// 1. instantiate a appender
SyncOstreamAppender syncTerminalAppender(std::cout);

// 2. instantiate a logger and bind the appender
Logger terminalLogger("mainLogger", syncTerminalAppender, LogLevel::Debug);

// 3. log (macro is recommanded)
terminalLogger.FATAL("this is a test log");
```

#### async appender

when it comes to async appender, you should join the thread after used.

```c++
// 1. instantiate a appender
AsyncOstreamAppender asyncTerminalAppender(std::cout);

// 2. instantiate a logger and bind the appender
Logger terminalLogger("mainLogger", asyncTerminalAppender, LogLevel::Debug);

// 3. log (macro is recommanded)
terminalLogger.FATAL("this is a test log");

// .....

// 4. join the thread before finish
asyncTerminalAppender.JoinThread();
```

#### 
