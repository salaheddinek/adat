#pragma once

#include "Logger.h"

namespace plog
{
    template<int instanceId>
    inline Logger<instanceId>& init(Severity maxSeverity = none, IAppender* appender = NULL)
    {
        static Logger<instanceId> logger(maxSeverity);
        return appender ? logger.addAppender(appender) : logger;
    }

    inline Logger<PLOG_DEFAULT_INSTANCE_ID>& init(Severity maxSeverity = none, IAppender* appender = NULL)
    {
        return init<PLOG_DEFAULT_INSTANCE_ID>(maxSeverity, appender);
    }
}

#ifdef EXTEND_THIRDPARTY_HPP
#include "ColorConsoleAppender.h"
#include "RollingFileAppender.h"

#include "MessageOnlyFormatter.h"
#include "FuncMessageFormatter.h"
#include "CsvFormatter.h"
#include "TxtFormatter.h"


namespace plog
{

class SeverityMessageFormatter
{
public:
    static util::nstring header()
    {
        return util::nstring();
    }

    static util::nstring format(const Record& record)
    {
        util::nostringstream ss;
        ss << PLOG_NSTR("[") << severityToString(record.getSeverity()) << PLOG_NSTR("] ") << record.getMessage() << PLOG_NSTR("\n");

        return ss.str();
    }
};
namespace Init {
enum Formatter{
    allInfo, messageOnly, functionMessage, severityMessage
};


inline bool console_logger(const plog::Severity console_log_severity = Severity::info,
                           const plog::Init::Formatter console_formatter = Formatter::severityMessage)
{
    if(plog::get())
        return false;


    switch (console_formatter) {
    case allInfo:{
        static plog::ColorConsoleAppender<plog::TxtFormatter> consoleAppender;
        plog::init<0>(console_log_severity, &consoleAppender);
        return true;
    }
    case messageOnly:{
        static plog::ColorConsoleAppender<plog::MessageOnlyFormatter> consoleAppender;
        plog::init<0>(console_log_severity, &consoleAppender);
        return true;
    }
    case functionMessage:{
        static plog::ColorConsoleAppender<plog::FuncMessageFormatter> consoleAppender;
        plog::init<0>(console_log_severity, &consoleAppender);
        return true;
    }
    case severityMessage:{
        static plog::ColorConsoleAppender<plog::SeverityMessageFormatter> consoleAppender;
        plog::init<0>(console_log_severity, &consoleAppender);
        return true;
    }
    }
    return false;
}

inline bool console_and_file_logger(const std::string log_file_path,
                                    const plog::Severity console_log_severity = Severity::info,
                                    const plog::Init::Formatter console_formatter = Formatter::severityMessage,
                                    const plog::Severity file_log_severity = Severity::debug){

    //check if logging system is already initiated
    if(plog::get())
        return false;


    switch (console_formatter) {
    case allInfo:{
        static plog::ColorConsoleAppender<plog::TxtFormatter> consoleAppender;
        plog::init<1>(console_log_severity, &consoleAppender);
        break;
    }
    case messageOnly:{
        static plog::ColorConsoleAppender<plog::MessageOnlyFormatter> consoleAppender;
        plog::init<1>(console_log_severity, &consoleAppender);
        break;
    }
    case functionMessage:{
        static plog::ColorConsoleAppender<plog::FuncMessageFormatter> consoleAppender;
        plog::init<1>(console_log_severity, &consoleAppender);
        break;
    }
    case severityMessage:{
        static plog::ColorConsoleAppender<plog::SeverityMessageFormatter> consoleAppender;
        plog::init<1>(console_log_severity, &consoleAppender);
        break;

    }
    }

    const std::string ext = ".csv";
    const size_t max_file_size = 100000;
    const int max_num_files = 10;
    if(log_file_path.compare (log_file_path.length() - ext.length(), ext.length(), ext) == 0){
        static plog::RollingFileAppender<plog::CsvFormatter>
                fileAppender(log_file_path.c_str(), max_file_size, max_num_files);

        plog::init<0>(file_log_severity, &fileAppender).addAppender(plog::get<1>());
        return true;
    }
    static plog::RollingFileAppender<plog::TxtFormatter>
            fileAppender(log_file_path.c_str(), max_file_size, max_num_files);

    plog::init<0>(file_log_severity, &fileAppender).addAppender(plog::get<1>());


    return true;
}

inline void console_logger_if_not_done_yet(
        const plog::Severity console_log_severity = Severity::info,
        const plog::Init::Formatter console_formatter = Formatter::severityMessage)
{
    console_logger(console_log_severity, console_formatter);
}

}  // namespace Init
}  // namespace plog
#endif




