#include <gtest/gtest.h>
#include "../model/classDeclaration/DashboardModel.h"

class DashboardModelTest : public ::testing::Test {
protected:
    DashboardModel model;

    void SetUp() override {
        // Initialize the model before each test
        model.initializeTables();
        model.initializeEquipments();
        model.initializeStaffs();
        model.initializeIngredients();
    }
};

// Test initializeTables method
TEST_F(DashboardModelTest, InitializeTables) {
    auto tables = model.getTable();
    ASSERT_EQ(tables.size(), 32); // Verify the number of tables

    for (int i = 0; i < tables.size(); ++i) {
        EXPECT_EQ(tables[i].tableNumber, "Table " + QString::number(i + 1));
        EXPECT_EQ(tables[i].status, "Available");
        EXPECT_EQ(tables[i].clientCount, 0);
    }
}

// Test initializeEquipments method
TEST_F(DashboardModelTest, InitializeEquipments) {
    auto equipments = model.getEquipments();
    ASSERT_EQ(equipments.size(), 16); // Verify the number of equipment types

    QStringList expectedNames = {
        "Cooking Burners", "Pots", "Pans", "Oven", "Wooden Spoons",
        "Blender", "Salad Bowls", "Pressure Cooker", "Juicer", "Sieve",
        "Funnels", "Kitchen Knives", "Work Fridge", "Dishwasher", "Washing Machine", "Sink"
    };

    QList<int> expectedTotals = {5, 10, 10, 1, 10, 1, 5, 2, 1, 1, 1, 5, 1, 1, 1, 1};

    for (int i = 0; i < equipments.size(); ++i) {
        EXPECT_EQ(equipments[i].name, expectedNames[i]);
        EXPECT_EQ(equipments[i].status, "Available");
        EXPECT_EQ(equipments[i].total, expectedTotals[i]);
        EXPECT_EQ(equipments[i].used, 0);
        EXPECT_EQ(equipments[i].unused, expectedTotals[i]);
    }
}

// Test initializeStaffs method
TEST_F(DashboardModelTest, InitializeStaffs) {
    auto staffs = model.getStaff();
    ASSERT_EQ(staffs.size(), 12); // Verify the number of staff members

    QStringList expectedNames = {"Head waiter", "Casseroles", "Waiter1", "Waiter2", 
                                  "Room Attendant1", "Room Attendant2", "Head Chef", 
                                  "Cook1", "Cook2", "Kitchen Assistant1", "Kitchen Assistant2", 
                                  "Dishwasher"};

    for (int i = 0; i < staffs.size(); ++i) {
        EXPECT_EQ(staffs[i].name, expectedNames[i]);
        EXPECT_EQ(staffs[i].status, "Not active");
    }
}

// Test initializeIngredients method
TEST_F(DashboardModelTest, InitializeIngredients) {
    auto ingredients = model.getIngredient();
    ASSERT_EQ(ingredients.size(), 6); // Verify the number of ingredients

    QStringList expectedNames = {"Tomatoes", "Onions", "Chili", "Salt", "Pepper", "Oil"};
    QList<int> expectedStockLevels = {100, 80, 50, 100, 70, 90};

    for (int i = 0; i < ingredients.size(); ++i) {
        EXPECT_EQ(ingredients[i].name, expectedNames[i]);
        EXPECT_EQ(ingredients[i].stockLevel, expectedStockLevels[i]);
    }
}

