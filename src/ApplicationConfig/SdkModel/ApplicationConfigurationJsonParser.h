// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ApplicationConfig.h"
#include "IApplicationConfigurationParser.h"
#include "Types.h"

namespace ExampleApp
{
    namespace ApplicationConfig
    {
        namespace SdkModel
        {
            class ApplicationConfigurationJsonParser : public IApplicationConfigurationParser, private Eegeo::NonCopyable
            {
            public:
                ApplicationConfigurationJsonParser(const std::shared_ptr<ApplicationConfiguration>& defaultConfig);

                ApplicationConfiguration ParseConfiguration(const std::string& serialized);
            private:
                const std::shared_ptr<const ApplicationConfiguration> m_defaultConfig;
            };
        }
    }
}
