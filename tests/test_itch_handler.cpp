//
// Created by Ivan Shynkarenka on 24.07.2017
//

#include "catch.hpp"

#include "trader/providers/nasdaq/itch_handler.h"

#include "filesystem/file.h"

using namespace CppCommon;
using namespace CppTrader::ITCH;

class MyHandler : public ITCHHandler
{
public:
    MyHandler() : _messages(0), _errors(0) {}

    size_t messages() const { return _messages; }
    size_t errors() const { return _errors; }

protected:
    bool HandleMessage(const SystemEventMessage& message) override { ++_messages; return true; }
    bool HandleMessage(const StockDirectoryMessage& message) override { ++_messages; return true; }
    bool HandleMessage(const StockTradingActionMessage& message) override { ++_messages; return true; }
    bool HandleMessage(const RegSHOMessage& message) override { ++_messages; return true; }
    bool HandleMessage(const MarketParticipantPositionMessage& message) override { ++_messages; return true; }
    bool HandleMessage(const MWCBDeclineMessage& message) override { ++_messages; return true; }
    bool HandleMessage(const MWCBStatusMessage& message) override { ++_messages; return true; }
    bool HandleMessage(const IPOQuotingMessage& message) override { ++_messages; return true; }
    bool HandleMessage(const AddOrderMessage& message) override { ++_messages; return true; }
    bool HandleMessage(const AddOrderMPIDMessage& message) override { ++_messages; return true; }
    bool HandleMessage(const OrderExecutedMessage& message) override { ++_messages; return true; }
    bool HandleMessage(const OrderExecutedWithPriceMessage& message) override { ++_messages; return true; }
    bool HandleMessage(const OrderCancelMessage& message) override { ++_messages; return true; }
    bool HandleMessage(const OrderDeleteMessage& message) override { ++_messages; return true; }
    bool HandleMessage(const OrderReplaceMessage& message) override { ++_messages; return true; }
    bool HandleMessage(const TradeMessage& message) override { ++_messages; return true; }
    bool HandleMessage(const CrossTradeMessage& message) override { ++_messages; return true; }
    bool HandleMessage(const BrokenTradeMessage& message) override { ++_messages; return true; }
    bool HandleMessage(const NOIIMessage& message) override { ++_messages; return true; }
    bool HandleMessage(const RPIIMessage& message) override { ++_messages; return true; }
    bool HandleMessage(const UnknownMessage& message) override { ++_errors; return true; }

private:
    size_t _messages;
    size_t _errors;
};

TEST_CASE("ITCHHandler", "[CppTrader][Providers][NASDAQ]")
{
    MyHandler handler;

    // Open the input file
    File input("../../tools/itch/sample.itch");
    if (!input.IsExists())
        input = File("../tools/itch/sample.itch");
    REQUIRE(input.IsExists());
    input.Open(true, false);

    // Perform input
    size_t size;
    uint8_t buffer[8192];
    while ((size = input.Read(buffer, sizeof(buffer))) > 0)
    {
        // Process the buffer
        handler.Process(buffer, size);
    }

    // Check results
    REQUIRE(handler.messages() == 1563071);
    REQUIRE(handler.errors() == 0);
}
