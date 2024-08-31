#include "HomePage.h"

#include "Zhen/OptionContent.h"
#include "module/BluetoothAudioPortClient.h"
#include "module/module_manager.h"

HomePage::HomePage()
{
    SetPageName( "HomePage" );
    SetTitle( "Home Page" );

    std::shared_ptr<OptionContent> content = std::make_shared<OptionContent>();
    content->AddOption("Init", std::bind(&module_manager::init,
        module_manager::get_instance()));
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

