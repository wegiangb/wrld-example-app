// Copyright eeGeo Ltd 2016, All Rights Reserved

#include "AppWiring.h"
#include "WorldModule.h"
#include "AppModule.h"
#include "LoadingScreenModule.h"
#include "NetworkModule.h"
#include "AppCameraModule.h"
#include "ToursModule.h"
#include "InteriorsExplorerModule.h"
#include "MyPinCreationModule.h"
#include "VisualMapModule.h"
#include "WorldAreaLoaderModule.h"
#include "IInitialExperienceModule.h"
#include "IWorldAreaLoaderModel.h"
#include "WorldPinsModule.h"
#include "InteriorsEntitiesPinsModule.h"
#include "PoiRingModule.h"
#include "WatermarkModule.h"
#include "ViewControllerUpdaterModule.h"
#include "ModalityModule.h"
#include "SettingsMenuModule.h"
#include "ReactionModelModule.h"
#include "WeatherMenuModule.h"
#include "SearchResultPoiModule.h"
#include "FlattenButtonModule.h"
#include "MapModeModule.h"
#include "CompassModule.h"
#include "NavigationService.h"
#include "InteriorsNavigationModule.h"
#include "IInitialExperienceController.h"
#include "AboutPageModule.h"
#include "OptionsModule.h"
#include "MyPinsModule.h"
#include "MyPinCreationDetailsModule.h"
#include "SearchModule.h"
#include "GeoNamesSearchServiceModule.h"
#include "EegeoSearchServiceModule.h"
#include "YelpSearchServiceModule.h"
#include "SearchMenuModule.h"
#include "SearchResultSectionModule.h"
#include "PlaceJumpsModule.h"
#include "TagSearchModule.h"
#include "WorldPinsPlatformServices.h"
#include "IWorldPinsService.h"
#include "IWorldPinsScaleController.h"
#include "IWorldPinsFloorHeightController.h"
#include "SearchResultOnMapModule.h"
#include "InteriorTransitionModel.h"
#include "InteriorSelectionModel.h"
#include "InteriorInteractionModel.h"
#include "InteriorMarkerModelRepository.h"
#include "IInteriorsEntitiesPinsController.h"
#include "GpsMarkerModule.h"
#include "IGpsMarkerController.h"
#include "MyPinDetailsModule.h"
#include "MobileExampleApp.h"
#include "ISearchRefreshService.h"

namespace ExampleApp
{
	namespace
	{
		void ResolveModuleSet(Hypodermic::Container& container, TModules& moduleSet)
		{
			for (const auto& module : moduleSet)
			{
				module->AssignContainer(&container);
				module->RegisterRenderableFilters();
				module->RegisterOpenablesAndReactors();
			}
			for (const auto& module: moduleSet)
			{
				const auto& filters = container.resolve<Eegeo::Rendering::RenderableFilters>();
				for (const auto& filter : module->GetRenderableFilters())
				{
					filters->AddRenderableFilter(*filter);
				}
				const auto& openables = container.resolve<OpenableControl::View::TOpenables>();
				for (const auto& openable : module->GetOpenables())
				{
					openables->AddItem(openable);
				}
				const auto& reactors = container.resolve<ScreenControl::View::TReactors>();
				for (const auto& reactor : module->GetReactors())
				{
					reactors->AddItem(reactor);
				}
			}
		}
	}

    AppWiring::AppWiring()
    : m_moduleContainerBuilder(std::make_shared<Hypodermic::ContainerBuilder>())
    , m_appContainerBuilder(std::make_shared<Hypodermic::ContainerBuilder>())
    , m_appContainer(nullptr)
    {
        m_moduleContainerBuilder->registerType<TModules>().singleInstance();
        m_moduleContainer = m_moduleContainerBuilder->build();
    }
    
    AppWiring::~AppWiring()
    {
        auto moduleSet = m_moduleContainer->resolve<TModules>();
        for (const auto& module : *moduleSet)
        {
            const auto& filters = m_appContainer->resolve<Eegeo::Rendering::RenderableFilters>();
            for (const auto& filter : module->GetRenderableFilters())
            {
                filters->RemoveRenderableFilter(*filter);
            }
        }
    }
    
    void AppWiring::RegisterModuleInstance(const std::shared_ptr<Module> module)
    {
        auto moduleSet = m_moduleContainer->resolve<TModules>();
        moduleSet->push_back(module);
    }

    void AppWiring::RegisterDefaultModules()
    {
        RegisterModule<WorldAreaLoader::SdkModel::WorldAreaLoaderModule>();
        RegisterModule<WorldModule>();
        RegisterModule<LoadingScreenModule>();
        RegisterModule<Net::SdkModel::NetworkModule>();
        RegisterModule<AppCamera::SdkModel::AppCameraModule>();
        RegisterModule<Tours::ToursModule>();
        RegisterModule<MyPinCreation::SdkModel::MyPinCreationModule>();
        RegisterModule<MyPinCreationDetails::View::MyPinCreationDetailsModule>();
        RegisterModule<MyPins::SdkModel::MyPinsModule>();
        RegisterModule<VisualMap::SdkModel::VisualMapModule>();
        RegisterModule<WorldPins::SdkModel::WorldPinsModule>();
        RegisterModule<InteriorsEntitiesPins::SdkModel::InteriorsEntitiesPinsModule>();
        RegisterModule<MyPinCreation::PoiRing::SdkModel::PoiRingModule>();
        RegisterModule<WeatherMenu::SdkModel::WeatherMenuModule>();
        RegisterModule<Watermark::SdkModel::WatermarkModule>();
        RegisterModule<ViewControllerUpdater::View::ViewControllerUpdaterModule>();
        RegisterModule<Modality::View::ModalityModule>();
        RegisterModule<SettingsMenu::SdkModel::SettingsMenuModule>();
        RegisterModule<Reaction::View::ReactionModelModule>();
        RegisterModule<SearchResultPoi::View::SearchResultPoiModule>();
        RegisterModule<FlattenButton::SdkModel::FlattenButtonModule>();
        RegisterModule<MapMode::SdkModel::MapModeModule>();
        RegisterModule<Compass::SdkModel::CompassModule>();
        RegisterModule<InteriorsNavigation::SdkModel::InteriorsNavigationModule>();
        RegisterModule<AboutPage::View::AboutPageModule>();
        RegisterModule<Options::OptionsModule>();
        RegisterModule<Search::SdkModel::SearchModule>();
        RegisterModule<Search::GeoNames::SdkModel::GeoNamesSearchServiceModule>();
        RegisterModule<Search::EegeoPois::SdkModel::EegeoSearchServiceModule>();
        RegisterModule<Search::Yelp::YelpSearchServiceModule>();
        RegisterModule<SearchMenu::SdkModel::SearchMenuModule>();
        RegisterModule<SearchResultSection::SdkModel::SearchResultSectionModule>();
        RegisterModule<PlaceJumps::SdkModel::PlaceJumpsModule>();
        RegisterModule<TagSearch::SdkModel::TagSearchModule>();
        RegisterModule<SearchResultOnMap::SdkModel::SearchResultOnMapModule>();
        RegisterModule<GpsMarker::SdkModel::GpsMarkerModule>();
        RegisterModule<MyPinDetails::SdkModel::MyPinDetailsModule>();
        RegisterModule<AppModule>();
        RegisterModule<InteriorsExplorer::SdkModel::InteriorsExplorerModule>();

        auto moduleSet = m_moduleContainer->resolve<TModules>();
        m_moduleRegistrationCallbacks.ExecuteCallbacks(*moduleSet);
    }

    void AppWiring::ApplyModuleRegistrations()
    {
    	Eegeo_ASSERT(m_appContainer == nullptr);
        auto moduleSet = m_moduleContainer->resolve<TModules>();
        for (const auto& module : *moduleSet)
        {
            module->Register(m_appContainerBuilder);
        }
    }

    void AppWiring::BuildContainer()
    {
    	if (m_appContainer == nullptr)
    	{
    		m_appContainer = m_appContainerBuilder->build();
    	}
    }

    void AppWiring::ResolveModules()
    {
    	BuildContainer();
    	ResolveModuleSet(*m_appContainer, *m_moduleContainer->resolve<TModules>());
    }
    
	void AppWiring::ResolveUiLeaves()
    {
        BuildContainer();
        auto moduleSet = m_moduleContainer->resolve<TModules>();
        for (const auto& module : *moduleSet)
		{
			module->AssignContainer(m_appContainer.get());
			module->RegisterUiLeaves();
			for (const auto& leaf : module->GetLeaves())
			{
				m_leaves.push_back(leaf);
			}
		}
	}

	void AppWiring::ResolveNativeLeaves()
	{
        BuildContainer();
        auto moduleSet = m_moduleContainer->resolve<TModules>();
        for (const auto& module : *moduleSet)
		{
			module->AssignContainer(m_appContainer.get());
			module->RegisterNativeLeaves();
			for (const auto& leaf : module->GetLeaves())
			{
				m_leaves.push_back(leaf);
			}
		}
	}


    const TContainer& AppWiring::GetContainer() const
    {
        return m_appContainer;
    }
    
    const std::shared_ptr<MobileExampleApp> AppWiring::BuildMobileExampleApp()
    {
        Eegeo_ASSERT(m_appContainer != nullptr, "Call ResolveModules before BuildMobileExampleApp");
        return m_appContainer->resolve<MobileExampleApp>();
    }
    
    void AppWiring::RegisterModuleCallback(Eegeo::Helpers::ICallback1<TModules&>& callback)
    {
        m_moduleRegistrationCallbacks.AddCallback(callback);
    }
    
    void AppWiring::UnregisterModuleCallback(Eegeo::Helpers::ICallback1<TModules&>& callback)
    {
        m_moduleRegistrationCallbacks.RemoveCallback(callback);
    }
}