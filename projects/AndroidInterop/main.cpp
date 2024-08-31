#include <iostream>
#include <chrono>
#include <Zhen/KeyboardReader.h>

#include "view/HomePage.h"
#include "Zhen/logging.h"
#include <log/log.h>

bool zhen_logger(const char* /*FILE*/, int/*line*/,
    Zhen::LogLevel, std::string const&/*tag*/, std::string const&);

int main()
{
    Zhen::SetLogCallBack(std::bind(&zhen_logger,
        std::placeholders::_1, std::placeholders::_2,
        std::placeholders::_3, std::placeholders::_4, std::placeholders::_5));
    LogDebug() << "Start to run.";

    KeyboardReader reader;
    reader.start();

    std::shared_ptr<BasePage> page = std::make_shared<HomePage>();
    PageManager::GetInstance().PushPage( std::move( page ) );
    PageManager::GetInstance().SetDisplayAreaWidth( 120 );
    PageManager::GetInstance().run();
    reader.stop();
    return 0;
}

bool zhen_logger
    (
    const char* a_file,
    int a_line,
    Zhen::LogLevel a_level,
    std::string const& a_tag,
    std::string const& a_log
    )
{
    android_LogPriority pri = ANDROID_LOG_DEBUG;
    switch (a_level)
    {
    case Zhen::LogLevel::Debug:
        pri = ANDROID_LOG_DEBUG;
        break;
    case Zhen::LogLevel::Info:
        pri = ANDROID_LOG_INFO;
        break;
    case Zhen::LogLevel::Warning:
        pri = ANDROID_LOG_WARN;
        break;
    case Zhen::LogLevel::Error:
        pri = ANDROID_LOG_ERROR;
        break;
    case Zhen::LogLevel::Fatal:
        pri = ANDROID_LOG_FATAL;
        break;
    default:
        pri = ANDROID_LOG_DEBUG;
        break;
    }

    __android_log_print_ext(pri, a_tag.c_str(), a_file,
        a_line, a_log.c_str());
    return false;
}

