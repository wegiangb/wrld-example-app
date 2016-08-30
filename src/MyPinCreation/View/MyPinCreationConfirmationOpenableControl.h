// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "OpenableControlViewModelBase.h"
#include "Reaction.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace View
        {
            class MyPinCreationConfirmationOpenableControl : public OpenableControl::View::OpenableControlViewModelBase, private Eegeo::NonCopyable
            {
                Eegeo::Helpers::TIdentity m_identity;

            public:
                MyPinCreationConfirmationOpenableControl(Eegeo::Helpers::TIdentity identity, const std::shared_ptr<Reaction::View::IReactionControllerModel>& reactionControllerModel);

                Eegeo::Helpers::TIdentity GetIdentity() const;
            };
        }
    }
}
