#include "HomePage.h"

#include "Zhen/OptionContent.h"
#include "module/ipc_manager.h"
#include "module/module_manager.h"

HomePage::HomePage()
{
    SetPageName( "HomePage" );
    SetTitle( "Home Page" );

    std::shared_ptr<OptionContent> content = std::make_shared<OptionContent>();
    m_init_option_id = content->AddOption("Init", std::bind(&module_manager::init,
        module_manager::get_instance()));
    m_start_stream_option_id = content->AddOption("Request Start Stream",
        std::bind(&HomePage::StartStream,
        this));
    content->AddOption("Request Stop Stream",
        std::bind(&HomePage::StopStream,
            this));
    content->AddOption("Request Suspend Stream",
        std::bind(&HomePage::SuspendStream,
            this));

    m_content = content;
}

std::string HomePage::GetPrintableString()const
{
    std::string ret = BasePage::GetPrintableString();
    ret.append( m_content->GetPrintableString() );
    return ret;
}

bool HomePage::OnEvent( std::shared_ptr<Event> a_event )
{
    bool r = m_content->OnEvent( a_event );
    if( !r )
    {
        r = BasePage::OnEvent( a_event );
    }
    return r;
}

void HomePage::StartStream()
{
    auto ipc = module_manager::get_instance()->
        get_module<ipc_manager>(ipc_manager::s_module_name);
    ipc->start_stream();
}

void HomePage::StopStream()
{
    auto ipc = module_manager::get_instance()->
        get_module<ipc_manager>(ipc_manager::s_module_name);
    ipc->stop_stream();
}

void HomePage::SuspendStream()
{
    auto ipc = module_manager::get_instance()->
        get_module<ipc_manager>(ipc_manager::s_module_name);
    ipc->suspend_stream();
}

