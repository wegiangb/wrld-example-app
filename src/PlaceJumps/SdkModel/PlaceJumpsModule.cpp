// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include <vector>
#include <string>
#include <fstream>
#include "PlaceJumpsModule.h"
#include "PlaceJumpsDataParser.h"
#include "PlaceJumpsModel.h"
#include "MenuModel.h"
#include "MenuOptionsModel.h"
#include "PlaceJumpMenuOption.h"
#include "PlaceJumpController.h"
#include "PlaceJumpSelectedMessageHandler.h"
#include "ICameraTransitionController.h"

namespace ExampleApp
{
    namespace PlaceJumps
    {
        namespace SdkModel
        {
            class PlaceJumpMenuModel : public Menu::View::MenuModel
            {
            };
            
            class PlaceJumpMenuOptionsModel : public Menu::View::MenuOptionsModel
            {
            public:
                PlaceJumpMenuOptionsModel(const std::shared_ptr<PlaceJumpMenuModel>& placeJumpModel) : Menu::View::MenuOptionsModel(*placeJumpModel)
                {
                }
            };
            
            void PlaceJumpsModule::Register(const std::shared_ptr<Hypodermic::ContainerBuilder>& builder)
            {
                builder->registerType<PlaceJumpController>().as<IPlaceJumpController>().singleInstance();
                builder->registerType<PlaceJumpMenuModel>().singleInstance();
                builder->registerType<PlaceJumpMenuOptionsModel>().singleInstance();
                builder->registerType<PlaceJumpSelectedMessageHandler>().singleInstance();
            }
            
            /*
            PlaceJumpsModule::PlaceJumpsModule(Eegeo::Helpers::IFileIO& fileIO,
                                               CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController,
                                               Menu::View::IMenuViewModel& menuViewModel,
                                               ExampleAppMessaging::TMessageBus& messageBus,
                                               Metrics::IMetricsService& metricsService,
                                               const Menu::View::IMenuReactionModel& menuReaction)
            {
                //m_pJumpController = Eegeo_NEW(PlaceJumpController)(cameraTransitionController);

                //m_pMenuModel = Eegeo_NEW(Menu::View::MenuModel)();
                //m_pMenuOptionsModel = Eegeo_NEW(Menu::View::MenuOptionsModel)(*m_pMenuModel);

                std::fstream stream;
                size_t size;

                if(!fileIO.OpenFile(stream, size, "placejumps.json"))
                {
                    Eegeo_ASSERT(false, "Failed to load placejumps.json definitions file.");
                }

                std::string json((std::istreambuf_iterator<char>(stream)),
                                 (std::istreambuf_iterator<char>()));

                std::vector<View::PlaceJumpModel> placeJumps;
                if(!View::PlaceJumpsDataParser::ParsePlaceJumps(json, placeJumps))
                {
                    Eegeo_ASSERT(false, "Failed to parse placejumps.json definitions file.");
                }

                // Populate menu with jump tions.
                for(std::vector<View::PlaceJumpModel>::iterator it = placeJumps.begin(); it != placeJumps.end(); it++)
                {
                    View::PlaceJumpModel& jump = *it;
                    m_pMenuOptionsModel->AddItem(jump.GetName(),
                                                 jump.GetName(), "", jump.GetIcon(),
                                                 Eegeo_NEW(View::PlaceJumpMenuOption)(jump, menuViewModel, messageBus, metricsService, menuReaction));
                }

                m_pPlaceJumpSelectedMessageHandler = Eegeo_NEW(PlaceJumpSelectedMessageHandler)(*m_pJumpController, messageBus);
            }*/
        }
    }
}
