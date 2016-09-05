// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultSectionModule.h"

#include "MenuModel.h"
#include "MenuOptionsModel.h"
#include "SearchResultSection.h"
#include "SearchResultSectionOrder.h"
#include "SearchResultRepositoryObserver.h"
#include "SearchResultSectionItemSelectedMessageHandler.h"
#include "SearchResultViewClearedObserver.h"
#include "SearchResultSectionController.h"
#include "ISearchResultPoiViewModel.h"

namespace ExampleApp
{
    namespace SearchResultSection
    {
        namespace SdkModel
        {
            void SearchResultSectionModule::Register(const std::shared_ptr<Hypodermic::ContainerBuilder>& builder)
            {
                builder->registerType<View::SearchResultSectionMenuModel>().singleInstance();
                builder->registerType<View::SearchResultSectionOptionsModel>().singleInstance();
                builder->registerType<View::SearchResultRepositoryObserver>().singleInstance();
                builder->registerType<SearchResultSectionItemSelectedMessageHandler>().singleInstance();
                builder->registerType<SearchResultViewClearedObserver>().singleInstance();
                builder->registerType<View::SearchResultSectionOrder>().as<View::ISearchResultSectionOrder>().singleInstance();
                builder->registerType<View::SearchResultSectionController>().singleInstance();
            }
            
            void SearchResultSectionModule::RegisterLeaves()
            {
                RegisterLeaf<View::SearchResultRepositoryObserver>();
                RegisterLeaf<SearchResultSectionItemSelectedMessageHandler>();
                RegisterLeaf<SearchResultViewClearedObserver>();
                RegisterLeaf<View::SearchResultSectionController>();
            }
            
            /*SearchResultSectionModule::SearchResultSectionModule(Menu::View::IMenuViewModel& searchMenuViewModel,
                                                                 Search::SdkModel::ISearchResultRepository& searchResultRepository,
                                                                 Search::SdkModel::ISearchQueryPerformer& searchQueryPerformer,
                                                                 CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController,
                                                                 const Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                                                 const Eegeo::Resources::Interiors::Markers::InteriorMarkerModelRepository& interiorMarkerRepository,
                                                                 AppCamera::SdkModel::IAppCameraController& appCameraController,
                                                                 ExampleAppMessaging::TMessageBus& messageBus)
            {
                m_pModel = Eegeo_NEW(Menu::View::MenuModel)();

                m_pMenuOptionsModel = Eegeo_NEW(Menu::View::MenuOptionsModel)(*m_pModel);
                
                m_pSearchResultRepositoryObserver = Eegeo_NEW(View::SearchResultRepositoryObserver)(searchResultRepository,
                                                                                                    messageBus);

                m_pSearchResultSectionItemSelectedMessageHandler = Eegeo_NEW(SearchResultSectionItemSelectedMessageHandler)(cameraTransitionController,
                                                                                                                      messageBus);
                
                m_pSearchResultViewClearedObserver = Eegeo_NEW(SearchResultViewClearedObserver)(searchQueryPerformer, messageBus);
                
                m_pSearchResultSectionOrder = Eegeo_NEW(View::SearchResultSectionOrder)();
            }

            SearchResultSectionModule::~SearchResultSectionModule()
            {
                Eegeo_DELETE m_pSearchResultSectionOrder;
                Eegeo_DELETE m_pSearchResultViewClearedObserver;
                Eegeo_DELETE m_pSearchResultSectionItemSelectedMessageHandler;
                Eegeo_DELETE m_pSearchResultRepositoryObserver;
                Eegeo_DELETE m_pMenuOptionsModel;
                Eegeo_DELETE m_pModel;
            }

            Menu::View::IMenuOptionsModel& SearchResultSectionModule::GetSearchResultSectionOptionsModel() const
            {
                return *m_pMenuOptionsModel;
            }

            Menu::View::IMenuModel& SearchResultSectionModule::GetSearchResultSectionModel() const
            {
                return *m_pModel;
            }
            
            View::ISearchResultSectionOrder& SearchResultSectionModule::GetSearchResultSectionOrder() const
            {
                return *m_pSearchResultSectionOrder;
            }*/
        }
    }
}
