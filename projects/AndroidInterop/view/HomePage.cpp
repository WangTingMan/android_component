#include "HomePage.h"

#include "Zhen/OptionContent.h"
#include "module/ipc_manager.h"
#include "module/module_manager.h"
#include "module/local_audio_service.h"

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
                   this ) );
    content->AddOption( "Request Presentation Delay",
        std::bind( &HomePage::RequestPresentationDelay,
                   this ) );

    content->AddOption("Show status",
        std::bind(&HomePage::ShowStatus,
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

void HomePage::RequestPresentationDelay()
{
    auto ipc = module_manager::get_instance()->
        get_module<ipc_manager>( ipc_manager::s_module_name );
    ipc->request_presentaion_delay();
}

void HomePage::ShowStatus()
{
    if (!m_status_page)
    {
        m_status_page = std::make_shared<BasePromptedPage>();
    }

    std::string status;

    auto audio_modules = module_manager::get_instance()->get_modules<local_audio_service>();
    status.append("Registered audio modules:\n");
    for (auto& module_ : audio_modules)
    {
        if (module_->get_init_status() == bluetooth_module::init_status::initialized)
        {
            if( module_->is_enabled())
            {
                status.append(module_->get_module_name());
                status.append("\n");
            }
        }
    }

    m_status_page->SetContentString(status);

    PageManager::GetInstance().PushPage(m_status_page);
}

