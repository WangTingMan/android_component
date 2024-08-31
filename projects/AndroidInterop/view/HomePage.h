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

    std::shared_ptr<OptionContent> m_content;
};

