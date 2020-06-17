#ifndef TST_TESTIROVANIE_H
#define TST_TESTIROVANIE_H

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <IKeypad.h>
#include <ILatch.h>
#include <lockcontroller.h>

using namespace testing;


struct mock_keypad : IKeypad
{
    MOCK_METHOD
    (
        bool,
        isActive,
        (),
        (override)
    );

    MOCK_METHOD
    (
        void,
        wait,
        (),
        (override)
    );

    MOCK_METHOD
    (
        PasswordResponse,
        requestPassword,
        (),
        (override)
    );

};

struct mock_latch : ILatch
{
    MOCK_METHOD
    (
        bool,
        isActive,
        (),
        (override)
    );

    MOCK_METHOD
    (
        DoorStatus,
        open,
        (),
        (override)
    );

    MOCK_METHOD
    (
        DoorStatus,
        close,
        (),
        (override)
    );

    MOCK_METHOD
    (
        DoorStatus,
        getDoorStatus,
        (),
        (override)
    );

};

TEST(Tests, test_1)
{
    // Arrange
    const short desired_number_of_calls = 1;
    mock_keypad keypad;
    mock_latch latch;
    LockController controller(&keypad, &latch);

    // Prepare mocks

    // Проверяем, что метод wait() класса IKeypad будет вызван один раз
    EXPECT_CALL(keypad, wait())
        .Times(desired_number_of_calls)
        .WillOnce(Return());

    // Act
    controller.wait();
}

TEST(Tests, test_2)
{
    // Arrange
    const short desired_number_of_calls = 1;
    mock_keypad keypad;
    mock_latch latch;
    LockController controller(&keypad, &latch);

    // Prepare mocks
        EXPECT_CALL(latch, getDoorStatus())
        // Проверяем, что метод getDoorStatus() класса ILatch будет вызван один раз
        .Times(desired_number_of_calls)
        .WillOnce(Return(DoorStatus::CLOSE));

    // Act
    bool is_open = controller.isDoorOpen();

    // Assert    
    //Метод isDoorOpen() класса LockController вернёт false
    ASSERT_FALSE(is_open);
}

TEST(Tests, test_3)
{
    // Arrange
    const short desired_number_of_calls = 1;
    mock_keypad keypad;
    mock_latch latch;
    LockController controller(&keypad, &latch);

    // Prepare mocks
    EXPECT_CALL(latch, getDoorStatus())
        // Проверяем, что метод getDoorStatus() класса ILatch будет вызван один раз;
        .Times(desired_number_of_calls)
        .WillOnce(Return(DoorStatus::OPEN));

    // Act
    bool is_open = controller.isDoorOpen();

    // Assert    
    //Метод isDoorOpen() класса LockController вернёт true
    ASSERT_TRUE(is_open);
}

TEST(Tests, test_4)
{
    // Arrange
    const short desired_number_of_calls = 1;
    mock_keypad keypad;
    mock_latch latch;
    LockController controller(&keypad, &latch);

    // Prepare mocks
    EXPECT_CALL(latch, open())
        // Метод open() класса ILatch будет вызван один раз
        .Times(desired_number_of_calls)
        .WillOnce(Return(DoorStatus::OPEN));

    // Act
    DoorStatus door_status = controller.unlockDoor();

    // Assert
    //Метод unlockDoor() класса LockController вернёт DoorStatus::OPEN
    ASSERT_EQ(DoorStatus::OPEN, door_status);
}

TEST(Tests, test_5)
{
    // Arrange
    const short desired_number_of_calls = 1;
    mock_keypad keypad;
    mock_latch latch;
    LockController controller(&keypad, &latch);

    // Prepare mocks
    EXPECT_CALL(latch, close())
        // Метод open() класса ILatch будет вызван один раз
        .Times(desired_number_of_calls)
        .WillOnce(Return(DoorStatus::CLOSE));

    // Act
    DoorStatus door_status = controller.unlockDoor();

    // Assert
    //Метод unlockDoor() класса LockController вернёт DoorStatus::OPEN
    ASSERT_EQ(DoorStatus::CLOSE, door_status);
}

TEST(Tests, test_6)
{
    // Arrange
    const short desired_number_of_calls = 1;
    mock_keypad keypad;
    mock_latch latch;
    LockController controller(&keypad, &latch);

    // Prepare mocks
    EXPECT_CALL(keypad, isActive())
        //  Метод isActive() класса IKeypad будет вызван один раз
        .Times(desired_number_of_calls)
        .WillOnce(Return(true));

    EXPECT_CALL(latch, isActive())
        //  Метод isActive() класса ILatch будет вызван один раз;
        .Times(desired_number_of_calls)
        .WillOnce(Return(true));

    // Act
    HardWareStatus hard_ware_status = controller.hardWareCheck();

    // Assert
    //Метод hardWareCheck() класса LockController вернёт HardWareStatus::OK
    ASSERT_EQ(HardWareStatus::OK, hard_ware_status);
}

TEST(Tests, test_7)
{
    // Arrange
    mock_keypad keypad;
    mock_latch latch;
    LockController controller(nullptr, &latch);

    // Prepare mocks
    EXPECT_CALL(keypad, isActive())
        //  Метод isActive() класса IKeypad будет вызван ноль или более раз
        .Times(AtLeast(0))
        .WillOnce(Return(true));

    EXPECT_CALL(latch, isActive())
        //  Метод isActive() класса ILatch будет вызван ноль или более раз
        .Times(AtLeast(0))
        .WillOnce(Return(true));

    // Act
    HardWareStatus hard_ware_status = controller.hardWareCheck();

    // Assert
    //Метод hardWareCheck() класса LockController вернёт HardWareStatus::ERROR
    ASSERT_EQ(HardWareStatus::ERROR, hard_ware_status);

}

TEST(Tests, test_8)
{
    // Arrange
    mock_keypad keypad;
    mock_latch latch;
    LockController controller(&keypad, &latch);

    // Prepare mocks
    EXPECT_CALL(keypad, isActive())
        //  Метод isActive() класса IKeypad будет вызван ноль или более раз
        .Times(AtLeast(0))
        .WillOnce(Return(true));

    EXPECT_CALL(latch, isActive())
        //  Метод isActive() класса ILatch будет вызван ноль или более раз
        .Times(AtLeast(0))
        .WillOnce(Return(false));

    // Act
    HardWareStatus hard_ware_status = controller.hardWareCheck();

    // Assert
    //Метод hardWareCheck() класса LockController вернёт HardWareStatus::ERROR
    ASSERT_EQ(HardWareStatus::ERROR, hard_ware_status);
}

TEST(Tests, test_9)
{
    // Arrange
    const short desired_number_of_calls = 1;
    mock_keypad keypad;
    mock_latch latch;
    LockController controller(&keypad, &latch);

    PasswordResponse user_input;
    user_input.status = PasswordResponse::Status::OK;
    //Пользователь вводит правильный пароль (0000)
    user_input.password = "0000";

    // Prepare mocks
    EXPECT_CALL(keypad, requestPassword())
            //Метод requestPassword() класса IKeypad будет вызван один раз
            .Times(desired_number_of_calls)
            .WillOnce(Return(user_input));

    // Act
    bool correct_password = controller.isCorrectPassword();

    // Assert
    //Метод isCorrectPassword() класса LockController вернёт true
    ASSERT_TRUE(correct_password);
}

TEST(Tests, test_10)
{
    // Arrange
    const short desired_number_of_calls = 1;
    mock_keypad keypad;
    mock_latch latch;
    LockController controller(&keypad, &latch);

    PasswordResponse user_input;
    user_input.status = PasswordResponse::Status::OK;
    // Пользователь вводит не правильный пароль (0001)
    user_input.password = "0001";


    // Prepare mocks
    EXPECT_CALL(keypad, requestPassword())
            // Метод requestPassword() класса IKeypad будет вызван один раз;
            .Times(desired_number_of_calls)
            .WillOnce(Return(user_input));

    // Act
    bool correct_password = controller.isCorrectPassword();

    // Assert
    // Метод isCorrectPassword() класса LockController вернёт false;
    ASSERT_FALSE(correct_password);
}

TEST(Tests, test_11)
{
    // Arrange
    mock_keypad keypad;
    mock_latch latch;
    LockController controller(&keypad, &latch);

    PasswordResponse user_input_1;
    user_input_1.status = PasswordResponse::Status::OK;
    //Пользователь вводит правильный старый пароль (0000)
    user_input_1.password = "0000";

    PasswordResponse user_input_2;
    user_input_2.status = PasswordResponse::Status::OK;
    // Пользователь вводит новый пароль (9999)
    user_input_2.password = "9999";


    // Prepare mocks
    EXPECT_CALL(keypad, requestPassword())
            .Times(3)                            // Проверяем, что у пользователя спросят пороль нужное количество раз
            .WillOnce(Return(user_input_1))     // Пользователь вводит правильный старый пароль (0000)
            .WillOnce(Return(user_input_2))    // Пользователь вводит новый пароль (9999)
            .WillOnce(Return(user_input_2));  // Ввод для проверки нового пороля (9999)

    // Act
    controller.resetPassword();
    // Проверка нового пороля
    bool correct_password = controller.isCorrectPassword();

    // Assert
    // Не на прямую(так как нет возможности) проверяем правильность нового пороля
    ASSERT_TRUE(correct_password);
}

TEST(Tests, test_12)
{
    // Arrange
    mock_keypad keypad;
    mock_latch latch;
    LockController controller(&keypad, &latch);

    PasswordResponse user_input_1;
    user_input_1.status = PasswordResponse::Status::OK;
     //Пользователь правильно вводит старый пароль (0000)
    user_input_1.password = "0000";

    PasswordResponse user_input_2;
    user_input_2.status = PasswordResponse::Status::OK;
    // Пользователь вводит новый пароль из условия (9876)
    user_input_2.password = "9876";

    // Prepare mocks
    EXPECT_CALL(keypad, requestPassword())
            .Times(4)                          // Проверяем, что у пользователя запросят ввод пороля нужное количество раз
            .WillOnce(Return(user_input_1))
            .WillOnce(Return(user_input_2))    // Изменяем пароль на 9876
            .WillOnce(Return(user_input_1))
            .WillOnce(Return(user_input_2));   // Повторно изменяем пороль

    // Act
    controller.resetPassword();
    user_input_1.password = user_input_2.password;
    user_input_2.password = "1111";
    controller.resetPassword();

    // Проверяем на правильность новый пароль
    bool correct_password = controller.isCorrectPassword();

    // Assert
    ASSERT_TRUE(correct_password);
}

#endif // TST_TESTIROVANIE_H
