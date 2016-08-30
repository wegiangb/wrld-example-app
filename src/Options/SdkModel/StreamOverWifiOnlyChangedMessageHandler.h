// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "BidirectionalBus.h"
#include "ICallback.h"
#include "StreamOverWifiOnlyChangedMessage.h"
#include "NetIncludes.h"

namespace ExampleApp
{
    namespace Options
    {
        namespace SdkModel
        {
            class StreamOverWifiOnlyChangedMessageHandler : private Eegeo::NonCopyable
            {
                const std::shared_ptr<ExampleAppMessaging::TMessageBus> m_messageBus;
                Eegeo::Helpers::TCallback1<StreamOverWifiOnlyChangedMessageHandler, const StreamOverWifiOnlyChangedMessage&> m_messageHandlerBinding;
                const std::shared_ptr<Net::SdkModel::INetworkCapabilities> m_networkCapabilities;
                
                void OnPerformedStreamOverWifiOnlyChange(const StreamOverWifiOnlyChangedMessage& message);
                
            public:
                StreamOverWifiOnlyChangedMessageHandler(const std::shared_ptr<ExampleAppMessaging::TMessageBus>& messageBus,
                                                        const std::shared_ptr<Net::SdkModel::INetworkCapabilities>& networkCapabilities);
                
                ~StreamOverWifiOnlyChangedMessageHandler();
            };
        }
    }
}
