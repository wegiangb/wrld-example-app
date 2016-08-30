// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "Interiors.h"
#include "WorldPins.h"
#include "IWorldPinsScaleController.h"
#include "Location.h"
#include "Rendering.h"
#include "Camera.h"
#include "VectorMath.h"
#include "Modality.h"
#include "BidirectionalBus.h"
#include "ICallback.h"
#include "SdkModelDomainEventBus.h"

namespace ExampleApp
{
    namespace WorldPins
    {
        namespace SdkModel
        {
            class WorldPinsScaleController : public IWorldPinsScaleController, private Eegeo::NonCopyable
            {
            private:
                const std::shared_ptr<IWorldPinsRepository> m_worldPinsRepository;
                const std::shared_ptr<IWorldPinsService> m_worldPinsService;
                float m_modality;
                float m_visibilityScale;
                float m_targetVisibilityScale;
                bool m_hideOutdoorPinsIndoors;
                const float m_visibilityAnimationDuration;
                
                const std::shared_ptr<const Eegeo::Resources::Interiors::InteriorInteractionModel> m_interiorInteractionModel;
                const std::shared_ptr<const Eegeo::Resources::Interiors::InteriorTransitionModel> m_interiorTransitionModel;

                const std::shared_ptr<ExampleAppMessaging::TMessageBus> m_messageBus;
                Eegeo::Helpers::TCallback1<WorldPinsScaleController, const WorldPinsVisibilityMessage&> m_visibilityMessageHandlerBinding;
                
                const std::shared_ptr<ExampleAppMessaging::TSdkModelDomainEventBus> m_sdkDomainEventBus;
                
                int m_visibilityMask;

            public:
                WorldPinsScaleController(const std::shared_ptr<IWorldPinsRepository>& worldPinsRepository,
                                         const std::shared_ptr<WorldPins::SdkModel::IWorldPinsService>& worldPinsService,
                                         const std::shared_ptr<ExampleAppMessaging::TMessageBus>& messageBus,
                                         const std::shared_ptr<Eegeo::Resources::Interiors::InteriorInteractionModel>& interiorInteractionModel,
                                         const std::shared_ptr<Eegeo::Resources::Interiors::InteriorTransitionModel>& interiorTransitionModel,
                                         const std::shared_ptr<ExampleAppMessaging::TSdkModelDomainEventBus>& sdkDomainEventBus);

                ~WorldPinsScaleController();

                void Update(float deltaSeconds, const Eegeo::Camera::RenderCamera& renderCamera);

                void SetModality(float modality);
                
                int GetVisibilityMask();
                
                void SetVisibilityMask(int visibilityMask);

                void SetHideOutdoorPinsIndoors(bool hideOutdoorPinsIndoors);
                
                void Show();
                void Hide();


            private:
                bool ShouldHidePin(WorldPins::SdkModel::WorldPinItemModel& worldPinItemModel,
                                   const Eegeo::Camera::RenderCamera& renderCamera);
                
                void UpdateWorldPin(WorldPins::SdkModel::WorldPinItemModel& worldPinItemModel,
                                    float deltaSeconds,
                                    const Eegeo::Camera::RenderCamera& renderCamera);

                void GetScreenLocation(const WorldPins::SdkModel::WorldPinItemModel& worldPinItemModel,
                                       Eegeo::v2& screenLocation,
                                       const Eegeo::Camera::RenderCamera& renderCamera) const;

                void OnWorldPinsVisibilityMessage(const WorldPinsVisibilityMessage& worldPinsVisibilityMessage);
            };
        }
    }
}
