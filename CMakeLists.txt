cmake_minimum_required(VERSION 3.16)

project(Restaurant VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()

qt_add_executable(Restaurant
        main/main.cpp

        controller/classDefinition/MainController.cpp
        # controller/classDefinition/DBController.cpp
        controller/classDefinition/MotionlessElementController.cpp
        # controller/classDefinition/MoveController.cpp

        controller/classDeclaration/MainController.h
        # controller/classDeclaration/DBController.h
        controller/classDeclaration/MotionlessElementController.h
        # controller/classDeclaration/MoveController.h


        model/classDefinition/Butler.cpp
        model/graphicElement/classDefinition/QGraphicElement.cpp
        # model/classDefinition/CardModel.cpp
        # model/classDefinition/Chief.cpp
        # model/classDefinition/ClientGroupCreator.cpp
        # model/classDefinition/ClientModel.cpp
        # model/classDefinition/Cook.cpp
        # model/classDefinition/DinningRoom.cpp
        model/classDefinition/DirtyDishesStorage.cpp
        # model/classDefinition/DishwasherModel.cpp
        # model/classDefinition/HeadWaiter.cpp
        model/classDefinition/Human.cpp
        # model/classDefinition/KitchenAssistant.cpp
        # model/classDefinition/KitchenCounter.cpp
        # model/classDefinition/MaterialModel.cpp
        # model/classDefinition/Order.cpp
        model/classDefinition/Recipe.cpp
        # model/classDefinition/RestaurantDiver.cpp
        # model/classDefinition/RoomClerk.cpp
        # model/classDefinition/Server.cpp
        # model/classDefinition/StorageModel.cpp
        # model/classDefinition/Table.cpp
        # model/classDefinition/UstensilModel.cpp
        model/classDefinition/WashingMachine.cpp
        
        model/graphicElement/classDeclaration/QGraphicElement.h
        model/classDeclaration/Butler.h
        # model/classDeclaration/CardModel.h
        # model/classDeclaration/Chief.h
        # model/classDeclaration/ClientGroupCreator.h
        # model/classDeclaration/ClientModel.h
        # model/classDeclaration/Cook.h
        # model/classDeclaration/DinningRoom.h
        model/classDeclaration/DirtyDishesStorage.h
        # model/classDeclaration/DishwasherModel.h
        # model/classDeclaration/HeadWaiter.h
        model/classDeclaration/Human.h
        # model/classDeclaration/KitchenAssistant.h
        # model/classDeclaration/KitchenCounter.h
        # model/classDeclaration/MaterialModel.h
        # model/classDeclaration/Order.h
        model/classDeclaration/Recipe.h
        # model/classDeclaration/RestaurantDiver.h
        # model/classDeclaration/RoomClerk.h
        # model/classDeclaration/Server.h
        # model/classDeclaration/StorageModel.h
        # model/classDeclaration/Table.h
        # model/classDeclaration/UstensilModel.h
        model/classDeclaration/WashingMachine.h


        view/DisplayInterfacesClass.cpp
        view/DisplayInterfacesClass.h
        view/view.cpp
        view/view.h
        view/view.ui
        view/kitchen.cpp
        view/kitchen.h
        view/kitchen.ui
        view/dashboard.cpp
        view/dashboard.h
        view/dashboard.ui
)

target_link_libraries(Restaurant PRIVATE Qt6::Widgets)

set_target_properties(Restaurant PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)