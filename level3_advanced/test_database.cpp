#include <gtest/gtest.h>
#include "mock_database.h"

// TODO STUDENTE 1: Crea la Test Fixture "DatabaseTest".
class DatabaseTest : public testing::Test {
protected:
    MockDatabase db;

    void SetUp() override {
        db.Connect();
        db.InsertUser("admin", 1, "superuser");
        db.InsertUser("guest", 2, "readonly");
    }

    void TearDown() override {
        db.ClearAll();
        db.Disconnect();
    }
};


// ESEMPIO PROFESSORE (utilizza la fixture che devi creare sopra):
TEST_F(DatabaseTest, RetrievesExistingAdmin) {
    UserRecord* admin = db.GetUser("admin");
    ASSERT_NE(admin, nullptr) << "L'admin dovrebbe essere inserito nel SetUp";
    EXPECT_EQ(admin->id, 1);
    EXPECT_EQ(admin->role, "superuser");
}

// TODO STUDENTE 2: Usando TEST_F, scrivi un test che verifichi l'utente "guest".
TEST_F(DatabaseTest, RetrievesExistingGuest) {
    UserRecord* guest = db.GetUser("guest");
    ASSERT_NE(guest, nullptr) << "Il guest dovrebbe essere inserito nel SetUp";
    EXPECT_EQ(guest->id, 2);
    EXPECT_EQ(guest->role, "readonly");
}

// TODO STUDENTE 3: Usando TEST_F, scrivi un test che prova a recuperare un utente 
// non esistente (es. "hacker") e verifica che il risultato sia nullptr.
TEST_F(DatabaseTest, UnknownUserReturnsNull) {
    UserRecord* unknown = db.GetUser("hacker");
    EXPECT_EQ(unknown, nullptr);
}

// TODO STUDENTE 4: Usando TEST_F, disconnetti esplicitamente il DB all'interno 
// del test (chiamando Disconnect()) e verifica che chiamare GetUser("admin") 
// restituisca nullptr (il DB non deve rispondere se non e' connesso).
TEST_F(DatabaseTest, GetUserFailsWhenDisconnected) {
    db.Disconnect();
    UserRecord* admin = db.GetUser("admin");
    EXPECT_EQ(admin, nullptr) << "Il DB non dovrebbe restituire utenti se disconnesso";
}