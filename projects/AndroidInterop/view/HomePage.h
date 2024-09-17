#pragma once
#include "Zhen/BasePage.h"

class OptionContent;

class HomePage : public BasePage
{

public:

    HomePage();

    std::string GetPrintableString()const override;

    bool OnEvent( std::shared_ptr<Event> a_event ) override;

private:

    void StartStream();

    void StopStream();

    void SuspendStream();

    std::shared_ptr<OptionContent> m_content;
    std::size_t m_init_option_id;
    std::size_t m_start_stream_option_id;
};

